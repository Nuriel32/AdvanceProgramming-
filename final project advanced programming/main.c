/*
Daniel Haim 313321614
Nuriel Cohen 208661611
*/

#include "functions.h"
void main()
{

	UserList lst;
	int n;
	bool made = false;
	int constable[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	int choice = 0;
	int summary[7] = { 0 };
	LotoArr winLoto;
	UserNode bestuser;
	FILE* file = NULL;

	makeEmptyUserList(&lst);
	srand(time(NULL));

	choice = printMainScreen();
	while (choice != 3)
	{

		switch (choice)
		{
		case 1:
			///lotory

			printf("Please enter number of users:\n");
			scanf("%d", &n);

			lst = SetUsers(n, constable);
			lst.lenoflist = n;
			lottoryGame(&lst, constable, &bestuser, summary, &winLoto, true);
			printUserList(lst, winLoto, &bestuser, summary);
			saveListToBinFile("LastResults.bin", lst, winLoto);
			made = true;

			break;
		case 2:

			file = fopen("LastResults.bin", "rb");

			if (file == NULL)
			{
				printf("No lottery has been drawn yet!\n");
				break;
			}
			else if (made)
			{
				printUserList(lst, winLoto, &bestuser, summary);
			}
			else
			{
				printFromBin("LastResults.bin", constable);
			}
			break;
		case 3:
			exit(1);
			break;
		default:
			choice = 0;
			printf("unvalid choice\n");
		}
		choice = printMainScreen();
	}
	freeListOfUsers(&lst);
}


