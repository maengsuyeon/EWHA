#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata.txt"
#define STsize 1000     //size of string table
#define HTsize 100   //size of hash table

// more define variables��
// main �Լ����� ���ǵ��� ���� �������� �������� Ȥ�� �Լ� ���� ���������� ����
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

// more global variables��
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
    //input ���� seperators[]�� ���� �� �ϳ��� ��ġ�ϴ� ��쿡��
    //input ���� ���Ϸκ��� ���Ӱ� �о���� �ݺ� ���� 
    //input ���� seperators[]�� ���ҿ� ��ġ���� ���� ������
}

// PrintHStable     -      Prints the hash table.write out the hashcode and the list of identifiers 
//         associated with each hashcode,but only for non-empty lists.
//         Print out the number of characters used up in ST. ?
void PrintHStable()
{
    //HT�� ���� ����ϴ� �Լ�
    //��, HT�� ���� non-empty list�� ���
    //HT�� �� ���ҵ��� index/pointer ���� ������ ����ü
    //HT���� next�� ���� null �� ���
    /*
    * �ʱ� ����
    * |  HT[0]  |  HT[1]  |  HT[2]  |  HT[3]  |...
    *  (0, null) (1, null) (2, null) (3, null) ...
    * 
    * hashcode�� ���� 2�� entry�� �߰��Ǵ� ���
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
    // �Է� ���Ϸκ��� identifier�� �о�ͼ� ST�� ����
    // identifier�� ��ȿ�Ѱ��� ������ ���� input�� ���� ���ĺ� ��ҹ�������/��������/_������ �Ǵ��Ͽ��� ��

    // �� �� ST�� �����ϴ� ������ġ nextid
    // ST�� ����ǰ� �� ���� �� ������ ��ġ nextfree
}

// ComputeHS    - Compute the hash code of identifier by summing the ordinal values of its
//           characters and then taking the sum modulo the size of HT. 
void ComputeHS(int nid, int nfree)
{
    //�ε��� nid���� nfree ������ �ش��ϴ� ST�� ���� �о�ͼ� ������ ��, HT�� ũ��� ������, +1 �� ���� hashcode
    //hashcode�� ���������� ����Ǿ� ���� 
}

// LookupHS    -For each identifier,Look it up in the hashtable for previous occurrence
//         of the identifier.If find a match, set the found flag as true.
//         Otherwise flase.
//         If find a match, save the starting index of ST in same id. ?
void LookupHS(int nid, int hscode)
{
    //hashcode�� �ش��ϴ� HT�� ����Ʈ�� Ž���Ͽ� �ش� identifier�� �̹� HT�� �ִ��� ������ ���θ� �Ǵ�
    //�Ǵ� ����� found ������ ����
}

// ADDHT   -   Add a new identifier to the hash table.
//         If list head ht[hashcode] is null, simply add a list element with
//         starting index of the identifier in ST.
//         IF list head is not a null , it adds a new identifier to the head of the chain ?
void ADDHT(int hscode)
{
    //HT�� �߰����� ���� identifier�� ���
    //index�� ST�� index, next�� null �� ���ο� HTEntry�� ����
    //���� HT�� �߰�
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
    PrintHeading(); // ��� �κ� �ܼ� ��� �Լ�
    initialize(); // �Է� ���� open && �Է� ���Ϸκ��� ù��° ���� �о�ͼ� input�� ����

    while (input != EOF) { // ������ ������ �ݺ�
        err = noerror; // err�� ���α׷� ���� ���� �߻��ϴ� ���� ������ ���� ����ϴ� ����. �ʱⰪ�� ���� �������� ����
        SkipSeperators(); // input���� �ϳ��� �о���µ�, delimiter�� ��� skip
        ReadID(); // ���� delimiter�� ��Ÿ�� ������ identifier �о����. �о� �� identifier�� ST�� ����
                  // nextid, nextfree ���� �� �� ����
        if (input != EOF && err != illid) { // illegal identifier�� �ƴ� ��� hashcode ��� �� lookup
            if (nextfree == STsize) { //nextid�� nextfree�� ST�� �ε���
                // ST�� ���� overflow �߻�
                // print error message
            }
            ST[nextfree++] = '\0'; // �׻� ���� �迭�� ������ �ι���

            ComputeHS(nextid, nextfree); // hashcode ��� (������ ���ǳ�Ʈ��)
            LookupHS(nextid, hashcode); // hashcode�� ComputeHS���� ���� �����
                                        // hashcode�� �ش��ϴ� ����Ʈ�� Ž��

            if (!found) { // LookupHS ���� ���, HT���� ã�� ���� found���� 0�� �ƴ� ������ ����
                // print message
                // ST�� ����� identifier HT �Է� ���� �� ���
                ADDHT(hashcode); // ���ο� HTentry�� �߰�
            }
            else {
                // print message
            }
        }
    }
    PrintHStable();
}