#include <stdio.h>
#include <stdlib.h>

//구조체선언
typedef struct TreeNode{
	int key; // key값은 모두 동일, 필드에서 입력받는 변수
	struct TreeNode *left, *right;
}
TreeNode;

//메인함수에서 목차를 불러오기 위해 table함수 구성
void table(){
	printf("****************************프로그램을 선택하세요*******************************");
	printf("********************************************************************************");
	printf("****************Binary Search Tree(BST), 완전 이진 트리 프로그램****************");
	printf("********************************************************************************");
	printf("1. Insert : 원소를 입력받아 BST에 넣는다.\n");
	printf("2. Delete : 원소를 찾아서 BST에서 삭제한다.\n");
	printf("3. Count : BST의 원소갯수를 출력한다.\n");
	printf("4. Pretorder_print : BST의 원소를 전위순회 방식으로 출력한다.\n");
	printf("5. Max : BST의 원소중 가장 큰 수를 출력한다.\n");
	printf("6. Height : BST의 높이를 출력한다.\n");
	printf("7. Median : BST의 원소중 중간값의 원소를 출력한다.\n");
	printf("8. Get_one_child_node : BST의 원소중에서 자식이 하나인 노드의 갯수를 출력한다.\n");
	printf("9. printf : 현재 BST의 원소를 작은 수부터 큰 수의 순서로 출력한다.\n");
	printf("10. Quit : BST프로그램을 끝낸다.\n");
	printf("********************************************************************************\n");
	//프로그램의 개요 설명
}

//(1)Insert
//key를 이진 탐색 트리 root에 삽입한다.
//key가 이미 root 안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, int key, int *count){
	TreeNode *p, *t; //p는 부모노드, t는 현재노드, *count는 중간값 출력을 위한 카운트
	TreeNode *n; //n은 새로운노드
	t = *root;
	p = NULL;
	// 탐색을 먼저수행
	while(t != NULL){
		if(key == t->key){
			printf("이미 존재하는 key 입니다.\n");
			return;
		}
		p = t;
		if(key < t->key) t = t->left;
		else t = t->right;
		//key가 현재 노드보다 작으면 왼쪽, 크면 오른쪽으로 삽입
	}
	// key가 트리 안에 없으므로 삽입 가능
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if(n==NULL) return;
	//데이터 복사
	n->key = key;
	n->left = n->right = NULL;
	// 부모노드와 연결
	if(p != NULL)
		if(key < p->key)
			p ->left = n;
		else p ->right =n;
		//root가 NULL인 경우
	else *root = n;
	(*count)++;
}

//(2)Delete
void delete_node(TreeNode **root, int key, int *count){
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key를 갖는 노드 t를 탐색, p는 t 의 부모노드, *count는 중간값 출력을 위한 카운트
	p = NULL;
	t = *root;
	// key를 갖는 노드 t를 탐색한다.
	while(t != NULL && t ->key != key){
		p = t;
		t = (key < t->key) ? t ->left : t ->right;
	}
	// 탐색이 종료된 시점에 t가 NULL이면 트리 안에 key가 없음
	if(t == NULL){
		printf("존재하지 않는 key 입니다.\n");
		return ;
	}
	//단말 노드인 경우
	if((t->left == NULL) && (t -> right == NULL)){
		if(p != NULL){
			// 부모 노드의 자식 필드를 NULL로 만든다.
			if(p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = NULL;
	}
	//하나의 자식만 가지는경우
	else if((t ->left == NULL) || (t->right == NULL)){
		child = (t->left != NULL) ? t->left : t ->right;
		if(p != NULL){
			if(p->left == t) // 부모를 자식과 연결
				p->left = child;
			else p->right = child;
		}
		else //만약 부모 노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}
	//두개의 자식을 가지는 경우
	else{
		//오른쪽 서브 트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->left;
		// 후계자를 찾아서 계속 왼쪽으로 이동한다.
		while(succ ->right != NULL){
			succ_p = succ;
			succ = succ->right; 
		}
		// 후속자의 부모와 자식을 연결
		if(succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//후속자가 가진 키 값을 현재 노드에 복사
		t->key = succ->key;
		// 원래의 후속자 삭제
		t = succ;
	}
	free(t);
	(*count)--;
}

//(3)Count
int get_count(TreeNode *node){
	int count = 0; //count초기화
	if (node != NULL){
		count = 1 + get_count(node->left) + get_count(node->right);
	}
	return count;
	//node가 NULL아니면 자기자신노드(root)1개 + 왼쪽노드의 갯수 + 오른쪽노드 갯수를 count에 저장 후 count값을 반환
}

//(4)Preorder_print
void preorder_print(TreeNode *root)
{
	if(root){
		printf("%d \n", root->key); //노드방문
		preorder_print(root->left); //왼쪽 서브트리 순회
		preorder_print(root->right); //오른쪽 서브트리 순회
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
			printf("최댓값 = %d\n",*max);
		}
	} 
	//오른쪽 자식노드가 NULL이 아닐경우 오른쪽 자식노드의 값을 max에 저장하고
	//오른쪽 자식노드가 NULL이면 마지막에 저장된 max값을 출력한다.
}

//(6)Height
int get_height(TreeNode *node){
	int height = 0;
	if(node != NULL){
		height = 1 + ((get_height(node->left), get_height(node->right)));
	}
	return height;
	//node가 NULL이 아닐경우 자기자신노드(root)+1 + 왼쪽노드의 높이 또는 오른쪽노드의 높이를 height에 저장 후 반환한다.
}

//(7)Median
void get_median(TreeNode *node, int mid1, int *mid2) //mid1:총 노드수, mid2중간값까지의 count는 포인터형으로받아 메인함수에서 반환
{
	if(node)
	{
		get_median(node->left,mid1,mid2);
		(*mid2)++;
		if(mid1%2) //갯수가 홀수
		{
			if(((mid1+1)/2) == (*mid2))
				printf("중간값 : %d\n",node->key);
		}
		else //갯수가 짝수
			if((mid1/2) == (*mid2))
				printf("중간값 : %d\n",node->key);
		get_median(node->right,mid1,mid2);
	}
}

//(8)Get_one_child_node
int Get_one_child_node(TreeNode *root){ //자식이 하나인 노드 탐색
	if (root != NULL)
	{
		if (root->left == NULL && root->right != NULL)
			return 1 + Get_one_child_node(root->right); 
		//왼쪽노드가 NULL이고 오른쪽노드가 NULL이 아닐 경우
		else if (root->left != NULL && root->right == NULL)
			return 1 + Get_one_child_node(root->left); 
		//왼쪽노드가 NULL이 아니고 오른쪽노드가 NULL일 경우
		else
			return Get_one_child_node(root->left) + Get_one_child_node(root->right); 
		//왼쪽노드와 오른쪽노드가 NULL이 아닐 경우
	}
	else return 0;

}

//(9)Print
void Print(TreeNode *node){
	if(node==NULL)
		return;
	//node가 NULL일경우 반환값 없음
	else{	
		Print(node->left);
		printf("%d \n",node->key);
		Print(node->right);
	}//inorder로 탐색
}

//메인함수
int main()
{
	int in=0; // 프로그램 선택을 위한 변수 
	int input=0; //프로그램 선택 후 프로그램 실행 여부를 위한 변수 
	int key, count=0, count1=0; 
	//key = 모든 값을 받아들이기 위한 변수, count = count함수에서 count를 받아들이기 위한 변수, count1 = get_median함수에서 *mid를 받아들이기 위한 변수
	TreeNode *root=NULL;
	//TreeNode의 함수에서 포인터값을 받아들이기 위한 변수

	//프로그램선택
	table();
	while((scanf_s("%d", &in)) != EOF){ //파일의 끝까지 검사하여 무한루프 방지
		fflush(stdin); //버퍼를 비우기 위해 scanf밑에 선언
		if(in<=0 || in>=11)
			printf("프로그램 선택을 잘못하셨습니다.\n다시 선택하십시오.\n");
		//프로그램 선택 목록인 경우가 아니면 다시 선택하도록함
		if(in==1){
			printf("숫자를 입력하세요.\n");
			scanf("%d", &key);
			insert_node(&root, key, &count); 
			//Insert값함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==2){
			printf("숫자를 입력하세요.\n");
			scanf("%d", &key);
			delete_node(&root, key, &count); 
			//Delete함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==3){
			count = 0;
			count = get_count(root); 
			//Count함수에서의 변수를 메인 함수에서 받아들임
			printf("노드의개수: %d\n",count);
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==4){
			preorder_print(root); 
			//Preorder_print함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==5){
			Max(root); 
			//Max값을 구하는 함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==6){
			printf("이진트리의 높이 : %d\n", get_height(root)); 
			//Height를 구하는 함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==7){
			get_median(root, count, &count1); 
			//Median값을 구하는 함수에서의 변수를 메인 함수에서 받아들임
			count1 = 0;
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==8){
			printf("자식이하나인노드 : %d\n", Get_one_child_node(root)); 
			//자식이 한개인 노드를 함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==9){
			printf("현재 BST안에 있는 원소\n");
			Print(root); 
			//Print함수에서의 변수를 메인 함수에서 받아들임
			printf("계속하려면 1을, 종료하려면 0을 입력하세요\n");
			scanf("%d", &input);
			if(input==1){
				system("cls");
				table();
				//1을 선택할경우 table로 이동하여 프로그램 계속 수행
			}
			else if(input==0)
				exit(0);
			//0을 선택할경우 프로그램 종료
		}

		if(in==10){
			exit(1);
			//입력값에 10을 입력하면 프로그램 종료
		}
	}
	return 0;
}