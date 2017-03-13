#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#define MAX_BUFFER 256

void menu(){
	printf("1. frist fit\n");
	printf("2. best fit\n");
	printf("3. worst fit\n");
	printf("4. exit\n");
}

void first_fit(FILE *fp, FILE *fp_best){
	char table[SIZE] = {0,}; //테이블사이즈 1000
	char OS[100] = {0,}; //OS 사이즈 100
	char buf[MAX_BUFFER] = {0,}; //메모장 최대 가로수 256칸 
	int len=0, size=100; //process파일 내에서 한 줄의 길이 , OS 사이즈
	int a, b, c; //메모리 사이즈를 받기 위한 변수 
	int count = 0; //process파일 내에서 줄 수만큼 카운트를 하기 위한 변수
	int copy_num=0; //a, b, c숫자를 (100*a) + (10*b) + c; 로 복사
	int copy_sum=0; //copy_num 을 합하는 변수

	fp = fopen("process.in", "r");
	fp_best = fopen("first.out", "w");

	fseek( fp, 0, SEEK_SET ); 
	while(fp, fgets(buf, MAX_BUFFER, fp) != NULL) { //버퍼수만큼 한줄씩 읽음
		count++; //줄 수 만큼 count++   
		for(int i=0; i<count; i++) 
		{
			for(int i=0; i<5; i++){
				if(buf[0] == 0)
					break;
				else if(i==2)
					a = buf[i]-48; //아스키코드값 int형과 char형차이인 48만큼 빼줌
				else if(i==3)
					b = buf[i]-48;
				else if(i==4)
					c = buf[i]-48;

				copy_num = (100*a) + (10*b) + c; // copy_num에 프로세스값 저장
				copy_sum += copy_num;
			}
			fprintf(fp_best, "status #%d\tprocess #\tsize\tstarting address\n", i+1);
			fprintf(fp_best, "         \tOS       \t%dK\t0\n", size);
			fprintf(fp_best, "         \tP%d       \t%d\t%d\n", i+1, copy_num, size);	


			buf[0] = '\0'; //buf값 초기화
		}
		fprintf(fp_best, "external fragmentation          %dK\n", copy_sum);
		fprintf(fp_best, "\n");
	}
	fclose(fp);
	fclose(fp_best);
}

void best_fit(){
}

void worst_fit(){

}

int main(){

	FILE *fp = NULL;
	FILE *fp_best = NULL;

	int choice;

	while(1){
		menu();
		printf("메뉴를 선택하세요\n");
		scanf("%d", &choice);

		switch(choice){
		case 1:
			first_fit(fp, fp_best);
			system("pause");
			system("cls");
			break;

		case 2:
			system("pause");
			system("cls");
			break;

		case 3:
			system("pause");
			system("cls");
			break;

		case 4: return 0;

		default:
			printf("잘못입력하셨습니다\n");
			system("pause");
			system("cls");

		}
	}

	return 0;
}