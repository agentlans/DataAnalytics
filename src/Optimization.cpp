#include "Optimization.hpp"

// C function for Nlopt to optimize 
static double target(unsigned n, const double* x, double* grad, void* f_data) {
    Vec v(x, x+n);
    auto f = static_cast<Function*>(f_data);
    return (*f)(v);
}

// Initialize optimizer using gradient-free method
Optimizer::Optimizer(const Function& f, const Vec& x, bool minimize, int max_eval) : f(f), x(x) {
    opt = nlopt_create(NLOPT_LN_SBPLX, x.size());
    void* fptr = (void*) &f;
    if (minimize) {
        nlopt_set_min_objective(opt, target, fptr);
    } else {
        nlopt_set_max_objective(opt, target, fptr);
    }
    // Set maximum number of evaluations
    if (max_eval != -1) {
        nlopt_set_maxeval(opt, max_eval);
    }
}

Optimizer::~Optimizer() {
    if (opt) nlopt_destroy(opt);
}

void Optimizer::set_lower_bounds(const Vec& lb) {
    nlopt_set_lower_bounds(opt, &lb[0]);
}

void Optimizer::set_upper_bounds(const Vec& ub) {
    nlopt_set_upper_bounds(opt, &ub[0]);
}

void Optimizer::optimize() {
    nlopt_result err = nlopt_optimize(opt, &x[0], &val);
    if (err < 0) {
        throw nlopt_result_to_string(err);
    }
}

double Optimizer::value() const {
    return val;
}

Vec Optimizer::best_parameters() const {
    return x;
}
