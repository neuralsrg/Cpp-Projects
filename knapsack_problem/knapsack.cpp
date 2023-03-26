#include <iostream>
#include <vector>

namespace knapsack
{
    class Node;
    class LevelList;
}

class knapsack::Node
{
    public:

    uint8_t new_val;
    uint32_t prev, cost, price;

    Node(uint8_t v=0, uint32_t p=0, uint32_t c=0, uint32_t price=0):
         new_val(v), prev(p), cost(c), price(price) {}
};

class knapsack::LevelList
{
    std::vector<knapsack::Node> list;

    public:

    LevelList(uint32_t len=0): list(len) {}
    void push_back(const knapsack::Node& n)
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

std::ostream& operator<<(std::ostream& cout, const knapsack::Node& n)
{
    cout << "(" << int(n.new_val) << "," << n.prev << "," << n.cost << "," << n.price << ")";
    return cout;
}

void build_list(u_int32_t n, u_int32_t c)
{
    uint32_t w, p;
    std::vector<uint32_t> weights(n), prices(n);

    std::vector<knapsack::LevelList> levels(n+1);

    for (u_int32_t i = 0; i < n; ++i) {
        std::cin >> w >> p;
        weights[i] = w;
        prices[i] = p;
    }

    // root
    levels[0].push_back(knapsack::Node(0, 0, 0, 0));

    // level cycle
    for (u_int32_t level = 1; level <= n; ++level) {

        u_int32_t add_weight = weights[level-1], add_price = prices[level-1];

        // candidate with new_value = 1
        u_int32_t cand1_idx = 0;
        u_int32_t cand1_weight = levels[level-1][cand1_idx].cost + add_weight;
        u_int32_t cand1_price = levels[level-1][cand1_idx].price + add_price;

        // over previous level nodes
        for (u_int32_t pl_node_idx=0; pl_node_idx < levels[level-1].size(); ++pl_node_idx) {

            // candidate with new_value = 0
            u_int32_t cand0_price = levels[level-1][pl_node_idx].price;
            u_int32_t cand0_weight = levels[level-1][pl_node_idx].cost;

            // if all cand1 are already pushed or cand1 exceeds capacity
            if ((cand1_idx >= levels[level-1].size()) || (cand1_weight > c)) {
                levels[level].push_back(knapsack::Node(0, pl_node_idx, cand0_weight, cand0_price));
            }
            // if cand0 dominates cand1
            else if ((cand0_weight <= cand1_weight) && (cand0_price >= cand1_price)) {
                cand1_idx += 1;
                cand1_weight = levels[level-1][cand1_idx].cost + add_weight;
                cand1_price = levels[level-1][cand1_idx].price + add_price;
                --pl_node_idx;
            }
            // if cand1 dominates cand0
            else if ((cand1_weight <= cand0_weight) && (cand1_price >= cand0_price)) {
                continue;
            }
            // if cand0 has lower weight and lower price
            else if ((cand0_weight < cand1_weight) && (cand0_price < cand1_price)) {
                levels[level].push_back(knapsack::Node(0, pl_node_idx, cand0_weight, cand0_price));
            }
            // if cand1 has lower weight and lower price
            else if ((cand1_weight < cand0_weight) && (cand1_price < cand0_price)) {
                levels[level].push_back(knapsack::Node(1, cand1_idx, cand1_weight, cand1_price));
                cand1_idx += 1;
                cand1_weight = levels[level-1][cand1_idx].cost + add_weight;
                cand1_price = levels[level-1][cand1_idx].price + add_price;
                --pl_node_idx;
            }
        }

        // pushing remaining candidates
        for (; cand1_idx < levels[level-1].size(); ++cand1_idx) {
            cand1_weight = levels[level-1][cand1_idx].cost + add_weight;
            cand1_price = levels[level-1][cand1_idx].price + add_price;
            if (cand1_weight <= c) {
                levels[level].push_back(knapsack::Node(1, cand1_idx, cand1_weight, cand1_price));
            }
        }
    }

    /*
    for (auto list: levels) {
        for (u_int32_t i = 0; i < list.size(); ++i) {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */

    // creating answer info
    uint32_t max_idx = levels[levels.size()-1].size()-1;
    uint32_t max_price = levels[levels.size()-1][max_idx].price;

    std::vector<u_int8_t> ans_vector;
    for (u_int32_t level = levels.size() - 1; level > 0; --level) {
        if (levels[level][max_idx].new_val) {
            ans_vector.push_back(level-1);
        }
        max_idx = levels[level][max_idx].prev;
    }

    // output answer
    std::cout << int(max_price) << " " << int(ans_vector.size()) << std::endl;
    for (auto l: ans_vector) {
        std::cout << int(l) << std::endl;
    }
}

int main()
{
    // n - number of objects
    // c - capacity
    u_int32_t n, c;
    std::cin >> n >> c;

    build_list(n, c);

    return 0;
}