#include <iostream>
#include "stdafx.h"
#include <cstdlib>

using namespace std;

struct Node
{
	int data;
	Node *left;
	Node *right;
};
Node* AddNode(int data);
bool Search(Node* root, int data);
Node* Insert(Node* root, int data);
void Inorder(Node* root);
void Merge(Node *&First_tree_root, Node *&Second_tree_root);

int main()
{
	Node* First_tree_root = 0;
	Node* Second_tree_root = 0;

	cout << "Enter integers to fill the binary tree (Enter any letter from A to Z to stop entering integers): \n";
	int first_tree_number;
	while (cin >> first_tree_number)
		First_tree_root = Insert(First_tree_root, first_tree_number);

	//очищение потока
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');

	cout << "Enter integers to fill the binary tree (Enter any letter from A to Z to stop entering integers): \n";
	int Second_tree_number;
	while (cin >> Second_tree_number)
		Second_tree_root = Insert(Second_tree_root, Second_tree_number);

	if (First_tree_root != 0 && Second_tree_root != 0)
	{
		cout << "First tree: ";
		Inorder(First_tree_root);
		cout << endl;

		cout << "Second tree: ";
		Inorder(Second_tree_root);
		cout << endl;

		Merge(First_tree_root, Second_tree_root);
		cout << "Total tree: ";
		Inorder(Second_tree_root);
		cout << endl;
	}
	else
	{
		cout << "One of the trees is not filled!" << endl;
	}

	system("pause");
	return 0;
}

Node* AddNode(int data)
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = 0;
	newNode->right = 0;

	return newNode;
}

bool Search(Node* root, int data)
{
	if (root == 0)
	{
		return false;
	}
	else if (root->data == data)
	{
		return true;
	}
	else if (data <= root->data)
	{
		return Search(root->left, data);
	}
	else
	{
		return Search(root->right, data);
	}

}

Node* Insert(Node* root, int data)
{
	if (Search(root, data) == false)
	{
		if (root == 0)
		{
			root = AddNode(data);
		}
		else if (data <= root->data)
		{
			root->left = Insert(root->left, data);
		}
		else
		{
			root->right = Insert(root->right, data);
		}
	}
	return root;
}

void Inorder(Node* root)
{
	if (root == 0)
	{
		return;
	}
	Inorder(root->left);
	cout << root->data << " ";
	Inorder(root->right);
}

void Merge(Node *&First_tree_root, Node *&Second_tree_root)
{
	if (First_tree_root->left != 0)
	{
		Merge(First_tree_root->left, Second_tree_root);
	}
	if (First_tree_root->right != 0)
	{
		Merge(First_tree_root->right, Second_tree_root);
	}
	if (Search(Second_tree_root, First_tree_root->data) == false)
	{
		Insert(Second_tree_root, First_tree_root->data);
	}
	delete First_tree_root;
	First_tree_root = 0;

}
