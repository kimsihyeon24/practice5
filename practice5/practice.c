#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS
int count = 0;
typedef struct TreeNode {
	int key;
	int data;
	
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* Ssearch(TreeNode* node, int key)//�ݺ� Ž��
{
	printf("�˻� ���� : %d\n", key);
	while (node != NULL) {
		count++;
		if (key == node->data)
			return node;

		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
	printf("�湮�� ����� �� : %d", count);
}

TreeNode* new_node(int item)// ��� �߰�
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert(TreeNode* root, int key) {
	TreeNode* ptr;     // Ž���� ������ ������ 
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));    // newNode ����
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	if (root == NULL) {    // Ʈ���� ��� ���� ��� 
		root = newNode;
		return root;
	}

	ptr = root;    // root ������ Ž�� ����  

	while (ptr) {
		if (key == ptr->key) {    // �ߺ��� 
			printf("Error : �ߺ����� ������ �ʽ��ϴ�!\n");
			return root;
		}
		else if (key < ptr->key) {    // ���� ����Ʈ�� 
			if (ptr->left == NULL) {    // ����ִٸ� �߰� 
				ptr->left = newNode;
				return root;
			}
			else {    // ������� �ʴٸ� �ٽ� Ž�� ���� 
				ptr = ptr->left;
			}
		}
		else {    // key > ptr->key ������ ����Ʈ�� 
			if (ptr->right == NULL) {    // ����ִٸ� �߰� 
				ptr->right = newNode;
				return root;
			}
			else {    // ������� �ʴٸ� �ٽ� Ž�� ���� 
				ptr = ptr->right;
			}
		}
	}

}

TreeNode* min_value_node(TreeNode* node)//�ǿ��� �ܸ���� ã�� ������
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, int key)//��� ����
{
	if (root == NULL) return root;
	

	if (root->key > key)
		root->left = delete_node(root->left, key);
	else if (root->key < key)
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

int inorder(TreeNode* root) // ������ȸ
{
	if (root) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

TreeNode* InsertIter(TreeNode* root, TreeNode* node)
{
	
	while (1)
	{

		count++;
		if (root->data == node->data) {
			printf("�̹� �����մϴ�.\n");
			return NULL;
		}

		if (root->data > node->data) {

			if (root->left == NULL) {
				root->left = node;
				return node;
			}
			else
				root = root->left;
		}
		else {
			if (root->right == NULL) {
				root->right = node;
				return node;
			}
			else
				root = root->right;
		}
	}
}

TreeNode* DeleteIter(TreeNode* root, int key)
{
	TreeNode* parent = NULL;
	TreeNode* target = NULL;
	int count = 0;
	int target_value = 0;
	

	while(root->data != key)
	{ 
		
		count++;
		parent = root;
		if (root->data > key)
			root = root->left;
		else
			root = root->right;
	}

	target = root;
	target_value = target->data;

	if (root->left != NULL && root->right != NULL) {
		root = root->right;
		while (1)
		{
			count++;
			parent = root;
			root = root->left;
			if (root->left == NULL)
				break;
		}

		target->data = root-> data;
		parent->left = NULL;
	}

	else if (root->left == NULL && root->right == NULL) {
		if (parent->left == target)
			parent->left = NULL;
		else
			parent->right = NULL;
	}

	else {
		if (target->right == NULL) {
			target->data = target->left->data;
			target->right = target->left->right;
			target->left = target->left->left;
		}
		else {
			target->data = target->right->data;
			target-> left = target->right->left;
			target->right = target->right->right;
		}
	}
	return target;
}


int main(void) {

	TreeNode* root = NULL;
	TreeNode* temp = NULL;
	
	root = insert(root, 25);
	root = insert(root, 16);
	root = insert(root, 41);
	root = insert(root, 42);
	root = insert(root, 46);
	root = insert(root, 53);
	root = insert(root, 55);
	root = insert(root, 62);
	root = insert(root, 63);
	root = insert(root, 64);
	root = insert(root, 65);
	root = insert(root, 70);
	root = insert(root, 74);
	root = insert(root, 60);
	

	
	printf("-------------------------\n|s     : �˻�           | \n|i     : ����߰�       |   \n|d     : ������       |  \n|t     : ���� ��ȸ      |  \n|I     : ��� �߰�(�ݺ�)|\n|D     : ��� ����(�ݺ�) |  \n|c     : ����           |\n-------------------------\n ");
	while (1) {
		char opt = "";
		int keyNum = 0;
		printf("�ɼ��� �Է��ϼ��� : \n");
		scanf_s("%c", &opt);
		switch (opt) {
		case 's':
			printf("�˻��� ���� �Է� : \n");
			scanf_s("%d", &keyNum);
			Ssearch(root,keyNum);
			inorder(root);
			printf("\n");
			printf("�湮�� ����� �� : %d\n", count);
			break;
		case 'i':
			printf("������ �� �Է�: \n");
			scanf_s("%d", &keyNum);
			insert(root, keyNum);
			inorder(root);
			printf("\n");
			printf("�湮�� ����� �� : %d\n", count);
			break;
		case 'd':
			printf("������ �� �Է�: \n");
			scanf_s("%d", &keyNum);
			delete_node(root, keyNum);
			inorder(root);
			printf("\n");
			printf("�湮�� ����� �� : %d\n", count);
			break;
		case 't':
			printf("������ȸ\n");
			inorder(root);
			printf("\n");
			break;
		case 'I':
			printf("������ �� �Է�: \n");
			scanf_s("%d", &keyNum);
			insert(root, keyNum);
			inorder(root);
			printf("\n");
			printf("�湮�� ����� �� : %d\n", count);
			break;
		case 'D':
			printf("������ �� �Է�: \n");
			scanf_s("%d", &keyNum);
			delete_node(root, keyNum);
			inorder(root);
			printf("\n");
			printf("�湮�� ����� �� : %d\n", count);
			break;
		case 'c':
			printf("����\n");
			break;
		}
		if (opt == 'c') {
			break;
		}
	}

}


