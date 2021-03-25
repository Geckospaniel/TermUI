#include "../../Container.hh"
#include "../../Tree.hh"
#include "../../Menu.hh"
#include "../../DebugHelper.hh"

int main()
{
	Container root(false);
	root.setTitle("root");
	Tree& tree = root.create <Tree> (Vector2(10, 10), Vector2(50, 50));
	tree.setTitle("tree");
	DebugHelper::logger = &root.create <Logger> (Vector2(50, 10), Vector2(90, 90), true);
	DebugHelper::logger->setTitle("debugLogger");
	Menu& m = root.create <Menu> (Vector2(10, 50), Vector2(50, 90));
	m.setTitle("menu");

	TreeNode& a = tree.root.add("a");
	TreeNode& a1 = a.add("1");
	TreeNode& a2 = a1.add("2");

	TreeNode& a2_1 = a2.add("2_1");
	TreeNode& a2_2 = a2.add("2_2");
	TreeNode& a2_2_1 = a2_2.add("2_2_1");

	TreeNode& a1_1 = a1.add("1_1");
	TreeNode& a1_2 = a1.add("1_2");

	TreeNode b = tree.root.add("b");

	while(true)
	{
		root.update();
	}

	return 0;
}
