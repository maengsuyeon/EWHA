#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata.txt"

#define STsize 1000  //size of string table
#define HTsize 100	//size of hash table

#define FALSE 0
#define TRUE 1

#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_' )
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )

typedef struct HTentry *HTpointer;
typedef struct HTentry {
  int index;  //index of identifier in ST
  HTpointer next;  //pointer to next identifier
} HTentry;

enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;

char seperators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0;  //the current identifier
int nextfree = 0;  //the next available index of ST
int hashcode;  //hash code of identifier
int sameid;  //first index of identifier

int found;  //for the previous occurrence of an identifie

ERRORtypes err;

FILE *fp;   //to be a pointer to FILE 
char input;

//Initialize - open input file

void initialize()
{
  fp = fopen("testdata1.txt", "r");
  input = fgetc( fp );
}


//isSerperator  -  distinguish the seperator
int isSeperator(char c) 
{
  int i;
  int sep_len;

  sep_len = strlen(seperators);
  for( i = 0 ; i < sep_len; i++ ) {
    if( c == seperators[i] )
      return 1;
  }
  return 0;
}

//printHeading	 -		Print the heading

void PrintHeading()
{
  printf("\n\n");
  printf("  -----------      ------------ \n");
  printf("  Index in ST       identifier  \n");
  printf("  -----------      ------------ \n");
  printf("\n");
}


// Skip Seperators - skip over strings of spaces,tabs,newlines, . , ; : ? !
//         if illegal seperators,print out error message.


// PrintHStable     -      Prints the hash table.write out the hashcode and the list of identifiers 
//         associated with each hashcode,but only for non-empty lists.
//         Print out the number of characters used up in ST. ?
void PrintHStable()
{
    int i, j;
    HTpointer here;

    printf("\n\n\n\n\n [[  HASH TABLE  ]] \n\n");

    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("  Hash Code %3d : ", i);
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

// PrintError    -    Print out error messages
//         overst :  overflow in ST
//         print the hashtable and abort by calling the function "abort()".
//         illid    : illegal identifier
//         illsp    :illegal seperator?
void PrintError(ERRORtypes err)
{   switch (err) {
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
    //input 값이 seperators[]의 원소 중 하나와 일치하는 경우에는
    //input 값을 파일로부터 새롭게 읽어오는 반복 수행 
    //input 값이 seperators[]의 원소와 일치하지 않을 때까지
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

    // 입력 파일로부터 identifier를 읽어와서 ST에 저장
    // identifier가 유효한가를 따지기 위해 input이 영어 알파벳 대소문자인지/숫자인지/_인지를 판단하여야 함

    // 이 때 ST에 저장하는 시작위치 nextid
    // ST에 저장되고 그 다음 빈 공간의 위치 nextfree
}

// ComputeHS    - Compute the hash code of identifier by summing the ordinal values of its
//           characters and then taking the sum modulo the size of HT. 
void ComputeHS(int nid, int nfree)
{
    int total = 0;
    for(int i = nid; i < nfree; i++){
        total += (int)ST[i];
    }
    hashcode = total % HTsize +1;

    //인덱스 nid부터 nfree 까지에 해당하는 ST의 값을 읽어와서 더해준 후, HT의 크기로 나누고, +1 한 값이 hashcode
    //hashcode는 전역변수로 선언되어 있음 
}

void LookupHS(int nid, int hscode)
{
    HTpointer here;
    if (HT[hscode] != NULL) {
        here = HT[hscode];
        int i = nid;
        int j = here->index;

        while(ST[i] != '\0'){
            if (ST[j] != ST[i]){
                found = FALSE;
                break;
            }

            found = TRUE;
            i++;
            j++;
        }
        here = here->next;
    }

    else { 
        found = FALSE;
    }
    //hashcode에 해당하는 HT의 리스트를 탐색하여 해당 identifier가 이미 HT에 있는지 없는지 여부를 판단
    //판단 결과는 found 변수에 저장
}


void ADDHT(int hscode) {
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr));
    ptr->index = nextid;
    ptr->next = HT[hscode];
    HT[hscode] = ptr;

    free(ptr);
}

    // HT에 추가되지 않은 identifier인 경우
    // index는 ST의 index, next는 null 인 새로운 HTEntry를 생성
    // 기존 HT에 추가


/*  MAIN   -   Read the identifier from the file directly into ST.
Compute its hashcode.
Look up the idetifier in hashtable HT[hashcode]
If matched, delete the identifier from STand print ST - index
of the matching identifier.
If not matched, add a new element to the list, pointing to new identifier.
Print the identifier, its index in ST, and whether it was entered or present.
Print out the hashtable, and number of characters used up in ST
*/

int main()
{
    int i;
    PrintHeading(); // 헤더 부분 단순 출력 함수
    initialize(); // 입력 파일 open && 입력 파일로부터 첫번째 값을 읽어와서 input에 저장

    while (input != EOF) { // EOF = end of file
        err = noerror; // err는 프로그램 수행 도중 발생하는 에러 구분을 위해 사용하는 변수. 초기값은 에러 없음으로 설정
        SkipSeperators(); // input값을 하나씩 읽어오는데, delimiter인 경우 skip
        ReadID(); // 다음 delimiter가 나타날 때까지 identifier 읽어오기. 읽어 온 identifier는 ST에 저장
                  // nextid, nextfree 값이 이 때 설정
        if (input != EOF && err != illid) { // illegal identifier가 아닌 경우 hashcode 계산 후 lookup
            if (nextfree == STsize) { //nextid와 nextfree는 ST의 인덱스
                // ST에 대한 overflow 발생
                // print error message
                err = overst;
                PrintError(err);
            }

            ST[nextfree++] = '\0'; // 항상 문자 배열의 끝에는 널문자

            ComputeHS(nextid, nextfree); // hashcode 계산 (계산식은 강의노트에)
            LookupHS(nextid, hashcode); // hashcode는 ComputeHS에서 계산된 결과값
                                        // hashcode에 해당하는 리스트를 탐색
            if (!found) { // LookupHS 수행 결과, HT에서 찾은 경우는 found값을 0이 아닌 값으로 설정
                printf("%10d      ", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("      (entered.)\n");
                ADDHT(hashcode); // 새로운 HTentry를 추가
            }
            else {
                // print message
                printf("%10d      ", sameid); //이미 있으므로 이미 존재하는 것의 index를 출력함
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                printf("      (already existed.)\n");
                nextfree = nextid;
            }
        }
    }
    PrintHStable();
}