#include "../../Container.hh"
#include "../../Logger.hh"
#include "../../Menu.hh"
#include "../../Tree.hh"

#include <fstream>
#include <vector>
#include <string>
#include <array>

class Program
{
public:
	Program(const std::string& path, Logger& output, Logger& debug, Tree& structure)
		: output(output), debug(debug)
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

		root.node = &structure.root;
		parseBlock(source, &root, 0, source.length());
	}

private:
	struct Block
	{
		struct Instruction
		{
			union
			{
				Block* inner;
				char op;

			} value;

			bool isOperation;
		};

		std::vector <Instruction> instructions;

		size_t index = 0;
		Block* active = nullptr;
		TreeNode* node = nullptr;
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
			debug.addMessage(LogLevel::Debug, "At ", i, " = ", src[i]);
			//	Loop start
			if(src[i] == '[')
			{
				//	Create a new block
				b->instructions.push_back({});
				b->instructions.back().isOperation = false;
				b->instructions.back().value.inner = new Block;
				b->instructions.back().value.inner->node = &b->node->add("block");

				unsigned depth = 1;

				size_t blockEnd;
				size_t blockStart = i + 1;

				debug.addMessage(LogLevel::Debug, "Start at ", i);

				//	Find the outermost matching brace
				for(i++; depth > 0 && i < src.length(); i++)
				{
					switch(src[i])
					{
						case '[': depth++; break;
						case ']': depth--; break;
					}

					debug.addMessage(LogLevel::Debug, "Depth is ", depth, " at ", src[i], " ", i);
				}

				//	Is the block unterminated?
				if(depth > 0)
				{
					debug.addMessage(LogLevel::Error, "Unterminated block at ", blockStart);
					return;
				}

				i--;
				debug.addMessage(LogLevel::Debug, "After search i = ", i);

				//	Set the end inside the braces
				blockEnd = i;

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
				debug.addMessage(LogLevel::Debug, "Adding instruction ", src[i]);
				b->instructions.push_back({});
				b->instructions.back().isOperation = true;
				b->instructions.back().value.op = src[i];
				b->node->add(std::string("INS: ") + src[i]);
			}
		}
	}

	std::vector <int> memory;
	size_t index = 0;

	Block root;

	Logger& output;
	Logger& debug;
};

int main()
{
	Container root(true);

	Menu& options = root.create <Menu> (Vector2(50, 10), Vector2(90, 50));
	Tree& structure = root.create <Tree> (Vector2(50, 50), Vector2(90, 90));
	Logger& debug = root.create <Logger> (Vector2(10, 10), Vector2(50, 50), true);
	Logger& output = root.create <Logger> (Vector2(10, 50), Vector2(50, 90), true);

	Program prog("test.bf", output, debug, structure);

	while(true)
	{
		root.update();
	}

	return 0;
}
