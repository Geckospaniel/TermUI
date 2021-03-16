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
	void setExpanded(bool state);

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
		root.tree = this;
	}

	void onKeyPress(int key) override;
	void draw() override;

	inline void setRedraw() { needsRedraw = true; }
	TreeNode root;

private:
	void drawNode(TreeNode* node, unsigned& y, std::vector <bool>& connectionsBehind);
	TreeNode* selected = nullptr;
};

#endif
