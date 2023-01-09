#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record{		// 생활관생 관리 레코드
	char name[20];	// 성명				
	char fm;		// 성별 ('F' 여성, 'M' 남성)				
	int entry;		// 입학년도 (4자리 숫자)
	int room;		// 방 호실
	int point;		// 벌점
};

int loadMembers(struct Record* p[]);		// 목록파일 읽기
void listMembers(struct Record* p[], int n);	// 목록 출력(리스트)
void editRoom(struct Record* p[], int n);		// 호실 수정
void makePenalty(struct Record* p[], int n);	// 벌점 부여
void findMembers(struct Record* p[], int n);	// 검색 (이름)
void saveReport(struct Record* p[], int n);	// 보고서 저장

int main(){
	struct Record* members[100]; 	// 최대 100명까지 관리할 수 있는 포인터 배열
	int count;	// 현재등록된 관생 수
	int menu;	// 메뉴번호
	count = loadMembers(members);	// 시작 전에 파일로부터 관생 리스트를 모두 읽어온다.
	while(1)
	{
		printf("\n[1]목록 [2]호실변경 [3]벌점부여 [4]검색 [5]보고서 저장 [0]종료 >> ");
		scanf("%d",&menu);	// 메뉴를 읽음

		if(menu==1){
			listMembers(members, count);	// 목록 출력
		}
		else if(menu==2){
			editRoom(members, count);	// 호실 변경
		}
		else if(menu==3){
			makePenalty(members, count); // 벌점 부여
		}
		else if(menu==4){
			findMembers(members, count);	// 검색
		}
		else if(menu==5){
			saveReport(members, count);	// 보고서 저장
		}
		else {
			break;
		}
	}
}

int loadMembers(struct Record* p[]){
	FILE *file;
	int n=0;
	file = fopen("members.txt","rt");
	while(!feof(file)){
		p[n]=(struct Record*)malloc(sizeof(struct Record));
		fscanf(file,"%s %c %d %d %d",p[n]->name,&(p[n]->fm),&(p[n]->entry),&(p[n]->room),&(p[n]->point));
		n++;
	}
	fclose(file);
	printf("%d명이 저장된 파일을 읽었습니다.\n",n);
	return n;
}

void listMembers(struct Record * p[], int n){
	int i;
	printf("\n전체목록입니다.\n");
	printf("NO 이름 성별 학번 호실 벌점\n");
	
	for(i=0; i<n; i++){
		printf("%d %s [%c] %d %d %d\n", (i+1), p[i]->name, p[i]->fm, p[i]->entry, p[i]->room, p[i]->point);
	}
}

// 15-1 문제
void editRoom(struct Record* p[], int n){
	char name[20];
	struct Record* rp; // 수정할 레코드 구조체의 포인터값
	int i, found=0, newroom;

	printf("호실 변경하려는 학생 이름은? >> ");
	scanf("%s", name);
	for(i=0;i<n;i++){
		if(strcmp(p[i]->name,name)==0){
			found=1;
			rp=p[i];
			break;
		}
	}
	if(found==1){
		printf("이름 성별 학번 호실 벌점\n");
		printf("%s [%c] %d %d %d\n", rp->name, rp->fm, rp->entry, rp->room, rp->point);

		printf("새로운 호실을 입력하시오. >> ");
		scanf("%d", &newroom); 

		rp->room = newroom;
		printf("수정완료!\n");
	}
	else{
		printf("없는 학생입니다.\n");
	}
}

// 15-2
void makePenalty(struct Record* p[], int n){
  // TODO
}

// 15-3
void findMembers(struct Record * p[], int n){
	int i, count=0;
	char name[20];
	while(1){
		printf("검색하려는 학생 이름을 2글자 이상 입력하세요. >> ");
		scanf("%s", name);
		if(strlen(name) > 1) break;
	}
  // TODO
}

// 15-4
void saveReport(struct Record* p[], int n){
  int m=0,f=0, empty[30],one[30],two[30];
  int six=0, seven=0, five=0, eight=0;
  int high=0;
  int room[30]={0};
	FILE* file1;
	file1 = fopen("report.txt","wt");
  for(int i=0; i<n; i++){
    if(p[i]->fm=='M') m++;
    else f++;
    if(p[i]->entry==2015) five++;
    else if(p[i]->entry==2016) six++;
    else if(p[i]->entry==2017) seven++;
    else if(p[i]->entry==2018) eight++;
    if (p[i]->point>=7) high++; 
    if (p[i]->room<200) room[p[i]->room-101]++;
    else room[p[i]->room-186]++;
  }
  fprintf(file1,"다윗관 현황 보고서\n1. 거주학생 수 : %d명 (남 %d명, 여 %d명)\n\n", f+m,m,f);
  fprintf(file1,"2. 호실 현황\n1)공실 : ");
  for(int i=0; i<n; i++){
    if(room[i]==0){
      if (i>=15) fprintf(file1,"%d ",i+186);
      else fprintf(file1,"%d ",i+101);
      }
    }
  fprintf(file1,"\n2) 1인실 : ");
  for(int i=0; i<n; i++){
    if(room[i]==1){
      if (i>=15) fprintf(file1,"%d ",i+186);
      else fprintf(file1,"%d ",i+101);
      }
    }
  
  fprintf(file1,"\n3) 2인실 : ");
  for(int i=0; i<n; i++){
    if(room[i]==2){
      if (i>=15) fprintf(file1,"%d ",i+186);
      else fprintf(file1,"%d ",i+101);
      }
    }
  fprintf(file1,"\n\n3. 학번별 현황\n");
  fprintf(file1,"1) 2015학번 : %d명\n",five);
  fprintf(file1,"2) 2016학번 : %d명\n",six);
  fprintf(file1,"3) 2017학번 : %d명\n",seven);
  fprintf(file1,"4) 2018학번 : %d명\n\n",eight);
  
  fprintf(file1,"4. 고벌점자(7점 이상) : %d명\n", high);
  for(int i=0; i<n; i++){
    if(p[i]->point>=7){
    fprintf(file1,"%s(%d) ",p[i]->name,p[i]->point);
      }
    }
  fprintf(file1,"\n\n5. 관생 목록\n");
	fprintf(file1,"NO 이름 성별 학번 호실 벌점\n");
	for(int i=0; i<n; i++){
		fprintf(file1,"%d %s [%c] %d %d %d\n", (i+1), p[i]->name, p[i]->fm, p[i]->entry, p[i]->room, p[i]->point);
	}
  
  // TODO
	fclose(file1);
  printf("저장되었습니다.\n");
  return;
}	
