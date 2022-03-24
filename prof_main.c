#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata.txt"
#define STsize 1000     //size of string table
#define HTsize 100   //size of hash table

// more define variable
// main 함수에서 정의되지 않은 변수들을 전역변수 혹은 함수 내의 지역변수로 선언
int nextid, nextfree;
int hashcode;
int found;

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index;     //index of identifier in ST
    HTpointer next;  //pointer to next identifier
} HTentry;

enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;

char seperators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];

// more global variables…
ERRORtypes err;

FILE* fp;   //to be a pointer to FILE 
char input;

//Initialize - open input file
void initialize()
{
    fp = fopen(FILE_NAME, "r");
    input = fgetc(fp);
}

// Skip Seperators - skip over strings of spaces,tabs,newlines, . , ; : ? !
//         if illegal seperators,print out error message.
void SkipSeperators()
{
    //input 값이 seperators[]의 원소 중 하나와 일치하는 경우에는
    //input 값을 파일로부터 새롭게 읽어오는 반복 수행 
    //input 값이 seperators[]의 원소와 일치하지 않을 때까지
}

// PrintHStable     -      Prints the hash table.write out the hashcode and the list of identifiers 
//         associated with each hashcode,but only for non-empty lists.
//         Print out the number of characters used up in ST. ?
void PrintHStable()
{
    //HT의 값을 출력하는 함수
    //단, HT의 값이 non-empty list인 경우
    //HT의 각 원소들은 index/pointer 값을 가지는 구조체
    //HT에서 next의 값이 null 인 경우
    /*
    * 초기 상태
    * |  HT[0]  |  HT[1]  |  HT[2]  |  HT[3]  |...
    *  (0, null) (1, null) (2, null) (3, null) ...
    * 
    * hashcode의 값이 2인 entry가 추가되는 경우
    *  (0, null) (1, null) (2, addr) (3, null) ...
    *                      (index, null)
    */
}

// PrintError    -    Print out error messages
//         overst :  overflow in ST
//         print the hashtable and abort by calling the function "abort()".
//         illid    : illegal identifier
//         illsp    :illegal seperator?
void PrintError(ERRORtypes err)
{
}

//ReadIO    -    Read identifier from the input file the string table ST directly into
//         ST(append it to the previous identifier).
//         An identifier is a string of letters and digits, starting with a letter.
//         If first letter is digit, print out error message. ?
void ReadID()
{
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
        total += ST[i];
    }
    hashcode = total % HTsize +1;

    //인덱스 nid부터 nfree 까지에 해당하는 ST의 값을 읽어와서 더해준 후, HT의 크기로 나누고, +1 한 값이 hashcode
    //hashcode는 전역변수로 선언되어 있음 
}

// LookupHS    -For each identifier,Look it up in the hashtable for previous occurrence
//         of the identifier.If find a match, set the found flag as true.
//         Otherwise flase.
//         If find a match, save the starting index of ST in same id. ?
void LookupHS(int nid, int hscode)
{
    //hashcode에 해당하는 HT의 리스트를 탐색하여 해당 identifier가 이미 HT에 있는지 없는지 여부를 판단
    //판단 결과는 found 변수에 저장
}

// ADDHT   -   Add a new identifier to the hash table.
//         If list head ht[hashcode] is null, simply add a list element with
//         starting index of the identifier in ST.
//         IF list head is not a null , it adds a new identifier to the head of the chain ?
void ADDHT(int hscode)
{

    //HT에 추가되지 않은 identifier인 경우
    //index는 ST의 index, next는 null 인 새로운 HTEntry를 생성
    //기존 HT에 추가
}

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
            }
            ST[nextfree++] = '\0'; // 항상 문자 배열의 끝에는 널문자

            ComputeHS(nextid, nextfree); // hashcode 계산 (계산식은 강의노트에)
            LookupHS(nextid, hashcode); // hashcode는 ComputeHS에서 계산된 결과값
                                        // hashcode에 해당하는 리스트를 탐색

            if (!found) { // LookupHS 수행 결과, HT에서 찾은 경우는 found값을 0이 아닌 값으로 설정
                // print message
                // ST에 저장된 identifier HT 입력 여부 등 출력
                ADDHT(hashcode); // 새로운 HTentry를 추가
            }
            else {
                // print message
            }
        }
    }
    PrintHStable();
}