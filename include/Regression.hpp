#ifndef _REGRESSION
#define _REGRESSION

#include "Eigen.hpp"

// Least squares linear regression
class LinearRegression {
public:
    typedef CompleteOrthogonalDecomposition<MatrixXd> Cod;
    void fit(const MatrixXd& x, const VectorXd& y);
    VectorXd predict(const MatrixXd& x);
private:
    MatrixXd solution;
};

#endif
