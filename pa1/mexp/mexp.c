/* CS 211 PA1: mexp
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>


int** allocate_matrix(int rows, int cols);
int** allocate_matrix(int rows, int cols){

  int** ret_val = malloc(rows * sizeof(int*));
  for(int i = 0; i< rows; i++){
    ret_val[i] = malloc(cols * sizeof(int));
  }
  return ret_val;
}

int main(int argc, char **argv)
{
    //printf("%s: not implemented\n", argv[0]);
	FILE* fp=fopen(argv[1],"r");

	int** matrix;
	int** ans;
	int size;
	

	fscanf(fp,"%d\n",&size);
	//printf("%d\n",size);
	matrix=allocate_matrix(size,size);
	ans=allocate_matrix(size,size);

	for (int r=0;r<size;r++){
		for (int c=0;c<size;c++){
			if (c<size-1){
				fscanf(fp,"%d ",&matrix[r][c]);
				//printf("%d ", matrix[r][c]);
			}
			else {
				fscanf(fp,"%d\n",&matrix[r][c]);
				//printf("%d\n",matrix[r][c]);
			}
		}
	}	
	
	int exp;
	fscanf(fp,"%d\n",&exp);
	//printf("%d\n",exp);
        int** temp;
        temp=allocate_matrix(size,size);

	for (int r=0;r<size;r++){
		for (int c=0;c<size;c++){
			temp[r][c]=0;
		}
	}
	for (int r=0;r<size;r++){
		for (int c=0;c<size;c++){
			ans[r][c]=matrix[r][c];
		}
	}	

	if (exp==0){
	
		for (int r=0;r<size;r++){
			for (int c=0;c<size;c++){
				if (r==c)
					ans[r][c]=1;
				else
					ans[r][c]=0;
			}
		}
	
	}

	while (exp>1){
		for (int r=0;r<size;r++){
			for (int c=0;c<size;c++){
				temp[r][c]=0;
				for (int k=0;k<size;k++){
					temp[r][c]+=ans[r][k]*matrix[k][c];
				}
			}
		}
		
	//	exp--;
	
	        for (int r=0;r<size;r++){
	                for (int c=0;c<size;c++){
                        ans[r][c]=temp[r][c];
                	}
		}
     
		exp--;		
	}
        
	/*else{
		int counter=1;
                for (int r=0;r<size;r++){
                        for (int c=0;c<size;c++){
                        	ans[r][c]=matrix[r][c];
				//printf("%d ",ans[r][c]);
                        }
                }
		

		while(counter<exp){
			counter++;

			for (int r=0;r<size;r++){
				for (int c=0;c<size;c++){
					temp[r][c]=ans[r][c];
				}
			}

			for (int r=0;r<size;r++){
				for (int c=0;c<size;c++){
					
					for (int k=0;k<size;k++){
						ans[r][c]+=temp[r][k]+matrix[k][c];
						temp[r][k]=ans[r][k];
					}
				}
			}
			for (int r=0;r<size;r++){
				for (int c=0;c<size;c++){
		//			if (counter==0)
						//ans[r][c]=0;
				
					ans[r][c]=0;
					for (int k=0;k<size;k++){
						
						//	ans[r][c]+=matrix[r][k]*matrix[k][c];
							
							ans[r][c]+=temp[r][k]*matrix[k][r];
					}
					for (int j=0;j<size;j++)
						      temp[r][j]=ans[r][c];
					
				}
			}
			
		}
	}*/

	for (int r=0;r<size;r++){
		for (int c=0;c<size;c++){
			if (c<size-1)
				printf("%d ",ans[r][c]);
			else 
				printf("%d\n",ans[r][c]);
		}
	} 
    return EXIT_SUCCESS;
}
