//Kamile Samusiovaite - ADS4
#include<stdio.h>
#include<stdlib.h>

#define SIZE 5
#define SOURCE 0
#define DESTINATION 1

//structure depicting graphics (struktura, vaziduojanti grafika)
typedef struct Graph { 											       
    int V;			  		 //the number of vertices in the graph (virsuniu sk.) 
    struct List* array;		//list of count neighbours (kaimynu sarasas)
} Graph;

//a structure depicting a list of adjacent locations (vaizduoja gretimu vietu sarasa)
typedef struct List { 												
    struct Node* head; //(mazgas)										
    int visited; 	   //a tag that indicates whether we were at a particular vertex (ar aplankyta konkreti virsune)
} List;

//node structure (mazgo struktura)
typedef struct Node { 											
    int dest;			//node neighbor vertex (kaimyno virsune)
    struct Node* next;	//the next neighbor of the node neighbor (sekantis kaimynas) 
} Node;

//functions prototypes 
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
Node* newNode(int dest);
void printGraph(Graph* graph);
int doesPathExist(Graph* graph, int src, int dest);

int main() {
	int neighbour[SIZE][SIZE] = { { 0, 1, 0, 1, 1},
				      { 1, 0, 1, 0, 0},
				      { 0, 1, 0, 1, 0},
				      { 1, 0, 1, 0, 1},
				      { 1, 0, 0, 1, 0}
	};

//	int neighbour[SIZE][SIZE] = { { 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
//				      { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
//				      { 0, 1, 0, 1, 1, 0, 1, 1, 1, 1},
//				      { 1, 0, 1, 0, 0, 1, 1, 1, 0, 0},
//				      { 1, 1, 1, 0, 0, 1, 0, 1, 1, 1},
//				      { 1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
//				      { 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
//				      { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
//				      { 0, 1, 1, 0, 1, 0, 0, 1, 0, 1},
//				      { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0}
//	};

	Graph* graph = createGraph(SIZE); 
	
	for(int i = 1; i < SIZE; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			if (i <= j) break;
			if (neighbour[i][j] == 1) addEdge(graph, i, j); 
		}
	}
 
    printGraph(graph); 
    
    printf("\nPath:");
    if (doesPathExist(graph, SOURCE, DESTINATION)) printf(" %d \nPath exist!", DESTINATION); 
	else printf("\nPath does not exist");

	return 0;
}

//functions for creating a graph 
struct Graph* createGraph(int V) {
    Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->V = V; 
    
    graph->array = (struct List*)malloc(V * sizeof(struct List));

    for (int i = 0; i < V; ++i) { 			
        graph->array[i].head = NULL; 	
        graph->array[i].visited = 0; 	
    }
 
    return graph; 						
}

void addEdge(Graph* graph, int src, int dest) {
    Node* check = NULL; 				
    Node* node = newNode(dest);

    if (graph->array[src].head == NULL) {
        node->next = graph->array[src].head;
        graph->array[src].head = node;
    }
    else {
        check = graph->array[src].head;
        while (check->next != NULL) { 
            check = check->next;
        }
        check->next = node;
    }
 
 	
    node = newNode(src);

    if (graph->array[dest].head == NULL) { 
        node->next = graph->array[dest].head;
        graph->array[dest].head = node;
    }
    else {
        check = graph->array[dest].head;
        while (check->next != NULL) {
            check = check->next;
        }
        check->next = node;
    } 
}

//function for node creation			
struct Node* newNode(int dest) {
    Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->dest = dest;	
    newNode->next = NULL;	

    return newNode;
}

//graph printing function
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {	
        Node* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) { 					
            printf("-> %d", pCrawl->dest);	
            pCrawl = pCrawl->next;			
        }
        printf("\n");
    }
}

//function that checks to see if an email can be sent through acquaintances
int doesPathExist(Graph* graph, int src, int dest) {
	List* list = graph->array;	
	Node* node = list[src].head;	

	list[src].visited = 1;		

	while (node) {					
		if (node->dest == dest) return 1;	
	
		if (list[node->dest].visited == 0) {
			printf(" %d", node->dest); 

			if (doesPathExist(graph, node->dest, dest)) {
				return doesPathExist(graph, node->dest, dest); 
			} else {
				list[src].visited = 0;	
				printf("<-"); 
				return 0;
			}
		}

		if (node->next != NULL) { 
			node = node->next;
		} else {
			return doesPathExist(graph, node->dest, dest); 
		}
	}
	return 0;
}

