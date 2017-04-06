#include "convert.h"

/*
	Objective: The purpose of this assignment is to work with random-access binary files.
*/

int convertMain(FILE *pInput, FILE *pOutput) { //argc number of arguments passed, argv array of strings passed

	char *pDataOutTxt = pInput;//dataOut.txt - passed via cmdline

	FILE *fpInputFile = fopen(pDataOutTxt, "r");
	FILE *fpOutputFile = fopen(OUTPUT_FILE, "wb");//convert dataOut.txt to a binary file named clients.dat, wb creates a file to write in binary mode, if the file exists, discard the current contents, may want to check if the user knows the file will be overwritten too

	//check if the file to be read is called dataOut.txt
	if (!(strcmp(pDataOutTxt, INPUT_FILE)) == 0) {
		printf("Error - The argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INPUT_FILE, pDataOutTxt);
		return 1;
	}

	//fopen opens the file; exit if file cannot be opened
	if (!fpInputFile) {
		printf("Error - Unable to open/create file <%s>.\n", INPUT_FILE);
		return 1;
	}

	if (!fpOutputFile) {
		printf("Error - Unable to open/create file <%s>.\n", OUTPUT_FILE);
		return 1;
	}

	Account temp = { {0},{0},{0},0,0.0 };//note {0} is an empty string
	char csvLine[MAX_CSV_LINE_LENGTH + 1] = { 0 }; //will contain the each line in file
	char *pToken = NULL;

	rewind(fpInputFile); //set pointer to beginning of file
	while (!feof(fpInputFile)) {

		if(fgets(csvLine, MAX_CSV_LINE_LENGTH, fpInputFile) != NULL) {//scan first line
			
			csvLine[strlen(csvLine) - 1] = '\0'; //gets rid of new line character in file
			pToken = strtok(csvLine, " "); //parse line with spaces

			if (pToken != NULL) {

				strcpy(temp.firstName, pToken);
				pToken = strtok(NULL, " ");
				strcpy(temp.lastName, pToken);
				pToken = strtok(NULL, " ");
				strcpy(temp.email, pToken);
				pToken = strtok(NULL, " ");
				temp.age = atoi(pToken);
				pToken = strtok(NULL, " ");
				temp.balance = atof(pToken);
				pToken = strtok(NULL, " ");//loops through the same line until we find a NULL at the end of the line

				fwrite(&temp, sizeof(Account), 1, fpOutputFile);

			}//end of if
		}//end of fgets
	}

	printf("< %s > was converted to < %s > successfully", pInput, pOutput);//if user clicks on option convert, and this source is successful then print out success message

	//close files
	fclose(fpInputFile);
	fclose(fpOutputFile);

	return 0;
}

