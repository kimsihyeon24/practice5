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

TreeNode* Ssearch(TreeNode* node, int key)//반복 탐색
{
	printf("검색 성공 : %d\n", key);
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
	printf("방문한 노드의 수 : %d", count);
}

TreeNode* new_node(int item)// 노드 추가
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert(TreeNode* root, int key) {
	TreeNode* ptr;     // 탐색을 진행할 포인터 
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));    // newNode 생성
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	if (root == NULL) {    // 트리가 비어 있을 경우 
		root = newNode;
		return root;
	}

	ptr = root;    // root 노드부터 탐색 진행  

	while (ptr) {
		if (key == ptr->key) {    // 중복값 
			printf("Error : 중복값은 허용되지 않습니다!\n");
			return root;
		}
		else if (key < ptr->key) {    // 왼쪽 서브트리 
			if (ptr->left == NULL) {    // 비어있다면 추가 
				ptr->left = newNode;
				return root;
			}
			else {    // 비어있지 않다면 다시 탐색 진행 
				ptr = ptr->left;
			}
		}
		else {    // key > ptr->key 오른쪽 서브트리 
			if (ptr->right == NULL) {    // 비어있다면 추가 
				ptr->right = newNode;
				return root;
			}
			else {    // 비어있지 않다면 다시 탐색 진행 
				ptr = ptr->right;
			}
		}
	}

}

TreeNode* min_value_node(TreeNode* node)//맨왼쪽 단말노드 찾아 내려감
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, int key)//노드 삭제
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

int inorder(TreeNode* root) // 중위순회
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
			printf("이미 존재합니다.\n");
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
	

	
	printf("-------------------------\n|s     : 검색           | \n|i     : 노드추가       |   \n|d     : 노드삭제       |  \n|t     : 중위 순회      |  \n|I     : 노드 추가(반복)|\n|D     : 노드 삭제(반복) |  \n|c     : 종료           |\n-------------------------\n ");
	while (1) {
		char opt = "";
		int keyNum = 0;
		printf("옵션을 입력하세요 : \n");
		scanf_s("%c", &opt);
		switch (opt) {
		case 's':
			printf("검색할 값을 입력 : \n");
			scanf_s("%d", &keyNum);
			Ssearch(root,keyNum);
			inorder(root);
			printf("\n");
			printf("방문한 노드의 수 : %d\n", count);
			break;
		case 'i':
			printf("삽입할 값 입력: \n");
			scanf_s("%d", &keyNum);
			insert(root, keyNum);
			inorder(root);
			printf("\n");
			printf("방문한 노드의 수 : %d\n", count);
			break;
		case 'd':
			printf("삭제할 값 입력: \n");
			scanf_s("%d", &keyNum);
			delete_node(root, keyNum);
			inorder(root);
			printf("\n");
			printf("방문한 노드의 수 : %d\n", count);
			break;
		case 't':
			printf("중위순회\n");
			inorder(root);
			printf("\n");
			break;
		case 'I':
			printf("삽입할 값 입력: \n");
			scanf_s("%d", &keyNum);
			insert(root, keyNum);
			inorder(root);
			printf("\n");
			printf("방문한 노드의 수 : %d\n", count);
			break;
		case 'D':
			printf("삭제할 값 입력: \n");
			scanf_s("%d", &keyNum);
			delete_node(root, keyNum);
			inorder(root);
			printf("\n");
			printf("방문한 노드의 수 : %d\n", count);
			break;
		case 'c':
			printf("종료\n");
			break;
		}
		if (opt == 'c') {
			break;
		}
	}

}


