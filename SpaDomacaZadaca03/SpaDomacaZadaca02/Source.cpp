#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <functional>

const int redovi = 20;
const int stupci = 40;
const int cellSize = 20;

using namespace std;

struct Point
{
    int x, y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Node {
    Point point;
    int gCost;
    int hCost;
    Node* parent;

    Node(Point p, int g, int h, Node* par) : point(p), gCost(g), hCost(h), parent(par) {}

    int fCost() const
    {
        return gCost + hCost;
    }
};

struct Compare
{
    bool operator()(const Node* a, const Node* b)
    {
        return a->fCost() > b->fCost();
    }
};

int heuristic(Point a, Point b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

bool isValid(int x, int y)
{
    return x >= 0 && x < redovi && y >= 0 && y < stupci;
}

vector<Point> getPath(Node* node)
{
    vector<Point> path;
    while (node != nullptr) {
        path.push_back(node->point);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Point> aStar(Point start, Point end)
{
    priority_queue<Node*, vector<Node*>, Compare> openSet;
    vector<vector<bool>> closedSet(redovi, vector<bool>(redovi, false));

    openSet.push(new Node(start, 0, heuristic(start, end), nullptr));

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        if (current->point == end)
            return getPath(current);

        closedSet[current->point.x][current->point.y] = true;

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; ++i) {
            int newX = current->point.x + dx[i];
            int newY = current->point.y + dy[i];

            if (isValid(newX, newY) && !closedSet[newX][newY])
            {
                int newGCost = current->gCost + 1;
                int newHCost = heuristic(Point(newX, newY), end);
                openSet.push(new Node(Point(newX, newY), newGCost, newHCost, current));
            }
        }
    }

    return vector<Point>();
}

void draw(sf::RenderWindow& window, const Point& current, const Point& end) {
    window.clear();

    for (int i = 0; i < redovi; ++i) {
        for (int j = 0; j < stupci; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            cell.setFillColor(sf::Color::White);
            window.draw(cell);
        }
    }

    // Draw current position
    sf::RectangleShape currentCell(sf::Vector2f(cellSize, cellSize));
    currentCell.setPosition(current.y * cellSize, current.x * cellSize);
    currentCell.setFillColor(sf::Color::Green);
    window.draw(currentCell);

    // Draw end position
    sf::RectangleShape endCell(sf::Vector2f(cellSize, cellSize));
    endCell.setPosition(end.y * cellSize, end.x * cellSize);
    endCell.setFillColor(sf::Color::Red);
    window.draw(endCell);

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(stupci * cellSize, redovi * cellSize), "A* Pathfinding");

    int startX, startY, endX, endY;
    cout << "Unesite redak i stupac tocke A (1-20): ";
    cin >> startX >> startY;
    cout << "Unesite redak i stupac tocke B (1-40): ";
    cin >> endX >> endY;

    Point start(startX - 1, startY - 1);
    Point end(endX - 1, endY - 1);

    vector<Point> path = aStar(start, end);

    if (path.empty())
    {
        cout << "No path found!" << endl;
        return 1;
    }

    for (const auto& point : path)
    {
        draw(window, point, end);
        sf::sleep(sf::milliseconds(100));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}