#ifndef _CROSSVALIDATION
#define _CROSSVALIDATION

#include <memory>
#include "Eigen.hpp"

struct CrossValidationData {
    MatrixXd train_x;
    MatrixXd train_y;
    MatrixXd test_x;
    MatrixXd test_y;
};

// Implements k-fold cross validation
class CrossValidation {
public:
    CrossValidation(const MatrixXd& x, const MatrixXd& y, 
        int folds, unsigned long seed = 0);
    // Get data for the ith fold of cross validation
    CrossValidationData get(int i);
private:
    // Matrix with random row order
    std::shared_ptr<MatrixXd> x, y;
    int k; // k-fold cross validation
    int d, nmod;
    // For computing the row index
    int fold_index(int i);
};

#endif