#ifndef TREE_HEADER
#define TREE_HEADER

#include "Window.hh"

struct TreeNode
{
	bool isExpanded;
};

class Tree : public Window
{
public:
	Tree(const Vector2& start, const Vector2& end) : Window(start, end)
	{
	}

private:
};

#endif
