#include "../../Container.hh"
#include "../../Logger.hh"
#include "../../Menu.hh"

#include <fstream>
#include <vector>
#include <string>
#include <array>

class Program
{
public:
	Program(const std::string& path, Logger& output, Logger& debug, Menu& cells)
		: output(output), debug(debug), cells(cells)
	{
		debug.addMessage(LogLevel::Debug, "Loading program ", path);

		std::ifstream file(path);

		//	Does the file exist?
		if(!file.is_open())
		{
			debug.addMessage(LogLevel::Error, "Unable to open file ", path);
			return;
		}

		std::string source;
		std::string line;

		//	Read the file
		while(std::getline(file, line))
		{
			//	Valid characters
			static std::string instructions = "+-<>.,[]";

			//	Eliminate all invalid characters
			for(auto c : line)
			{
				if(instructions.find(c) != std::string::npos)
					source += c;
			}
		}

		debug.addMessage(LogLevel::Debug, "Parsing source ", source);

		parseBlock(source, &root, 0, source.length());

		std::function <void(size_t, Block*)> printAll;
		printAll = [&printAll, &debug](size_t indent, Block* b) -> void
		{
			debug.addMessage(LogLevel::Normal, "Block has ", b->instructions.size(), " instructions");
			for(auto& ins : b->instructions)
			{
				if(!ins.isOperation)
				{
					printAll(indent + 2, ins.value.inner);
					continue;
				}

				std::string ind(indent, ' ');
				debug.addMessage(LogLevel::Normal, ind, ins.value.op);
			}
		};

		printAll(0, &root);
	}

private:
	struct Block
	{
		struct Instruction
		{
			union
			{
				Block* inner;
				unsigned char op;

			} value;

			bool isOperation;
		};

		std::vector <Instruction> instructions;

		size_t index = 0;
		Block* active = nullptr;
	};

	struct Cell
	{
		int value;
		MenuEntry& visual;
	};

	void parseBlock(const std::string& src, Block* b, size_t start, size_t end)
	{
		debug.addMessage(LogLevel::Debug, "Parsing block ", start, " - ", end);

		for(size_t i = start; i < end; i++)
		{
			//	Loop start
			if(src[i] == '[')
			{
				//	Create a new block
				b->instructions.push_back({});
				b->instructions.back().isOperation = false;
				b->instructions.back().value.inner = new Block;

				unsigned depth = 1;

				size_t blockEnd;
				size_t blockStart = ++i;

				debug.addMessage(LogLevel::Debug, "Start at ", i);

				//	Find the outermost matching brace
				for(; depth > 0 && i < src.length(); i++)
				{
					switch(src[i])
					{
						case '[': depth++; break;
						case ']': depth--; break;
					}
				}

				//	Is the block unterminated?
				if(depth > 0)
				{
					debug.addMessage(LogLevel::Error, "Unterminated block at ", blockStart);
					return;
				}

				//	Set the end inside the braces
				blockEnd = i - 1;

				//	Parse the inner block if it isn't empty
				if(blockStart <= blockEnd)
					parseBlock(src, b->instructions.back().value.inner, blockStart, blockEnd);
			}

			//	If the closing brace appears here, it's an error
			else if(src[i] == ']')
			{
				debug.addMessage(LogLevel::Error, "Unnecessary closing brace at ", i);
				return;
			}

			else
			{
				b->instructions.push_back({});
				b->instructions.back().isOperation = true;
				b->instructions.back().value.op = src[i];
			}
		}
	}

	std::vector <int> memory;
	size_t index = 0;

	Block root;

	Logger& output;
	Logger& debug;
	Menu& cells;
};

int main()
{
	Container root(true);

	Menu& options = root.create <Menu> (Vector2(50, 10), Vector2(90, 50));
	Menu& cells = root.create <Menu> (Vector2(50, 50), Vector2(90, 90));
	Logger& debug = root.create <Logger> (Vector2(10, 10), Vector2(50, 50), true);
	Logger& output = root.create <Logger> (Vector2(10, 50), Vector2(50, 90), true);

	Program prog("test.bf", output, debug, cells);

	while(true)
	{
		root.update();
	}

	return 0;
}
