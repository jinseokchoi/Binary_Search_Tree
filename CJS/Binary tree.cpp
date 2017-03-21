#include <stdio.h>
#include <stdlib.h>

//����ü����
typedef struct TreeNode{
	int key; // key���� ��� ����, �ʵ忡�� �Է¹޴� ����
	struct TreeNode *left, *right;
}
TreeNode;

//�����Լ����� ������ �ҷ����� ���� table�Լ� ����
void table(){
	printf("****************************���α׷��� �����ϼ���*******************************");
	printf("********************************************************************************");
	printf("****************Binary Search Tree(BST), ���� ���� Ʈ�� ���α׷�****************");
	printf("********************************************************************************");
	printf("1. Insert : ���Ҹ� �Է¹޾� BST�� �ִ´�.\n");
	printf("2. Delete : ���Ҹ� ã�Ƽ� BST���� �����Ѵ�.\n");
	printf("3. Count : BST�� ���Ұ����� ����Ѵ�.\n");
	printf("4. Pretorder_print : BST�� ���Ҹ� ������ȸ ������� ����Ѵ�.\n");
	printf("5. Max : BST�� ������ ���� ū ���� ����Ѵ�.\n");
	printf("6. Height : BST�� ���̸� ����Ѵ�.\n");
	printf("7. Median : BST�� ������ �߰����� ���Ҹ� ����Ѵ�.\n");
	printf("8. Get_one_child_node : BST�� �����߿��� �ڽ��� �ϳ��� ����� ������ ����Ѵ�.\n");
	printf("9. printf : ���� BST�� ���Ҹ� ���� ������ ū ���� ������ ����Ѵ�.\n");
	printf("10. Quit : BST���α׷��� ������.\n");
	printf("********************************************************************************\n");
	//���α׷��� ���� ����
}

//(1)Insert
//key�� ���� Ž�� Ʈ�� root�� �����Ѵ�.
//key�� �̹� root �ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, int key, int *count){
	TreeNode *p, *t; //p�� �θ���, t�� ������, *count�� �߰��� ����� ���� ī��Ʈ
	TreeNode *n; //n�� ���ο���
	t = *root;
	p = NULL;
	// Ž���� ��������
	while(t != NULL){
		if(key == t->key){
			printf("�̹� �����ϴ� key �Դϴ�.\n");
			return;
		}
		p = t;
		if(key < t->key) t = t->left;
		else t = t->right;
		//key�� ���� ��庸�� ������ ����, ũ�� ���������� ����
	}
	// key�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if(n==NULL) return;
	//������ ����
	n->key = key;
	n->left = n->right = NULL;
	// �θ���� ����
	if(p != NULL)
		if(key < p->key)
			p ->left = n;
		else p ->right =n;
		//root�� NULL�� ���
	else *root = n;
	(*count)++;
}

//(2)Delete
void delete_node(TreeNode **root, int key, int *count){
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key�� ���� ��� t�� Ž��, p�� t �� �θ���, *count�� �߰��� ����� ���� ī��Ʈ
	p = NULL;
	t = *root;
	// key�� ���� ��� t�� Ž���Ѵ�.
	while(t != NULL && t ->key != key){
		p = t;
		t = (key < t->key) ? t ->left : t ->right;
	}
	// Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� key�� ����
	if(t == NULL){
		printf("�������� �ʴ� key �Դϴ�.\n");
		return ;
	}
	//�ܸ� ����� ���
	if((t->left == NULL) && (t -> right == NULL)){
		if(p != NULL){
			// �θ� ����� �ڽ� �ʵ带 NULL�� �����.
			if(p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}
	//�ϳ��� �ڽĸ� �����°��
	else if((t ->left == NULL) || (t->right == NULL)){
		child = (t->left != NULL) ? t->left : t ->right;
		if(p != NULL){
			if(p->left == t) // �θ� �ڽİ� ����
				p->left = child;
			else p->right = child;
		}
		else //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}
	//�ΰ��� �ڽ��� ������ ���
	else{
		//������ ���� Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->left;
		// �İ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while(succ ->right != NULL){
			succ_p = succ;
			succ = succ->right; 
		}
		// �ļ����� �θ�� �ڽ��� ����
		if(succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//�ļ��ڰ� ���� Ű ���� ���� ��忡 ����
		t->key = succ->key;
		// ������ �ļ��� ����
		t = succ;
	}
	free(t);
	(*count)--;
}

//(3)Count
int get_count(TreeNode *node){
	int count = 0; //count�ʱ�ȭ
	if (node != NULL){
		count = 1 + get_count(node->left) + get_count(node->right);
	}
	return count;
	//node�� NULL�ƴϸ� �ڱ��ڽų��(root)1�� + ���ʳ���� ���� + �����ʳ�� ������ count�� ���� �� count���� ��ȯ
}

//(4)Preorder_print
void preorder_print(TreeNode *root)
{
	if(root){
		printf("%d \n", root->key); //���湮
		preorder_print(root->left); //���� ����Ʈ�� ��ȸ
		preorder_print(root->right); //������ ����Ʈ�� ��ȸ
	}
}

//(5)Max
void Max(TreeNode *root) 
{
	TreeNode *max;
	max = root;
	while(max->right != NULL)
	{
		max = max->right;
		if(max->right == NULL)
		{
			printf("�ִ� = %d\n",*max);
		}
	} 
	//������ �ڽĳ�尡 NULL�� �ƴҰ�� ������ �ڽĳ���� ���� max�� �����ϰ�
	//������ �ڽĳ�尡 NULL�̸� �������� ����� max���� ����Ѵ�.
}

//(6)Height
int get_height(TreeNode *node){
	int height = 0;
	if(node != NULL){
		height = 1 + ((get_height(node->left), get_height(node->right)));
	}
	return height;
	//node�� NULL�� �ƴҰ�� �ڱ��ڽų��(root)+1 + ���ʳ���� ���� �Ǵ� �����ʳ���� ���̸� height�� ���� �� ��ȯ�Ѵ�.
}

//(7)Median
void get_median(TreeNode *node, int mid1, int *mid2) //mid1:�� ����, mid2�߰��������� count�� �����������ι޾� �����Լ����� ��ȯ
{
	if(node)
	{
		get_median(node->left,mid1,mid2);
		(*mid2)++;
		if(mid1%2) //������ Ȧ��
		{
			if(((mid1+1)/2) == (*mid2))
				printf("�߰��� : %d\n",node->key);
		}
		else //������ ¦��
			if((mid1/2) == (*mid2))
				printf("�߰��� : %d\n",node->key);
		get_median(node->right,mid1,mid2);
	}
}

//(8)Get_one_child_node
int Get_one_child_node(TreeNode *root){ //�ڽ��� �ϳ��� ��� Ž��
	if (root != NULL)
	{
		if (root->left == NULL && root->right != NULL)
			return 1 + Get_one_child_node(root->right); 
		//���ʳ�尡 NULL�̰� �����ʳ�尡 NULL�� �ƴ� ���
		else if (root->left != NULL && root->right == NULL)
			return 1 + Get_one_child_node(root->left); 
		//���ʳ�尡 NULL�� �ƴϰ� �����ʳ�尡 NULL�� ���
		else
			return Get_one_child_node(root->left) + Get_one_child_node(root->right); 
		//���ʳ��� �����ʳ�尡 NULL�� �ƴ� ���
	}
	else return 0;

}

//(9)Print
void Print(TreeNode *node){
	if(node==NULL)
		return;
	//node�� NULL�ϰ�� ��ȯ�� ����
	else{	
		Print(node->left);
		printf("%d \n",node->key);
		Print(node->right);
	}//inorder�� Ž��
}

//�����Լ�
int main()
{
	int in=0; // ���α׷� ������ ���� ���� 
	int input=0; //���α׷� ���� �� ���α׷� ���� ���θ� ���� ���� 
	int key, count=0, count1=0; 
	//key = ��� ���� �޾Ƶ��̱� ���� ����, count = count�Լ����� count�� �޾Ƶ��̱� ���� ����, count1 = get_median�Լ����� *mid�� �޾Ƶ��̱� ���� ����
	TreeNode *root=NULL;
	//TreeNode�� �Լ����� �����Ͱ��� �޾Ƶ��̱� ���� ����

	//���α׷�����
	table();
	while((scanf_s("%d", &in)) != EOF){ //������ ������ �˻��Ͽ� ���ѷ��� ����
		fflush(stdin); //���۸� ���� ���� scanf�ؿ� ����
		if(in<=0 || in>=11)
			printf("���α׷� ������ �߸��ϼ̽��ϴ�.\n�ٽ� �����Ͻʽÿ�.\n");
		//���α׷� ���� ����� ��찡 �ƴϸ� �ٽ� �����ϵ�����
		if(in==1){
			printf("���ڸ� �Է��ϼ���.\n");
			scanf("%d", &key);
			insert_node(&root, key, &count); 
			//Insert���Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==2){
			printf("���ڸ� �Է��ϼ���.\n");
			scanf("%d", &key);
			delete_node(&root, key, &count); 
			//Delete�Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==3){
			count = 0;
			count = get_count(root); 
			//Count�Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����ǰ���: %d\n",count);
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==4){
			preorder_print(root); 
			//Preorder_print�Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==5){
			Max(root); 
			//Max���� ���ϴ� �Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==6){
			printf("����Ʈ���� ���� : %d\n", get_height(root)); 
			//Height�� ���ϴ� �Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==7){
			get_median(root, count, &count1); 
			//Median���� ���ϴ� �Լ������� ������ ���� �Լ����� �޾Ƶ���
			count1 = 0;
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==8){
			printf("�ڽ����ϳ��γ�� : %d\n", Get_one_child_node(root)); 
			//�ڽ��� �Ѱ��� ��带 �Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==9){
			printf("���� BST�ȿ� �ִ� ����\n");
			Print(root); 
			//Print�Լ������� ������ ���� �Լ����� �޾Ƶ���
			printf("����Ϸ��� 1��, �����Ϸ��� 0�� �Է��ϼ���\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1�� �����Ұ�� table�� �̵��Ͽ� ���α׷� ��� ����
			}
			else if(input==0)
				exit(0);
			//0�� �����Ұ�� ���α׷� ����
		}

		if(in==10){
			exit(1);
			//�Է°��� 10�� �Է��ϸ� ���α׷� ����
		}
	}
	return 0;
}