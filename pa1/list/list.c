/* CS 211 PA1: list
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{
	int val;
	struct node* next;
};


struct node * insert(struct node* head,int num);
struct node * delete(struct node* head, int num);
void print (struct node* head);
int size(struct node* head);

struct node* insert(struct node* head, int num){

        struct node * prev=NULL;
        struct node * curr=head;

        struct node * temp=malloc(sizeof(struct node));
        temp->val=num;
        temp->next=NULL;

        while (curr!=NULL){
                if (num< curr->val)
                        break;
                else if (num==curr->val)
                        return head;
                prev=curr;
                curr=curr->next;
        }

        temp->next=curr;
        if (prev!=NULL)
                prev->next=temp;

        else
                head=temp;

        return head;

}


struct node * delete(struct node* head, int num){
        struct node * prev=NULL;
        struct node * curr=head;

        while (curr!=NULL){
                if (num<curr->val)
                        return head;
                else if (num==curr->val)
                        break;
                prev=curr;
                curr=curr->next;
        }

        if (curr==NULL)
                return head;
        if (prev==NULL)
                head=curr->next;
        else
                prev->next=curr->next;
        free(curr);
        return head;
}

void print(struct node * head){
        struct node* curr=head;
        if (head!=NULL){
                printf(" %d",curr->val);
                curr=curr->next;

                while (curr!=NULL){
                        printf(" %d",curr->val);
                        curr=curr->next;
                }
        }

        printf("\n");
}

int size_list(struct node * head){
        struct node * curr=head;
        int size=0;

        while (curr!=NULL){
                size++;
                curr=curr->next;
        }

        return size;
}

int main(int argc, char **argv)
{
//    printf("%s: not implemented\n", argv[0]);

	char* cmd=malloc(20*sizeof(char));
	int count=0;
	int goInsert=0;
	int goDelete=0;
	int val=0;
	struct node* head=NULL;
	while(scanf("%s[^D]",cmd)==1){
//		char dir='t';
//		int num=0;
	//	scanf("%c %d",&dir,&num);
		//scanf(" %c[^D]",&cmd[1]);
		
		if (count%2==0){
			//printf("%s ",cmd);
			if (cmd[0]==100){
				goDelete=1; //delete call here
				goInsert=0;
			}
			else if (cmd[0]==105){
				goInsert=1; //insert call here
				goDelete=0;
			}
		}
		else{
			//printf("%s\n",cmd);
			val=atoi(cmd); 
			if (goInsert==1)
				head=insert(head,val);
			else if (goDelete==1)
				head=delete(head,val);
			printf("%d :",size_list(head));
			print(head);
			//printf("Delete: %d\nInsert: %d\nValue: %d\n",goDelete,goInsert,val);
		}
		
		count++;
	}

    return EXIT_SUCCESS;
}
