/**

Objective: 

The purpose of this project is to refactor and integrate Parts A and B into a single, 
multi source file program.

This source file will be the entry point.

Note don't #include "covert.h", include it in convert.c because the source file will include the header there, but adding a guard in datadefs.h should fix this problem too.
**/

#include "datadefs.h" //ensure this is only called once here

#define _CRT_SECURE_NO_WARNINGS

#define	INPUT_FILE	"dataOut.txt"	//plain txt file with raw data
#define	OUTPUT_FILE "clients.dat"	//binary file after raw data is convereted
#define INDEX_FILE	"lastname.idx"	//index in assorted last name order of clients.dat

//function prototypes
void nothing(void);//used to just do something with pfunc[0]
void convert(FILE *pInput, FILE *pOutput);
void index(FILE *pInput, FILE *pOutput, FILE *pIndex);
void naturalOrderFromAssign06(FILE *pInput, FILE *pOutput, FILE *pIndex);
void sortedOrder(FILE *pInput, FILE *pOutput, FILE *pIndex);
void exitAssignment(void);		//Note exit is C word already, and when I tried to name this function exit I got an redefinition error

int(*pfunc[5])();				//creates an array of function pointers

int main(int argc, char *argv[]) { //argc number of arguments passed, argv array of strings passed

	char *pInput	= argv[1];	//dataOut.txt	- passed via cmdline
	char *pOutput	= argv[2];	//clients.dat	- passed via cmdlind
	char *pIndex	= argv[3];	//lastname.idx	- passed via cmdlind

	if (argc == 4) { //arugment checks need to be in the beginning before fopen calls

		if (!(strcmp(argv[1], INPUT_FILE)) == 0) {
			printf("The first argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INPUT_FILE, argv[1]);
			return 1;
		}

		if (!(strcmp(argv[2], OUTPUT_FILE)) == 0) {
			printf("Error - The second argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", OUTPUT_FILE, argv[2]);
			return 1;
		}

		if (!(strcmp(argv[3], INDEX_FILE)) == 0) {
			printf("Error - The second argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INDEX_FILE, argv[2]);
			return 1;
		}
	}
	else if (argc > 3) {
		printf("Error - Too many arugments supplied.\n");
		return 1;
	}
	else {
		printf("Error - Three argument expected.\n");
		return 1;
	}//end of (argc == 3)

	//TODO Implement the following menu in assign06.c using an array of function pointers.
	pfunc[0] = nothing; //TODO nothing?
	pfunc[1] = convert;
	pfunc[2] = index;
	pfunc[3] = naturalOrderFromAssign06;//TODO need to name this differnt from naturalOrder because display.c already has one
	pfunc[4] = sortedOrder;
	pfunc[5] = exitAssignment;

	int choice;

	do {
		choice = enterChoice();

		if (choice == 0 || choice >= 6) {
			printf("Error - %s\n", "Incorrect choice, good bye!");
			return 1;//returns error
		}

		if (choice == 5) {
			pfunc[choice]();//exit option
			return 0;
		}

		pfunc[choice](pInput, pOutput, pIndex);

	} while (choice > 0 || choice < 6); 

	return 0;
}

//just return an incorrect input message
void nothing(void) {
	printf("Error - %s\n", "Incorrect choice, good bye!");
	return 1;//TODO return 1 or 0
}

//convert dataOut.txt to clients.dat
void convert(FILE *pInput, FILE *pOutput) {
	convertMain(pInput, pOutput); //added success convert message in convert.c
}

//convert clients.dat to lastname.idx
//TODO check if convert data was successful, then do this (if not throw an error because there needs to be a client.dat to be converted to index
void index(FILE *pInput, FILE *pOutput, FILE *pIndex) { //TODO we don't do anything with pInput, but we need pOutput in the second param, in order for it to be called in index.c properly
	indexMain(pOutput, pIndex);//added success index message in index.c
}

//sort clients.dat to natural order
void naturalOrderFromAssign06(FILE *pInput, FILE *pOutput, FILE *pIndex) {
	char sortOrder[] = "natural"; //TODO change these varibales to define or in datadefs.h??
	displayMain(pInput, pOutput, pIndex, sortOrder);
}

//sort clients.dat in sorted last name order using lastname.idx has reference point for file pointers
void sortedOrder(FILE *pInput, FILE *pOutput, FILE *pIndex) {	
	char sortOrder[] = "sorted last name";
	displayMain(pInput, pOutput, pIndex, sortOrder);	
}

void exitAssignment(void) {
	printf("%s\n", "Good bye!");
}


//borrowed code from Charlie
int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"
		"1 - Convert File\n"
		"2 - Index File\n"
		"3 - Display in Natural order\n"
		"4 - Display in Sorted Order\n"
		"5 - Exit\n?");

	scanf("%d", &menuChoice);
	while (getchar() != '\n');

	return menuChoice;
}