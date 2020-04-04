/* CS 211 PA1: rle
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void freeArr(char* arr);
void freeArr(char* arr){
	//for (int i=0;i<strlen(arr);i++)
i	//	free(arr[i]);
	free (arr);
}*/

int main(int argc, char **argv)
{
  // printf("%s: not implemented\n", argv[0]);
	if (argc<2){
		exit(0);
	}
	int size=strlen(argv[1]);
	if (size==0)
		exit(0);
	
	/*char *test;
	test=malloc(size*sizeof(char));

	free(test);*/
	
	char *input;
	input=malloc(size*sizeof(char));
	
	char *output;
	output=malloc(2*size*sizeof(char));
//	printf("ch1\n");
	input=argv[1];
	
	for (int i=0;i<size;i++){
		if (input[i]>='0' && input[i]<='9'){
			printf("error\n");
			exit(0);
		}
	}
//	printf("Input String: %s\n",input);

	int indexI=0;
	int indexO=0;
	//int indexO=0;

	char ptr=input[0];
	output[indexO]=ptr;
	indexO++;
	int count=0;

	//printf("ch2\n");
	while (indexI<size){ //check what happens if they have equal length
		
	//	printf("ch3\n");
		if (input[indexI]==ptr){
			count++;
		}	
		else {
				//printf("ch3.5\n");
			ptr=input[indexI];
			//printf("%c\n",ptr);
			//indexO++;
			//printf("%d\n",indexO);
                        char* number=malloc(10*sizeof(char));

                        //printf("ch3.6\n");
                        //
                        sprintf(number,"%d",count);
                        for (int i=0;i<strlen(number);i++){
                                output[indexO]=number[i];

                                indexO++;
                        }
			//printf("%s\n",output);
			//indexO++;
			output[indexO]=ptr;
			indexO++;
			/*char* number=malloc(10*sizeof(char));
			
			//printf("ch3.6\n");

			sprintf(number,"%d",count);*/
			/*printf("ch3.7\n");
			for (int i=0;i<strlen(number);i++){
				output[indexO]=number[i];
				
				indexO++;
			}
			
			printf("here\n");*/
			/*strcat(output,number);
			printf("chX\n");	
			char* append=malloc(10*sizeof(char));
			//append[0]=ptr;
			append="";
			int n=strlen(append);
			printf("%d\n",n);

			printf("ch3.8\n");
			
			strcat(append,number);
			printf("ch3.85\n");
			printf("%s\n",append);

			strcat(append,output);

			printf("ch3.9\n");*/
			//ptr=input[indexI];
			count=1;
			free(number);
		}
		///printf("ch4\n");
		indexI++;
	}
	//printf("out of loop\n");
//	printf("%d\n",indexO+1);

	char *last=malloc(10*sizeof(char));
	sprintf(last,"%d",count);
                        for (int i=0;i<strlen(last);i++){
                                output[indexO]=last[i];

                                indexO++;
                        }
	//if (strlen(output)<size)
	if (indexO<=size){
	for (int i=0;i<indexO;i++)
		printf("%c",output[i]);
	printf("\n");
	}
	else 
		printf("%s\n",input);
	//else 
	//freeArr(input);
	//freeArr(output);
	
	free(output);
	//free(input);
	free(last);	
	
    return EXIT_SUCCESS;
}
