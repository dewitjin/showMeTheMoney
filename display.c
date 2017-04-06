/**

Objective: This is the display.c for part C.

**/

#include "display.h"
#include <math.h> 

IndexKey indexKey;//TODO probably change this so it's not a global

int displayMain(FILE *pInput, FILE *pOutput, FILE *pIndexFromData, char *sortOrder) { //argc number of arguments passed, argv array of strings passed

	indexKey = LAST;//don't really need this for display.c but carried over from index.c from part B

	char *pData = pOutput;//clients.dat - passed via cmdline
	char *pIndex = pIndexFromData;//lastname.idx - passed via cmdlind

	if (!(strcmp(pData, INPUT_FILE)) == 0) {
		printf("Error - The first argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INPUT_FILE, pData);
		return 1;
	}

	if (!(strcmp(pIndex, INDEX_FILE)) == 0) {
		printf("Error - The second argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INDEX_FILE, pIndex);
		return 1;
	}
	
	FILE *fpData = fopen(pData, "rb"); //reading clients.dat
	FILE *fpIndex = fopen(pIndex, "rb"); //reading from lastname.idx

	//fopen opens the file; exit if file cannot be opened, if it can't be open then you don't need to close it because it wasn't opened!
	if (!fpData) {
		printf("Error - Unable to open/create file <%s>.\n", INPUT_FILE);
		return 1;
	}

	if (!fpIndex) {
		printf("Error - Unable to open/create file <%s>.\n", INDEX_FILE);
		return 1;
	}

	if (strcmp(sortOrder, "natural") == 0) { //TODO put natural in a variable or something?
		naturalOrder(fpData);
	}
	else if (strcmp(sortOrder, "sorted last name") == 0) {
		ascendingLastName(fpData, fpIndex);
	}

	//close files
	fclose(fpData);
	fclose(fpIndex);

	return 0;
}

//display data in last name ascending order
void ascendingLastName(FILE *fpData, FILE *fpIndex) {

	IndexHeader idxHeader;
	IndexRecord idxTemp;

	int readCount;
	int recCount;

	int ageTotal = 0, count = 0;
	float ageAverage = 0.0, balanceTotal = 0.0, balanceAverage = 0.0;

	//calculate record count in data file
	recCount = fileSize(fpData) / sizeof(Account);

	//read header record in index file
	readCount = fread(&idxHeader, sizeof(IndexHeader), 1, fpIndex);

	//check that application versions match
	if (strcmp(idxHeader.appName, APP_NAME) != 0) {
		printf("\nError - Data and Index Files created by differennt application versions\n");
		fclose(fpData);
		fclose(fpIndex);
		return 1;
	}

	//check that record count of data file matches index header
	if (idxHeader.recCount != recCount) {
		printf("\nSeek Error - Data and Index File have a record count mismatch\n");
		fclose(fpData);
		fclose(fpIndex);
		return 1;
	}

	Account temp = { { 0 },{ 0 },{ 0 }, 0, 0.0 };//note {0} is an empty string

	printf("Data File Read in Indexed Order (Last Name)\n\n");
	//print header to console for debug
	printf("%-13s %-13s %-20s %3s %10s\n", "FirstName", "LastName", "Email Address", "Age", "Balance"); //start printing header
	printf("%s\n", DIVIDER);

	//rewind(fpIndex); //note this set pointer to beginning of file of lastname.idx, but we do not want it here because we do not want to rewind the index file pointer after reading the IndexHeader, you want to read from that point (first index record)
	
	readCount = fread(&idxTemp, sizeof(IndexRecord), 1, fpIndex);

	//continue processing all index records
	while ((!feof(fpIndex)) && (readCount == 1)) {

		//seek record in data file based on file position
		//stored in previously read index record
		if (fseek(fpData, idxTemp.filePos, SEEK_SET) != 0) {//SEEK_SET	Beginning of file, so if fseek returns a 0 then it's an error, if it doesn't then fseek will work and you use the file position to find the account in clients.dat
			printf("Seek Error\n");
			return 1;
		}

		//read data record and output
		fread(&temp, sizeof(Account), 1, fpData);//reading from a binary file
		printf("%-13s %-13s %-20s %3d %10.2lf\n",
			temp.firstName,
			temp.lastName,
			temp.email,
			temp.age,
			temp.balance);

		ageTotal += temp.age;
		balanceTotal += temp.balance;
		count++;

		// read next index record
		readCount = fread(&idxTemp, sizeof(IndexRecord), 1, fpIndex);
		//printf("DEBUG %lu %s\n", idxTemp.filePos, idxTemp.key.lastName); //check that lastname.idx has correct data
	}//end of while

	ageAverage = (roundUp)(((float)ageTotal) / count); //need to cast to float 
	balanceAverage = balanceTotal / count;

	printf("%s\n", DIVIDER);
	printf("%34s %17d %10.2lf\n", "Total:", ageTotal, balanceTotal);
	printf("%37s %14.1lf %10.2f\n", "Average: ", ageAverage, balanceAverage);

	printf("\n< %s > was displayed to sorted last name order successfully", INPUT_FILE);//success message for main file menu option
}

//outputs the natural order for the clients.dat file, read from clients.dat not lastname.idx
void naturalOrder(FILE *fpInputFile) {

	Account temp = { { 0 },{ 0 },{ 0 }, 0, 0.0 };//note {0} is an empty string

	printf("\n%-13s %-13s %-20s %3s %10s\n", "FirstName", "LastName", "Email Address", "Age", "Balance"); //start printing header
	printf("%s\n", DIVIDER);

	int ageTotal = 0, count = 0;
	double ageAverage = 0.0, balanceTotal = 0.0, balanceAverage = 0.0;

	rewind(fpInputFile);//set pointer to beginning of file, don't rewind in ascendinglastname(), because do not rewind the index file pointer after reading the IndexHeader, you want to read from that point (first index record)
	while (!feof(fpInputFile)) {

		int bytesRead = fread(&temp, sizeof(Account), 1, fpInputFile);//reading from a binary file

		if (bytesRead > 0) {

			printf("%-13s %-13s %-20s %3d %10.2lf\n",
				temp.firstName,
				temp.lastName,
				temp.email,
				temp.age,
				temp.balance);

			ageTotal += temp.age;
			balanceTotal += temp.balance;
			count++;

		}//end of if

	}

	ageAverage = (roundUp)(((float)ageTotal) / count); //need to cast to float 
	balanceAverage = balanceTotal / count;

	printf("%s\n", DIVIDER);
	printf("%34s %17d %10.2lf\n", "Total:", ageTotal, balanceTotal);
	printf("%37s %14.1lf %10.2f\n", "Average: ", ageAverage, balanceAverage);

	printf("\n < %s > was displayed to natural order successfully", INPUT_FILE);//success message for main file menu option
}

//rounding up
float roundUp(float val) {
	return ceilf(val * 100) / 100;
}

//borrowed code 
long fileSize(FILE *input) {

	long orgPos;
	long startPos;
	long endPos;

	orgPos = ftell(input);//save orig file position
	rewind(input);
	startPos = ftell(input);
	fseek(input, 0, SEEK_END);
	endPos = ftell(input);
	fseek(input, orgPos, SEEK_SET);//restore orig position

	return (endPos - startPos);

}

