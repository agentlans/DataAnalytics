#ifndef _SCALEH
#define _SCALEH

#include "Eigen.hpp"

// Scales the columns of the matrix to 0 mean and standard deviation 1
class StandardScaler {
public:
    void fit(const MatrixXd& m, bool scale=true);
    MatrixXd transform(const MatrixXd& m) const;
    MatrixXd inverse_transform(const MatrixXd& m) const;
private:
    VectorXd means;
    VectorXd sds;
};

#endif
