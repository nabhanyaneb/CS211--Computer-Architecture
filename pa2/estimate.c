/* PA2 estimate */

#include <stdio.h>
#include <stdlib.h>

double** allocate_matrix(double r, double c);
double** transpose(double** matrix, int r, int c);
double** multiply(double** matrixA, double** matrixB, int r1, int c1, int r2, int c2);
double ** inverse(double** matrix, int r);
void print_matrix(double** matrix, int r, int c);
double** free_matrix(double** matrix, int r, int c);

double** allocate_matrix (double r, double c){
        double** ret_val = malloc(r * sizeof(double*));
        for(int i=0; i<r; i++){
                ret_val[i] = malloc(c * sizeof(double));
        }
        return ret_val;
}

double** transpose(double** matrix, int r, int c){
	double** result=allocate_matrix((double)c,(double)r);

	for (int i=0;i<r;i++){
		for (int j=0;j<c;j++){
			result[j][i]=matrix[i][j];
		}
	}

	return result;
}

double** multiply(double** matrixA, double** matrixB, int r1, int c1, int r2, int c2){
	double** result=allocate_matrix(r1,c2);

	if (c1!=r2){
		printf("error\n");
		return NULL;
	}

	for (int i=0;i<r1;i++){
		for (int j=0;j<c2;j++){
			result[i][j]=0;
			for (int k=0;k<c1;k++)
				result[i][j]+=(matrixA[i][k]*matrixB[k][j]);
		}
	}

	return result;
	
}

double ** inverse(double** matrix, int r){
        double** reduced = allocate_matrix(r,2*r);
        double holder;
        double point;

        for(int i = 0; i < r; i++){
                for(int j = 0; j < r; j++){
                        reduced[i][j] = matrix[i][j];
                }
        }

        for(int i = 0; i < r; i++){
                for(int j = r; j < 2*r; j++){
                        if(i==j-r){
                                reduced[i][j]=1;
                        }else{
                                reduced[i][j]=0;
                        }
                }
        }
        for(int i=0;i<r;i++){
                for(int j=0;j<r;j++){
                        if(i!=j){
                                holder = reduced[j][i]/reduced[i][i];
                                for(int k=0;k<2*r;k++){
                                        reduced[j][k] -= holder*reduced[i][k];
                                }
                        }
                }
        }

        for(int i=0;i<r;i++){
                point = reduced[i][i];
                for(int j=0;j<2*r;j++){
                        reduced[i][j] = reduced[i][j]/point;
                }
        }

        double** inverse = allocate_matrix(r,r);
        for(int i = 0; i < r; i++){
                for(int j = 0; j < r; j++){
                        inverse[i][j] = reduced[i][j+r];
                }
        }
	for (int i=0;i<r;i++)
		free(reduced[i]);
	free(reduced);
        return inverse;
}

void print_matrix(double** matrix, int r, int c){
	for (int i=0;i<r;i++){
		for (int j=0;j<c;j++){
			printf("%.0f",matrix[i][j]);
		}
		printf("\n");
	}
	//printf("\n");
}

double** free_matrix(double** matrix, int r, int c){
	for (int i=0;i<r;i++)
		free(matrix[i]);
	return matrix;
}

int main(int argc, char **argv)
{
//	fprintf(stderr, "%s: not implemented\n", argv[0]);
	
	FILE* train=fopen(argv[1],"r");
	FILE* data=fopen(argv[2],"r");

	char* test1=malloc(10*sizeof(char));
	char* test2=malloc(10*sizeof(char));

	fscanf(train,"%s\n",test1);
	fscanf(data,"%s\n",test2);

	int k,n,m;

	fscanf(train,"%d\n%d\n",&k,&n);
	fscanf(data,"%d\n%d\n",&k,&m);

	double** matrix_train=allocate_matrix((double)n,(double)k+1);
	for (int r=0;r<n;r++){
		for (int c=0;c<k+1;c++){
			if (c<k)
				fscanf(train,"%lf ",&matrix_train[r][c]);
			else
				fscanf(train,"%lf\n",&matrix_train[r][c]);			
		}
	}

	double** matrix_X=allocate_matrix((double)n,(double)k+1);
	double** matrix_Y=allocate_matrix((double)n,1);

	for (int r=0;r<n;r++){
		for (int c=0;c<k+1;c++){
			if (c==0)
				matrix_X[r][c]=1;
			else
				matrix_X[r][c]=matrix_train[r][c-1];
		}
	}

	for (int r=0;r<n;r++)
		matrix_Y[r][0]=matrix_train[r][k];


	//printf("%d %d %d\n",k,n,m);

       
	/*print_matrix(matrix_train,n,k+1);
	print_matrix(matrix_X,n,k+1);
	print_matrix(matrix_Y,n,1);*/
	
	double** transpose_X=transpose(matrix_X, n, k+1);
	//print_matrix(transpose_X,k+1,n);

	double** xTx=multiply(transpose_X,matrix_X,k+1,n,n,k+1);
	//print_matrix(xTx,k+1,k+1);

	double** inverse_xTx=inverse(xTx,k+1);
	//print_matrix(inverse_xTx,k+1,k+1);

	double** inverseXT=multiply(inverse_xTx,transpose_X,k+1,k+1,k+1,n);
	//print_matrix(inverseXT,k+1,n);

	double** matrix_W=multiply(inverseXT,matrix_Y,k+1,n,n,1);
	//print_matrix(matrix_W,k+1,1);

	double** matrix_data=allocate_matrix(m,k);
        for (int r=0;r<m;r++){
                for (int c=0;c<k;c++){
                        if (c<k)
                                fscanf(data,"%lf ",&matrix_data[r][c]);
                        else
                                fscanf(data,"%lf\n",&matrix_data[r][c]);   
                }
        }
	
	double** new_X=allocate_matrix(m,k+1);
        for (int r=0;r<m;r++){
                for (int c=0;c<k+1;c++){
                        if (c==0)
                                new_X[r][c]=1;
                        else
                                new_X[r][c]=matrix_data[r][c-1];
                }
        }	
	
	double** new_Y=multiply(new_X,matrix_W,m,k+1,k+1,1);
	print_matrix(new_Y,m,1);
         
	free(test1);
	free(test2);

	for (int i=0;i<n;i++)
                 free(matrix_train[i]);
        free(matrix_train);	

	for (int i=0;i<m;i++)
		free(matrix_data[i]);
	free(matrix_data);

	for (int i=0;i<n;i++)
	        free(matrix_X[i]);
	free(matrix_X);

        for (int i=0;i<n;i++)
                free(matrix_Y[i]);
	free(matrix_Y);

        for (int i=0;i<k+1;i++)
                free(transpose_X[i]);
	free(transpose_X);

        for (int i=0;i<k+1;i++)
                free(xTx[i]);
	free(xTx);

        for (int i=0;i<k+1;i++)
                free(inverse_xTx[i]);	
	free(inverse_xTx);

        for (int i=0;i<k+1;i++)
                free(inverseXT[i]);
	free(inverseXT);

        for (int i=0;i<k+1;i++)
                free(matrix_W[i]);
	free(matrix_W);

        for (int i=0;i<m;i++)
                free(new_X[i]);
	free(new_X);

        for (int i=0;i<m;i++)
                free(new_Y[i]);
	free(new_Y);
	/*matrix_X=free_matrix(matrix_X,n,k+1);
		free(matrix_X);

	matrix_Y=free_matrix(matrix_Y,n,1);
		free(matrix_Y);

	transpose_X=free_matrix(transpose_X,k+1,n);
		free(transpose_X);
	
	xTx=free_matrix(xTx,k+1,k+1);
		free(xTx);

	inverse_xTx=free_matrix(inverse_xTx,k+1,k+1);
		free(inverse_xTx);

	inverseXT=free_matrix(inverseXT,k+1,n);
		free(inverseXT);

	matrix_W=free_matrix(matrix_W,k+1,1);
		free(matrix_W);

	new_X=free_matrix(new_X,m,k+1);
		free(new_X);
	new_Y=free_matrix(new_Y,m,1);
		free(new_Y);*/

	//printf("%s %s\n",test1,test2);
	
	
//	return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
