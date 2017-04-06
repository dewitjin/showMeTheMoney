/*

Move all data structure definitions and typedefs into 
a header file named datadefs.h and ensure it is only called once.

*/

#ifndef DATADEFS_H //explantions on guard https://en.wikipedia.org/wiki/Include_guard
#define DATADEFS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

#ifndef MAX_CSV_LINE_LENGTH //note since we include ifndef DATADEFS_H, we probably don't need to define these again
#define MAX_CSV_LINE_LENGTH 2048
#endif // #ifndef MAX_CSV_LINE_LENGTH

#ifndef MAX_FIRST_NAME_LENGTH
#define MAX_FIRST_NAME_LENGTH 40
#endif // #ifndef MAX_FIRST_NAME_LENGTH

#ifndef MAX_LAST_NAME_LENGTH
#define MAX_LAST_NAME_LENGTH 40
#endif // #ifndef MAX_LAST_NAME_LENGTH

#ifndef MAX_EMAIL_LENGTH
#define MAX_EMAIL_LENGTH 120
#endif // #ifndef MAX_EMAIL_LENGTH

typedef struct {
	char firstName[MAX_FIRST_NAME_LENGTH + 1];//+1 makes sure the array will contain the null too
	char lastName[MAX_LAST_NAME_LENGTH + 1];
	char email[MAX_EMAIL_LENGTH + 1];
	int age;
	double balance;
}Account;


typedef	enum { FIRST, LAST, EMAIL, AGE, BALANCE }IndexKey;

typedef union {
	char firstName[MAX_FIRST_NAME_LENGTH + 1];//+1 makes sure the array will contain the null too
	char lastName[MAX_LAST_NAME_LENGTH + 1];
	char email[MAX_EMAIL_LENGTH + 1];
	int age;
	double balance;
}KeyType;

typedef struct {
	KeyType	key;
	long	filePos;
}IndexRecord;

typedef struct {
	IndexKey	idxKey;
	char	appName[20];
	int		recCount;
}IndexHeader;

#endif // !DATADEFS.H