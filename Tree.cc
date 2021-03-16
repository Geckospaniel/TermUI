#include "Tree.hh"

#include <functional>

TreeNode& TreeNode::add(const std::string& name)
{
	TreeNode* child = new TreeNode;

	child->parent = this;
	child->tree = tree;
	tree->expandedNodes++;

	child->setName(name);
	children.push_back(child);

	return *child;
}

void TreeNode::setName(const std::string& name)
{
	this->name = name;
	tree->setRedraw();
}

void TreeNode::setExpanded(bool state)
{
	//	Make sure that expandedNodes doesn't get too high
	if(!isExpanded && state)
		tree->expandedNodes++;

	//	Make sure that expandedNodes doesn't get too low
	else if(isExpanded && !state)
		tree->expandedNodes--;

	isExpanded = state;
	tree->setRedraw();
}

void Tree::onKeyPress(int key)
{
	std::function <TreeNode*(TreeNode*, size_t&)> findNode;
	findNode = [this, &findNode](TreeNode* origin, size_t& pos) -> TreeNode*
	{
		TreeNode* current = origin;

		//	Does the selection reach further?
		if(pos >= selected)
			return current;

		//	Are there child nodes which can be set active?
		if(current->isExpanded && !current->children.empty())
		{
			for(auto& child : current->children)
			{
				pos++;
				TreeNode* result = findNode(child, pos);

				if(result != nullptr)
					return result;
			}
		}

		return nullptr;
	};

	size_t pos = 0;

	switch(key)
	{
		case KEY_DOWN:
			//	Set the cursor at the beginning if it overflows
			if(++selected > expandedNodes)
				selected = 1;

			//	Update the selected node
			selectedNode = findNode(&root, pos);
		break;

		case KEY_UP:
			//	Set the cursor at the end if it overflows
			if(--selected <= 0)
				selected = expandedNodes;

			//	Update the selected node
			selectedNode = findNode(&root, pos);
		break;

		case 10: case KEY_RIGHT:
			Window::clear();
			selectedNode->setExpanded(!selectedNode->isExpanded);
		break;
	}

	needsRedraw = true;
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
		Color::Name bg = Color::Black;

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

		//	If this node is selected, highlight it
		if(child == selectedNode)
			fg = Color::LightWhite;

		//	Only make the actual node name more dim
		setColor(fg, bg);
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
