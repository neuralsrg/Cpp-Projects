#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include "solver.hpp"

class LR
{
    int n, m;
    std::vector<int> p, c;
    std::vector<double> lambda, d_lambda, solver_weights;
    std::vector<std::vector<int>> W;

    std::vector<double> compute_lagrange_coefs();
    int compute_g(int, const std::vector<int>&);
    void normalize_d_lambda();
    double step(int, bool);

    public:

    LR(int, int);
    std::pair<double, vector<double>> fit(int);
};

LR::LR(int n, int m): n(n), m(m), p(n), c(m), lambda(m-1, 1.0),
                      d_lambda(m-1), solver_weights(0), W(0)
{
    W.resize(n, std::vector<int>(m));
    for (auto& v: c) {
        std::cin >> v;
    }

    for (auto& v: p) {
        std::cin >> v;
    }

    for (auto& row: W){
        for (auto& v: row) {
            std::cin >> v;
        }
        solver_weights.push_back(double(row.back()));
    }
}

std::vector<double> LR::compute_lagrange_coefs()
{
    double new_coef = 0;
    std::vector<double> coefs(n+1);
    for (int x_idx = 0; x_idx < n; ++x_idx) {
        new_coef = p[x_idx];
        for (int lambda_idx = 0; lambda_idx < m-1; ++lambda_idx)
            new_coef -= (W[x_idx][lambda_idx]*lambda[lambda_idx]);
        coefs[x_idx] = (new_coef > 0 ? new_coef : 0);
    }

    new_coef = 0;
    for (int i = 0; i < int(lambda.size()); ++i)
        new_coef += (c[i]*lambda[i]);
    coefs[n] = new_coef;

    return coefs;
}

int LR::compute_g(int g_ind, const std::vector<int>& x_indices)
{
    int g = c[g_ind];
    for (auto& ind: x_indices) {
        g -= W[ind][g_ind];
    }

    return g;
}

void LR::normalize_d_lambda()
{
    double norm = 0;
    for (auto& v: d_lambda) {
        norm += std::pow(v, 2);
    }
    norm = std::pow(norm, 0.5);
    norm = norm > 1e-7 ? norm : 1e-7;
    for (auto& v: d_lambda) {
        v /= norm;
    }
}

double LR::step(int iteration, bool update_lambda=true)
{
    float learning_rate = 1 / float(iteration);
    auto lagrange_coefs = compute_lagrange_coefs();

    double free_term = lagrange_coefs.back();
    lagrange_coefs.pop_back();

    ListSolver solver(n, c.back());
    auto price_inds = solver.solve(lagrange_coefs, solver_weights);

    if (update_lambda) {
        for (int i = 0; i < m - 1; ++i)
            d_lambda[i] = compute_g(i, price_inds.second);
        
        normalize_d_lambda();

        for (int i = 0; i < int(lambda.size()); ++i) {
            double& l = lambda[i];
            l -= (learning_rate*d_lambda[i]);
            l = l >= 0 ? l : 0;
        }
    }

    return price_inds.first + free_term;
}

std::pair<double, vector<double>> LR::fit(int n_iters)
{
    double d, d_new = 0;
    for (int iter = 1; iter <= n_iters; ++iter) {
        d_new = step(iter);
        if (abs(d_new - d) < 1e-7)
            break;
        d = d_new;
    }
    d = step(1, false);

    return std::make_pair(d, lambda);
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    LR lr(n, m);
    auto d_lambda = lr.fit(20000);

    std::cout << d_lambda.first << std::endl;
    for (auto& v: d_lambda.second) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
