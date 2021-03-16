#include "../../Container.hh"
#include "../../Tree.hh"

int main()
{
	Container root(true);
	Tree& tree = root.create <Tree> (Vector2(10, 10), Vector2(90, 90));

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
