// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// A Structure to represent a NODE in the Adjacency List
typedef struct node {
	int dest;
	int weight;
	struct node* next;
} NODE;

// A structure to represent an adjacency liat
typedef struct list {
	int id;
	char name[20];
	long long phno;
	NODE *head; // pointer to head node of Linked List
	NODE *block_list;
} LIST;


// A structure to represent a graph - size of the array will be  the number of vertices in graph
typedef struct graph {
	int src;
	LIST* array;
} GRAPH;
int block_check(GRAPH *graph, long long src_num, long long dest_num);
int index_num(GRAPH *graph, long long num);
void printGraph(GRAPH* graph);
int check(GRAPH *graph , int i ,int j);
// To create a new node in the adjacency list
NODE *newnode(int dest) {
	NODE *new = (NODE *) malloc(sizeof(NODE));
	if (new == NULL) exit(-1);
	
	new->dest = dest;
	//new->weight = weight;
	new->next = NULL;
	return new;
}

// Adds an edge to an undirected graph
void addEdge(GRAPH* graph, int src, int dest) {
	// Add an edge from src to dest.  A new node is added at FRONT
	NODE* newNode = newnode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Since GRAPH is undirected, add an edge from dest to src as well
	/*newNode = newnode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;*/
}


// To creates a graph of V vertices
GRAPH *createGraph(int n , long long num[] , char name[][20])
 {
	GRAPH *graph = (GRAPH *) malloc(sizeof(GRAPH));
	graph->src = n;

	graph->array = (LIST *) malloc (n * sizeof(LIST));

	// Initialise each adjacency list as empty by making head as NULL
	for (int i = 0; i < n; i++) 
	{
		graph->array[i].head = NULL;
		graph->array[i].id = i;
		strcpy(graph->array[i].name,name[i]);
		graph->array[i].phno = num[i];
	}
	for(int i = 0 ; i < n ; i++)
	{
		int count = 0; 
		for(int j = 0 ; j < n ; j++ )
		{
			if(rand()%3==0&&j!=i&&check(graph,i,j)==1&&count<10)
			{
				addEdge(graph, i,j);
				count++;
			}
		}
	}
	
	return graph;
}


int ccs(long long *array,int l ,int n)
{
	for(int i=0;i<l;i++)
		if(array[i]==n)
			return 0;
	return 1;	
}

void find(GRAPH *graph,long long source,long long dest,int l,long long array[])
{
	if(l>3)
		return ;
	else if(source == dest)
		for(int i =0 ;i<l;i++)
			i<l-1?printf("%lld-> ",array[i] ):printf("%lld\n", array[i]);
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

void findShortestPathsL6(GRAPH *graph, long long source, long long dest)
{
	//NODE *a = graph->array[source].head;
	bool flag=block_check(graph,source,dest);
	//printf("%d\n",flag);
	if (flag==true)
		printf("Number not found, blocked\n");
	else {
	long long mathew[1000]={-1};
	mathew[0] = source;
	find(graph,source,dest,1,mathew);
	}
}
//----------------------------------------
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
			NODE *newNode = newnode(dest);
			newNode->next = graph->array[src].block_list;//Adding the number in blocked list
			graph->array[src].block_list = newNode;
			printf("The number is blocked\n\n");
		}
	}
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
//---------------------------------------------				//Proceeded by Sahithi Krishna from here
//This funtion unblocks a blocked number.
void unblock(GRAPH *graph, long long src_num, long long dest_num)
{
	int i,src,dest;
	src=index_num(graph,src_num);//the id number of the source number is stored in src
	dest=index_num(graph,dest_num);//the id number of the destination number is stored in dest	
	if (dest==-1)
		printf("\nSorry, Number not found in the database\n");
	else
	{
		int check=block_check(graph,dest_num,src_num);
		if (check==0)//from check function if it returns 0 it means there is a number in the list 
			printf("Number is already absent from your block list\n");
		else
		{
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
int check(GRAPH *graph , int i ,int j)
{
	NODE* cnode = graph->array[i].head;
	while (cnode) {
			if(cnode->dest == j)
				return 0;
			cnode = cnode->next;
	}
	return 1;
}
// To print the adjacenncy list representation of graph
void printGraph(GRAPH* graph) {
	/*for(int i = 0 ; i < graph->src ; i++)
	{
		printf("%d:%s, %lld \n",graph->array[i].id,graph->array[i].name,graph->array[i].phno );
	}*/
	for (int v = 0; v < graph->src; ++v) {
		NODE* cnode = graph->array[v].head;
		printf("\nCONTACT LIST OF %s , %lld: \n  ", graph->array[v].name,graph->array[v].phno);
		while (cnode) {
			printf("-> %s (%lld) ", graph->array[cnode->dest].name, graph->array[cnode->dest].phno);
			cnode = cnode->next;
		}
		printf("\n");
	}
}
int index_num(GRAPH *graph, long long num)
{
	int i;
	for (i = 0; i < graph->src; ++i)
	{
		if (graph->array[i].phno==num)
		return i;
	}
	return -1;
}

int main(int argc, char *argv[]) {
	// create the graph given in above fugure
	int n = 5;
	//GRAPH* graph = createGraph(n);
	FILE *f1 = fopen("names-numbers.txt","r");
	long long num[100];char name[100][20],temp[20];int i=0,nameid=0;
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
	GRAPH* graph = createGraph(nameid,num,name);
	printf("%d......\n",nameid );

	printGraph(graph);
	findShortestPathsL6(graph,   9490125904,7856042399);
	
	printf("\n");
	findShortestPathsL6(graph,  9490125904, 7856042399);
	printf("\n");

	printf("\n");
	printf("9490125904 has been blocked by 7856042399\n");
	block(graph,7856042399,9490125904);
	int r=index_num(graph,7856042399);
	printf("Block list of %s (%lld)\n",graph->array[r].name,graph->array[r].phno);//This is to display the blocked list
	int c=print_book(graph,graph->array[r].block_list);
	if (c==0)
	{
		printf("\n\n\nNo contacts blocked.\n");
	}

	unblock(graph,7856042399,9490125904);//Calling the unblocking function to unblock a number
	r=index_num(graph,7856042399);
	printf("Block list of %s (%lld)\n",graph->array[r].name,graph->array[r].phno);//This is to display the blocked list
	 c=print_book(graph,graph->array[r].block_list);
	if (c==0)
	{
		printf("No contacts blocked.\n");
	}
	return 0;
}