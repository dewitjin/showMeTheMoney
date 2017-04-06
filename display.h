#include "datadefs.h"

#define INPUT_FILE "clients.dat" 
#define INDEX_FILE "lastname.idx"//read from lastname.idx (index), grab the file position and find the account data from clients.dat
#define APP_NAME "Assignment 6 Part B"
#define DIVIDER "---------------------------------------------------------------"//note divider should be put in separate headers because it's different for diff displays

float roundUp(float val);//rounds value to get the Charlie's output

long fileSize(FILE *input);//borrowed code

void naturalOrder(fpData);
void ascendingLastName(fpData, fpIndex);

int displayMain(FILE *pInput, FILE *pOutput, FILE *pIndex, char *sortOrder);