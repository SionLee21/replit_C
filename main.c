#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char GRADE[3][10]={"Deluxe", "Luxury", "Suite"}; // 객실등급 명칭 

struct st_card{		// 객실 관리 카드 레코드
	int no;		// 객실번호 (3자리 숫자)
	int grade; // 객실 등급 (1:deluxe, 2:luxury, 3:suite)
	int capa;		// 수용최대인원 (2~10명)
	char name[20];	// 예약자 성명				
	int person;		// 예약 인원
};

int loadCards(struct st_card* p[]);		// 객실정보 읽기
void listCards(struct st_card* p[], int n);	// 객실 목록 출력
void makeReserve(struct st_card* p[], int n);		// 객실 예약
void cancelReserve(struct st_card* p[], int n);	// 예약 취소
void findCards(struct st_card* p[], int n);	// 객실 검색
void saveReport(struct st_card* p[], int n);	// 보고서 저장
void findRoom(struct st_card* p[], int n);	// 빈 객실 찾기
int addCards(struct st_card* p[], int n);	// 객실 추가 

int main(){
	struct st_card* cards[50]; 	// 최대 50개의 객실을 관리할 수 있는 구조체 포인터 배열
	int count;	// 현재 등록된 카드 수
	int menu;	// 메뉴번호
	count = loadCards(cards);	// 시작 전에 파일로부터 객실 리스트를 모두 읽어온다.
	while(1)
	{
		// 메뉴 출력
		printf("\n[1]객실목록 [2]예약 [3]예약취소 [4]검색 [5]저장 [6]빈객실찾기 [7]객실추가 [0]종료 >> ");
		scanf("%d",&menu);	// 메뉴를 읽음

		if(menu==1){
			listCards(cards, count);	// 객실 목록 출력
		}
		else if(menu==2){
			makeReserve(cards, count);	// 예약하기
		}
		else if(menu==3){
			cancelReserve(cards, count); // 예약 취소
		}
		else if(menu==4){
			findCards(cards, count);	// 검색
		}
		else if(menu==5){
			saveReport(cards, count);	// 보고서 저장
		}
		else if(menu==6){
			findRoom(cards, count);	// 빈 객실 찾기
		}
		else if(menu==7){
			count = addCards(cards, count);	// 객실 추가
		}
		else {
			break;
		}
	}
}

int loadCards(struct st_card* p[]){
	FILE *file;
	int n=0;
	file = fopen("rooms.txt","r");
	while(!feof(file)){
		p[n]=(struct st_card*)malloc(sizeof(struct st_card));
		int result = fscanf(file,"%d %d %d",&(p[n]->no),&(p[n]->grade),&(p[n]->capa));
		if (result < 1) break;
		n++;
	}
	fclose(file);
	printf("%d개의 객실 정보를 읽었습니다.\n",n);
	return n;
}

void listCards(struct st_card * p[], int n){
	int i;
	printf("\n전체 객실 목록입니다.\n");
	printf("객실번호 / 등급 / 최대인원 / 예약상황\n");
	
	for(i=0; i<n; i++){
		printf("%d호 / %s / %d명 / ", p[i]->no, GRADE[p[i]->grade-1], p[i]->capa);
		if(p[i]->person > 0)
			printf("예약 : %s %d명\n",p[i]->name, p[i]->person);
		else
			printf("예약없음\n");
	}
}

// 15-5
void makeReserve(struct st_card* p[], int n){
	char name[20];
	struct st_card* rp; // 예약할 카드레코드 구조체의 포인터값
	int i, roomno, newperson,test=0;

	printf("예약하실 고객 이름은? >> ");
	scanf("%s", name);
	printf("예약 인원수를 입력하시오. >> ");
	scanf("%d", &newperson);

  while(1){
  	printf("예약하실 객실 번호는? >> ");
  	scanf("%d", &roomno);
  	
  	for(i=0;i<n;i++){
  		if(p[i]->no==roomno){
  			rp=p[i];
        test=1;
  			break;
  		}
  	}
    if(test==1){
      if(rp->person!=0){
        printf("예약불가(예약된 객실)\n");
      }
      else if(rp->capa<newperson)
        printf("예약불가(인원 초과)\n");
      else{
      	rp->person = newperson;
      	strcpy(rp->name, name);
      	printf("예약완료!\n");
        break;
        }
      test=0;
      }
    else printf("예약불가(객실번호 오류)\n");
  }
}

// 15-6
void cancelReserve(struct st_card* p[], int n){
  int i,yn, roomno, newperson,test=0;
  struct st_card* rp;
  printf("예약 취소하실 객실 번호는? >> ");
  scanf("%d", &roomno);
  	for(i=0;i<n;i++){
  		if(p[i]->no==roomno&&p[i]->person!=0){
  			rp=p[i];
        test=1;
  			break;
  		}
  	}
   if(test==1){
     printf("객실번호 / 등급 / 예약자 / 예약인원\n");
     printf("%d호 / %s / %s / %d명\n", rp->no,GRADE[rp->grade-1],rp->name,rp->person);
     printf("위 예약을 취소할까요? (YES 1, NO 0) >> ");
     scanf("%d",&yn);
     test=0;
     if(yn==1){
       printf("취소했습니다.\n");
       rp->person=0;
     }
     else return;
    }
  else printf("예약된 객실이 아닙니다.\n");
}

// 15-7
void findCards(struct st_card * p[], int n){
	int i, count=0;
	char name[20];
	while(1){
		printf("검색하려는 고객 이름을 2글자 이상 입력하세요. >> ");
		scanf("%s", name);
		if(strlen(name) > 1) break;
	}
	printf("객실번호 / 등급 / 예약자 / 예약인원 / 최대인원\n");
  for (int i=0; i<n; i++){
  if(strstr(p[i]->name,name)){
    count++;
    printf("%d호 / %6s / %s / %d명 / %d명\n", p[i]->no,GRADE[p[i]->grade-1],p[i]->name,p[i]->person,p[i]->capa);
    }
  }
  printf("%d명 검색됨\n",count);
}
// 15-8
void saveReport(struct st_card* p[], int n){
  FILE* file1;
	file1 = fopen("rooms_report.txt","wt");
  int lux[4]={0},del[4]={0},sui[4]={0},total=0; //lux[0]=총 방의 개수, lux[1]=예약된 방 개수, lux[2]=예약 고객 수, lux[3]=남은 최대수용 고객
  for(int i=0; i<n; i++){
    if(p[i]->grade==1){
      del[0]++;
      if(p[i]->person!=0){
        del[1]++;
        del[2]+=p[i]->person;
        }
      else del[3]+=p[i]->capa;
      }
    else if(p[i]->grade==2){
      lux[0]++;
      if(p[i]->person!=0){
        lux[1]++;
        lux[2]+=p[i]->person;
        }
      else lux[3]+=p[i]->capa;
    }
    else if(p[i]->grade==3){
      sui[0]++;
      if(p[i]->person!=0){
        sui[1]++;
        sui[2]+=p[i]->person;
        }
      else sui[3]+=p[i]->capa;
    }
  }
  fprintf(file1,"객실 현황 보고서\n\n");
  fprintf(file1,"객실등급 : Deluxe\n1. 객실 수 : 총 %d실 중 %d실 예약 중\n2. 예약 고객 : 총 %d명\n3. 남은 최대수용 고객 : 총 %d명\n\n",del[0],del[1],del[2],del[3]);
  fprintf(file1,"객실등급 : Luxury\n1. 객실 수 : 총 %d실 중 %d실 예약 중\n2. 예약 고객 : 총 %d명\n3. 남은 최대수용 고객 : 총 %d명\n\n",lux[0],lux[1],lux[2],lux[3]);
  fprintf(file1,"객실등급 : Suite\n1. 객실 수 : 총 %d실 중 %d실 예약 중\n2. 예약 고객 : 총 %d명\n3. 남은 최대수용 고객 : 총 %d명\n\n",sui[0],sui[1],sui[2],sui[3]);
  fprintf(file1,"객실 예약 목록\n객실번호 / 등급 / 최대인원 / 예약상황\n");
  for(int i=0; i<n; i++){
		fprintf(file1,"%d호 / %s / %d명 / ", p[i]->no, GRADE[p[i]->grade-1], p[i]->capa);
		if(p[i]->person > 0)
			fprintf(file1,"예약 : %s %d명\n",p[i]->name, p[i]->person);
		else
			fprintf(file1,"예약없음\n");
	}
  fprintf(file1,"예약 인원 합계 : %d명", del[2]+lux[2]+sui[2]);
	fclose(file1);
  printf("저장되었습니다.\n");
  return;
}	

//15-9
void findRoom(struct st_card* p[], int n){
  int person,grade,count=0,rgrade;
  printf("투숙 인원수는? >> ");
  scanf("%d",&person);
  printf("원하시는 객실 등급은? (Deluxe 1, Luxury 2. Suite 3, 무관 0) >> ");
  scanf("%d",&grade);
  printf("객실번호 / 등급 / 최대인원\n");
  for(int i=0; i<n; i++){
    if(p[i]->person==0&&p[i]->capa>=person&&(p[i]->grade>=grade||grade==0)){
      count++;
      printf("%d호 / %s / %d명\n", p[i]->no, GRADE[p[i]->grade-1], p[i]->capa);
      }
    }
  printf("총 %d개의 객실이 예약 가능합니다.\n", count);
}

// 15-10
int addCards(struct st_card* p[], int n){
  int roomno,grade,capa,test=0;
  while(test==0){
    printf("추가할 객실번호는? >> ");
    scanf("%d",&roomno);
    for(int i=0; i<n; i++){
      if(p[i]->no==roomno){
        printf("이미 등록된 객실번호입니다.\n");
        break;
        }

     else if((p[i+1]->no!=roomno)&&(p[i]->no==roomno-1||p[i]->no==roomno+1)){
      printf("객실등급(Deluxe 1, Luxury 2. Suite 3)과 최대인원을 입력하세요 >> ");
      scanf("%d %d",&grade,&capa);
      p[n]->no=roomno;
      p[n]->grade=grade;
      p[n]->capa=capa;
      test=1;
      break;
      }
    else if(i==n-1&&(p[i]->no!=roomno-1||p[i]->no!=roomno+1)){
      printf("연속적인 객실번호가 아닙니다.\n");
      break;
      }
    }
  }  
  printf("객실을 추가하였습니다.\n");
	return n+1;
}