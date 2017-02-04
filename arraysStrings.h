// Phu-Lam Pham
// TCSS 333 WI 2017 - Assignment 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//fill in the parameters and return type
char* joinrev(char *s1, char *s2);
void* joinrev_generic(void *a, void *b, int typeSize, int aNElements, int bNElements);
int readTextAddBinary(char file1[], char file2[]);
int readBinaryNormText(char file1[], char file2[]);
int readNormTextWriteNormBinary(char file1[], char file2[]);
int wc(char file[]);
