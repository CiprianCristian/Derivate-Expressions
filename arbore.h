#pragma once

#ifndef LIBRARIES_H
#include "libraries.h"
#endif

#include "symbols.h"

struct TreeNode
{
	string info;
	string coef;
    TreeNode* left, * right;

	TreeNode()
	{
		this->left = NULL;
		this->right= NULL;
	}

    TreeNode* operator=(const TreeNode* t)
    {
		TreeNode* treeNode = new TreeNode;
        treeNode->info = t->info;
        treeNode->left = t->left;
        treeNode->right = t->right;
        return treeNode;
    }
};
typedef TreeNode* ExpTree;
ExpTree createNode(string info)
{
	TreeNode* temp = new TreeNode();
	if (temp == NULL)
	{
		cout << "Out of space!\n";
		return (temp);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->info = info;

	if (info.length() > 3)
		temp->coef = info.substr(3, info.length() - 3);
	else temp->coef = "2";
	return temp;
};
ExpTree constructTree(ExpTree tree, vector<string> postfix)
{
	stack<TreeNode*> st;
	TreeNode* temp_tree1;
	TreeNode* temp_tree2;
	for (auto token : postfix)
	{
		if (isBinaryOperator(token))
		{
			tree = createNode(token);
			temp_tree1 = st.top(); st.pop();
			tree->right = temp_tree1;
			if (st.empty())
			{
				temp_tree2 = createNode("0");
				tree->left = temp_tree2;
			}
			else
			{
				temp_tree2 = st.top(); st.pop();
				tree->left = temp_tree2;
			}
			st.push(tree);
		}
		else if (isUnaryOperator(token))
		{
			tree = createNode(token);
			temp_tree1 = st.top(); st.pop();
			tree->right = temp_tree1;
			st.push(tree);
		}
		else
		{
			tree = createNode(token);
			st.push(tree);
		}
	}
	return tree;
}
void showNode(ExpTree T)
{
	cout << T->info << " ";
}
void showTree(ExpTree T)
{
	ExpTree q[1000];
	int n = 0, m = 0;
	q[++n] = T;
	while (n)
	{
		ExpTree p[1000];
		m = 0;
		for (int i = 1; i <= n; i++)
		{
			showNode(q[i]);
			if (q[i]->left) p[++m] = q[i]->left;
			if (q[i]->right) p[++m] = q[i]->right;
		}
		cout << "\n";
		n = m;
		for (int i = 1; i <= n; i++)
			q[i] = p[i];
	}
}
void inorder(ExpTree T)
{
	if (T != NULL)
	{
		inorder(T->left);
		showNode(T);
		inorder(T->right);
	}
}
