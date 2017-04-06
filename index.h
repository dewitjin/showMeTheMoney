#include "datadefs.h"

#define INPUT_FILE	"clients.dat" 
#define OUTPUT_FILE "lastname.idx" //use this to read in display.c
#define APP_NAME	"Assignment 6 Part B"

int indexMain(FILE *pData, FILE *pIndexFromData);
int ascending(const void *left, const void *right);
long fileSizeIndex(FILE *input);//borrowed code 