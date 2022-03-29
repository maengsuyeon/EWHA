#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <string.h>

#define FILE_NAME "testdata1.txt"
#define STsize 1000 //size of string table
#define HTsize 100 // size of hash table

#define FALSE 0
#define TRUE 1

//#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z') )
#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_' )
#define isDigit(x) (x>='0' && x<='9')


enum errorTypes {
    noerror, illsp, illid, overst, toolong
};
typedef enum errorTypes ERRORtypes;

char seperators[] = " .,;:?!\t\n";

typedef struct HTentry* HTpointer; //HTentry구조체를 가리키는 포인터
typedef struct HTentry {
    int index; //index of identifier in ST
    HTpointer next; //pointer to next identifier
} HTentry;


//해시테이블과 심볼테이블
HTpointer HT[HTsize];
char ST[STsize];


int nextid = 0; //the current identifier
int nextfree = 0; //the next available index of ST
int hashcode; //hash code of identifier
int sameid; //fisrt index of identifier

int found; //for the previous ocurrence of a idntifier

ERRORtypes err;

FILE* fp; 
char input; 

void initialize()
{
    fopen_s(&fp, "testdata1.txt", "r");
    input = fgetc(fp);
}

int isSeperator(char c) 
{
    int i;
    int sep_len;

    //구분자를 저장한 char배열의 길이
    sep_len = strlen(seperators);

    //해당 길이 만큼 반복하여, 배열 내에 존재하는 경우
    for (i = 0; i < sep_len; i++) {
        if (c == seperators[i]) return 1; // 구분자임
    }

    return 0; // 존재하지 않는 경우 구분자가 아님
}


void PrintHeading()
{
    printf("\n\n");
    printf("  -----------      ------------ \n");
    printf("  Index in ST       identifier  \n");
    printf("  -----------      ------------ \n");
    printf("\n");
}


void PrintHStable()
{
    int i, j;
    HTpointer here;

    printf("\n\n\n\n\n [[  HASH TABLE  ]] \n\n");

    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("  Hash Code %3d : ", i);
        }
        //HT가 null인 경우 출력하지 않음
        else {
            continue;
        }
        for (here = HT[i]; here != NULL; here = here->next) {
            j = here->index;
            while (ST[j] != '\0' && j < STsize) {
                printf("%c", ST[j++]);
                printf("      ");

            }
            printf("\n");
        }

        printf("\n\n\n < %5d characters are used in the string table > \n ", nextfree);
    }
}


void PrintError(ERRORtypes err) 
{
    switch (err) {
    case overst: //오버플로우가 발생하면, 오류문구를 출력하고 지금까지의 해시테이블 출력 후 아예종료
        printf("...Error... OVERFLOW ");
        PrintHStable();
        exit(0);
        break;
    case illsp: //허락되지 않은 구분자 사용
        printf("...Error...   %c is illegal seperator \n", input);
        break;
    case illid:
        printf("...Error...    ");
        //숫자고 문자인데도 오류인 경우 -> 여기지우면 오류
        while (input != EOF && (isLetter(input) || isDigit(input))) {
            printf("%c", input);
            input = fgetc(fp);
        }
        printf(" start with digit \n");
        break;
    case noerror:
        printf("noerror!");
        break;
    case toolong:
        printf("...Error...   ")
        for (int i = nextid; i < nextfree - 1; i++)
            printf("%c", ST[i]);
        printf("   too long identifier");
        break;
    }
}


void SkipSeperators() 
{
    // \ !(a||b) 는 !a && !b : 즉, a,b모두 아니어야함
    while (input != EOF && !(isLetter(input) || isDigit(input))) { //문자도 아니고 숫자도 아니고 마지막 글자도 아님
        if (!isSeperator(input)) { //구분자도 아니면
            err = illsp; //문자 X 숫자 X 구분자 X -> errType : 올바르지 못한 구분자
            PrintError(err); //에러로 출력
        }
        input = fgetc(fp); //다음 글자를 읽어서 반복
    }
    //문자 or 숫자이면, while loop 탈출
}


void ReadID() 
{

    //nextid : 문자가 시작하는 인덱스
    //nextfree : letter를 넣을 ST의 index 넣으면 ++되기 때문에 다넣으면 word바로 다음 빈칸을 가리킨다
    nextid = nextfree;

    //이 함수에 들어오는 input은
    // 1. 문자의 첫글자
    // 2. 숫자/문자
    // 두 조건을 만족 -> 문자/숫자가 아닌 것은 word의 첫자로 인정하지 않고 skip하므로

    //즉, 숫자로 시작하는 문자는 ST에도 들어가지않음...
    if (isDigit(input)) { //숫자인 경우 -> "숫자로 시작하는 문자"는 에러
        err = illid; // 에러 타입 지정
        PrintError(err);
    }
    else { // 문자인 경우 ( 즉, 단어의 첫글자이면서 문자로 시작하는 경우)

     //위의 if - else 문으로 word의 첫 글자가 "문자"라는 조건까지 만족
     //while문 (첫글자가 아니면 숫자도 가능하기때문에 word를 완성시키기 위해 구분자(불법 구분포함) 등장 이전까지 while)
        while (input != EOF && (isLetter(input) || isDigit(input))) {
            char id[] = "";

            //ST 테이블의 nextfree index에 글자를 삽입 ->  STsize를 초과해서 넣을 수는 없음
            if (nextfree == STsize) { //STsize를 초과해서 넣을 수는 없음
                err = overst; // 오버플로우 에러
                PrintError(err);
                //여기에 break필요없나?!->아 overflow면 PrintError에서 exit됨
            }

            //오버 플로우만 아니면, ST에 입력받은 input을 넣어줌
            ST[nextfree++] = input; //ST에 넣어줌.
            input = fgetc(fp);  //다음 letter를 읽어서 구분자(불법구분자 포함)이 나올때 까지 반복
        }
        //구분자가 등장하기 이전까지 한 word를 한자씩 읽어와서 ST에 저장해둠
    }
}


void ComputeHS(int nid, int nfree) 
{ 
    //nid : word의 첫 시작 index , nfree : word의 마지막 letter + 1 index(공백저장됨)
        int total = 0;
        for (int i = nid; i < nfree; i++) {
            total += (int)ST[i];
        }
    hashcode = total % HTsize + 1;

    //인덱스 nid부터 nfree 까지에 해당하는 ST의 값을 읽어와서 더해준 후, HT의 크기로 나누고, +1 한 값이 hashcode
    //hashcode는 전역변수로 선언되어 있음 
}


void LookupHS(int nid, int hscode)
{
    HTpointer here = HT[hscode];
    int x = 0;
    if (here + x != NULL) {
        int i = nid;
        int j = here->index;
        while (ST[i] != '\0') {
            if (ST[j] != ST[i]) {
                found = FALSE;
                break;
            }
            found = TRUE;
            i++;
            j++;
        }
        x++;
        here = here->next;
    }

    else {
        found = FALSE;
    }
    //hashcode에 해당하는 HT의 리스트를 탐색하여 해당 identifier가 이미 HT에 있는지 없는지 여부를 판단
    //판단 결과는 found 변수에 저장
}

// 생성된 HTpointer 객체의 필드에 데이터 삽입 및 객체 삽입
void ADDHT(int hscode) 
{
    HTpointer ptr;
    ptr = (HTpointer)malloc(sizeof(HTentry));
    ptr->index = nextid;
    ptr->next = HT[hscode];
    HT[hscode] = ptr;
}


int main() 
{
    int i;
    PrintHeading();
    initialize();

    while (input != EOF) {

        err = noerror;//디폴트로 "noerror:에러가 아님"
        SkipSeperators();

        ReadID();

        // if(nextfree - nextid >12){
        //     err = toolong;
        //     PrintError(err);
        // }

        if (input != EOF && err != illid) {

            if (nextfree == STsize) {
                err = overst;
                PrintError(err);
            }

            ST[nextfree++] = '\0'; //한 덩어리 끝

            ComputeHS(nextid, nextfree);
            LookupHS(nextid, hashcode);
            HTpointer ptr;
            ptr = (HTpointer)malloc(sizeof(HTentry));
            if

            if (!found) { // LookupHS 수행 결과, HT에서 찾은 경우는 found값을 0이 아닌 값으로 설정
                printf("%10d      ", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("      (entered.)\n");
                ADDHT(hashcode); // 새로운 HTentry를 추가
                free(ptr);
            }

            else {
                printf("%6d      ", sameid);
                for (i = nextid; i < nextfree; i++)
                    printf("%c", ST[i]);
                printf("      (already existed)\n");
                nextfree = nextid;
            }
            free(ptr);
        }
    }

    PrintHStable();
}
