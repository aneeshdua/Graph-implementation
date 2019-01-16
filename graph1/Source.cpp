#include<iostream>

using namespace std;

class graph
{
	int adj_matrix[10][10];
	char letters[10];
	int n;
public:
	void temp();
	void create();
	void disp_matrix();
	void bfs();
	void dfs();
	void prim_tree();
	void dijkstra(int);
	int minDistance(int*, bool*);

};

void graph::temp()
{
	n = 5;
	int temp[10][10] = { { 0, 2, 0, 6, 0 },
	{ 2, 0, 3, 8, 5 },
	{ 0, 3, 0, 0, 7 },
	{ 6, 8, 0, 0, 9 },
	{ 0, 5, 7, 9, 0 },
	};
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			adj_matrix[i][j] = temp[i][j];
}

void graph::create()
{
	cout << "Enter number of elements"<<endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter letter" << endl;
		cin >> letters[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			cout << "Enter weight of edge if " << letters[i] << " and " << letters[j] << " are connected(else enter 0)";
			cin >> adj_matrix[i][j];
			cout << endl;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj_matrix[j][i] = adj_matrix[i][j];
}

void graph::disp_matrix()
{
	cout << "The adjacency matrix is--" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << adj_matrix[i][j]<<'\t';
		cout << endl;
	}
}

void graph::dfs() //ITERATIVE DFS
{
	int x = 0, i;
	char visited_stack[10];
	int visited[10];
	//INTITIALISE VISIT STACK 
	for (i = 0; i < n; i++)
		visited[i] = 0;
	int top = 0;
	//PRINT SOURCE VERTEX
	visited_stack[top] = letters[0];
	visited[0] = 1;
	cout << letters[0] << endl;
	do
	{
		int flag = 0;
		for (i = 0; i < n; i++)
		{
			int f = 0;
			//FIND ADJACENT LETTER POSITION IN MATRIX
			for (int c = 0; c < n; c++)
				if (visited_stack[top] == letters[c])
					x = c;
			//CHECK IF CURRENT ELEMENT IS ALREADY VISITED
			if (visited[i] == 1)
				f = 1;
			//CHECK FOR ADJACENT UNVISITED VERTEX
			if (adj_matrix[x][i] >0 && f==0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1) //ADD VERTEX TO STACK
		{
			top++;
			visited_stack[top] = letters[i];
			visited[i] = 1;
			cout << letters[i] << endl;
		}
		else
			top--; //REMOVE THE TOP STACK AS NO MORE UNVISITED STACKS PRESENT
	} while (top != 0);
}

void graph::bfs() //ITERATIVE BFS
{
	char queue[10], temp;
	int front = -1, rear = -1;
	int i = 0,x=0;
	//PRINTING SOURCE VERTEX
	cout << letters[0] << endl;
	do
	{
		for (i = 1; i < n; i++) //ITERATING OVER ROW OF MATRIX 
		{
			int f = 0;
			for (int j = 0; j < n; j++) //CHECKING WHETHER CURRENT ELEMENT IS VISITED
				if (letters[i] == queue[j])
				{
					f = 1;
				}
			if(adj_matrix[x][i] >0 && f==0) //ADD UNVISITED VERTEX TO QUEUE
			{
				if (front == -1)
				{
					front = rear = 0;
					queue[rear] = letters[i];
				}
				else
				{
					rear++;
					queue[rear] = letters[i];
				}
			}
		}
		if (front != -1) //POPPING AS NO MORE UNVISITED VERTEX LEFT
		{
			temp = queue[front];
			cout << temp << endl;
			front++;
		}
		for (int j = 0; j < n; j++) //FINDING POSITION OF ADJACENT VERTEX
			if (letters[j] == temp)
				x = j;
	} while (front <= rear);
}

void graph::prim_tree()
{
	int copy_matrix[10][10];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			copy_matrix[i][j] = adj_matrix[i][j];
			if (i == j)
			{
				copy_matrix[i][j] = 9999;
			}
		}
	}
	int x = 0,min,a,b, mincost=0;
	int visited[10] = {0,0,0,0,0,0,0,0,0,0};
	visited[0] = 1;
	while (x < n-1)
	{
		min = 999;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (copy_matrix[i][j] < min && copy_matrix[i][j] != 0)
				{
					if (visited[j] == 0)
					{
						min = copy_matrix[i][j];
						a = i;
						b = j;
					}
				}
			}
		}
		if (visited[a] == 0 || visited[b] == 0)
		{
			cout << "Edge " << letters[a] << " & " << letters[b] << "have minimum Ccost= " << min*120 << endl;
			mincost += min;
			visited[b] = 1;

			x++;
		}
	}
	cout << "Minimum Cost--" << mincost*120 << endl;
}

int graph::minDistance(int dist[], bool sptSet[])
{
	int min = 999, min_index;
	for (int v = 0; v < n; v++)
	{
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	}
	return min_index;
}

void graph::dijkstra(int src )
{
	int dist[20];
	bool sptSet[20];
	for (int i = 0; i< n; i++)
	{
		dist[i] = 999;
		sptSet[i] = false;
	}
	dist[src] = 0;
	for (int count=0;count<n-1;count++)
	{
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < n; v++)
		{
			if (!sptSet[v] && adj_matrix[u][v] && dist[u] != 999 && dist[u] + adj_matrix[u][v] < dist[v])
				dist[v] = dist[u] + adj_matrix[u][v];
		}
	}
	cout << "Vertex Distance from Source";
	for (int i = 0; i < n; i++)
		cout << i << '\t' << dist[i] << endl;
}
int main()
{
	graph sample;
	sample.create();
	sample.disp_matrix();
	sample.prim_tree();
	int src;
	cout << "Enter Source Vertex";
	cin >> src;
	sample.dijkstra(src);
	system("PAUSE");
	return 0;
}