#include "RedBlackTree.h"
using namespace std;

int main()
{
	
	RedBlackTree <int> test;
	test.insert(7);
	test.insert(3);
	test.insert(18);
	test.insert(10);
	test.insert(22);
	test.insert(8);
	test.insert(11);
	test.insert(26);

	RedBlackTree<int> test2;
	test2=test;


	RedBlackTree<int> test3=test2;


	test3.remove(10);


	system("pause");
	return 0;
}