#ifndef _INTERPOLATION
#define _INTERPOLATION

#include <gsl/gsl_spline.h>
#include "General.hpp"

class Interpolation {
public:
    Interpolation();
    ~Interpolation();
    void fit(const Vec& x, const Vec& y);
    Vec predict(const Vec& x);
private:
    gsl_interp_accel *acc;
    gsl_spline *spline = NULL;
};

#endif
