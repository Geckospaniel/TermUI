#include "Tree.hh"

TreeNode& TreeNode::add(const std::string& name)
{
	TreeNode* child = new TreeNode;
	child->setName(name);
	child->tree = tree;

	children.push_back(child);
	return *child;
}

void TreeNode::setName(const std::string& name)
{
	this->name = name;
	//tree->setRedraw();
}

void TreeNode::setExpanded(bool state)
{
	isExpanded = state;
	//tree->setRedraw();
}

void Tree::onKeyPress(int key)
{
}

void Tree::draw()
{
	if(!needsRedraw)
		return;

	std::vector <bool> conn;
	unsigned y = 0;

	drawNode(&root, y, conn);
}

void Tree::drawNode(TreeNode* node, unsigned& y, std::vector <bool>& connectionsBehind)
{
	for(size_t i = 0; i < node->children.size(); i++)
	{
		TreeNode* child = node->children[i];

		std::string indentStr;
		std::string nameStr;

		//	Make the color more dim if it's unexpanded
		Color::Name fg = child->isExpanded ? Color::White : Color::Gray;

		//	Prevent the root node from drawing connections
		if(!connectionsBehind.empty())
		{
			/*	Since connectionsBehind stores the vertical connection
			 *	state for each depth, we can easily add a vertical
			 *	when a parent node wants there to be a connection
			 *	to another node that's later than this one */
			for(size_t c = 0; c < connectionsBehind.size(); c++)
				indentStr += connectionsBehind[c] ? "| " : "  ";

			//	Nice visuals
			indentStr += "|";
			nameStr += "__ ";
		}

		nameStr += child->name;

		//	Display the indent and connections
		setColor(Color::White, Color::Black);
		drawTextLine(indentStr, 0, y, true);

		//	Only make the actual node name more dim
		setColor(fg, Color::Black);
		drawTextLine(nameStr, indentStr.length(), y++, false);

		//	Should the node contents be displayed?
		if(!child->children.empty() && child->isExpanded)
		{
			//	If there's more nodes after this one, display the connection
			bool addConnection = i + 1 < node->children.size();

			//	Tell the child node that it should draw a connection
			connectionsBehind.push_back(addConnection);

			//	Draw the child node and remove the connection from memory
			drawNode(child, y, connectionsBehind);
			connectionsBehind.pop_back();
		}
	}
}
