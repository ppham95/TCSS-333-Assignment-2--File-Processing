// Phu-Lam Pham
// TCSS 333 WI 2017 - Assignment 2

#include "arraysStrings.h"
#include "vectors.h"

char* joinrev(char *s1, char *s2) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	char *result = malloc(len1 + len2 + 1);	// a char is already 1 byte
    strcpy(result, s1);
    strcat(result, s2);
    
    int left = len1, right = len1 + len2 - 1;
    char temp;
    while(left < right) {
		temp = result[right];
		result[right] = result[left];
		result[left] = temp;
		left++;
		right--;
	}
    return result;
}

void* joinrev_generic(void *a, void *b, int typeSize, int aNElements, int bNElements) {
	void *result = malloc(typeSize*(aNElements + bNElements));
	memcpy(result, a, typeSize*aNElements);
	memcpy(result + typeSize*aNElements, b, typeSize*bNElements);

	void *left = (void*)result + (aNElements)*typeSize, *right = (void*)result + (aNElements + bNElements-1)*typeSize;
 	void *temp[typeSize];
	while(left < right) {
  		memcpy(temp,right,typeSize);
  		memmove(right,left,typeSize);
  		memcpy(left,temp,typeSize);
  		left+=typeSize;
  		right-=typeSize;
	}
	return result;
}

int readTextAddBinary(char file1[], char file2[]) {
	char buffer[4];  
 	char *line=malloc(4);

 	// safeRead from lecture
 	if(!line){
		fprintf(stderr,"unable to allocate 4 bytes to line\n");
		return 1;
	}
 	int lineSize=4;  
 	int lineStrLen=0, bufferStrLen=0;

 	FILE *fp=fopen(file1,"r"), *output = fopen(file2, "wb"); 
	if(!fp){
		fprintf(stderr,"unable to open %s to read\n", file1);
	 	return 1;
	}

	if(!output) {
		fprintf(stderr,"unable to create %s\n", file2);
	 	return 1;
	}

 	while(fgets(buffer,sizeof(buffer),fp)){
		bufferStrLen=strlen(buffer);
  		while(lineSize < lineStrLen+bufferStrLen+1){
			fprintf(stderr,"reallocating %d bytes\n",lineSize*2);
   			line=realloc(line,lineSize*2);
   			if(!line){
				fprintf(stderr,"unable to reallocate %d bytes to line\n",lineSize*2);
				return 1;
			}	
   			lineSize*=2;
  		}
  		strcpy(line+lineStrLen,buffer);
  		lineStrLen+=bufferStrLen;

  		// Each line of input file contains 2 vectors
		// x1 y1 z1 x2 y2 z2
		float x1, y1, z1, x2, y2, z2;
 		vector v;
  		if(buffer[bufferStrLen-1]=='\n'){ 
   			// printf("%s",line);	// to read .txt content during debugging
   			sscanf(line, "%f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2);
   			v = vector_init(x1 + x2, y1 + y2, z1 + z2);
   			float vect[] = {v.x, v.y, v.z, v.length};
   			fwrite(&vect, sizeof(float), 4, output);
   			lineStrLen=0;
  		}
  	}
  	free(line);
	fclose(fp);
	fclose(output);
	return 0;
}

int readBinaryNormText(char file1[], char file2[]) {
	FILE *fp=fopen(file1, "rb"), *output=fopen(file2, "w");	

	if(!fp){
		fprintf(stderr,"unable to open %s to read\n", file1);
	 	return 1;
	}

	if(!output) {
		fprintf(stderr,"unable to create %s\n", file2);
	 	return 1;
	}

	vector v;
	while(fread(&v,sizeof(v),1,fp)==1) {
		vector_normalize(&v);
		fprintf(output, "%f\t%f\t%f\t%f\t", v.x, v.y, v.z, v.length);
	}

	fclose(fp);
	fclose(output);
	return 0;
}

int wc(char file[]) {
	int lines = 0, words = 0, chars = 0;
	FILE *fp = fopen(file, "r");
	if(!fp) {
		fprintf(stderr,"unable to open %s\n", file);
		return 1;
	}
	char ch, prev;
	while ((ch=getc(fp)) != EOF) {
		chars++;
		// \n followed by an empty line does not make a word
		if (isspace(ch) && !isspace(prev)) words++;
		if (ch == '\n') lines++;

		prev = ch;
	}	
	printf("Number of lines: %d\nNumber of words: %d\nNumber of characters: %d\n", lines, words, chars);
	fclose(fp);
	return 0;
}

int readNormTextWriteNormBinary(char file1[], char file2[]) {
	char buffer[4];  
 	char *line=malloc(4);

 	// safeRead from lecture
 	if(!line){
		fprintf(stderr,"unable to allocate 4 bytes to line\n");
		return 1;
	}
 	int lineSize=4;  
 	int lineStrLen=0, bufferStrLen=0;

 	FILE *fp=fopen(file1,"r"), *output = fopen(file2, "wb"); 
	if(!fp){
		fprintf(stderr,"unable to open %s to read\n", file1);
	 	return 1;
	}

	if(!output) {
		fprintf(stderr,"unable to create %s\n", file2);
	 	return 1;
	}
 	while(fgets(buffer,sizeof(buffer),fp)){
		bufferStrLen=strlen(buffer);
  		while(lineSize < lineStrLen+bufferStrLen+1){
			fprintf(stderr,"reallocating %d bytes\n",lineSize*2);
   			line=realloc(line,lineSize*2);
   			if(!line){
				fprintf(stderr,"unable to reallocate %d bytes to line\n",lineSize*2);
				return 1;
			}	
   			lineSize*=2;
  		}
  		strcpy(line+lineStrLen,buffer);
  		lineStrLen+=bufferStrLen;
  	}

    char *t = "\t";
  	char *token;
  	float x, y, z, length;
  	token = strtok(line, t);

  	// input file follows: x\ty\tz\tlength...(repeated) of vectors
  	while(token != NULL) {
  		sscanf(token, "%f", &x);
  		token = strtok(NULL, t);
  		sscanf(token, "%f", &y);
  		token = strtok(NULL, t);
  		sscanf(token, "%f", &z);
  		token = strtok(NULL, t);
  		sscanf(token, "%f", &length);
  		token = strtok(NULL, t);

  		float vect[] = {x, y, z, length};
   		fwrite(&vect, sizeof(float), 4, output);
  	}

  	free(token);
  	free(line);
	fclose(fp);
	fclose(output);
	return 0;
}