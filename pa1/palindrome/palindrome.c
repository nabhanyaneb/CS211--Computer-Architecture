/* CS 211 PA1: palindrome
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    //printf("%s: not implemented\n", argv[0]);
	int size=strlen(argv[1]);
	
	char* input=malloc(size*sizeof(char));
	input=argv[1];
	//printf("%s\n",input);
	char* zip=malloc(size*sizeof(char));
	int indexZ=0;
	for (int i=0;i<size;i++){
		if (input[i]!=32){
			if (input[i]>=65 && input[i]<=90){
				zip[indexZ]=input[i]+32;
				indexZ++;
			}
			else if (input[i]>=97 && input[i]<=122){
				zip[indexZ]=input[i];
				indexZ++;
			}
			
		}
	}
	
	for (int i=indexZ;i<size;i++)
		zip[i]='\0';		

	//printf("%s\n",zip);

	int size2=indexZ;
	for (int i=0;i<size2;i++){
		if (zip[i]!=zip[size2-i-1]){
			printf("no\n");
			exit(0);
		}
	}

	printf("yes\n");
	//free(input);
	free(zip);
    return EXIT_SUCCESS;
}
