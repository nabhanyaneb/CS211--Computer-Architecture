/* CS 211 PA4
 * Created for: nn291
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*struct HashNode allocate_node(struct HashNode node);
struct Gate allocate_gate(struct Gate gate, typedef enum kind_t dir, int n);
int checkOrAdd(char* name);*/

enum kind_t{ AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER };

struct HashNode{
	char* name;
	int val;
};

struct Gate{
	enum kind_t kind;
	int size;
	int* params;
};

struct HashNode allocate_node(struct HashNode node);
struct Gate allocate_gate(struct Gate gate, enum kind_t dir, int n);
int checkOrAdd(char* name);
void doAlgorithm(struct Gate* circuit);
void decToBinPrint(int num); 
struct HashNode getNode(int ptr);

int iNum,oNum;
int tNum=0;
int cSize=0;
struct HashNode* inputs, *outputs,*temps;
struct Gate* circuit;
struct HashNode allocate_node(struct HashNode node){
	node.name=malloc(100*sizeof(char));
	node.val=0;
	return node;
}

struct Gate allocate_gate(struct Gate gate, enum kind_t dir, int n){
	//gate.cmd=malloc(12*sizeof(char));
	gate.kind=dir;
	gate.size=n;
	gate.params=malloc(gate.size*sizeof(int));
	return gate;
}

int checkOrAdd(char* name){
	for (int i=0;i<iNum;i++){
		if (strcmp(inputs[i].name,name)==0)
			return i;
	}

	for (int o=0;o<oNum;o++){
		if (strcmp(outputs[o].name,name)==0)
			return iNum+o;
	}

	for (int t=0;t<tNum;t++){
		if (strcmp(temps[t].name,name)==0)
			return iNum+oNum+t;
	}

	temps[tNum]=allocate_node(temps[tNum]);
	temps[tNum].name=name;
	if (strcmp(name,"1")==0)
		temps[tNum].val=1;
	tNum++;
	return (iNum)+oNum+(tNum-1);	
}

/*int iNum,oNum;
int tNum=0;
struct HashNode* inputs, *outputs, *temps;*/
int main(int argc, char **argv)
{
    //printf("%s: not implemented\n", argv[0]);

	FILE* fp=fopen(argv[1],"r");
	char* dir=malloc(12*sizeof(char));

	//Initialize and Declare INPUTS

	fscanf(fp,"%s",dir);
	fscanf(fp,"%d",&iNum);

	inputs=malloc(iNum*sizeof(struct HashNode));
	
	for (int i=0;i<iNum;i++)
		inputs[i]=allocate_node(inputs[i]);

	for (int i=0;i<iNum;i++){
		if (i==iNum-1)
			fscanf(fp,"%s\n",inputs[i].name);
		else
			fscanf(fp,"%s",inputs[i].name);
	}

	//printf("%s ",dir);
	//for (int i=0;i<iNum;i++)
	//	printf("%s ",inputs[i].name);
	//printf("\n");

	
	//Initialize and Declare OUTPUTS	
		
	fscanf(fp,"%s",dir);
	fscanf(fp,"%d",&oNum);

	outputs=malloc(oNum*sizeof(struct HashNode));

	for (int o=0;o<oNum;o++)
		outputs[o]=allocate_node(outputs[o]);
	
	for (int o=0;o<oNum;o++){
		if (o==oNum-1)
			fscanf(fp,"%s\n",outputs[o].name);
		else 
			fscanf(fp,"%s",outputs[o].name);
	}

	//printf("%s ",dir);
	//for (int o=0;o<oNum;o++)
	//	printf("%s ",outputs[o].name);
	//printf("\n");
	
	circuit=malloc(sizeof(struct Gate));
	cSize=0;
	temps=malloc(100*sizeof(struct HashNode));
	temps[tNum]=allocate_node(temps[tNum]);
	
	
	//Building the Gate

	while(!feof(fp)){
	//	printf("starting loop\n");
		fscanf(fp,"%s",dir);

		enum kind_t nextKind;

		if (strcmp(dir,"AND")==0) nextKind=AND;
		if (strcmp(dir,"OR")==0) nextKind=OR;
		if (strcmp(dir,"NAND")==0) nextKind=NAND;
		if (strcmp(dir,"NOR")==0) nextKind=NOR;
		if (strcmp(dir,"XOR")==0) nextKind=XOR;
		if (strcmp(dir,"NOT")==0) nextKind=NOT;
		if (strcmp(dir,"PASS")==0) nextKind=PASS;
		if (strcmp(dir,"DECODER")==0) nextKind=DECODER;
		if (strcmp(dir,"MULTIPLEXER")==0) nextKind=MULTIPLEXER;

		if (strcmp(dir,"AND")==0 || strcmp(dir,"OR")==0 || strcmp(dir,"NAND")==0 || strcmp(dir,"NOR")==0 || strcmp(dir,"XOR")==0){

			char* name1=malloc(100*sizeof(char));
			char* name2=malloc(100*sizeof(char));
			char* name3=malloc(100*sizeof(char));
			fscanf(fp,"%s%s%s\n",name1,name2,name3);
			//printf("%s %s %s %s\n",dir,name1,name2,name3);
			
			int p1=checkOrAdd(name1);
			int p2=checkOrAdd(name2);
			int p3=checkOrAdd(name3);	

	//		
	//		printf("%s %s %s %s\n",dir,name1,name2,name3);
			circuit[cSize]=allocate_gate(circuit[cSize],nextKind,3);
	//		circuit[cSize].cmd=dir;
			circuit[cSize].params[0]=p1;
			circuit[cSize].params[1]=p2;
			circuit[cSize].params[2]=p3;
		
			//realloc(circuit, circuitSize+1*sizeof(struct HashNode);
			
		}

		else if (strcmp(dir,"NOT")==0 || strcmp(dir,"PASS")==0){

			char* name1=malloc(100*sizeof(char));
			char* name2=malloc(100*sizeof(char));
			fscanf(fp,"%s%s\n",name1,name2);
			
			int p1=checkOrAdd(name1);
			int p2=checkOrAdd(name2);

			circuit[cSize]=allocate_gate(circuit[cSize],nextKind,2);
                        circuit[cSize].params[0]=p1;
                        circuit[cSize].params[1]=p2;
		}

		else if (strcmp(dir,"DECODER")==0){ //DO LATER
			//printf("in decoder\n");
			int dim=0;
			fscanf(fp,"%d",&dim);
			int mySize=dim+pow(2,dim)+1;
			//printf("my Size is %d\n",mySize);
			circuit[cSize]=allocate_gate(circuit[cSize],nextKind,mySize);
			//printf("before for loop\n");
			for (int x=0;x<mySize-1;x++){
				char* name1=malloc(100*sizeof(char));
				if (x==mySize-2)
					fscanf(fp,"%s\n",name1);
				else 
					fscanf(fp,"%s",name1);
				int p=checkOrAdd(name1);
				circuit[cSize].params[x]=p;
				//printf("%d\n",p);
			}
			//printf("after for loop\n");
			circuit[cSize].params[mySize-1]=dim;
			//for (int s=0;s<mySize;s++)
			//	printf("%d ",circuit[cSize].params[s]);
			//printf("\n");
		}
		
		else if (strcmp(dir,"MULTIPLEXER")==0){ //DO LATER
			int s=0;
			fscanf(fp,"%d",&s);
			int mySize=pow(2,s)+s+1+1;
			circuit[cSize]=allocate_gate(circuit[cSize],nextKind,mySize);
			for (int x=0;x<pow(2,s);x++){ 	//input
				char* name1=malloc(100*sizeof(char));
				fscanf(fp,"%s",name1);
				int p=checkOrAdd(name1);
				circuit[cSize].params[x]=p;

				if (strcmp(name1,"0")==0)
					circuit[cSize].params[x]=-1;
				
				if (strcmp(name1,"1")==0)
					circuit[cSize].params[x]=-2;
				
			}

			for (int x=pow(2,s);x<pow(2,s)+s+1;x++){	//selector and output
				char* name2=malloc(100*sizeof(char));
				if (x==pow(2,s)+s)
					fscanf(fp,"%s\n",name2);
				else 
					fscanf(fp,"%s",name2);
				int p=checkOrAdd(name2);
				circuit[cSize].params[x]=p;
			}
			circuit[cSize].params[mySize-1]=s;

			
		}
		//printf("end of iteration\n");
		cSize++;		
		circuit=realloc(circuit, 2*cSize*sizeof(struct Gate));	
		
	
	}
	
	//printf("TEMPS ");	
	//for (int t=0;t<tNum;t++)
	//	printf("%s ",temps[t].name);
	//printf("\n");
	
	//const char* kindNames[]={"AND","OR","NAND","NOR","XOR","NOT","PASS","DECODER","MULTIPLEXER"};

	//for (int s=0;s<cSize;s++){
	//	printf("%s: ",kindNames[circuit[s].kind]);
	//	for (int c=0;c<circuit[s].size;c++)
	//		printf("%d ",circuit[s].params[c]);
	//}
	//printf("\n");
	//printf("Circuit Size: %d\n",cSize);
	doAlgorithm(circuit);
    return EXIT_SUCCESS;
}


void doAlgorithm(struct Gate* circuit){
	double twoN=pow(2,iNum);
	int count=0;
	while (count<twoN){
//		decToBinPrint(count);
		int* a = malloc(iNum*sizeof(int));
		int n=count;
		int z;	
		for (z=0;n>0;z++){
			a[z]=n%2;
			n/=2;
		}
	
		for (int y=z;y<iNum;y++)
			a[y]=0;

        	for (z=iNum-1;z>=0;z--){
                	inputs[iNum-1-z].val=a[z];
			//if (z==0)
			//	printf("%d",inputs[iNum-1-z].val);

                	printf("%d ",inputs[iNum-1-z].val);
        	}
        	printf("| ");		
		
		for (int g=0;g<cSize;g++){
		//	printf("Iteration %d\n",g);
			switch(circuit[g].kind){
				case 0: {

					struct HashNode first;
					int ptr=circuit[g].params[0];
					if (ptr<iNum){
                 				first= inputs[ptr];
					}
       					else if (ptr>=iNum && ptr<oNum+iNum){
                				first= outputs[ptr-iNum];
					}
        				else{
						 first= temps[ptr-iNum-oNum];
					}
		
					/*printf("%s %d\n",first.name,first.val);*/
					
					struct HashNode second;
					ptr=circuit[g].params[1];

                                    	if (ptr<iNum){
                                                second= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                second= outputs[ptr-iNum];
                                        }
                                        else{
                                                 second= temps[ptr-iNum-oNum];
                                        }
					/*printf("%s %d\n",second.name,second.val);*/

					struct HashNode comp;
					ptr=circuit[g].params[2];	
                                        if (ptr<iNum){
                                                comp= inputs[ptr]; 
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];
						
                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

					if (first.val==1 && second.val==1)
						comp.val=1;
					else 
						comp.val=0;
	
					if (ptr<iNum){
						inputs[ptr].val=comp.val;
					}	
					else if (ptr>=iNum && ptr<oNum+iNum){
						outputs[ptr-iNum].val=comp.val;
					}				
					else{
						temps[ptr-iNum-oNum].val=comp.val;
					}	
					break;			
				}
				case 1: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/

                                        struct HashNode second;
                                        ptr=circuit[g].params[1];

                                        if (ptr<iNum){
                                                second= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                second= outputs[ptr-iNum];
                                        }
                                        else{
                                                 second= temps[ptr-iNum-oNum];
                                        }
                                        /*printf("%s %d\n",second.name,second.val);*/

                                        struct HashNode comp;
                                        ptr=circuit[g].params[2];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                        if (first.val==1 || second.val==1)
                                                comp.val=1;
                                        else
                                                comp.val=0;

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
					break;
				}
				case 2: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/

                                        struct HashNode second;
                                        ptr=circuit[g].params[1];

                                        if (ptr<iNum){
                                                second= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                second= outputs[ptr-iNum];
                                        }
                                        else{
                                                 second= temps[ptr-iNum-oNum];
                                        }
                                        /*printf("%s %d\n",second.name,second.val);*/

                                        struct HashNode comp;
                                        ptr=circuit[g].params[2];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                        if (first.val!=1 || second.val!=1)
                                                comp.val=1;
                                        else
                                                comp.val=0;

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
                                        break;
				}
				case 3: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/

                                        struct HashNode second;
                                        ptr=circuit[g].params[1];

                                        if (ptr<iNum){
                                                second= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                second= outputs[ptr-iNum];
                                        }
                                        else{
                                                 second= temps[ptr-iNum-oNum];
                                        }
                                        /*printf("%s %d\n",second.name,second.val);*/

                                        struct HashNode comp;
                                        ptr=circuit[g].params[2];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                        if (first.val!=1 && second.val!=1)
                                                comp.val=1;
                                        else
                                                comp.val=0;

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
                                        break;

				}
                                case 4: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/

                                        struct HashNode second;
                                        ptr=circuit[g].params[1];

                                        if (ptr<iNum){
                                                second= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                second= outputs[ptr-iNum];
                                        }
                                        else{
                                                 second= temps[ptr-iNum-oNum];
                                        }
                                        /*printf("%s %d\n",second.name,second.val);*/

                                        struct HashNode comp;
                                        ptr=circuit[g].params[2];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                        if ((first.val==1 && second.val==0) || (second.val==1 && first.val==0))
                                                comp.val=1;
                                        else
                                                comp.val=0;

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
                                        break;

                                }
                                case 5: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/

                                      

                                        struct HashNode comp;
                                        ptr=circuit[g].params[1];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                        if (first.val==0)
                                                comp.val=1;
                                        else
                                                comp.val=0;

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
                                        break;
                                }
                                case 6: {
                                        struct HashNode first;
                                        int ptr=circuit[g].params[0];
                                        if (ptr<iNum){
                                                first= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                first= outputs[ptr-iNum];
                                        }
                                        else{
                                                 first= temps[ptr-iNum-oNum];
                                        }

                                        /*printf("%s %d\n",first.name,first.val);*/



                                        struct HashNode comp;
                                        ptr=circuit[g].params[1];
                                        if (ptr<iNum){
                                                comp= inputs[ptr];
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                comp= outputs[ptr-iNum];
                                        }
                                        else{
                                                comp= temps[ptr-iNum-oNum];

                                        }
                                        /*printf("%s %d\n",comp.name,comp.val);*/

                                     	comp.name=first.name;
					comp.val=first.val;
                                                
                                    

                                        if (ptr<iNum){
                                                inputs[ptr].val=comp.val;
                                        }
                                        else if (ptr>=iNum && ptr<oNum+iNum){
                                                outputs[ptr-iNum].val=comp.val;
                                        }
                                        else{
                                                temps[ptr-iNum-oNum].val=comp.val;
                                        }
                                        break;
                                }
                                case 7: {
					//printf("Case 7\n");
					//printf("i am in here buddy\n");
					int dim=circuit[g].params[circuit[g].size-1];
					//printf("my dim is: %d\n",dim);
					//printf("dimwit\n");
					int twoDim=pow(2,dim);
					//printf("%d\n",twoDim);
					int ptr=0;
					struct HashNode* dIns=malloc(dim*sizeof(struct HashNode));
					struct HashNode* dOuts=malloc(twoDim*sizeof(struct HashNode));
					
					//printf("i got here! %d \n",dim);
					for (int d=0;d<dim;d++){
						ptr=circuit[g].params[d];

						if (ptr<iNum){
							dIns[d].name=inputs[ptr].name;
							dIns[d].val=inputs[ptr].val;
						}
						else if (ptr>=iNum && ptr<oNum+iNum){
							dIns[d].name=outputs[ptr-iNum].name;
							dIns[d].val=outputs[ptr-iNum].val;
						}
						else{
							dIns[d].name=temps[ptr-iNum-oNum].name;
							dIns[d].val=temps[ptr-iNum-oNum].val;
						}
		
					}
					//printf("fuckityfuckityfuck!\n");
					for (int d=0;d<twoDim;d++){
						//printf("in here\n");
						ptr=circuit[g].params[d+dim];
						//printf("PTR: %d\n",ptr);
						if (ptr<iNum){
						//	printf("FUCK\n");
							dOuts[d].name=inputs[ptr].name;
							dOuts[d].val=0;
						}
						else if (ptr>=iNum && ptr<oNum+iNum){
						//	printf("FUCK2\n");
							dOuts[d].name=outputs[ptr-iNum].name;
							dOuts[d].val=0;
						}
						else{
						//	printf("FUCK3\n");
							dOuts[d].name=temps[ptr-iNum-oNum].name;
							dOuts[d].val=0;
						}
						//printf("down here\n");
					}

					for (int i=0;i<twoDim;i++){
						int* b=malloc(dim*sizeof(int));
						int  j=i;
						int x;
						int chk=1;
						for (x=0;j>0;x++){
							b[x]=j%2;
							j/=2;
						}
						for (int k=x;k<dim;k++)
							b[k]=0;

						for (int k=0;k<dim;k++){
							if (b[dim-k-1]!=dIns[k].val)
								chk=0;
						}
						if (chk==1)
							dOuts[i].val=1;
						ptr=circuit[g].params[i+dim];	
                                        	if (ptr<iNum){
                                                	inputs[ptr].val=dOuts[i].val;
                                        	}	
                                        	else if (ptr>=iNum && ptr<oNum+iNum){
                                                	outputs[ptr-iNum].val=dOuts[i].val;
                                       		}
                                       		else{
                                                	temps[ptr-iNum-oNum].val=dOuts[i].val;
                                        	}
						
					}
					break;
                                }
                                case 8: {
					int s=circuit[g].params[circuit[g].size-1];
					int twoS=pow(2,s);

					struct HashNode* mIn=malloc(twoS*sizeof(struct HashNode));
					struct HashNode* mSel=malloc(s*sizeof(struct HashNode));
					struct HashNode mOut;

					int ptr=0;

					for (int x=0;x<twoS;x++){
						ptr=circuit[g].params[x];

						if (ptr==-1){
							mIn[x].name="0";
							mIn[x].val=0;
						}
						else if (ptr==-2){
							mIn[x].name="1";
							mIn[x].val=1;
						}
						else if (ptr<iNum){
							mIn[x].name=inputs[ptr].name;
							mIn[x].val=inputs[ptr].val;
						}
						else if (ptr>=iNum && ptr<oNum+iNum){
							mIn[x].name=outputs[ptr-iNum].name;
							mIn[x].val=outputs[ptr-iNum].val;
						}
						else{
							mIn[x].name=temps[ptr-iNum-oNum].name;
							mIn[x].val=temps[ptr-iNum-oNum].val;
						}
					}
							
					for (int x=twoS;x<twoS+s;x++){
						ptr=circuit[g].params[x];

                                                if (ptr==-1){
                                                        mSel[x-twoS].name="0";
                                                        mSel[x-twoS].val=0;
                                                }
                                                else if (ptr==-2){
                                                        mSel[x-twoS].name="1";
                                                        mSel[x-twoS].val=1;
                                                }
                                                else if (ptr<iNum){
                                                        mSel[x-twoS].name=inputs[ptr].name;
                                                        mSel[x-twoS].val=inputs[ptr].val;
                                                }
                                                else if (ptr>=iNum && ptr<oNum+iNum){
                                                        mSel[x-twoS].name=outputs[ptr-iNum].name;
                                                        mSel[x-twoS].val=outputs[ptr-iNum].val;
                                                }
                                                else{
                                                        mSel[x-twoS].name=temps[ptr-iNum-oNum].name;
                                                        mSel[x-twoS].val=temps[ptr-iNum-oNum].val;
                                                }
	
					}

						ptr=circuit[g].params[twoS+s];
                                                
						if (ptr==-1){
                                                        mOut.name="0";
                                                        mOut.val=0;
                                                }
                                                else if (ptr==-2){
                                                        mOut.name="1";
                                                        mOut.val=0;
                                                }
                                                else if (ptr<iNum){
                                                        mOut.name=inputs[ptr].name;
                                                        mOut.val=0;
                                                }
                                                else if (ptr>=iNum && ptr<oNum+iNum){
                                                        mOut.name=outputs[ptr-iNum].name;
                                                        mOut.val=0;
                                                }
                                                else{
                                                        mOut.name=temps[ptr-iNum-oNum].name;
                                                        mOut.val=0;
                                                }

						for (int i=0;i<twoS;i++){
                                                	int* b=malloc(s*sizeof(int));
                                                	int  j=i;
                                                	int x;
                                                	int chk=1;
                                                	for (x=0;j>0;x++){
                                                        	b[x]=j%2;
                                                        	j/=2;
                                                	}
                                                	for (int k=x;k<s;k++)
                                                        	b[k]=0;

                                                	for (int k=0;k<s;k++){
                                                        	if (b[s-k-1]!=mSel[k].val)
                                                                	chk=0;
                                               		}	
			
							if (chk==1)
								mOut.val=mIn[i].val;
													
						}	

                                                if (ptr<iNum){
                                                        inputs[ptr].val=mOut.val;
                                                }
                                                else if (ptr>=iNum && ptr<oNum+iNum){
                                                        outputs[ptr-iNum].val=mOut.val;
                                                }
                                                else{
                                                        temps[ptr-iNum-oNum].val=mOut.val;
                                                }
					break;
                                }		
			}	
	
		}
		for (int o=0;o<oNum;o++){
			printf("%d",outputs[o].val);
			if (o!=oNum-1)
				printf(" ");
		}
		printf("\n");
		count++;
	}
}

void decToBinPrint(int num){

	int* a=malloc(iNum*sizeof(int));
	
	int n,i;
	n=num;
	for (i=0;n>0;i++){
		a[i]=n%2;
		n/=2;
	}

	for (int z=i;z<iNum;z++)
		a[z]=0;

	for (i=iNum-1;i>=0;i--){
		inputs[iNum-1-i].val=a[i];
	//	printf("%d ",inputs[iNum-1-i].val);
	}
	//printf("| ");

}

struct HashNode getNode(int ptr){
	struct HashNode ret;
	if (ptr<iNum){
		 ret= inputs[ptr];
	}
	if (ptr>=iNum && ptr<oNum){
		ret= outputs[ptr-iNum];
	}
	else{
	 ret= temps[ptr-iNum-oNum];
	}
	return ret;
}
