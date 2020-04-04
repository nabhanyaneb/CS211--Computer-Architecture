/* CS 211 PA1: roman
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
//    printf("%s: not implemented\n", argv[0]);
	
	int convert=atoi(argv[1]);
	int ans=convert;

	//printf("%d\n",convert);
	
	while (ans>=1000){
		printf("M");
		ans-=1000;
	}

	while (ans>=900){
		printf("CM");
		ans-=900;
	}

	while (ans>=500){
		printf("D");
		ans-=500;
	}

	while (ans>=400){
		printf("CD");
		ans-=400;
	}

	while (ans>=100){
		printf("C");
		ans-=100;
	}

	while (ans>=90){
		printf("XC");
		ans-=90;
	}

	while (ans>=50){
		printf("L");
		ans-=50;
	}

	while (ans>=40){
		printf("XL");
		ans-=40;
	}

	while (ans>=10){
		printf("X");
		ans-=10;
	}
	
	while (ans>=9){
		printf("IX");
		ans-=9;
	}
	
	while (ans>=5){
		printf("V");
		ans-=5;
	}
	
	while (ans>=4){
		printf("IV");
		ans-=4;
	}
		
	while (ans>=1){
		printf("I");
		ans--;
	}

	printf("\n");
    return EXIT_SUCCESS;
}
