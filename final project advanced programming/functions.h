#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef unsigned char BYTE;

//To save how many hits the loto form has.
typedef struct loto_arr {
	int** _parr;//Pointer to arr of pointers(SIZE 6);
	int _numofhits;//numberof hits
}LotoArr;

typedef struct loto_list
{
	struct loto_Node* head;
	struct loto_Node* tail;
	int _numoflines;
}LotoList;
typedef struct loto_Node {
	struct loto_arr _lotoArr;
	struct loto_Node* next;

}LotoNode;
typedef struct user {
	char* _name;
	LotoList _lines;
	int _totalhits;
}User;
typedef struct user_node
{
	User _player;
	struct user_node* next;
}UserNode;
typedef struct user_list {
	struct user_node* head;
	struct user_node* tail;
	int lenoflist;
}UserList;


LotoArr randLoto(int* constable);
LotoList autoLoto(int n, int* constable);
LotoList manualLoto(int n, int* constable);
LotoArr LotoFill(int* constable);

//Handle lists.
UserNode* createNewUserNode(User user, UserNode* next);
LotoNode* createNewLotoNode(LotoArr loto, LotoNode* next);
void insertDataToEndUserList(UserList* lst, User user);
void insertDataToEndLotoList(LotoList* lst, LotoArr lotoform);
void insertNodeToEndUserList(UserList* lst, UserNode* tail);
void insertNodeToEndLotoList(LotoList* lst, LotoNode* tail);
void makeEmptyUserList(UserList* lst);
void makeEmptyLotoList(LotoList* lst);
bool isEmptyUserList(UserList* lst);
bool isEmptyLotoList(LotoList* lst);

//Handle structs.
User SetUserHelper(char* name, LotoList lines);
UserList SetUsers(int n, int* constable);
LotoArr setLotoArr(int** parr, int numofhits);
char* setName();
//new functions solo
void lottoryGame(UserList* lst, int* constable, UserNode* bestuser, int* summary, LotoArr* winLoto, bool status);
void setWinsPerUser(User* player, LotoArr winningloto, int* constable, int* summary);
void SetArrofListPointers(LotoNode** arr, LotoList lst);
int printMainScreen();
//Forqsort
int CompareLotoNodeHits(void* a, void* b);
void sortList(LotoNode** arrofptr, LotoList* lst);

//endOfForqsort()

//bucket
int* totalhitsum(UserList lst);

//endofbucket
void printUserList(UserList lst, LotoArr win, UserNode* bestuser, int* summary);

// bin
void saveListToBinFile(char* file_name, UserList lst, LotoArr winningloto);
void checkFile(FILE* f);
void compressAndPrintCard(LotoArr loto, FILE* file);
void printFromBin(char* filename, int* constable);
void checkMemoryAllocation(void* ptr);
void showMenu();
void freeListOfUsers(UserList* lst);
void freeListOfLoto(LotoList* lst);
//endof bin