/* CS 211 PA1: bst
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>

struct node{
        int value;
        struct node* left;
        struct node* right;
};

struct node* root;

struct node* newNode(int val, struct node* left, struct node* right);
struct node* insert(struct node* BST, int val);
struct node* delete(struct node* BST, struct node* origBST, int val);
int search(struct node* BST, int val,int printIt);
void print(struct node* BST);
void freeBST(struct node* bst);

void print(struct node* BST){
	if(BST){
		printf("(");
		print(BST->left);
		printf("%d",BST->value);
		print(BST->right);
		printf(")");
	}
}

struct node* newNode(int val, struct node* left, struct node* right){
        struct node* n=malloc(sizeof(struct node));
        n->value=val;
        n->left=left;
        n->right=right;
        return n;
}

struct node* insert(struct node* BST, int val){
        int level=1;
        if (BST==NULL){
        printf("inserted");
        printf("\n");
        return newNode(val,NULL,NULL);
        }
        int added=0;
        struct node* ptr=BST;

        while (added==0){
                if (val==ptr->value){
                        printf("not inserted\n");
                        return BST;
                }
                else if (val> ptr->value){
                        if (ptr->right==NULL){
                                added=1;
                                level++;
                                printf("inserted\n");
                          
                                ptr->right=newNode(val,NULL,NULL);
                        }
                        else {
                                ptr=ptr->right;
                                level++;
                        }
                }else if (val<ptr->value){
                        if (ptr->left==NULL){
                                added=1;
                                level++;
                                printf("inserted\n");
                                
                                ptr->left=newNode(val,NULL,NULL);
                        }
                        else {
                                ptr=ptr->left;
                                level++;
                        }
                }
        }

        return BST;
}


int search(struct node* BST, int val,int printIt){
        struct node* ptr=BST;
        int level=1;
        while (ptr!=NULL){
                if (ptr->value==val){

                        return level;
                }
                if (ptr->value>val){
                        level++;
                        ptr=ptr->left;
                }

                else if(ptr->value<val){
                        level++;
                        ptr=ptr->right;
                }
        }
        //if (printIt==1) printf("absent\n");
        return 0;
}

struct node* delete(struct node* BST, struct node* origBST,int val){
        if (BST==NULL){
                return BST;
        }

        if (val< BST->value)
                BST->left = delete(BST->left,origBST,val);
        else if (val > BST->value)
                BST->right=delete(BST->right,origBST,val);

        else{
                if (BST->left==NULL && BST->right==NULL)
                        BST=NULL;
                else if (BST->left==NULL){
                        struct node * tempNode= BST->right;
                        free(BST);
                        return tempNode;

                }

                else if (BST->right==NULL){
                        struct node * tempNode= BST->left;
                        free(BST);
                        return tempNode;
                }

                else{


                        struct node* tempNode=BST->right;

                        while (tempNode!=NULL){
                                if (tempNode->left==NULL)
                                        break;
                                else tempNode=tempNode->left;
                        }
                        BST->value=tempNode->value;
                        BST->right=delete(BST->right, origBST,tempNode->value);
                }

        }
        return BST;
}

struct node* findMin(struct node* BST);

struct node* findMin(struct node* BST){
        if (BST->left==NULL)
                return BST;
        return findMin(BST->left);
}

void freeBST(struct node* bst) {
    if (bst->left != NULL) {
        freeBST(bst->left);
    }
    if (bst->right != NULL) {
        freeBST(bst->right);
    }
    free(bst);
}

int main(int argc, char **argv)
{
    //printf("%s: not implemented\n", argv[0]);


	char* cmd=malloc(20*sizeof(char));

	int count=0;
	int goInsert=0;
	int goDelete=0;
	int goSearch=0;
	int goPrint=0;
	
	struct node* BST=NULL;
    	int val=0;

	while(scanf("%s[^D]",cmd)==1){
		if (count%2==0){
			//printf("%s ",cmd);
			if (cmd[0]==100){ //d
				goInsert=0;
				goDelete=1;
				goSearch=0;
				goPrint=0;
			}	
                        if (cmd[0]==105){ //i
                                goInsert=1;
                                goDelete=0;
                                goSearch=0;
                                goPrint=0;
                        }
			if (cmd[0]==115){ //s
                                goInsert=0;
                                goDelete=0;
                                goSearch=1;
                                goPrint=0;
                       	}
                        if (cmd[0]==112){ //p
                                goInsert=0;
                                goDelete=0;
                                goSearch=0;
                                goPrint=1;
				count++;
				//printf("\n");
				val=0;
				print(BST);
				printf("\n");
                        }
		}

		else{
			//printf("%s\n",cmd);
			val=atoi(cmd);

			if (goInsert==1)
				BST=insert(BST,val);
			else if(goSearch==1){
				int check=search(BST,val,1);
				if (check>=1)
					printf("present\n");
				else
					printf("absent\n");				
			}	
			else if (goDelete==1){
			        int chk=search(BST,val,0);
                        	if (chk>=1){
                                	printf("deleted\n");
                                	BST=delete(BST,BST,val);
                        	}
                        	else
					printf("absent\n");
                        	BST=delete(BST,BST,val);
			}
			//printf("Delete: %d\nInsert: %d\nSearch: %d\nPrint: %d\nValue: %d\n",goDelete,goInsert,goSearch,goPrint,val);
		}
	
		count++;
	}	
	freeBST(BST);
	return EXIT_SUCCESS;
}
