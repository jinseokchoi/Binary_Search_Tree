#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int date;
	struct TreeNode *left,*right;
}TreeNode;

//�޴�
void menu()
{
	printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�\n");
	printf("��         M E N U              ��\n");
	printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�\n");
	printf("��0)Quit                        ��\n");
	printf("��1)Insert                      ��\n");
	printf("��2)Delete                      ��\n");
	printf("��3)Count                       ��\n");
	printf("��4)Preorder_print              ��\n");
	printf("��5)Max                         ��\n");
	printf("��6)Height                      ��\n");
	printf("��7)Median                      ��\n");
	printf("��8)Get_one_child_node          ��\n");
	printf("��9)Print                       ��\n");
	printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�\n");
	printf("���ϴ� ��ȣ�� �Է��ϼ��� : ");
}
//�����Լ�
void insert_node(TreeNode **root, int key, int *cnt)  //key = ���ο� ���
{
	TreeNode *p, *t; //p�� �θ� ���,t�� ���� ���
	TreeNode *n; //n�� ���ο� ���

	t = *root;
	p = NULL;

	//Ž�� ����
	while(t != NULL) 
	{
		if(key == t->date) return; //�̹� �����ϴ� ���ΰ��
		p = t;
		if(key < p->date) t = p->left; //key�� data���� ���� ��� ���� ����.
		else t = p->right;  //Ŭ ��� ������ ����.
	}
	//key�� Ʈ���ȿ� �����Ƿ� ���԰���
	//Ʈ�� ��� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));  //���� Ȯ��
	if(n == NULL) return;  //���� Ȯ���� ���Ѱ��
	//������ ����
	n->date = key;
	n->left = n->right = NULL;  //key�� ���� ��ũ�� null������ �ʱ�ȭ
	//�θ� ���� ����
	if(p != NULL)  //�θ� ��尡 �������
		if(key < p->date)  //key ���� �θ� ��� ������ ������� ����
			p->left = n;
		else p->right = n;  //Ŭ��� ������
	else *root = n;  //�θ� ��尡 ������� key ���� ��Ʈ ������
	(*cnt)++;
}
//�����Լ�
void delete_node(TreeNode **root, int key, int *cnt)
{
	TreeNode *p, *child , *succ, *succ_p, *t;

	//key�� ���� ��� t�� Ž��,p�� t�� �θ� ���
	p = NULL;
	t = *root;
	//key�� ���� ��� t�� Ž���Ѵ�.
	while(t !=  NULL && t->date != key)  //key���� ��ġ�� ã�� ������ �ݺ�
	{
		p = t;
		t = (key < t->date ) ? t->left : t->right;  //key ���� t ������ ������ ���� �ڽ�����, ũ�� ������ �ڽ����� �̵�
	}
	//Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� key���� ����
	if(t == NULL)  //Ž�� Ʈ���� ���� Ű
	{
		printf("key ���� Ʈ���ȿ� �����ϴ�.\n");
		return;  //key�� �����Ƿ� �Լ� ����
	}
	//ù ��° ��� : �ܸ� ����� �����
	if((t->left == NULL) && (t->right == NULL))
	{
		if(p != NULL)
		{
			//�θ� ����� �ڽ� �ʵ带 NULL�� �����.
			if(p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else  //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}
	//�� ��° ��� : �ϳ��� �ڽĸ� ������ ���
	else if((t->left == NULL) || (t->right == NULL))
	{
		child = (t->left != NULL) ? t->left : t->right;  //������ ����� �ڽĳ��
		if(p != NULL)
		{
			if(p->left == t)  //������ ����� �θ� �ڽİ� ����
				p->left = child;
			else p->right = child;
		}
		else  //���� �θ� ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}
	//�� ��° ��� : �� ���� �ڽ��� ������ ���
	else
	{
		//���� ���� Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->left;
		//�İ��ڸ� ã�Ƽ� ��� ���������� �̵��Ѵ�.
		while(succ->right != NULL)
		{
			succ_p = succ;
			succ = succ->right;
		}
		//�ļ����� �θ�� �ڽ��� ����
		if(succ_p->right == succ)
			succ_p->right = succ->left;
		else
			succ_p->left = succ->left;
		//�ļ��ڰ� ���� Ű ���� ���� ��忡 ����
		t->date = succ->date;
		//���� �ļ��� ����
		t = succ;
	}
	free(t);
	(*cnt)--;
}
//������ȸ ���
//   n1
//  /  ��
// n2    n3
//n1 n2 n3 ������ ���
void preorder_print(TreeNode *node)
{
	if(node)  //��尡 ������ ���
	{
		printf("%d ",node->date);  //��� ���
		preorder_print(node->left);  //���� �ڽ����� �̵�
		preorder_print(node->right);  //������ �ڽ����� �̵�
	}
}
//max�� ã��
//���� ū ���� ���� �����ʿ� ����
TreeNode * findmax(TreeNode *node)
{
	if(node->right != NULL)      //������ �ڽ��� �������
		findmax(node->right);    //�������ڽ����� �̵�
	else return node;			 //���̻� ������ �ڽ��� ������� ���
}
//Ʈ���� ����
int get_height(TreeNode *node)
{
	int height=0;
	if(node != NULL)
		//���ʰ� �������� ���� �� �� ū �� + 1
		 height = 1 + (get_height(node->left)>get_height(node->right)?get_height(node->left):get_height(node->right) );
	return height;
}
//�߰��� ���
void median(TreeNode *node, int cnt1, int *cnt2) //cnt1 : �� ����, cnt2�߰��������� count
{
	//inorder������ ���������� ī��Ʈ
	if(node)
	{
		median(node->left,cnt1,cnt2);  //���ʳ�� Ž��
		(*cnt2)++;
		if(cnt1%2) //������ Ȧ��
		{
			if(((cnt1+1)/2) == (*cnt2))
				printf("�߰��� : %d\n",node->date);
		}
		else //������ ¦��
			if((cnt1/2) == (*cnt2))
				printf("�߰��� : %d\n",node->date);
		median(node->right,cnt1,cnt2);  //�����ʳ�� Ž��
	}		
}
//�ڽ��� �ϳ��� ����� ����
int get_one_child_node(TreeNode *node, int *cnt)
{
	if(node)
	{
		//���� ������(inoder��) Ž��
		get_one_child_node(node->left,cnt);  //���ʳ�� Ž��
		//���� �ڽ��� ���� ������ �ڽ��� �ִ°��
		if(node->left == NULL)
		{
			if(node->right != NULL)
				(*cnt)++;
		}
		//������ �ڽ��� ���� ���� �ڽ��� �ִ°��
		else
			if(node->right == NULL)
				(*cnt)++;
		get_one_child_node(node->right,cnt);  //�����ʳ�� Ž��
	}
	return *cnt;
}
//���� Ž��Ʈ���� �ۼ� ������ ����Ϸ��� inorder�� ����ϸ� �ȴ�.
void inorder(TreeNode *node)
{
	if(node)
	{
		inorder(node->left);		//���ʳ�� Ž��
		printf("%d ",node->date);	//��� ���
		inorder(node->right);		//�����ʳ�� Ž��
	}
}

int main(void)
{
	TreeNode *binary = NULL;  //���ο� Ʈ��
	TreeNode *temp;  //����ü ��ȯ�� �Լ��� ������ ����
	int choice,node; //node = ����,������ ��� ����
	int cnt = 0, o_cnt = 0; //cnt:��� ����, o_cnt:�ڽ��� �ϳ��� ���and
	char c;
	int n=0;
	while(1)
	{
		system("cls");
		menu();

		n=scanf("%d%c",&choice,&c);  
		if(n==0 || c != '\n')  //n�� 0�̸� choice�� ������ ���� ������
		{					   //c �� ����Ű('\n')�� ������ ������ �ٸ����� �Է��Ѱ��
			fflush(stdin);	   //���� ���� ������������ ����.
			choice = 10;	   //choice�� 10�� �־� default�� ������ ��.
		}

		switch(choice) 
		{
		case 0: exit(0);                           //����
		case 1: {                                  //����
			printf("���� �߰��� �� �Է� : ");
			n = scanf("%d%c",&node,&c);
			if(n==0 || c != '\n')				   //choice�Ͱ��� ������ �޵�����.
			{
				printf("������ �Է��Ҽ� �ֽ��ϴ�.\n");
				fflush(stdin);
				break;
			}
			insert_node(&binary,node,&cnt);
		} break;
		case 2: {                                  //����
			printf("������ �� �Է� : ");
			n = scanf("%d%c",&node,&c);
			if(n==0 || c != '\n')			   //choice�Ͱ��� ������ �޵�����.
			{
				printf("������ �Է��Ҽ� �ֽ��ϴ�.\n");
				fflush(stdin);
				break;
			}
			delete_node(&binary,node,&cnt);
		}break;
		case 3: printf("���� ����� ���� : %d\n",cnt); break;  //ī��Ʈ
		case 4: {								//������ȸ
			preorder_print(binary);
			printf("\n"); 
		}break;
		case 5: {							    //max��
			if(binary == NULL)					//Ʈ���� ��������� max�Լ� ȣ��.
			{
				printf("Ʈ���� ����ֽ��ϴ�.\n");
				break;
			}
			temp = findmax(binary);
			printf("Ʈ���� max���� : %d\n",temp->date); 
		} break;
		case 6: printf("Ʈ���� ���̴� : %d\n",get_height(binary)); break;  //Ʈ���� ����
		case 7: {								//�߰���
			median(binary,cnt,&o_cnt);
			o_cnt = 0;
		} break;
		case 8: {								//�ڽ� ��尡 �Ѱ��� ��尹��
			printf("�ڽ��� �ϳ��� ����� ���� : %d\n",get_one_child_node(binary,&o_cnt)); 
			o_cnt = 0;
		} break;
		case 9: {								//���������� ���
			inorder(binary);
			printf("\n");
		}break;
		default: printf("�߸� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���\n");
		}
		system("pause");

	}

	return 0;
}



























