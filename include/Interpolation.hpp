#ifndef _INTERPOLATION
#define _INTERPOLATION

#include <vector>
#include <gsl/gsl_spline.h>

typedef std::vector<double> Vec;

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
