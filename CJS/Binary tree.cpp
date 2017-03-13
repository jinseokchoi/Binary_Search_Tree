#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int date;
	struct TreeNode *left,*right;
}TreeNode;

//메뉴
void menu()
{
	printf("◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("◇         M E N U              ◇\n");
	printf("◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("◇0)Quit                        ◇\n");
	printf("◇1)Insert                      ◇\n");
	printf("◇2)Delete                      ◇\n");
	printf("◇3)Count                       ◇\n");
	printf("◇4)Preorder_print              ◇\n");
	printf("◇5)Max                         ◇\n");
	printf("◇6)Height                      ◇\n");
	printf("◇7)Median                      ◇\n");
	printf("◇8)Get_one_child_node          ◇\n");
	printf("◇9)Print                       ◇\n");
	printf("◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
	printf("원하는 번호를 입력하세요 : ");
}
//삽입함수
void insert_node(TreeNode **root, int key, int *cnt)  //key = 새로운 노드
{
	TreeNode *p, *t; //p는 부모 노드,t는 현재 노드
	TreeNode *n; //n은 새로운 노드

	t = *root;
	p = NULL;

	//탐색 수행
	while(t != NULL) 
	{
		if(key == t->date) return; //이미 존재하는 값인경우
		p = t;
		if(key < p->date) t = p->left; //key가 data보다 작을 경우 왼쪽 노드로.
		else t = p->right;  //클 경우 오른쪽 노드로.
	}
	//key가 트리안에 없으므로 삽입가능
	//트리 노드 구성
	n = (TreeNode *)malloc(sizeof(TreeNode));  //공간 확보
	if(n == NULL) return;  //공간 확보를 못한경우
	//데이터 복사
	n->date = key;
	n->left = n->right = NULL;  //key의 양쪽 링크값 null값으로 초기화
	//부모 노드와 연결
	if(p != NULL)  //부모 노드가 있을경우
		if(key < p->date)  //key 값이 부모 노드 값보다 작을경우 왼쪽
			p->left = n;
		else p->right = n;  //클경우 오른쪽
	else *root = n;  //부모 노드가 없을경우 key 값을 루트 값으로
	(*cnt)++;
}
//삭제함수
void delete_node(TreeNode **root, int key, int *cnt)
{
	TreeNode *p, *child , *succ, *succ_p, *t;

	//key를 갖는 노드 t를 탐색,p는 t의 부모 노드
	p = NULL;
	t = *root;
	//key를 갖는 노드 t를 탐색한다.
	while(t !=  NULL && t->date != key)  //key값의 위치를 찾은 때까지 반복
	{
		p = t;
		t = (key < t->date ) ? t->left : t->right;  //key 값이 t 값보다 작으면 왼쪽 자식으로, 크면 오른쪽 자식으로 이동
	}
	//탐색이 종료된 시점에 t가 NULL이면 트리 안에 key값이 없음
	if(t == NULL)  //탐색 트리에 없는 키
	{
		printf("key 값이 트리안에 없습니다.\n");
		return;  //key가 없으므로 함수 종료
	}
	//첫 번째 경우 : 단말 노드인 경우자
	if((t->left == NULL) && (t->right == NULL))
	{
		if(p != NULL)
		{
			//부모 노드의 자식 필드를 NULL로 만든다.
			if(p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else  //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = NULL;
	}
	//두 번째 경우 : 하나의 자식만 가지는 경우
	else if((t->left == NULL) || (t->right == NULL))
	{
		child = (t->left != NULL) ? t->left : t->right;  //삭제할 노드의 자식노드
		if(p != NULL)
		{
			if(p->left == t)  //삭제할 노드의 부모를 자식과 연결
				p->left = child;
			else p->right = child;
		}
		else  //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}
	//세 번째 경우 : 두 개의 자식을 가지는 경우
	else
	{
		//왼쪽 서브 트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->left;
		//후계자를 찾아서 계속 오른쪽으로 이동한다.
		while(succ->right != NULL)
		{
			succ_p = succ;
			succ = succ->right;
		}
		//후속자의 부모와 자식을 연결
		if(succ_p->right == succ)
			succ_p->right = succ->left;
		else
			succ_p->left = succ->left;
		//후속자가 가진 키 값을 현재 노드에 복사
		t->date = succ->date;
		//원래 후속자 삭제
		t = succ;
	}
	free(t);
	(*cnt)--;
}
//전위순회 출력
//   n1
//  /  ＼
// n2    n3
//n1 n2 n3 순으로 출력
void preorder_print(TreeNode *node)
{
	if(node)  //노드가 존재할 경우
	{
		printf("%d ",node->date);  //노드 출력
		preorder_print(node->left);  //왼쪽 자식으로 이동
		preorder_print(node->right);  //오른쪽 자식으로 이동
	}
}
//max값 찾기
//가장 큰 값은 가장 오른쪽에 존재
TreeNode * findmax(TreeNode *node)
{
	if(node->right != NULL)      //오른쪽 자식이 있을경우
		findmax(node->right);    //오른쪽자식으로 이동
	else return node;			 //더이상 오른쪽 자식이 없을경우 출력
}
//트리의 높이
int get_height(TreeNode *node)
{
	int height=0;
	if(node != NULL)
		//왼쪽과 오른쪽의 높이 중 더 큰 값 + 1
		 height = 1 + (get_height(node->left)>get_height(node->right)?get_height(node->left):get_height(node->right) );
	return height;
}
//중간값 출력
void median(TreeNode *node, int cnt1, int *cnt2) //cnt1 : 총 노드수, cnt2중간값까지의 count
{
	//inorder순으로 작은값부터 카운트
	if(node)
	{
		median(node->left,cnt1,cnt2);  //왼쪽노드 탐색
		(*cnt2)++;
		if(cnt1%2) //갯수가 홀수
		{
			if(((cnt1+1)/2) == (*cnt2))
				printf("중간값 : %d\n",node->date);
		}
		else //갯수가 짝수
			if((cnt1/2) == (*cnt2))
				printf("중간값 : %d\n",node->date);
		median(node->right,cnt1,cnt2);  //오른쪽노드 탐색
	}		
}
//자식이 하나인 노드의 개수
int get_one_child_node(TreeNode *node, int *cnt)
{
	if(node)
	{
		//작은 수부터(inoder순) 탐색
		get_one_child_node(node->left,cnt);  //왼쪽노드 탐색
		//왼쪽 자식이 없고 오른쪽 자식은 있는경우
		if(node->left == NULL)
		{
			if(node->right != NULL)
				(*cnt)++;
		}
		//오른쪽 자식이 없고 왼쪽 자식이 있는경우
		else
			if(node->right == NULL)
				(*cnt)++;
		get_one_child_node(node->right,cnt);  //오른쪽노드 탐색
	}
	return *cnt;
}
//이진 탐색트리를 작순 수부터 출력하려면 inorder로 출력하면 된다.
void inorder(TreeNode *node)
{
	if(node)
	{
		inorder(node->left);		//왼쪽노드 탐색
		printf("%d ",node->date);	//노드 출력
		inorder(node->right);		//오른쪽노드 탐색
	}
}

int main(void)
{
	TreeNode *binary = NULL;  //새로운 트리
	TreeNode *temp;  //구조체 반환형 함수를 저장할 변수
	int choice,node; //node = 삽입,삭제할 노드 변수
	int cnt = 0, o_cnt = 0; //cnt:노드 갯수, o_cnt:자식이 하나인 노드and
	char c;
	int n=0;
	while(1)
	{
		system("cls");
		menu();

		n=scanf("%d%c",&choice,&c);  
		if(n==0 || c != '\n')  //n이 0이면 choice를 정수로 받지 않은것
		{					   //c 가 엔터키('\n')가 아지면 정수후 다른것을 입력한경우
			fflush(stdin);	   //현재 재대로 받지않은것을 지움.
			choice = 10;	   //choice에 10을 주어 default로 가도록 함.
		}

		switch(choice) 
		{
		case 0: exit(0);                           //종료
		case 1: {                                  //삽입
			printf("새로 추가할 값 입력 : ");
			n = scanf("%d%c",&node,&c);
			if(n==0 || c != '\n')				   //choice와같이 정수만 받도록함.
			{
				printf("정수만 입력할수 있습니다.\n");
				fflush(stdin);
				break;
			}
			insert_node(&binary,node,&cnt);
		} break;
		case 2: {                                  //삭제
			printf("삭제할 값 입력 : ");
			n = scanf("%d%c",&node,&c);
			if(n==0 || c != '\n')			   //choice와같이 정수만 받도록함.
			{
				printf("정수만 입력할수 있습니다.\n");
				fflush(stdin);
				break;
			}
			delete_node(&binary,node,&cnt);
		}break;
		case 3: printf("현재 노드의 갯수 : %d\n",cnt); break;  //카운트
		case 4: {								//전위순회
			preorder_print(binary);
			printf("\n"); 
		}break;
		case 5: {							    //max값
			if(binary == NULL)					//트리가 비어있을때 max함수 호출.
			{
				printf("트리가 비어있습니다.\n");
				break;
			}
			temp = findmax(binary);
			printf("트리의 max값은 : %d\n",temp->date); 
		} break;
		case 6: printf("트리의 높이는 : %d\n",get_height(binary)); break;  //트리의 높이
		case 7: {								//중간값
			median(binary,cnt,&o_cnt);
			o_cnt = 0;
		} break;
		case 8: {								//자식 노드가 한개인 노드갯수
			printf("자식이 하나인 노드의 갯수 : %d\n",get_one_child_node(binary,&o_cnt)); 
			o_cnt = 0;
		} break;
		case 9: {								//작은순으로 출력
			inorder(binary);
			printf("\n");
		}break;
		default: printf("잘못 입력하였습니다. 다시 입력하세요\n");
		}
		system("pause");

	}

	return 0;
}



























