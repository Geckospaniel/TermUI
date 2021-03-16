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

private:
	friend class Tree;
	std::string name;

	bool isExpanded = true;
	std::vector <TreeNode*> children;

	//	Handle for the tree to indicate redraws
	Tree* tree;
};

class Tree : public Window
{
public:
	Tree(const Vector2& start, const Vector2& end) : Window(start, end)
	{
	}

	void onKeyPress(int key) override;
	void draw() override;

	TreeNode root;

private:
	void drawNode(TreeNode* node, unsigned& y,
				  std::vector <bool>& connectionsBehind);

	TreeNode* selected = nullptr;
};

#endif
