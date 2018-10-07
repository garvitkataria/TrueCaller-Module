/*		
		DS PROJECT -->> TRUECALLER APP LIKE MODULE
-----------------------------------------------
	Name: Anurag Gupta		201601006
	Name: Anubhav Ujjawal	201601005
	Name: Garvit Kataria	201601028
	Last Update: Fri Apr 14 22:16:51 IST 2017
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// A Structure to represent a NODE in the Adjacency List
typedef struct node {
	int dest;
	struct node* next;
} NODE;

typedef struct node1 {
	 int dest;
	int op;
	struct node1* next;
} HIST;


// A structure to represent a person in the Graph
typedef struct list {
	int id;
	char name[20];
	long long phno;
	NODE *head; // pointer to head node of Linked List
	NODE *block_list;
	HIST *hist;
} LIST;


// A structure to represent a graph - size of the array will be  the number of people
typedef struct graph {
	int src;
	LIST* array;
} GRAPH;
void home(GRAPH* graph);
void back(GRAPH *graph);
void waitFor (unsigned int secs);

// To create a new node in the adjacency list
NODE *newnode(int dest) 
{
	NODE *new = (NODE*) malloc(sizeof(NODE));//allocating memory to a new node
	if (new == NULL) 
		exit(-1);
	
	new->dest = dest;
	new->next = NULL;
	return new;
}
HIST *newnode1(int dest,int op) 
{
	HIST *new = (HIST*) malloc(sizeof(HIST));	//allocating memory to a new node
	if (new == NULL) 
		exit(-1);
	
	new->dest = dest;
	new->op = op;
	new->next = NULL;
	return new;
}


//This is a function to check if the entered phone number is present in the data base or not
int check(GRAPH *graph , int i ,int j)
{
	NODE* cnode = graph->array[i].head;
	while (cnode) {
			if(cnode->dest == j)//The phone number is present in the data and traversing to the next node
				return 0;
			cnode = cnode->next;
	}
	return 1;
}

// Adds an edge to an undirected graph
void addEdge(GRAPH* graph, int src, int dest) {
	// Add an edge from src to dest.  A new node is added at FRONT
	NODE* newNode = newnode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

//This function is used to return the id number of the entered phone number
int index_num(GRAPH *graph, long long num)
{
	int i;
	for (i = 0; i < graph->src; ++i)
	{
		if (graph->array[i].phno==num)
		return i;//returning the id number
	}
	return -1;//else return -1
}
void ADDhist(GRAPH *graph,long long src_num,long long dest_num,int op)
{
	int src,dest;
	src = index_num(graph,src_num);
	dest = index_num(graph,dest_num);
	HIST *cnode = newnode1(dest,op);//op 1:search op 2:block op3:unblock
	cnode->next = graph->array[src].hist;
	graph->array[src].hist= cnode;
	
}
void printHistory(GRAPH *graph,HIST *hist)
{
	if(hist!=NULL)
	{
		printHistory(graph,hist->next);		
		switch (hist->op)
		{
			case 1:	
				printf("%lld(%s) was searched by you \n\n",graph->array[hist->dest].phno,graph->array[hist->dest].name);
				break;
			case 2:	
				printf("%lld(%s) was blocked by you \n\n",graph->array[hist->dest].phno,graph->array[hist->dest].name);
				break;
			case 3:	
				printf("%lld(%s) was unblocked by you \n\n",graph->array[hist->dest].phno,graph->array[hist->dest].name);
				break;
		}
		//hist = hist->next;
	}
}
void print_hist(GRAPH *graph, long long src_num)
{
	int src;
	src = index_num(graph,src_num);
	HIST *hist = graph->array[src].hist;
	if (hist==NULL)
	{
		printf("\nNO History Found\n\n");
		return;	
	}
	printHistory(graph,hist);
	
}

//This function checks if a number is blocked or not
int block_check(GRAPH *graph, long long src_num, long long dest_num)
{
	int i,src,dest;
	src=index_num(graph,src_num);//the id number of the source number is stored in src
	dest=index_num(graph,dest_num);//the id number of the destination number is stored in dest
	if (dest==-1)
		return -1;	//Here there exists no such number
	NODE* cnode = graph->array[dest].block_list;//creating  pointer in the block list 
	while(cnode)
	{
		if (cnode->dest==src)
		{
			return 1;		//number is in block list
		}
		cnode=cnode->next;
	}
	return 0;
}
//This funtion unblocks a blocked number.
void unblock(GRAPH *graph, long long src_num, long long dest_num)
{
	int i,src,dest;
	src=index_num(graph,src_num);//the id number of the source number is stored in src
	dest=index_num(graph,dest_num);//the id number of the destination number is stored in dest	
	if (dest==-1)
	{	
		printf("\nSorry, Number not found in the database\n");
		return;	
	}	
	else
	{
		int check=block_check(graph,dest_num,src_num);
		if (check==0)//from check function if it returns 0 it means there is a number in the list 
			printf("Number is already absent from your block list\n");
		else
		{
			ADDhist( graph, src_num, dest_num, 3);			
			NODE* cnode = graph->array[src].block_list;
			if(cnode == NULL)//if the linked list is empty
			{
				return;
			}
			else if (cnode->dest==dest)//if the element is present in the first node
			{
				graph->array[src].block_list = cnode->next;
				printf("The number is unblocked\n\n");
				return;
			}
			else			//if the element is present in the next of node 
			{
				while(cnode->next!=NULL)
				{
					if(cnode->next->dest==dest)
					{
						cnode->next=(cnode->next)->next;//traversing through the list 
						printf("The number is unblocked\n\n");
						return;
					}
					//head = cnode;
					cnode=cnode->next;
				}
			}
		}
	}
}
//This function adds a number to the blocked list
void block(GRAPH *graph, long long src_num, long long dest_num) 
{
	int i,src,dest;
	src=index_num(graph,src_num);//the id number of the source number is stored in src
	dest=index_num(graph,dest_num);//the id number of the destination number is stored in dest
	if (dest==-1)//The number is not present in the database 
		printf("\nSorry, Number not found in the database\n");
	else
	{
		int check=block_check(graph,dest_num,src_num);//checking if the number is already present in the blocked list
		if (check==1)
			printf("Number is already present in your block list\n");
		else
		{
			ADDhist( graph, src_num, dest_num, 2);			
			NODE *newNode = newnode(dest);
			newNode->next = graph->array[src].block_list;//Adding the number in blocked list
			graph->array[src].block_list = newNode;
			printf("The number is blocked\n\n");
		}
	}
}

// To creates a graph of n vertices with each vertice representing a person 
GRAPH *createTruecallerGraph(int n , long long num[] , char name[][20]) {
	GRAPH *graph = (GRAPH *) malloc(sizeof(GRAPH));
	graph->src = n;

	graph->array = (LIST *) malloc (n * sizeof(LIST));
	bool *flag = (bool*)calloc(n,sizeof(bool));
	// Initialise each adjacency list as empty by making head as NULL
	srand((unsigned int) time(NULL));
	for (int i = 0; i < n; i++) 
	{
		graph->array[i].head = NULL;
		graph->array[i].block_list=NULL;
		graph->array[i].hist=NULL;
		graph->array[i].id = i;
		strcpy(graph->array[i].name,name[i]);
		int r=rand()%n;
		while(flag[r]==true)		//comment this loop till 2nd last line of array and uncomment the last line of loop if you don't want to randomly allocate the numbers to names
		{
			r=rand()%n;
		}
		flag[r]=true;
		graph->array[i].phno = num[r];
		//graph->array[i].phno = num[i];	//uncomment this line and comment above lines till loop to allocate the numbers sequentially rather than randomly allocating
	}
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < n ; i++)
	{
		int count = 0; 
		for(int j = 0 ; j < n ; j++ )
		{
			if(rand()%4==0&&j!=i&&check(graph,i,j)==1&&count<10)
			{
				addEdge(graph, i,j);
				count++;
			}
		}
	}
	
	return graph;
}

void register_new(GRAPH *graph)
{
	system("clear||cls");
	printf("\t\t\t\t\t\t\t\tWelcome to TrueCaller App\n\n\n");
	printf("\t\t\t\tWelcome to Registration Portal\n\n\n");
	printf("\n\n\nEnter your Number\n\n");
	char no[20];

	long long number;
	scanf(" %s",no);
	if(strlen(no)!=10)
	{
		printf("The number entered is invalid. We are redirecting you back.\n\n");
		waitFor(3);
		home(graph);
	
	}
	number  = atoll(no);
	int verify=index_num(graph,number);
	if (verify!=-1)
	{
		printf("\n\nNumber is already registered.\n\n\n\nYou will be redirected back.");
		waitFor(3);
		//home(graph);
	}
	else
	{	
		graph->array[graph->src].head=NULL;
		graph->array[graph->src].block_list=NULL;
		graph->array[graph->src].id = graph->src;
		graph->array[graph->src].hist=NULL;
		graph->array[graph->src].phno = number;
		printf("\n\nEnter your Name\n\n");
		char name[20];
		scanf("%s",name);
		strcpy(graph->array[graph->src].name,name);
		(graph->src)++;
		int count = 0,j; 
		srand((unsigned int)time(NULL));
		for(j = 0 ; j < graph->src ; j++ )
		{
			if(rand()%4==0&&j!=(graph->src-1)&&count<10)
			{
				addEdge(graph,graph->src-1,j);
				count++;
			}
		}
		printf("\n\nNumber is registered successfully.");
		printf("\n\nYour Phonebook is also randomly created.\n");
		waitFor(4);
	}
}
//This function prints the phone book of a single node
int print_book(GRAPH *graph, NODE *cnode)
{
	int c=0;
	while (cnode) {
		printf("-> %s (%lld) ", graph->array[cnode->dest].name, graph->array[cnode->dest].phno);
		cnode = cnode->next;
		c++;
	}
	printf("\n");
	return c;
}
// To print the adjacenncy list representation of graph
void printGraph(GRAPH* graph) 
{
	for (int v = 0; v < graph->src; ++v) 
	{
		printf("\nCONTACT LIST OF %s , %lld: \n  ", graph->array[v].name,graph->array[v].phno);
		int c=print_book(graph,graph->array[v].head);
	}
}
//This function checks if the number is already present in the array of the traversed paths
int ccs(long long *array,int l ,long long n)
{
	for(int i=0;i<l;i++)
		if(array[i]==n)
			return 0;
	return 1;	
}
//Find the number in the phone book
int a=0;
void find(GRAPH *graph,long long source,long long dest,int l,long long array[])
{
	if (a>2)	//To print only 3 paths
		return;
	if(l>7)	//Maximum length of the path is 7 
		return ;
	else if(source == dest)//if the number to be searched is present in the phone book of the same contact
	{
		a++;
		for(int i =0 ;i<l;i++)
		{
			int index=index_num(graph,array[i]);
			i<l-1?printf("%lld (%s) -> ",array[i],graph->array[index].name ):printf("%lld (%s)\n", array[i],graph->array[index].name);
		}
		if (a==3) printf("\n\n\n");
	}
	int i;
	for ( i = 0; i < graph->src; ++i)
		{
			if(graph->array[i].phno==source)
				break;
		}	
	NODE *list = graph->array[i].head;
	while(list)
	{
		if(ccs(array,l,graph->array[list->dest].phno))
		{
			array[l] = graph->array[list->dest].phno;
			find(graph,array[l],dest,l+1,array);
			
		}
		list = list->next;
		
	}
}
//function which calls (find function) to recursively search a phone number by traverse contactlist one by one.
void search_number(GRAPH *graph, long long source, long long dest)
{
	int flag=block_check(graph,source,dest);//checks if the number is in blocked list or not 
	
	if (flag==-1)
	{
		printf("\nSorry, Number not found in the database\n");
		return;	
	}
	else if (flag==1)
		printf("\nNumber not found, blocked\n");
	else 
	{
		long long path_arr[1000]={-1};
		path_arr[0] = source;//intializing the array path with first node 
		a=0;
		find(graph,source,dest,1,path_arr);//calling the find function to search the number
		if (a==0)
			printf("\nSorry, Contact not found\n");
	}
	ADDhist( graph, source, dest, 1);

}
//wait for a given time
void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

//this function returns back to home 
void back(GRAPH *graph)
{
	printf("\n\n\nPress 0 to exit and any other key to go back\n\n");
	int d;
	scanf("%d",&d);
	if (d==0)
		exit(-1);
	else		//This returns back to home if any other key is pressed
		home(graph);
}
void del_hist(GRAPH *graph,long long number)
{
	int src = index_num(graph,number);
	graph->array[src].hist = NULL;
	return;
}

//This function gives options to block search and unblock in the home page 
void option_2_search(GRAPH *graph, long long number)
{
	long long search;
	int d;
	printf("\nPress 1 to search a number\n\nPress 2 to block a number\n\nPress 3 to unblock a number\n\nPress 4 to check your search history\n\nPress 5 to delete history\n\nPress 6 to go to  home page\n\nPress any other key to exit.\n\n");
	scanf("%d",&d);
	if (d==1)//The user wants to search a number
	{
		printf("\nEnter the Number you want to search.\n\n");
		scanf("%lld",&search);
		printf("\n");
		search_number(graph,number,search);//Calling the search function to search a number
		option_2_search(graph,number);
	}
	else if (d==2)//The user wants to block a number
	{
		printf("\nEnter the Number you want to block.\n\n");
		scanf("%lld",&search);
		block(graph,number,search);//Calling the block function to block a number
		option_2_search(graph,number);
	}
	else if(d==3)//The user wants to unblock a number
	{
		printf("\nEnter the Number you want to unblock.\n\n");
		scanf("%lld",&search);
		unblock(graph,number,search);//Calling the unblocking function to unblock a number
		option_2_search(graph,number);
	}
	else if (d==4)
	{
		printf("Printing your history data\n\n");
		print_hist(graph,number);
		option_2_search(graph,number);
			
	}
	else if (d==5)
	{
		printf("Your History was deleted\n\n");
		del_hist(graph,number);
		option_2_search(graph,number);
			
	}
	else if (d==6)//The user wants to go back to home
		home(graph);
	else		
		exit(-1);
}
//This function is just to create a friendly interface of truecaller.
void option(GRAPH* graph,int inp)
{
	system("cls||clear");
	printf("\t\t\t\t\t\t\t\tWelcome to TrueCaller App\n\n\n");
	long long number;
	int r;
	switch(inp)
	{
		case 1:
			printGraph(graph);
			back(graph);
			break;
		case 2: printf("Enter your Phone Number\n\n");
			scanf("%lld",&number);
			r=index_num(graph,number);
			if (r==-1)
			{
				printf("Contact Not Registered.\n\n\n\nYou will be redirected back.");
				waitFor(3);
				home(graph);
			}
			else
			{
				printf("\n\t\t\tHello %s\n\n",graph->array[r].name);
				option_2_search(graph,number);
			}
			break;
		case 3: 
			register_new(graph);
			home(graph);
			break;
		case 4: 
			printf("Enter your Phone Number\n\n");
			scanf("%lld",&number);
			r=index_num(graph,number);
			if (r==-1)
			{
				printf("Contact Not Registered.\n\n\n\nYou will be redirected back.");
				waitFor(3);
				home(graph);
			}
			else
			{
				printf("\n\t\t\tPhonebook of %s\n\n",graph->array[r].name);
				print_book(graph,graph->array[r].head);
				back(graph);
			}
			break;
		case 5:
			printf("Enter your Phone Number\n\n");
			scanf("%lld",&number);
			r=index_num(graph,number);
			if (r==-1)
			{
				printf("Contact Not Registered.\n\n\n\nYou will be redirected back.");
				waitFor(3);
				home(graph);
			}
			else
			{
				printf("\n\t\t\tBlock list of %s\n",graph->array[r].name);
				int c=print_book(graph,graph->array[r].block_list);
				if (c==0)
				{
					printf("\n\n\nNo contacts blocked.\n");
					waitFor(3);
					home(graph);
				}
				else
					back(graph);
			}
			break;
		
		default: return;
	}
}
void home(GRAPH* graph)
{
	system("clear||cls");
	printf("\t\t\t\t\t\t\t\tWelcome to TrueCaller App\n\n\n");
	int inp;
	long long number;
	printf("Press 1 to check complete database of all Phonebooks\n\n");
	printf("Press 2 to login and search or block a number\n\n");
	printf("Press 3 to register a new number\n\n");
	printf("Press 4 to open your Phonebook\n\n");
	printf("Press 5 to check your Block list\n\n");
	printf("Press any other key to exit\n\n");
	scanf("%d",&inp);
	option(graph,inp);
}
int main(int argc, char *argv[])
{
	// create the graph given in above fugure
	//GRAPH* graph = createTruecallerGraph(n);
	
	FILE *f1 = fopen("names-numbers.txt","r");
	long long num[100];
	char name[100][20],temp[20];
	int i=0,nameid=0;
	while(fscanf(f1,"%s",temp)!=EOF)
	{
		if(i%2==0)
			strcpy(name[nameid],temp);
		else
		{
			//printf("%s\n", );
			num[nameid] = atoll(temp);
			//printf("%lld\n",num[nameid] );
			nameid++;
		}
		i++;
	}
	fclose(f1);
	GRAPH* graph = createTruecallerGraph(nameid,num,name);
	//printGraph(graph);
	home(graph);
	
	return 0;
}
