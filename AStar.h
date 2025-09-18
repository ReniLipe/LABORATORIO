//
// Created by renat on 18/09/2025.
//

#ifndef CMAKESFMLPROJECT_ASTAR_H
#define CMAKESFMLPROJECT_ASTAR_H

//
// Created by renat on 18/09/2025.
//
using namespace std;
#pragma once
#include <vector>
#include <functional>
#include<set>
#include<cmath>
#include<iostream>
#include<algorithm>

struct Node {
    int x,y;
    float cost;
    float heuristic;
    Node* parent;

    Node(int x, int y, float cost = 0, float heuristic = 0, Node* parent = nullptr)
        : x(x), y(y), cost(cost), heuristic(heuristic), parent(parent) {}

    float getTotalCost() const {return cost + heuristic;}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Node& other) const {
        return getTotalCost() < other.getTotalCost();
    }
};

class AStar {
public:
    static vector<Node> findPath(const vector<vector<int>>& gird, Node start,Node end);

private:
    static float calculateHeuristic(int x1,int y1,int x2,int y2);
    static bool isValid(int x, int y ,const vector<vector<int>>& grid);
    static vector<Node> getNeighbors(const Node& node,const vector<vector<int>>& grid);
    static vector<Node> recostructPath(Node* endNode);
};

#endif //CMAKESFMLPROJECT_ASTAR_H