#include "solver.hpp"

ListSolver::ListSolver(int n, int C): n(n), C(C) {}

pair<double, vector<int>> ListSolver::solve(const vector<double> &price, const vector<double> &weight)
{
    std::vector<LevelList> levels(n+1);

    // root
    levels[0].push_back(Node(0, 0, 0, 0));

    // level cycle
    for (u_int32_t level = 1; level <= u_int32_t(n); ++level) {

        u_int32_t add_weight = weight[level-1], add_price = price[level-1];

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
            if ((cand1_idx >= levels[level-1].size()) || (cand1_weight > u_int32_t(C))) {
                levels[level].push_back(Node(0, pl_node_idx, cand0_weight, cand0_price));
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
                levels[level].push_back(Node(0, pl_node_idx, cand0_weight, cand0_price));
            }
            // if cand1 has lower weight and lower price
            else if ((cand1_weight < cand0_weight) && (cand1_price < cand0_price)) {
                levels[level].push_back(Node(1, cand1_idx, cand1_weight, cand1_price));
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
            if (cand1_weight <= u_int32_t(C)) {
                levels[level].push_back(Node(1, cand1_idx, cand1_weight, cand1_price));
            }
        }
    }

    // creating answer info
    uint32_t max_idx = levels[levels.size()-1].size()-1;
    uint32_t max_price = levels[levels.size()-1][max_idx].price;

    std::vector<int> ans_vector;
    for (u_int32_t level = levels.size() - 1; level > 0; --level) {
        if (levels[level][max_idx].new_val) {
            ans_vector.push_back(int(level-1));
        }
        max_idx = levels[level][max_idx].prev;
    }

    return std::make_pair(double(max_price), ans_vector);
}