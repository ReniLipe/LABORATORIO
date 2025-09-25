//
// Created by renat on 18/09/2025.
//
using namespace std;
#include "AStar.h"
#include <unordered_set>
#include <queue>

struct NodeCompare {
    bool operator() (const Node* a, const Node* b) {
        return a->cost < b->cost;
    }
};

float AStar::calculateHeuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool AStar::isValid(int x, int y, const vector<vector<int>>& grid) {
    return x >= 0 && y >= 0 && x < grid[0].size() && y < grid.size() && grid[x][y] == 0; //0=percorso libero
}
vector<Node> AStar::getNeighbors(const Node &node, const vector<vector<int>> &grid) {
    vector<Node> neighbors;
    const int directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; //right,down,left,up

    for (const auto& dir: directions) {
      int newX = node.x + dir[0];
      int newY = node.y + dir[1];

        if (isValid(newX, newY, grid)) {
            neighbors.emplace_back(newX, newY);
        }
    }
    return neighbors;
}

vector<Node> AStar::recostructPath(Node* endNode) {
    vector<Node> path;
    Node*current = endNode;

    while (current !=nullptr) {
        path.push_back(*current);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Node> AStar::findPath(const vector<vector<int>>& grid, Node Start,Node end) {
    priority_queue<Node*, vector<Node*>, NodeCompare> openSet;
    vector<Node*>allNodes; //per gestire bene la memoria

    auto startNode= new Node(Start.x, Start.y);
    startNode->heuristic = calculateHeuristic(Start.x, Start.y, end.x, end.y);
    openSet.push(startNode);
    allNodes.push_back(startNode);

    vector<vector<bool>> closedSet(grid.size(), vector<bool>(grid[0].size(), false));

    while (!openSet.empty()) {
        Node* current=openSet.top();
        openSet.pop();

        if (current->x == end.x && current->y == end.y) {
            auto path= recostructPath(current);

            //rilibera la memoria
            for (auto node: allNodes) delete node;
            return path;
        }

        closedSet[current->x][current->y] = true;

        for (const auto& neighborPos: getNeighbors(*current,grid)) {
            if (closedSet[neighborPos.x][neighborPos.y]) continue;

            float newCost= current->cost + 1.0f;
            Node* neigbhorNode = nullptr;
//cerca il nodo se esiste di già
            for (auto node: allNodes) {
                if (node->x == neighborPos.x && node->y == neighborPos.y) {
                    neigbhorNode = node;
                    break;
                }
            }
            if (neigbhorNode == nullptr) {
                neigbhorNode = new Node(neighborPos.x, neighborPos.y);
                neigbhorNode->heuristic = calculateHeuristic(neighborPos.x, neighborPos.y, end.x, end.y);
                allNodes.push_back(neigbhorNode);
                openSet.push(neigbhorNode);
            }

            if (newCost < neigbhorNode->cost) {
                neigbhorNode->cost = newCost;
                neigbhorNode->parent = current;
            }
        }
    }

    //libera la memoria se non trovi il percorso
    for (auto node: allNodes) delete node;
    return {}; //percorso non trovato

}
