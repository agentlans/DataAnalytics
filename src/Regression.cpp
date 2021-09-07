#include <Eigen/QR>

#include "Regression.hpp"

void LinearRegression::fit(const MatrixXd& x, const VectorXd& y) {
    Cod qr = Cod(x);
    solution = qr.solve(y);
}

VectorXd LinearRegression::predict(const MatrixXd& x) {
    return x * solution;
}

