#include "libraries.h"
#include "expression.h"
#include "arbore.h"
#include "deriv.h"

int main()
{
	unsigned int success;
	string expresie;
	getline(cin, expresie);

	tokenStream infix;
	tokenize(infix, expresie, success);

	if (!success) return success;

	tokenStream postfix;
	postfixize(infix, postfix);

	ExpTree tree = NULL;
	tree = constructTree(tree, postfix);
	
	ExpTree derivTree = new TreeNode;

	deriveaza(tree, derivTree);
	tree = derivTree;
	simplifica(tree);
	afiseaza(tree);
	
	return 0;
}