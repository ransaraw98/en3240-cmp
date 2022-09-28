/* Embedded systems Assignment 3 */

#include <stdio.h>
#include <stdlib.h>

const char infName1 [] = "original.txt";
const char infName2 [] = "compressed.txt";

FILE *inputfile1;
FILE *inputfile2;

//Comparison function for sorting
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

//File length calculator
int filesize(FILE *fp){
	int size = 0;

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp,0L,SEEK_SET);
	rewind(fp);

	return size;
}

//struct for dictionary creation
struct word_entry{
	unsigned int element;
	unsigned int occurences;
	unsigned int index;
};


int main(void){
	char buffer [32]= "";
	static unsigned int flen1 = 0;
	unsigned int temp = 0;
	unsigned int prev_ele = NULL;
	unsigned int curr_ele = NULL;
	unsigned int index = -1;
	//READING FILE 1
	inputfile1 = fopen(infName1, "r");
	flen1 = (filesize(inputfile1)/33); //Number of words

	unsigned int *f1_cntnt = calloc(flen1,sizeof(int));
	unsigned int *f1_cntnt_cpy = calloc(flen1,sizeof(int));
	struct word_entry *frequencies = calloc(flen1,sizeof(int)*3);
	
	for (int i=0; i<flen1; i++){
		fgets(buffer,33,inputfile1); 			//Read 32 bytes 
		fseek(inputfile1,1,SEEK_CUR);			//Skip new line byte				
		//f1_cntnt[i] =atoi(buffer);
		temp =(unsigned int)strtoul(buffer,NULL,2);
		f1_cntnt[i] =temp;
		f1_cntnt_cpy[i] =temp;
	}
	
	
	qsort(f1_cntnt_cpy, flen1, sizeof(int), comp);		//sort array elements
	for(int i =0; i<= flen1; i ++){
		
		printf("%X\n",f1_cntnt_cpy[i]);
		
	}	
	for(int i=0; i<=flen1; i++){
		
		curr_ele = f1_cntnt_cpy[i];
		if (prev_ele != curr_ele){
			index += 1;
			frequencies[index].element = curr_ele;
			frequencies[index].occurences = 1;
			prev_ele = curr_ele;	
		}		
		else{
			frequencies[index].occurences +=1;
			prev_ele= curr_ele;
		}		
	
	
	}

	

	fclose(inputfile1);
	
	

	free(f1_cntnt);
	return 0;
}
