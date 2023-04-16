#ifndef SOLVER_DOC
#define SOLVER_DOC

#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:

    uint8_t new_val;
    uint32_t prev, cost, price;

    Node(uint8_t v=0, uint32_t p=0, uint32_t c=0, uint32_t price=0):
         new_val(v), prev(p), cost(c), price(price) {}
};

class LevelList
{
    std::vector<Node> list;

    public:

    LevelList(uint32_t len=0): list(len) {}
    void push_back(const Node& n)
    {
        list.push_back(n);
    }
    uint32_t size()
    {
        return list.size();
    }
    Node& operator[](const int idx)
    {
        return list[idx];
    }
};

class ListSolver {

    int n, C;

public:
    ListSolver(int n, int C);

    pair<double, vector<int>> solve(const vector<double> &price, const vector<double> &weight);

};

#endif
