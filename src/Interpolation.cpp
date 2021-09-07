#include "Interpolation.hpp"

Interpolation::Interpolation() {
    acc = gsl_interp_accel_alloc();
}

Interpolation::~Interpolation() {
    if (spline) {
        gsl_spline_free(spline);
    }
    gsl_interp_accel_free(acc);
}

// Note: what if object already initialized? OK to call spline_init again?
void Interpolation::fit(const Vec& x, const Vec& y) {
    if (x.size() != y.size()) {
        throw "X and Y must be the same size.";
    }
    spline = gsl_spline_alloc(gsl_interp_cspline, x.size());
    gsl_spline_init(spline, &x[0], &y[0], x.size());
}

Vec Interpolation::predict(const Vec& x) {
    Vec y;
    for (double xi : x) {
        y.push_back(gsl_spline_eval(spline, xi, acc));
    }
    return y;
}

