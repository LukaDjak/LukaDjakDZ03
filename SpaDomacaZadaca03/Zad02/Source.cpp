#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

const int rows = 20;
const int columns = 40;

struct Point
{
	int x, y;
	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(const Point& other) const
	{
		return !(*this == other);
	}
	bool operator<(const Point& other) const
	{
		return tie(x, y) < tie(other.x, other.y);
	}
};

struct Node 
{
	Point point;
	int cost;
	Node* parent;
	Node(Point p, int c, Node* par) : point(p), cost(c), parent(par) {}
};

struct Compare 
{
	bool operator()(const Node* a, const Node* b) 
	{
		return a->cost > b->cost;
	}
};

bool isValid(int x, int y, const vector<vector<bool>>& grid) 
{
	return x >= 0 && x < rows && y >= 0 && y < columns && !grid[x][y];
}

vector<Point> reconstructPath(Node* node) 
{
	vector<Point> path;
	while (node != nullptr) 
	{
		path.push_back(node->point);
		node = node->parent;
	}
	reverse(path.begin(), path.end());
	return path;
}

vector<Point> dijkstra(Point start, Point end, const vector<vector<bool>>& grid) 
{
	priority_queue<Node*, vector<Node*>, Compare> pq;
	map<Point, int> distances;
	map<Point, Node*> allNodes;

	pq.push(new Node(start, 0, nullptr));
	distances[start] = 0;

	while (!pq.empty()) 
	{
		Node* current = pq.top();
		pq.pop();

		if (current->point == end)
			return reconstructPath(current);

		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; ++i) 
		{
			int newX = current->point.x + dx[i];
			int newY = current->point.y + dy[i];

			if (isValid(newX, newY, grid)) 
			{
				Point neighbor(newX, newY);
				int newCost = current->cost + 1;

				if (distances.find(neighbor) == distances.end() || newCost < distances[neighbor]) 
				{
					distances[neighbor] = newCost;
					Node* neighborNode = new Node(neighbor, newCost, current);
					pq.push(neighborNode);
					allNodes[neighbor] = neighborNode;
				}
			}
		}
	}
	return vector<Point>();
}

void printGrid(const vector<vector<bool>>& grid, const vector<Point>& path, const Point& start, const Point& end) 
{
	vector<vector<char>> displayGrid(rows, vector<char>(columns, '*'));

	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < columns; ++j) 
		{
			if (grid[i][j])
				displayGrid[i][j] = '#';
		}
	}

	for (const auto& point : path) 
	{
		if (point != start && point != end) 
			displayGrid[point.x][point.y] = '/';
	}

	displayGrid[start.x][start.y] = 'A';
	displayGrid[end.x][end.y] = 'B';

	for (const auto& row : displayGrid) 
	{
		for (const auto& cell : row)
			cout << cell;
		cout << '\n';
	}
}

void generateWalls(vector<vector<bool>>& grid, int numWalls) 
{
	srand(time(0));
	while (numWalls > 0) 
	{
		int wallX = rand() % rows;
		int wallY = rand() % columns;
		if (!grid[wallX][wallY]) 
		{
			grid[wallX][wallY] = true;
			numWalls--;
		}
	}
}

int main() 
{
	int startX, startY, endX, endY;
	cout << "Unesite redak i stupac tocke A (1-20, 1-40): ";
	cin >> startX >> startY;
	cout << "Unesite redak i stupac tocke B (1-20, 1-40): ";
	cin >> endX >> endY;

	Point start(startX - 1, startY - 1);
	Point end(endX - 1, endY - 1);

	vector<vector<bool>> grid(rows, vector<bool>(columns, false));
	int numWalls = 50;
	generateWalls(grid, numWalls);

	vector<Point> path = dijkstra(start, end, grid);

	if (path.empty()) 
	{
		cout << "No path found!" << endl;
		return 1;
	}

	printGrid(grid, path, start, end);

	return 0;
}