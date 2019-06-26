#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node *right;
	struct Node *child;
	struct Node *parent;
	struct Node *leaf;
};
void reading(char *,struct Node *);
void readingCommands(char *,struct Node*);
struct Node* insert(struct Node*,int,int *);
struct Node* DFS(struct Node*,int);
void list(struct Node*,FILE *);
void main(void) {
	struct Node* root = NULL;
	root  = (struct Node*)malloc(sizeof(struct Node));
	char in1[512],in2[512];
	scanf("%s",&in1);
	scanf("%s",&in2);
    reading(in1,root);
	readingCommands(in2,root);
	DFS(root,-1);

}
void reading(char *path,struct Node* root) {
    FILE *input_file,*input_file2;
    char  line[255];
    int first,second,third,forth;
    int checker=0,i;
	struct Node* childNodes=NULL;
	childNodes=(struct Node*)malloc(sizeof(struct Node));
	
    if ((input_file = fopen(path,"r")) == NULL) {
        printf("Error! opening file");

        /* Program exits if the file pointer returns NULL. */
    } else {
        input_file2 = fopen(path,"r");
        while (!feof(input_file))
        {
			int *numbers;
            if(checker==0) {
                fscanf(input_file2,"%d %d",&first,&second);
				root->data=first;
				root->parent=NULL;
				root->right=NULL;
				root->child=NULL;
				/*add root*/
				numbers = (int*) malloc(second * sizeof(int));
                for(i=0; i<second; i++) {
                    fscanf(input_file2,"%d %d",&third,&forth);
					numbers[i]=third;
					if(root->child==NULL){
						struct Node *temp=NULL;
						temp=(struct Node*)malloc(sizeof(struct Node));
						temp->data=third;
						temp->parent=root;
						temp->child=NULL;
						temp->right=NULL;
						root->child=temp;
					}else{
						struct Node *temp=NULL;
						temp=root->child;
						while(temp->right!=NULL){
							temp=temp->right;
						}
						struct Node *newNode=NULL;
						newNode=(struct Node*)malloc(sizeof(struct Node));
						newNode->data=third;
						newNode->parent=root;
						newNode->child=NULL;
						newNode->right=NULL;
						temp->right=newNode;
						temp->leaf=newNode;

					}
                }
				childNodes=root->child;
                fgets(line, sizeof(line), input_file);
                checker=1;
				free(numbers);
            } else {
				int checker2=0;
                fgets(line, sizeof(line), input_file);
                sscanf(line,"%d %d",&first,&second);
				numbers = (int*) malloc(second * sizeof(int));
                for(i=0; i<second; i++) {
                    if(!feof(input_file2)) {
                        fscanf(input_file2,"%d %d",&third,&forth);
						numbers[i]=third;
						checker2=1;
                    }
					
                }
				if(checker2){
					
					for(i=0; i<second; i++) {
					if(numbers[i]==0){
						second--;
						}
					}
					/*second means number of nodes will be added to tree*/
					/*numbers,second*/
					/*add numbers array to tree*/
					childNodes=insert(childNodes,second,numbers);
					
					
				}
	

				/*free numbers array for next insertions*/
				free(numbers);

            }
        }

    }
}
void readingCommands(char *path,struct Node *nodex){
	FILE *input_file;
	char first;
	int second;
	if ((input_file = fopen(path,"r")) == NULL) {
        printf("Error! opening file");

        /* Program exits if the file pointer returns NULL. */
    }else{
		while (!feof(input_file)){
			fscanf(input_file,"%c %d\n",&first,&second);
			
			if(first=='d'){
				struct Node* delNode=NULL;
				delNode=DFS(nodex,second);
				
				if(delNode!=NULL){
				
				if(delNode->child==NULL){/*that means this node is child node*/
					int checker=0;
					if(delNode==delNode->parent->child){/*first child of the it's parent node*/
						if(delNode->right==NULL){
							delNode->parent->child=NULL;

							free(delNode);/*There is a bug:If we delete all child nodes of same node there will be fault in DFS algorithm*/
						}else{
						delNode->parent->child=delNode->right;

						free(delNode);
						}
						checker=1;

					}
					if(delNode->right==NULL&&checker==0){/*the last child of the it's parent node*/
						struct Node* temp=NULL;
						temp=delNode->parent->child;
						while(temp->right!=delNode){
							temp=temp->right;
						}
						temp->right=NULL;
					
						free(delNode);
						checker=1;
						
					}
					if(checker!=1){
						
						struct Node* temp=NULL;
						temp=delNode->parent->child;
						while(temp->right!=delNode){
							temp=temp->right;
						}
						temp->right=delNode->right;

						free(delNode);
					}
				}
				if(delNode->parent==NULL){/*delete root Node*/
					struct Node* temp=NULL;
					struct Node* temp2=NULL;
					struct Node* temp3=NULL;
					struct Node* temp4=NULL;
					temp=delNode->child->right;
					temp3=delNode->child;
					nodex->data=temp3->data;
					temp3->right=NULL;
					if(temp3->child!=NULL){
					nodex->child=temp3->child;
					
					temp4=nodex->child;
					while(temp4->right!=NULL){
						temp4=temp4->right;
					}
					temp4->right=temp;
					
					temp4=nodex->child;
					while(temp4->right!=NULL){
						temp4->parent=nodex;
						temp4=temp4->right;
					}
					temp4->parent=nodex;	
					}else{
						nodex->child=temp;
					}		
				}
				if(delNode->parent!=NULL&&delNode->child!=NULL){/*delete leaf node*/
					int checker=0;
					if(delNode==delNode->parent->child){/*if deleted node was most left child*/
						struct Node* temp=NULL;
						temp=delNode->child;
						delNode->parent->child=delNode->child;
						while(temp->right!=NULL){
							temp->parent=delNode->parent;
							temp=temp->right;
						}temp->right=delNode->right;
						checker=1;
					}
					if(delNode->right==NULL&&checker==0){/*if deleted node was most right child*/
						struct Node* temp=NULL;
						temp=delNode->parent->child;
						while(temp->right!=delNode){
							temp=temp->right;
						}
						
						temp->right=delNode->child;
						while(temp->right!=NULL){
							temp->parent=delNode->parent;
							temp=temp->right;
						}
						temp->parent=delNode->parent;
						checker=1;
					}
					if(checker!=1){/*if deleted node was middle child*/
						struct Node* rightx=NULL;
						struct Node* leftx=NULL;
						leftx=delNode->parent->child;
						rightx=delNode->right;
						
						while(leftx->right!=delNode){
							leftx=leftx->right;
						}
						
						leftx->right=delNode->child;
						while(leftx->right!=NULL){
							leftx->parent=delNode->parent;
							leftx=leftx->right;
						}
						leftx->right=rightx;
					}
				}
				}
				
			}else{
				struct Node* listNode=NULL;
				listNode=DFS(nodex,second);
				if(listNode!=NULL){
					FILE *output;
					output=fopen("output.txt","a");
					
					struct Node* newnode=NULL;
					newnode=(struct Node*)malloc(sizeof(struct Node));
					newnode->right=NULL;
					newnode->parent=NULL;
					newnode->child=listNode->child;
					newnode->data=listNode->data;
					
					list(listNode,output);
					fprintf(output,"\n");
				}
			}
		
		}
	}
}
struct Node* insert(struct Node* childNodes,int numberOfNodes,int *numbers){
	int i,numberOfChild=0;
	struct Node *temp=NULL;
	struct Node *headChild=NULL;
	
	headChild=childNodes;
	temp=childNodes;
	
	while(temp!=NULL){
		temp=temp->leaf;
		numberOfChild++;
		/*find number of child nodes*/
	}
	free(temp);
	if(numberOfNodes<=numberOfChild){
		/*If number of child nodes are enough for insertion*/

		for(i=0;i<numberOfNodes;i++){
		struct Node *newNode=NULL;
		newNode=(struct Node*)malloc(sizeof(struct Node));
		newNode->data=numbers[i];
		newNode->parent=childNodes;
		newNode->child=NULL;
		newNode->right=NULL;
		newNode->leaf=childNodes->leaf;
		childNodes->child=newNode;
		childNodes=childNodes->leaf;
		}
		headChild=headChild->child;
		/*this is new head of child nodes*/
		
		struct Node *temp2=NULL;
		temp2=headChild;
		/*copy the head of child nodes for traversing and relinking*/
		for(i=0;i<numberOfNodes-1;i++){
			headChild->leaf=headChild->leaf->child;
			headChild=headChild->leaf;
		}
		
		return temp2;
	}else{/*If number of child nodes are not enough for instertion*/
		for(i=0;i<numberOfNodes;i++){
			struct Node *newNode=NULL;
			newNode=(struct Node*)malloc(sizeof(struct Node));
			newNode->data=numbers[i];
			newNode->parent=childNodes;
			newNode->child=NULL;
			newNode->right=NULL;
			if(childNodes!=NULL){
				if(childNodes->child==NULL){
					childNodes->child=newNode;
					/*add first child*/
				}else{
					struct Node *temp=NULL;
					temp=childNodes->child;
					while(temp->right!=NULL){
						temp=temp->right;
					}
					temp->right=newNode;
					temp->leaf=newNode;
					/*traverse all children*/
				}
				childNodes=childNodes->leaf;
			}else{
				
				childNodes=headChild;
		
				struct Node *temp=NULL;
				temp=childNodes->child;
				while(temp->right!=NULL){
					temp=temp->right;
				}
				newNode->parent=temp->parent;
				temp->right=newNode;
				temp->leaf=newNode;
					/*traverse all children*/
				childNodes=childNodes->leaf;
				/*return beginning of the list and add new nodes to tree*/
			}
			
		}
		struct Node *temp2=NULL;
		struct Node *temp3=NULL;
		temp2=headChild;
		temp3=headChild->child;
		for(i=0;i<numberOfChild-1;i++){
			temp2=headChild->child;
			while(temp2->leaf!=NULL){
				temp2=temp2->leaf;
			}
			temp2->leaf=headChild->leaf->child;
			headChild=headChild->leaf;
		}
		return temp3;
		
		
	}
	
}
struct Node* DFS(struct Node* nodex,int key){
	struct Node *temp=NULL;
	struct Node *RA=NULL;
	temp=nodex;
	if(temp->data==key){
		return temp;
	}
	else{
	while(temp->child!=NULL){
		temp=temp->child;
		if(temp->data==key){
		DFS(temp,key);
		return;
		}
		
	}
	while(temp->right!=NULL){
		
		if(temp->child!=NULL){
			DFS(temp,key);
			return;
		}
		temp=temp->right;
		if(temp->data==key){
		DFS(temp,key);
		return;
		}
	}
	if(temp->child!=NULL){
		DFS(temp,key);
	}
	while(temp->parent!=NULL){
		temp=temp->parent;

		if(temp->right!=NULL){
			DFS(temp->right,key);
			return;
		}else{
			return;
		}
	}
	}
}
void list(struct Node* nodex,FILE *output){
	struct Node *temp=NULL;
	temp=nodex;
	while(temp->child!=NULL){
		fprintf(output,"%d,",temp->data);
		printf("%d\n",temp->data);
		temp=temp->child;
		
	}
	while(temp->right!=NULL){
		
		if(temp->child!=NULL){
			list(temp,output);
			return;
		}
		fprintf(output,"%d,",temp->data);
		printf("%d\n",temp->data);
		temp=temp->right;
	}
	printf("%d\n",temp->data);
	fprintf(output,"%d,",temp->data);
	if(temp->child!=NULL){
		list(temp,output);
	}
	
	while(temp->parent!=NULL){
		temp=temp->parent;

		if(temp->right!=NULL){
			list(temp->right,output);
			return;
		}else{
			return;
		}
	}
}