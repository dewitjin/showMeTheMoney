/*
	Objective - converts clients.dat to lastname.idx
*/

#include "index.h"

IndexKey indexKey; //TODO probably don't need this to be global

int indexMain(FILE *pData, FILE *pIndexFromData) { 

	char *pDataOutTxt = pData;		//clients.dat - passed via cmdline
	char *pIndex = pIndexFromData;	//lastname.idx - passed via cmdlind

	IndexHeader indexHeader;
	IndexRecord *indexRecords;
	
	indexKey = LAST;

	int		readCount;
	int		writeCount;
	int		dataRecordCount;
	int		indexRecordCount;
	long	filePos;

	//check if the file to be read is called clients.dat
	if (!(strcmp(pData, INPUT_FILE)) == 0) {
		printf("Error - The first argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", INPUT_FILE, pData);
		return 1;
	}

	if (!(strcmp(pIndexFromData, OUTPUT_FILE)) == 0) {
		printf("Error - The second argument supplied is incorrect.\nIt should be <%s> but instead it is <%s>.\n", OUTPUT_FILE, pIndexFromData);
		return 1;
	}
	
	//open files after cmd argument checks
	FILE *fpInputFile = fopen(pDataOutTxt, "rb");//reading clients.dat
	FILE *fpOutputFile = fopen(pIndex, "wb");//used to start lastname.idx 

	//fopen opens the file; exit if file cannot be opened
	if (!fpInputFile) {
		printf("Error - Unable to open/create file <%s>.\n", INPUT_FILE);
		return 1;
	}

	if (!fpOutputFile) {
		printf("Error - Unable to open/create file <%s>.\n", OUTPUT_FILE);
		return 1;
	}

	//calculate record count in data file
	dataRecordCount = fileSize(fpInputFile) / sizeof(Account);

	//allocate an array to hold an equal number of index records
	indexRecords = (IndexRecord *)calloc(dataRecordCount, sizeof(IndexRecord));

	//populate index header record
	indexHeader.idxKey = indexKey;
	strcpy(indexHeader.appName, APP_NAME);
	indexHeader.recCount = dataRecordCount;
	
	//rewind(fpInputFile); //Note: Do not rewind the index file pointer after reading the IndexHeader, you want to read from that point (first index record)

	filePos = ftell(fpInputFile);
	indexRecordCount = 0;

	Account temp = { { 0 },{ 0 },{ 0 },0,0.0 };//note {0} is an empty string
	
	//read the first data record
	readCount = fread(&temp, sizeof(Account), 1, fpInputFile);
	
	//process all data records
	while (!feof(fpInputFile) && (readCount == 1)) {
	
		//populate index record from data record
		strcpy(indexRecords[indexRecordCount].key.lastName, temp.lastName);
		indexRecords[indexRecordCount].filePos = filePos;
		indexRecordCount++;				//added a record - increment to next element
		filePos = ftell(fpInputFile);	//store file pos before next read advances it
		readCount = fread(&temp, sizeof(Account), 1, fpInputFile);	//read next record
	
	}//end of while

	qsort(indexRecords, indexRecordCount, sizeof(IndexRecord), ascending);

	//start of borrowed code 
	printf("Index Header Size: %d\nIndex Record Size: %d\n\n"
		, sizeof(IndexHeader), sizeof(IndexRecord));

	printf("Creating Index File\n");

	// write Index Header to file
	writeCount = fwrite(&indexHeader, sizeof(IndexHeader), 1, fpOutputFile);
	// Write Index Records to file
	writeCount = fwrite(indexRecords, sizeof(IndexRecord), indexRecordCount, fpOutputFile);
	printf("%d Records Processed\n", writeCount);
	printf("\nFileSize: %d\n\n", fileSize(fpOutputFile));
	// release this memory and set it free
	free(indexRecords); //TODO remember to do this for other programs
	//end of borrowed code

	printf("< %s > was converted to < %s > (index) successfully", pDataOutTxt, pIndex);//if user clicks on option index, and this source is successful then print out success message

	//close files
	fclose(fpInputFile);
	fclose(fpOutputFile);

	return 0;
}

// calculates the size of a file, borrowed code from Charlie
long fileSizeIndex(FILE *input) {
	long orgPos;
	long startPos;
	long endPos;

	orgPos = ftell(input);// save orig file position
	rewind(input);
	startPos = ftell(input);
	fseek(input, 0, SEEK_END);
	endPos = ftell(input);
	fseek(input, orgPos, SEEK_SET);

	return(endPos - startPos);
}

//borrowed code BUT cast to IndexRecord instead of void and used strcmp to compare
int ascending(const void *left, const void *right)
{
	IndexRecord *pLeft = (IndexRecord*)left;
	IndexRecord *pRight = (IndexRecord*)right;

	return strcmp(pLeft->key.lastName,pRight->key.lastName);
}


