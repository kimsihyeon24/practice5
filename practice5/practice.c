#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct Treenode* left, * right;
} TreeNode;

TreeNode* Sserch(TreeNode* node, int key)
{
	while (node != NULL) {
		if (key == node -> key) return node;
		else if (key < node->key)
			node = node -> left;
		else {
			node = node -> right;
		}
		return NULL;
	}
}

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key)
{
	if (node == NULL) return new_node(key);

	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);

	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		TreeNode* temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}


	return root;
}

void inorder(TreeNode* root)
{
	if (root) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}


int main(void) {
	TreeNode* root = NULL;
	TreeNode* temp = NULL;

	root = insert_node(root, 25);
	root = insert_node(root, 16);
	root = insert_node(root, 41);
	root = insert_node(root, 42);
	root = insert_node(root, 46);
	root = insert_node(root, 53);
	root = insert_node(root, 55);
	root = insert_node(root, 62);
	root = insert_node(root, 63);
	root = insert_node(root, 64);
	root = insert_node(root, 65);
	root = insert_node(root, 70);
	root = insert_node(root, 74);
	root = insert_node(root, 60);


	printf("-------------\n|s     : 검색          \n|i     : 노드추가          \n|d     : 노드삭제          \n|t     : 중위 순회          \n|I     : 노드 추가(반복)\n|D     :노드 삭제(반복) \n|c     : 종료");

	
	printf("\n");
	inorder(root);
}


