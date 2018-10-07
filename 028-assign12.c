// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
} LIST;


// A structure to represent a graph - size of the array will be  the number of vertices in graph
typedef struct graph {
	int src;
	LIST* array;
} GRAPH;

// To create a new node in the adjacency list
NODE *newnode(int dest) {
	NODE *new = (NODE *) malloc(sizeof(NODE));
	if (new == NULL) exit(-1);
	
	new->dest = dest;
	//new->weight = weight;
	new->next = NULL;
	return new;
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
GRAPH *createGraph(int n , long long num[] , char name[][20]) {
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
			if(rand()%2!=0&&j!=i&&check(graph,i,j)==1&&count<10)
			{
				addEdge(graph, i,j);
				count++;
			}
		}
	}
	
	return graph;
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
//--------------------------------------------------------	//	Proceeded by Garvit Kataria from here
int ccs(long long *array,int l ,int n)
{
	for(int i=0;i<l;i++)
		if(array[i]==n)
			return 0;
	return 1;	
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

void findShortestPathsL6(GRAPH *graph, long long source, long long dest)
{
	//NODE *a = graph->array[source].head;
	long long mathew[1000]={-1};
	mathew[0] = source;
	find(graph,source,dest,1,mathew);
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
	printGraph(graph);

	printf("-------------------------------\n");
	printf("Searching A Contact No.\n");
	findShortestPathsL6(graph,  7856042399,  9490125904);


	printf("\n");
	return 0;
}
/*
Additional feature of integration and deletion of history 
*/
/*
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
	HIST *new = (HIST*) malloc(sizeof(HIST));
	if (new == NULL) 
		exit(-1);
	
	new->dest = dest;
	new->op = op;
	new->next = NULL;
	return new;
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
void del_hist(GRAPH *graph,long long number)
{
	int src = index_num(graph,number);
	graph->array[src].hist = NULL;
	return;
}


*/