### GROUP NAME:"OK DS"


		PROJECT DETAILS : TRUECALLER LIKE APP MODULE


AIM:	
This project features a small module of the Truecaller app that has the ability to search, block and unblock any number from the database. It works on the concept/principle on which truecaller works. It enables searching of a number which may not be in the contact list of the user but may be in the contact list of one of his friends of friends. There is also a number blocking and unblocking functionality which avoids searching by particular unwanted or spam numbers. This can be further extended to updating the data base with integration of social media information with events and news updates.

 
TASKS: 	
1. Generating the phonebooks from the database
2. Searching the number through others phonebook	
3. Blocking a number by a user 
4. Unblocking a blocked number by the user
5. Maintaining and deleting operations history of the user.

DATA STRUCTURE USED : Graph is used for the data creation because it will be efficient in terms of space and complexity as compared to trees. Searching, blocking and unblocking can be done in linear or constant time using adjacency list of graph. It takes constant time to insert edge in graph. Along with this, accessing an element can also be done in constant time using graphs. 

Data Structure Briefing:

	NODE : This data structure is for representing a node in contact list.

	HIST : This data structure is for storing the operations history of a person.
	
	LIST : This represents a person with his name,phone number, blocklist and history.

	GRAPH : This is for creating a Graph of the Persons for the truecaller app. 



------------------------------------------>Functions Created<------------------------------------------


* NODE *newnode(int dest) :	Creates and returns a new node. It allocates the memory and stores the data "dest" in the data and "next" address as null.
	
* int check(GRAPH *graph , int i ,int j) :	Checks if the id of person is already allocated in the while phonebook creation or not. If the number is present, it returns 0 else returns 1. 

* void addEdge(GRAPH* graph, int src, int dest) :		Adds an edge to the unidirectional graph. Add an edge from src to dest by adding a node in the front.	It is done in constant time.

* int index_num(GRAPH *graph, long long num) :	This function returns the index i.e., id of the given phone number.

* int block_check(GRAPH *graph, long long src_num, long long dest_num) :		This function checks if the number to be searched is present in the block list of the user or not. It returns 1 if the number dest_num is in the block list of src_num and 0 if it is not present in the block list.

* void unblock(GRAPH *graph, long long src_num, long long dest_num) :		Unblocks the chosen number by deleting that particular node from the block list. It first checks if the number is present in the block list and unblocks it if it is present in the block list or gives appropriate message. The worst case complexity is linear time for this operation.

* void block(GRAPH *graph, long long src_num, long long dest_num) :	Adds the number blocked to the blocklist such that if the blocklisted user searches for this person, he won't be able to find it in truecaller. It first checks if the number is present in the database using index_num function and then checks if the number is present in the blocked list. If the number is not in the blocklist, it adds the number in the block list. This approach is chosen as it takes constant time, i.e, O(1) to block the number.

* GRAPH *createTruecallerGraph(int n , long long num[] , char name[][20]) :	This function creates and returns the graph from the data present in the file. It adds the details in the adjacency list either randomly or directly as per the choice. It adds a maximum of 10 numbers in each users contact list. Graph is preferred as the data structure as worst case complexity for insertion of edge is O(1).

* int print_book(GRAPH *graph, NODE *cnode) :		Prints the names and phone numbers of the given user's phonebook linked list. It also returns the number of contacts present in that linked list.

* void printGraph(GRAPH* graph) :		It traverses through the graph and prints the contact list of every members by calling print_book function.

* int ccs(long long *array,int l ,long long n) :		While searching helps to check if the number to be searched is already present in the array of paths.

* void find(GRAPH *graph,long long source,long long dest,int l,long long array[]) :		This is a recursive function which searches the dest number from the source number and prints the path through which the number is 	found. It keeps on traversing through the friends phonebook, checking if the path is not cyclic.

* void search_number(GRAPH *graph, long long source, long long dest) :	This function initiates the searching by calling the recursive function find() and prints if the result is found or not.

* void waitFor (unsigned int secs) :		Function to give time delay for good user interface.

* void back(GRAPH *graph) :		Function to give choices to return back after the operations.

* void option_2_search(GRAPH *graph, long long number) :		Function which gives different options such as searching, blocking and unblocking to allow user to input appropriate option and call the fuctions as per the input.

* void option(GRAPH* graph,int inp) :		Function which allows user to select different operations such as printing contact list, block list, etc. This function makes the project user interactive.

* void home(GRAPH* graph) :	Function to display the options in the home menu.

* * void register_new(GRAPH *graph) :	Function to register a new number in the database in a constant time.

* HIST *newnode1(int dest ,int op) : Creates and returns a new node. IT allocates dynamic memory and stores the data . IT is for HIST.

* void ADDhist(GRAPH *graph,long long src_num,long long dest_num,int op) :	It adds history to the history list of the person. The function has worst case complexity of O(1).

* void printHistory(GRAPH *graph,HIST *hist) :
	IT prints the history of a person recursively in linear time.

* void print_hist(GRAPH *graph,long long src_num)	:
	it calls printHistory if the History of a function is not NULL.

* void del_hist(GRAPH *graph,long long number): This function deletes the history of a number.  		


* int main() :	The main function which reads data from the file and calls the appropriate functions to operate the Truecaller.
  

---


GROUP MEMBERS	-	ROLL NUMBER	-	TASKS DONE

Anurag Gupta	-	201601006	-	Blocking, Unblocking, Main function, User Interface, Registration of new number, other utility functions 

Garvit kataria	-	201601028	-	Searching the user's number and history integration and deletion, files management 

Anubhav ujjawal	-	201601005	-	Generating the graph and adjacency list creation and history creation
