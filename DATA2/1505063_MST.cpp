#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0
using namespace std;
class HeapItem
{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize( int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = i;
			A[i+1].key = MAXREAL;
			map[i] = i+1; //map tracks which vertex is stored at which heap node
		}
		A[1].key=0;
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, int key)
    {
        //Write your codes here
        heapLength=heapLength+1;
        A[heapLength].data=data;
        A[heapLength].key=key;
        map[data]=heapLength;
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin()
	{
	    //write your codes here
	    HeapItem t;

       if(heapLength>=1)
	    {
	    t=A[1];
	    A[1]=A[heapLength];
	    A[heapLength]=t;
	    map[A[heapLength].data]=heapLength;
	  //  map[A[1].data]=1;
	    heapLength--;
	    heapify(1);
	    //printHeap();
	    return t;}
	    else
            return A[1];

	}





    //This function returns the key value of a data stored in heap
	float getKey(int data)
	{
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i)
	{
		int l,r,smallest;
		//if(i==heapLength)
           // return;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				{
				    map[A[i].data]=i;
				    return;

				}//nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int f)
	{
	    if(f==0)
	    return;

        int i=f/2;
        int l,r,smallest;
        l=2*i;
        r=2*i+1;
        if(l>heapLength && r>heapLength)
				return; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

            if(A[i].key <= A[smallest].key)
				return;
				 else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}
        buHeapify(f/2);
	}
      //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key)
	{
		//Write your codes here.
		printf("%f   %d  before\n",key,data);
		int i=map[data];
		printf("%d  i\n",i);
		A[i].key=key;
		A[i].data=data;
		printf("%f     %d\n",A[i].key,A[i].data);
		if(i==heapLength)
       buHeapify(i);
       if(i==1)
        heapify(i);

	}
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item,int weight) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	void setLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;

}

void ArrayList::insertItem(int newitem,int weight)
{
	int * tempList ;

	if (length == listMaxSize)
	{

		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem;
	length=length+1;
	list[length]=weight;
	length++ ;
}
void ArrayList::setLength()
{
    length=0;
}
int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	{list[position] = list[length-2] ;
	list[position+1] = list[length-1] ;
	}
	length=length-2 ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;

	int *color;
	int *dis;

	int *timefinal;
	int *timeDiscovery;
	int   time;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
    int *parent;
    int weight;
    ArrayList  * adjList ;
	Graph(bool dir = false);
	~Graph();
	void setElement(int nVertices);
	void setColor(int i,int col);
	void setparent(int i,int j);
	void setdis(int i,int d);
    void setTime(int i,int d);
    void setDiscovery(int i,int time);
    int getDiscovery(int i);
    int getTimefinal(int i);
	int getColor(int i);
	int getparent(int i);
	int getdis(int i);
	void setnVertices(int n);
	void addEdge(int u, int v,int weight);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void DFS_VISIT(int i);//will run bfs in the graph
	void dfs();
	int Getvertices();
	void Shortest_path(int u,int v);//will run dfs in the graph
	Graph Minimum_spanning_tree(Graph g,Graph regraph);
};
int Graph::getColor(int i)
{
    return this->color[i];
}
int Graph::getDiscovery(int i)
{
    return this->timeDiscovery[i];
}
void Graph::setDiscovery(int i,int time)
{
    this->timeDiscovery[i]=time;
}
int Graph::getparent(int i)
{
    return this->parent[i];
}
int Graph::getTimefinal(int i)
{
    return this->timefinal[i];
}
int Graph::getdis(int i)
{
    return this->dis[i];
}
void Graph::setColor(int i,int col)
{
    this->color[i]=col;
}
void Graph::setTime(int i,int col)
{
    this->timefinal[i]=col;
}
void  Graph::setparent(int i,int j)
{
    this->parent[i]=j;
}
void Graph::setdis(int i,int d)
{
    this->dis[i]=d;
}
void Graph::setElement(int nVertices)
{
   color=new int[nVertices];
	dis=new int[nVertices];
     parent=new int[nVertices];
     for(int i=0;i<nVertices;i++)
        parent[i]=-1;
     timefinal=new int[nVertices];
     timeDiscovery=new int[nVertices];
}
Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
  adjList=0;
	directed = dir ;
	color=0;
	dis=0;
	parent=0;
	timefinal=0;
	timeDiscovery=0;
	weight=0;
	//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	//cout<<"duibar"<<endl;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	//cout<<adjList[0].getLength()<<endl;
	for(int i=0;i<nVertices;i++)
        adjList[i].setLength();
	setElement(nVertices);
}
int Graph::Getvertices()
{
    return this->nVertices;
}
void Graph::addEdge(int u, int v,int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v,weight) ;
	adjList[v].insertItem(u,weight) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function


     if(adjList[u].searchItem(v)!=NULL_VALUE)
    {
       // cout<<"oh no"<<endl;
        adjList[u].removeItem(v);
    adjList[v].removeItem(u);
    this->nEdges--;
    }
    else
        return;


}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!=NULL_VALUE&&adjList[v].searchItem(u)!=NULL_VALUE)
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices

    for(int i=0;i<adjList[u].getLength();i++)
    {
        for(int j=0;j<adjList[v].getLength();j++)
        {
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
                return true;
        }
    }
   return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
     if(source<0||source>=nVertices) return;
    for(int i=0; i<nVertices; i++)
    {
        //setColor(i,WHITE);
        color[i] = WHITE ;
        //setparent(i,-1);
        parent[i] = -1 ;
       // setdis(i,INFINITY);
        dis[i] = INFINITY ;
    }
    Queue q ;
    //setColor(source,GREY);
    color[source] = GREY;

    dis[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int deq=q.dequeue();
        for(int i=0;i<adjList[deq].getLength();i++)
        {

            if(getColor(adjList[deq].getItem(i))==WHITE)
            {

               color[adjList[deq].getItem(i)]=GREY;

               dis[adjList[deq].getItem(i)]=getdis(deq)+1;

               parent[adjList[deq].getItem(i)]=deq;
                q.enqueue(adjList[deq].getItem(i));
            }
        }

   color[deq]=BLACK;
    printf("%d     ",deq);
    }
}
void  Graph::DFS_VISIT(int i)
{
       time=time+1;

       timeDiscovery[i]=time;
       printf("%d  ",i);
       color[i]=GREY;
       for(int j=0;j<adjList[i].getLength();j++)
       {
           if(color[adjList[i].getItem(j)]==WHITE)
           {
              // printf("a");
               parent[adjList[i].getItem(j)]=i;
               DFS_VISIT(adjList[i].getItem(j));
           }
       }
       color[i]=BLACK;
       time=time+1;
       timefinal[i]=time;
       printf("  %d    ",i);

}
void Graph::dfs()
{
    //write this function
   for(int i=0;i<nVertices;i++)
   {
       color[i]=WHITE;
       parent[i]=-1;
   }
    time=0;
    for(int i=0;i<nVertices;i++)
    {
        if(color[i]==WHITE)
            DFS_VISIT(i);
    }
}
void Graph::Shortest_path(int u,int v)
{
    bfs(u);
    printf("%d->",v);
    while(v!=u)
    {
        printf("%d->",parent[v]);
        v=parent[v];
    }
    printf("\n");
}
int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    return INFINITY ;
    bfs(u);
    return getdis(v);

}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        //printf("%d:", i+1);
        for(int j=0; j<adjList[i].getLength();j=j+2)
        {
            printf("%d   %d\n",i+1, adjList[i].getItem(j)+1);
        }
        //printf("\n");
    }
}
Graph  Minimum_spanning_tree(Graph g)
{

    MinHeap Q;
  Graph regraph;
  regraph.setnVertices(g.Getvertices());
   Q.initialize(g.Getvertices());

     g.setparent(0,-1);

     while(Q.Empty()==false)
     {
         HeapItem mini=Q.removeMin();

         regraph.weight=regraph.weight+mini.key;

         for(int i=0;i<g.adjList[mini.data].getLength();i=i+2 )
         {

          if(Q.map[g.adjList[mini.data].getItem(i)]<=(Q.heapLength+1)&&(g.adjList[mini.data].getItem(i+1)<Q.A[Q.map[g.adjList[mini.data].getItem(i)]].key))
          {

                  Q.A[Q.map[g.adjList[mini.data].getItem(i)]].key=g.adjList[mini.data].getItem(i+1);


                  Q.buHeapify(Q.map[g.adjList[mini.data].getItem(i)]);

                  if(g.parent[g.adjList[mini.data].getItem(i)]>=0)
                    {
                        regraph.removeEdge(g.adjList[mini.data].getItem(i),g.parent[g.adjList[mini.data].getItem(i)]);
                    }

                        g.setparent(g.adjList[mini.data].getItem(i),mini.data);

                  regraph.addEdge(g.adjList[mini.data].getItem(i),mini.data,g.adjList[mini.data].getItem(i+1));

          }
         }
     }
     return regraph;
}
Graph::~Graph()
{
    //write your destructor here
    if(color!=0)
    {delete[] dis;
    delete[] color;
    delete[] parent;
    delete[] timeDiscovery;
    delete[] timefinal;
    }
}




//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g=new Graph();



    FILE  *fp;
   int d1,d2,d3;

   fp = fopen("C:\\Users\\DELL\\Desktop\\file.txt","r");
   fscanf(fp,"%d %d",&d1,&d2);

         g.setnVertices(d1);

   while(!feof(fp))
   {
         fscanf(fp,"%d %d %d",&d1,&d2,&d3);
          g.addEdge(d1-1,d2-1,d3);
   }
  Graph regraph=  Minimum_spanning_tree(g);
    regraph.printGraph();
    cout<<regraph.weight<<endl;
    return 0;
}
