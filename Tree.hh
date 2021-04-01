#ifndef TREE_HEADER
#define TREE_HEADER

#include "Window.hh"

#include <vector>

class Tree;
class TreeNode
{
public:
	TreeNode& add(const std::string& name);

	void setName(const std::string& name);

	//	Depending on state, hides/expands a node. Returns true if success
	bool setExpanded(bool state);

private:
	friend class Tree;
	std::string name;

	//	Should the children be hidden after expansion?
	bool hideChildren = false;

	//	Are children visible?
	bool isExpanded = true;

	std::vector <TreeNode*> children;

	TreeNode* parent;
	Tree* tree;
};

class Tree : public Window
{
public:
	Tree(const Vector2& start, const Vector2& end) : Window(start, end)
	{
		root.tree = this;
	}

	void onKeyPress(int key) override;
	void draw() override;

	TreeNode root;

private:
	friend class TreeNode;

	void drawNode(TreeNode* node, unsigned& y, std::vector <bool>& connectionsBehind);
	TreeNode* selectedNode = &root;

	size_t selected = 0;
	size_t visibleNodes = 0;
};

#endif
