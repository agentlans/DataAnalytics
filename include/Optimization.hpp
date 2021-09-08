#ifndef _OPTIMIZATION
#define _OPTIMIZATION

#include <nlopt.h>
#include "General.hpp"

class Optimizer {
public:
    Optimizer(const Function& f, const Vec& x, 
        bool minimize=true, int max_eval=-1);
    ~Optimizer();

    void set_lower_bounds(const Vec& lb);
    void set_upper_bounds(const Vec& ub);

    void optimize();

    double value() const;
    Vec best_parameters() const;
private:
    nlopt_opt opt = nullptr;

    Function f; // Function to optimize
    Vec x; // Optimal parameters
    double val; // Optimal value
};

#endif
