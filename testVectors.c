#include <stdio.h>
#include "vectors.h"

int main(int argc, char *argv[]){
	vector v1,v2;

 if(argc != 7){
		printf("The correct format is testVectors x1 y1 z1 x2 y2 z2\n");
		return 1;
	}
	//initialize vectors
	v1=vector_init(atof(argv[1]),	atof(argv[2]),atof(argv[3]));
	v2=vector_init(atof(argv[4]),	atof(argv[5]),atof(argv[6]));
	
	//print v1 v2
	printf("The original vectors are:\n");
	vector_print(v1);
	vector_print(v2);
	
	//add v1 to v2 and print out the result
	printf("The sum of vectors is:\n");
	vector_print(vector_add(v1,v2));

 
	//find dot product of v1 and v2 and print it out
	printf("The dot product is: %f\n",vector_dot(v1,v2));

	
	//normalize v1 and v2 using the normalize method and print out v1 and v2 after normalization
	//if the length is 0 then print out an additional warning message saying that the vector was not normalized
	
	
	printf("The normalized vectors are:\n");
	
	if(vector_normalize(&v1)){
		fprintf(stderr,"The vector has zero length and was not normalized \n");
	}
	vector_print(v1);
	if(vector_normalize(&v2)){
		fprintf(stderr,"zero length did not normalize \n");
	}
	vector_print(v2);
 return 0;
}
