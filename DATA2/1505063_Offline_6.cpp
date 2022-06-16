#include<stdio.h>
#include<stdlib.h>
#include<iostream>
//#include<stdio.h>
//#include<stdlib.h>
//#include<iostream>
#include<fstream>
using namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
	int **par;
	int *color;
	int *dis;
	int *parent;
	int *timeDiscovery;
	int *timefinal;
	int time; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int weight);
	void removeEdge(int u, int v);
	void getColor(int u,int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfs();
	void floyd_warshall();
	void parentprintGraph();
	void DFS_VISIT(int source);//will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	par=0;
	directed = dir ;
	color=0;
	time=0;
	timefinal=0;
	timeDiscovery=0;//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            {
                if(i==j)
                    matrix[i][j]=0;
                else
                matrix[i][j] = 9999;
            } //initialize the matrix cells to 0
    }
     par = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
       par[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            {

                par[i][j] = 9999;
            } //initialize the matrix cells to 0
    }
    color=new int[nVertices];
    dis=new int[nVertices];
    parent=new int [nVertices];
    timeDiscovery=new int [nVertices];
    timefinal=new int [nVertices];
}

void Graph::addEdge(int u, int v,int weight)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = weight;
    par[u][v]=u;
//    if(!directed) matrix[v][u] = 1;
//    nEdges++;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
     if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
     if(matrix[u][v]!=0)
     {matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
   nEdges--;}
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
     if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
     if(matrix[u][v]!=0)
        return true;
     else
        return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u>=nVertices)
        return -1;
    int count=0;
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]!=0)
            count++;
    }
    return count;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u>=nVertices)
        return;
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]!=0)
            cout<<"    "<<matrix[u][i];

    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
     if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
     for(int i=0;i<nVertices;i++)
     {
         if(matrix[u][i]!=0&&(matrix[v][i]!=0))
            return true;
     }
      return false;
}

void Graph::bfs(int source)
{
    //write this function
    if(source<0||source>=nVertices)return;
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
   // setdis(source,0);
    dis[source] = 0 ;
    q.enqueue(source) ;
     while( !q.empty() )
    {
        //complete this part
        int deq=q.dequeue();
        for(int i=0;i<nVertices;i++)
        {
            //printf("%d",getColor(i));
            if((color[i]==WHITE)&&(matrix[deq][i]!=0))
            {
               // setColor(adjList[deq].getItem(i),GREY);
               color[i]=GREY;
               // setdis(adjList[deq].getItem(i),getdis(deq)+1);
               dis[i]=dis[deq]+1;
               // setparent(adjList[deq].getItem(i),deq);
               parent[i]=deq;
                q.enqueue(i);
            }
        }
   // setColor(deq,BLACK);
   color[deq]=BLACK;
    printf("%d     ",deq);
    }

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
      if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    return INFINITY ;
    else{
     bfs(u);
    return dis[v];
    }

}
void  Graph:: DFS_VISIT(int i)
{
    time=time+1;

       timeDiscovery[i]=time;
       printf("%d  ",i);
       color[i]=GREY;
       for(int j=0;j<nVertices;j++)
       {
           if((color[j]==WHITE)&&(matrix[i][j]!=0))
           {
              // printf("a");
               parent[j]=i;
               DFS_VISIT(j);
           }
       }
       color[i]=BLACK;
       time=time+1;
       timefinal[i]=time;
       printf("  %d    ",i);

}


void Graph::dfs()
{
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

void Graph::floyd_warshall()
  {
//      int par[nVertices][nVertices];
//      for(int i=0;i<nVertices;i++)
//      {
//          for(int j=0;j<nVertices;j++)
//            {
//                if(matrix[i][j]!=9999&&(matrix[i][j]!=0))
//                {
//                    par[i][j]=i;
//                }
//                else
//                    par[i][j]=9999;
//            }
//      }
       for (int k = 0; k < nVertices; k++)
    {

        for (int i = 0; i < nVertices; i++)
        {

            for (int j = 0; j < nVertices; j++)
            {

                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    par[i][j]=par[k][j];
                    }
            }
        }
    }
    printGraph();
    parentprintGraph();

  }



void Graph::printGraph()
{
   // printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        //printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
//            if(matrix[i][j]==1)
//                printf(" %d", j);
cout<<matrix[i][j]<<"    ";
        }
        printf("\n");
    }
    cout<<"\n"<<endl;

}
  void Graph::parentprintGraph()
{

        for(int i=0;i<nVertices;i++)
    {
        //printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
//            if(matrix[i][j]==1)
//                printf(" %d", j);
if(par[i][j]!=9999)
cout<<par[i][j]+1<<"    ";
else
    cout<<par[i][j]<<"    ";
        }
        printf("\n");
    }
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

      int n,m;
    Graph g;
    //g.setDirected(true);
    int u,v,w;
    int sum = 0,x;
    ifstream inFile;
    inFile.open("D:\\1505063\\input_file.txt");
    if(!inFile)
    {
        cout << "Unable to Open file";
        exit(1);
    }
    inFile >> n;
    inFile >> m;
    cout << "Inputs: " <<endl;
    cout << n << " " << m <<endl;
    g.setnVertices(n);
    //g.setEdgeCount(m);
    for(int i=0; i<m; i++)
    {
        inFile >> u>>v>>w;
        //inFile >> v;
        //inFile >> w;
        printf("%d %d %d\n",u,v,w);
        g.addEdge(u-1,v-1,w);

    }
    g.printGraph();
    g.floyd_warshall();
//    int n;
//    Graph g;
//    printf("Enter number of vertices: ");
//    scanf("%d", &n);
//    g.setnVertices(n);
//
//    while(1)
//    {
//        printf("1. Add edge.2.Has common adjacent.3.Is Edge \n");
//        printf("4. (Add from homework). 5. Print Graph  6. Exit.\n");
//        printf("7.Call BFS.8.Get distance  9.Call DFS\n");
//        printf("10.Get Degree 11.Remove Edge  12.Floyd_Warshall\n");
//
//        int ch;
//        scanf("%d",&ch);
//        if(ch==1)
//        {
//            int u, v,weight;
//            scanf("%d%d%d", &u, &v,&weight);
//            g.addEdge(u, v,weight);
//        }
//        else if(ch==2)
//        {
//         {
//              int u, v;
//            scanf("%d%d", &u, &v);
//          printf("%d\n",g.hasCommonAdjacent(u,v));
//        }
//        }
//        else if(ch==3)
//        {
//             {
//              int u, v;
//            scanf("%d%d", &u, &v);
//          printf("%d\n",g.isEdge(u,v));
//        }
//        }
//        else if(ch==5)
//        {
//            g.printGraph();
//        }
//        else if(ch==6)
//        {
//            break;
//        }
//        else if(ch==7)
//        {
//            int item;
//            scanf("%d",&item);
//            g.bfs(item);
//        }
//          else if(ch==8)
//        {
//            int item1,item2;
//            scanf("%d %d",&item1,&item2);
//          printf("\n%d\n",g.getDist(item1,item2));
//        }
//        else if(ch==9)
//        {
//            g.dfs();
//            printf("\n");
//        }
//
//        else if(ch==10)
//        {
//            int u;
//            scanf("%d",&u);
//            printf("%d\n",g.getDegree(u));
//        }
//        else if(ch==11)
//        {
//             int u, v;
//            scanf("%d%d", &u, &v);
//            g.removeEdge(u, v);
//        }
//        else if(ch==12)
//        {
//     g.floyd_warshall();
//        }
//    }

}
