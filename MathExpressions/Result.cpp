#include "Result.hpp"
#include <cmath>
#include <math.h>

Result::Result(double x): m(std::make_shared<Mantissa>()), p(0), sign(x < 0) {
    x = x >= 0 ? x : -1 * x;
    double f,i;
    while ((f = modf(x, &i)) > 0) {
        x*=10; --p;
    }
    long long l = (long long) i;
    do {
        m->push_in_end(l % power);
    } while ((l /= power > 0));
};

std::shared_ptr<Result> lowpow(std::shared_ptr<Result> r, int n) {
    for (int i = 0; i < n / symb_count; ++i) {
        r = mul(r, power);
        r->setpow(r->getpow() - symb_count);
    }
    if (n % symb_count > 0) {
        int k = 1, m = n % symb_count;
        for (int j = 0; j < m; ++j)
            k *= 10;
        r = mul(r, k);
        r->setpow(r->getpow() - m);
    }
    return r;
};

std::shared_ptr<Result> highpow(std::shared_ptr<Result> r, int n){
    for (int i = 0; i < n/symb_count; ++i) {
        r = div(r, power);
        r->setpow(r->getpow() + symb_count);
    }
    if (n % symb_count > 0) {
        int k = 1, m = n % symb_count;
        for (int j = 0; j < m; ++j) {
            k *= 10;
            r = div(r, k);
            r->setpow(r->getpow() + m);
        }
    }
    return r;
};

//

std::ostream& operator<< (std::ostream& cout, std::shared_ptr<Result> r) {
    if (r->sign) {
        cout << '-';
        printres(r);
        return cout;
    }
    printres(r);
    return cout;
};

std::shared_ptr<Result> precision(std::shared_ptr<Result> r){
    int p = -1 * std::cout.precision();
    if (r->getpow() == p)
        return r;
    if (r->getpow() < p)
        return highpow(r, p - r->getpow());
    return lowpow(r, r->getpow() - p);
};

void printres(std::shared_ptr<Result> r) {
    int pr = std::cout.precision();
    int e = std::ceil((double)pr / symb_count) - r->m->get_size();
    e = e > 0 ? e : 0;
    if (e) {
        for (int i = 0; i < e; ++i) {
            r->m->push_in_end(0);
        }
    }
    int i = r->m->get_size() - 1;
    for (i = r->m->get_size() - 1; i > ((double)pr / symb_count - 1); --i) {
        if (i == r->m->get_size() - 1)
            std::cout << std::setw(1) << std::setfill('0') <<(*r->m)[i];
        else
            std::cout << std::setw(symb_count) << std::setfill('0') <<(*r->m)[i];
    }
    int m = pr % symb_count, p = 1;
    for (int j = 0; j < m; ++j) {
        p *= 10;
    }
    if (i == r->m->get_size() - 1)
        std::cout << (*r->m)[i] / p << '.' << (*r->m)[i] % p ;
    else {
        std::cout << std::setw(symb_count - m) << std::setfill('0') << (*r->m)[i] / p;
        std::cout << '.' << (*r->m)[i] % p ;
    }
    while (i > 0) {
        --i;
        std::cout << std::setw(symb_count) << std::setfill('0') << (*r->m)[i];
    }
    for (int i = 0; i < e; i++)
        r->m->pop_from(r->m->get_size() - 1 - i);
};

//+

std::shared_ptr<Result> sumequalpow(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    long long sum = 0;
    if (r1->m->get_size() > r2->m->get_size()) {
        std::shared_ptr<Result> tmp = r1;
        r1 = r2;
        r2 = tmp;
    }
    auto newr = std::make_shared<Result>(r2->m->dup(), r2->p);
    for (int i = 0; i < r1->m->get_size(); ++i) {
        sum = (*newr->m)[i] + (*r1->m)[i];
        (*newr->m)[i] = sum % power;
        sum /= power;
        for (int j = i + 1; j < newr->m->get_size(); ++j) {
            sum += (*newr->m)[j];
            (*newr->m)[j] = sum % power;
            sum /= power;
        }
        while (sum) {
            newr->m->push_in_end(sum % power);
            sum /= power;
        }
    }
    return newr;
};

std::shared_ptr<Result> operator+ (std::shared_ptr<Result> r1,std::shared_ptr<Result> r2) {
    r1 = precision(r1); r2 = precision(r2);
    int p1 = r1->getpow(), p2 = r2->getpow();
    if (p1 > p2)
        r1 = lowpow(r1, p1 - p2);
    else if (p2 > p1)
        r2 = lowpow(r2, p2 - p1);
    if (!r1->sign && !r2->sign)
        return sumequalpow(r1, r2);
    if (r1->sign && r2->sign) {
        r1 = std::make_shared<Result>(r1->m->dup(), r1->p);
        r2 = std::make_shared<Result>(r2->m->dup(), r2->p);
        auto newr = sumequalpow(r1, r2);
        newr->setsign(!newr->sign);
        return newr;
    }
    if (!r1->sign && r2->sign) {
        r2 = std::make_shared<Result>(r2->m->dup(), r2->p);
        return reduseequalpow(r1, r2);
    }
    r1 = std::make_shared<Result>(r1->m->dup(), r1->p);
    auto newr = reduseequalpow(r1, r2);
    newr->setsign(!newr->sign);
    return newr;
};

//*
std::shared_ptr<Result> mul(std::shared_ptr<Result> r, int n) {
    long long l = 0;
    auto newr = std::make_shared<Result>(r->m->dup(), r->p);
    newr->sign = !((!r->sign && n > 0) || (r->sign && n < 0));
    n = n >= 0 ? n : -1 * n;
    for (int i = 0; i < newr->m->get_size(); ++i) {
        l = (*newr->m)[i] * (long long)n + l;
        (*newr->m)[i] = l % power;
        l /= power;
    }
    if (l)
        newr->m->push_in_end(l);
    return newr;
};

std::shared_ptr<Result> operator* (std::shared_ptr<Result> r, int n) {
    r = precision(r);
    return mul(r, n);
};


std::shared_ptr<Result> operator* (std::shared_ptr<Result> r1,std::shared_ptr<Result> r2) {
    r1 = precision(r1); r2 = precision(r2);
    bool s = r1->sign == r2->sign;
    int p = 0;
    auto res = std::make_shared<Result>(0);
    for (int i = 0; i < r1->m->get_size(); ++i) {
        auto add = r2 * (*r1->m)[i];
        add->setpow(add->getpow() + p);
        p += symb_count;
        res = res + add;
    }
    res->setsign(s);
    return res;
};

// /
std::shared_ptr<Result> div (std::shared_ptr<Result> r, int n) {
    auto newr = std::make_shared<Result>(r->m->dup(), r->p);
    newr->setsign(!((!r->sign && n > 0) || (r->sign && n < 0)));
    n = n >= 0 ? n : -1 * n;
    long long tmp = (long long)((*r->m)[r->m->get_size() - 1]);
    for (int i = r->m->get_size() - 1; i >= 0; --i){
        (*newr->m)[i] = (int)(tmp / n);
        if (i)
            tmp = tmp % n * power + (*r->m)[i-1];
    }
    for (int j = newr->m->get_size() - 1; (*newr->m)[j] == 0; --j) {
        if (!j)
            break;
        newr->m->pop_from(j);
    }
    return newr;
};

std::shared_ptr<Result> operator/ (std::shared_ptr<Result> r, int n) {
    r = precision(r);
    return div(r,n);
};

// -
bool operator> (std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    if (r1->m->get_size() != r2->m->get_size())
        return(r1->m->get_size() > r2->m->get_size());
    if (r1->p > r2->p)
        r1 = lowpow(r1, r1->p - r2->p);
    else if (r1->p < r2->p)
        r2 = lowpow(r2, r2->p - r1->p);
    int i = r1->m->get_size()-1;
    while ((*r1->m)[i] == (*r2->m)[i]){
        if (!i)
            return false;
        else
            --i;
    }
    return ((*r1->m)[i] > (*r2->m)[i]);
};

std::shared_ptr<Result> reduseequalpow(std::shared_ptr<Result> r1, std::shared_ptr<Result> r2) {
    if (r2->m->get_size() == 1 && (*r2->m)[0] == 0)
        return std::make_shared<Result>(r1->m->dup(), r1->p);
    if (!(r1 > r2 || r2 > r1))
        return std::make_shared<Result>(0);
    if (r1 > r2) {
        auto newr = std::make_shared<Result> (r1->m->dup(), r1->p);
        for (int i = 0; i < r2->m->get_size(); ++i) {
            int res = (*newr->m)[i] - (*r2->m)[i];
            if (res < 0) {
                int j;
                for (j = i + 1; (*newr->m)[j] == 0; ++j) {
                    (*newr->m)[j] = power - 1;
                }
                (*newr->m)[j] -= 1;
                res += power;
            }
            (*newr->m)[i] = res;
        }
        for (int i = newr->m->get_size() - 1; (*newr->m)[i] == 0; --i) {
            newr->m->pop_from(i);
        }
        return newr;
    }
    auto newr = reduseequalpow(r2, r1);
    newr->setsign(1);
    return newr;
};

std::shared_ptr<Result> operator- (std::shared_ptr<Result> r1,std::shared_ptr<Result> r2) {
    r1 = precision(r1); r2 = precision(r2);
    int p1 = r1->getpow(), p2 = r2->getpow();
    if (p1 > p2)
        r1 = lowpow(r1, p1 - p2);
    else if (p2 > p1)
        r2 = lowpow(r2, p2 - p1);
    if (!r1->sign && !r2->sign)
        return reduseequalpow(r1, r2);
    if (r1->sign && r2->sign) {
        r1 = std::make_shared<Result>(r1->m->dup(), r1->p);
        r2 = std::make_shared<Result>(r2->m->dup(), r2->p);
        auto newr = reduseequalpow(r1, r2);
        newr->setsign(!newr->sign);
        return newr;
    }
    if (!r1->sign && r2->sign) {
        r2 = std::make_shared<Result>(r2->m->dup(), r2->p);
        return r1 + r2;
    }
    r1 = std::make_shared<Result>(r1->m->dup(), r1->p);
    auto newr = r1 + r2;
    newr->setsign(1);
    return newr;
};

bool zero(std::shared_ptr<Result> r) {
    for (int i = 0; i < r->m->get_size(); ++i) {
        if ((*r->m)[i])
            return false;
    }
    return true;
};

//elem functions
std::shared_ptr<Result> sin(std::shared_ptr<Result> r) {
    int i = 0;
    auto res = std::make_shared<Result>(0);
    auto tmp = std::make_shared<Result>(r->m->dup(), r->p);
    r = precision(r);
    tmp = precision(tmp);
    res = precision(res);
    while (!zero(tmp)) {
        res = res + tmp;
        ++i;
        tmp = tmp * r * r *(-1) / ((2 * i) * (2 * i + 1));
    }
    return res;
};

std::shared_ptr<Result> cos(std::shared_ptr<Result> r) {
    int i = 0;
    auto res = std::make_shared<Result>(0);
    auto tmp = std::make_shared<Result>(1);
    r = precision(r);
    tmp = precision(tmp);
    res = precision(res);
    while (!zero(tmp)) {
        res = res + tmp;
        ++i;
        tmp = tmp * r * r *(-1) / ((2 * i - 1) * (2 * i));
    }
    return res;
};

std::shared_ptr<Result> asin(std::shared_ptr<Result> r) {
    int i = 0;
    auto res = std::make_shared<Result>(0);
    auto tmp = std::make_shared<Result>(r->m->dup(), r->p);
    r = precision(r);
    tmp = precision(tmp);
    res = precision(res);
    while (!zero(tmp / (2 * i + 1))) {
        res = res + tmp / (2 * i + 1);
        ++i;
        tmp = tmp * r * r * (2 * i - 1) / (2 * i);
    }
    return res;
};

std::shared_ptr<Result> exp(std::shared_ptr<Result> r) {
    int i = 0;
    auto res = std::make_shared<Result>(0);
    auto tmp = std::make_shared<Result>(1);
    r = precision(r);
    tmp = precision(tmp);
    res = precision(res);
    while (!zero(tmp)) {
        res = res + tmp;
        ++i;
        tmp = tmp * r / i;
    }
    return res;
};

std::shared_ptr<Result> ln(std::shared_ptr<Result> r) {
    int i = 1;
    auto x = r - std::make_shared<Result> (1);
    auto res = std::make_shared<Result>(0);
    auto tmp = std::make_shared<Result>(x->m->dup(), x->p);
    x = precision(x);
    tmp = precision(tmp);
    res = precision(res);
    while (!zero(tmp / i)) {
        res = res + tmp / i;
        ++i;
        tmp = tmp * x * (-1);
    }
    return res;
};
