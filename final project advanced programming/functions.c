#include "functions.h"
//List functions.
void insertDataToEndUserList(UserList* lst, User user)
{
	UserNode* newtail;
	newtail = createNewUserNode(user, NULL);
	insertNodeToEndUserList(lst, newtail);
}
void insertDataToEndLotoList(LotoList* lst, LotoArr lotoform)
{
	LotoNode* newtail;
	newtail = createNewLotoNode(lotoform, NULL);
	insertNodeToEndLotoList(lst, newtail);
}
void insertNodeToEndUserList(UserList* lst, UserNode* tail)
{
	if (isEmptyUserList(lst))
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}
void insertNodeToEndLotoList(LotoList* lst, LotoNode* tail)
{
	if (isEmptyLotoList(lst))
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
	lst->_numoflines++;
}
void makeEmptyUserList(UserList* lst)
{
	lst->head = lst->tail = NULL;
}
void makeEmptyLotoList(LotoList* lst)
{
	lst->head = lst->tail = NULL;
}
UserNode* createNewUserNode(User user, UserNode* next)
{
	UserNode* res;
	res = (UserNode*)malloc(sizeof(UserNode));
	checkMemoryAllocation(res);
	res->_player._name = user._name;
	res->_player._lines = user._lines;
	res->_player._totalhits = user._totalhits;
	res->next = next;
	return res;
}
LotoNode* createNewLotoNode(LotoArr loto, LotoNode* next)
{
	LotoNode* res;
	res = (LotoNode*)malloc(sizeof(LotoNode));
	checkMemoryAllocation(res);
	res->next = next;
	res->_lotoArr._numofhits = loto._numofhits;
	res->_lotoArr._parr = loto._parr;
	return res;
}
bool isEmptyUserList(UserList* lst)
{
	return (lst->head == NULL);
}
bool isEmptyLotoList(LotoList* lst)
{
	return (lst->head == NULL);
}

//handle structs
/*
* This function is a subfunction to set the single user data
* @parm char* name - > the name of the user
* @parm LotoList  lines -> a List of the tors that the user has.
* @return User .
*/
User SetUserHelper(char* name, LotoList lines)
{
	User user;
	user._name = (char*)malloc(sizeof(char) * (strlen(name)));
	checkMemoryAllocation(name);
	strcpy(user._name, name);
	user._lines = lines;
	user._totalhits = 0;
	return user;
}
/*
* This function Set the data of of the struct LotoARR
* @parm int** parr -> An arr of pointers to the numbers.
* @parm int numof hits - > the amount of the hits that the loto arr hit.
* @return LotoARR.
*/
LotoArr setLotoArr(int** parr, int numofhits)
{
	LotoArr lotolist;
	lotolist._parr = parr;
	lotolist._numofhits = numofhits;
}

// Fill loto functions
/*
* This function random loto tor
* @parm int* constable -> the table of numbers 1-15
* @return Loto ARR.
*/
LotoArr randLoto(int* constable)
{
	LotoArr loto;
	int num;
	int** arr = (int**)malloc(sizeof(int*) * 6);
	checkMemoryAllocation(arr);
	bool helper[16];
	int counter = 0;
	while (counter < 6)
	{
		num = 1 + rand() % 15;
		if (helper[num])
		{
			helper[num] = false;
			arr[counter] = constable + num - 1;
			counter++;
		}

	}
	loto._numofhits = 0;
	loto._parr = arr;
	return loto;
}
/*
* This function handle an automate loto fill .
* @parm int n -> the number of tors .
* @parm int* constable -> the table of numbers 1-15
* @return LotoList.
*/
LotoList autoLoto(int n, int* constable)
{
	LotoList list;
	makeEmptyLotoList(&list);
	int i;
	LotoArr data;
	for (i = 0; i < n; i++)
	{
		data = randLoto(constable);
		insertDataToEndLotoList(&list, data);
	}
	list._numoflines = n;
	return list;
}
/*
* This function handle the manual fill of loto tors.
* @parm int n -> the number of the tors.
* @parm int* constable the table of numbers 1-15
* @return LotoList.
*/
LotoList manualLoto(int n, int* constable)
{
	LotoList list;
	int i;
	LotoArr data;
	makeEmptyLotoList(&list);

	for (i = 0; i < n; i++)
	{
		data = LotoFill(constable);
		insertDataToEndLotoList(&list, data);
		if (i < n - 1)
			printf("Next Row:\n");
	}
	list._numoflines = n;
	return list;
}
/*
* This is a subfunction for namualLoto functions ,the function handle the inputs from the user.
* @parm int* constable the table of numbers 1-15
* @return LotoArr.
*/
LotoArr LotoFill(int* constable)
{
	LotoArr loto;
	int num = 0;
	int** arr = (int**)malloc(sizeof(int*) * 6);
	checkMemoryAllocation(arr);
	bool helper[16];
	int counter = 0;
	while (counter < 6)
	{
		printf("Enter a number:");
		scanf("%d", &num);
		if (helper[num] && (num <= 15 && num >= 1))
		{
			helper[num] = false;
			arr[counter] = constable + num - 1;
			counter++;
		}
		else
		{
			printf("Enter a vailid number or do not use the same number twice\n");
		}

	}
	loto._numofhits = 0;//No need for hits.
	loto._parr = arr;
	return loto;
}
/*
* This function take a place of the Main function to handle the setup of n users , and create a list of those users.
* @parm n -> number of users.
* @parm int* constable -> the table of numbers 1-15
* @parm LotoArr* win -> a pointer to a winning tor.
* @return UserList.
*/

UserList SetUsers(int n, int* constable)
{
	UserList lst;
	User user;
	int i;
	int numOfLines;
	int userchoise;
	char* name;
	LotoList lotolist;

	makeEmptyUserList(&lst);
	for (i = 0; i < n; i++)
	{
		printf("name of user:\n");
		getchar();
		name = setName();
		printf("1-auto or 2-manual\n");//print to user;
		scanf("%d", &userchoise);
		printf("howmany\n");
		scanf("%d", &numOfLines);
		if (userchoise == 1)
		{
			lotolist = autoLoto(numOfLines, constable);
		}
		else
			lotolist = manualLoto(numOfLines, constable);

		lotolist._numoflines = numOfLines;
		user = SetUserHelper(name, lotolist);
		free(name);
		insertDataToEndUserList(&lst, user);
	}
	return lst;

}
/*
* This is a void function that serve as main function of the game .
*brief : Set the wins per user , sort the tors by num of hits ,create a winning tor,find the best player.
* @parm UserList* lst - > a pointer to filled lst of users.
* @parm int* constable -> the table of numbers 1-15
* @parm bool status -> If to rand one single winning loto or not.
* @parm UserNode* bestpuser -> output parmeter that return the player with the best avarge .
*/
void lottoryGame(UserList* lst, int* constable, UserNode* bestuser, int* summary, LotoArr* winLoto, bool status)
{
	LotoArr winningloto;
	if (status)
		winningloto = randLoto(constable);
	else
	{
		winningloto = *winLoto;
	}
	UserNode* curr = lst->head;
	UserNode* topuser = &lst->head->_player;
	float maxavg = 0;
	int(*comparehelper)(void*, void*);
	comparehelper = CompareLotoNodeHits;
	while (curr != NULL)
	{
		setWinsPerUser(&curr->_player, winningloto, constable, summary);
		if ((float)curr->_player._totalhits / (float)curr->_player._lines._numoflines > maxavg)
		{
			topuser = curr;
			maxavg = ((float)curr->_player._totalhits / (float)curr->_player._lines._numoflines);
		}
		LotoNode** arrofptr = (LotoNode**)malloc(sizeof(LotoNode*) * (curr->_player._lines._numoflines));
		checkMemoryAllocation(arrofptr);
		SetArrofListPointers(arrofptr, curr->_player._lines);
		qsort(arrofptr, curr->_player._lines._numoflines, sizeof(LotoNode*), comparehelper);
		sortList(arrofptr, &curr->_player._lines);
		free(arrofptr);
		curr = curr->next;
	}
	*bestuser = *topuser;
	*winLoto = winningloto;

}
/*
* This function set the wins for each player.
* @parm User* player -> the player we want to set his winning.
* @parm LotoArr winningloto -> the winning tor that we check match with.
* @parm int* constable -> the table of numbers 1-15
*/
void setWinsPerUser(User* player, LotoArr winningloto, int* constable, int* summary)//
{
	LotoNode* curr = player->_lines.head;
	bool helper[16];
	int i;
	for (i = 0; i < 6; i++)
		helper[*winningloto._parr[i]] = false;
	while (curr != NULL)
	{
		for (i = 0; i < 6; i++)
		{
			if (!helper[*(curr->_lotoArr._parr[i])])
			{
				curr->_lotoArr._numofhits++;
				player->_totalhits++;
			}
		}
		summary[curr->_lotoArr._numofhits]++;
		curr = curr->next;
	}
}

void printUserList(UserList lst, LotoArr win, UserNode* bestuser, int* summary)
{
	int i;
	UserNode* curr = lst.head;
	LotoNode* lotoarr = curr->_player._lines.head;
	printf("The Winning Loto is:\n");
	for (i = 0; i < 6; i++) {
		printf("%d ", **(win._parr + i));
	}
	printf("\n");
	while (curr != NULL)
	{
		printf("USER: %s\n", curr->_player._name);
		while (lotoarr != NULL)
		{
			printf("total hit for this line : %d\n", lotoarr->_lotoArr._numofhits);//new nuriel for test.
			for (i = 0; i < 6; i++)
			{
				printf("%d ", **(lotoarr->_lotoArr._parr + i));
			}
			printf("\n");
			lotoarr = lotoarr->next;
		}
		curr = curr->next;
		if (curr != NULL)
			lotoarr = curr->_player._lines.head;
	}
	printf("Summary of All Hits:\n");
	for (i = 0; i < 7; i++)
	{
		printf("num of rows with %d hits:%d\n", 6 - i, summary[6 - i]);
	}

	printf("User with The Best Average of HITS:\n");
	printf("%s\n", bestuser->_player._name);

}
/*
* This is a void function that set an arr of pointer to the list nodes.
* @parm LotoNode** arr -> an arr of pointers to the LotoList nodes.
* @parm LotoList lst -> the list with the data.
*/
void SetArrofListPointers(LotoNode** arr, LotoList lst)
{
	int i = 0;
	LotoNode* curr = lst.head;
	while (curr != NULL)
	{
		arr[i] = curr;
		i++;
		curr = curr->next;
	}
}
/*
* This is a generic function that serve as compare function for Qsort.
* This function compare by the num of hits.
* @parm void* a -> some pointer to data.
* @parm void* b-> some pointer to data.
* return int.((neg number if the data we compare in b is bigger then the data we compare in a || pos number  if the data we compare in a is bigger then the data we compare in b))
*/
int CompareLotoNodeHits(void* a, void* b)
{
	int na;
	int nb;
	LotoNode** _a = (LotoNode**)a;
	LotoNode** _b = (LotoNode**)b;
	nb = (_b[0]->_lotoArr._numofhits);
	na = (_a[0]->_lotoArr._numofhits);
	return ((nb - na));
}
/*
* This is a void function that sort the list.
* @parm LotoNode** arrofptr -> arr of pointers to LotoNode* sorted by numofhits.
* @parm LotoList* lst -> the lst we set as sorted.
*/
void sortList(LotoNode** arrofptr, LotoList* lst)
{
	if (isEmptyLotoList(lst))
		return;
	int i = 0;
	lst->head = arrofptr[0];
	LotoNode* curr = lst->head;

	for (i = 1; i < lst->_numoflines; i++)
	{
		curr->next = arrofptr[i];
		curr = curr->next;
	}
	curr->next = NULL;
	lst->tail = curr;
}
/*24.12.2021*/
/*
* This function handle the summarize of tors by numof hits.
* the summarize work by Bucket Sort alguritem.
* @parm UserList lst -> the list we get the data of hits from.
* @return int* -> arr of counters Size 7.
*/
int* totalhitsum(UserList lst)
{
	int* bucket = (int*)calloc(7, sizeof(int));
	UserNode* currUsr = lst.head;
	LotoNode* currLotoNode = currUsr->_player._lines.head;
	while (currUsr != NULL)
	{
		while (currLotoNode != NULL)
		{

			bucket[currLotoNode->_lotoArr._numofhits]++;
			currLotoNode = currLotoNode->next;
		}
		currUsr = currUsr->next;
	}

	return bucket;
}
/*
* This is  avoid function that play as the main function To save the binary file .
* @parm char* file_name -> the name that user want to call to the binary file.
* @parm UserList lst -> the list of users that we want to write on the binary file.
* @parm LotoArr  winningloto -> the winning loto.
*/
void saveListToBinFile(char* file_name, UserList lst, LotoArr winningloto)
{
	FILE* file = fopen(file_name, "wb");
	checkFile(file);
	fwrite(&lst.lenoflist, sizeof(int), 1, file);
	int i;
	int lenofname;
	UserNode* curr = lst.head;
	LotoNode* currlotonode;
	for (i = 0; i < lst.lenoflist; i++)
	{
		lenofname = strlen(curr->_player._name);
		fwrite(&lenofname, sizeof(int), 1, file);
		fwrite(curr->_player._name, sizeof(char), lenofname, file);
		fwrite(&curr->_player._lines._numoflines, sizeof(int), 1, file);
		currlotonode = curr->_player._lines.head;
		while (currlotonode != NULL)
		{
			compressAndPrintCard(currlotonode->_lotoArr, file);
			currlotonode = currlotonode->next;
		}
		curr = curr->next;

	}
	compressAndPrintCard(winningloto, file);
	fclose(file);
}
/*
* This is a sub function for saveListToBinFile that handle the compress of the one tor to get saved in the 3 BYTES instead of 4 Bytes.
* @parm LotoArr loto -> the The data we want to compress .
* @FILE* file -> a pointer to the file that we want to write on.
*/
void compressAndPrintCard(LotoArr loto, FILE* file)
{
	int maskint = 15;
	int i;
	BYTE output;
	for (i = 0; i < 3; i++)
	{
		output = 0;
		output = (char)*(loto._parr[(2 * i)]) << 4;
		output |= (char)*(loto._parr[(2 * i) + 1]);
		fwrite(&output, 1, 1, file);
	}

}
/*
* check if the file is opened with no bugs.
*/
void checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Opening file failed!\n");
		exit(-1);
	}
}

int printMainScreen()
{
	int choice = 0;

	showMenu();

	scanf("%d", &choice);
	while (1)
	{
		if (choice > 0 && choice < 4)
			return choice;
		else
		{
			system("cls");
			printf("Please Enter a Valid Choice\n\n");
			showMenu();
			scanf("%d", &choice);

		}
	}
}

void printFromBin(char* filename, int* constable)
{
	LotoArr arr;
	LotoList list;
	User user;
	UserList lst;
	LotoArr winLoto;
	UserNode bestuser;
	int numofusers, numOfLines = 0, lenofname;
	int i, j, k, temp = 0;
	int summary[7] = { 0 };
	char* name = NULL;
	BYTE data = 0;
	BYTE mask = 15;
	unsigned int** card;
	FILE* file = fopen(filename, "rb");
	checkFile(filename);
	makeEmptyUserList(&lst);


	fread(&numofusers, sizeof(int), 1, file);
	for (i = 0; i < numofusers; i++)
	{
		fread(&lenofname, sizeof(int), 1, file);
		name = (char*)malloc(sizeof(char) * (lenofname + 1));
		checkMemoryAllocation(name);
		fread(name, sizeof(char), lenofname, file);
		name[lenofname] = '\0';

		fread(&numOfLines, sizeof(int), 1, file);
		makeEmptyLotoList(&list);

		for (j = 0; j < numOfLines; j++)
		{
			card = (unsigned int**)malloc(sizeof(unsigned int*) * 6);
			checkMemoryAllocation(card);

			for (k = 0; k < 3; k++)
			{
				fread(&data, 1, 1, file);
				card[2 * k + 1] = constable + (mask & data) - 1;
				temp = data & (~(mask));
				temp = temp >> 4;
				card[k * 2] = constable + temp - 1;
			}

			arr._parr = card;
			arr._numofhits = 0;

			insertDataToEndLotoList(&list, arr);


		}
		list._numoflines = numOfLines;
		user = SetUserHelper(name, list);
		insertDataToEndUserList(&lst, user);
		free(name);

	}


	//print win loto:

	card = (unsigned int**)malloc(sizeof(unsigned int*) * 6);
	checkMemoryAllocation(card);

	for (k = 0; k < 3; k++)
	{
		fread(&data, 1, 1, file);
		card[2 * k + 1] = (constable + (mask & data) - 1);
		temp = data & (~(mask));
		temp = temp >> 4;
		card[k * 2] = constable + temp - 1;
	}

	winLoto._parr = card;
	lst.lenoflist = numofusers;
	lottoryGame(&lst, constable, &bestuser, summary, &winLoto, false);
	printUserList(lst, winLoto, &bestuser, summary);
	freeListOfUsers(&lst);
	fclose(file);

}

void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		puts("a memory allocation has occured");
		exit(1);
	}
}

char* setName()
{
	char ch;
	char* string;
	int length = 10;
	int i = 0;

	string = (char*)malloc(length + 1);
	checkMemoryAllocation(string);
	ch = getchar();
	while (ch != '\n')
	{
		if (i == length)
		{
			length *= 2;
			string = (char*)realloc(string, length + 1);
			checkMemoryAllocation(string);
		}
		string[i] = ch;
		i++;
		ch = getchar();
	}
	string[i] = '\0';
	string = (char*)realloc(string, i + 1);
	checkMemoryAllocation(string);
	return string;
}
/*
* void function that print manu
*/
void showMenu()
{
	printf("Welcome to Save That Money LoTory!\n");
	printf("Please choose requested num:\n");
	printf("1.Enter number of users\n");
	printf("2.Show results\n");
	printf("3.Exit\n");
}
void freeListOfUsers(UserList* lst)
{
	if(isEmptyUserList(lst))
		return;
	UserNode* curr = lst->head;
	UserNode* next;
	LotoList* currlotolst = &curr->_player._lines;
	while (curr != NULL)
	{
		next = curr->next;
		currlotolst = &curr->_player._lines;
		freeListOfLoto(currlotolst);
		free(curr);
		curr = next;
	}

}
void freeListOfLoto(LotoList* lst)
{
	if (isEmptyLotoList(lst))
		return;
	LotoNode* curr = lst->head;
	LotoNode* next;
	while (curr!=NULL)
	{
		next = curr->next;
		free(curr->_lotoArr._parr);
		free(curr);
		curr = next;
	}
}