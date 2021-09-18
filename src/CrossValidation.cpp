#include <vector>
#include <cassert>

#include "CrossValidation.hpp"
#include "Random.hpp"

CrossValidation::CrossValidation(const MatrixXd& x, const MatrixXd& y, 
    int folds, unsigned long seed) : k(folds) { 
    assert(x.rows() == y.rows());
    // To hold a matrix with random row order
    this->x = std::make_shared<MatrixXd>(MatrixXd(x.rows(), x.cols()));
    this->y = std::make_shared<MatrixXd>(MatrixXd(y.rows(), y.cols()));
    // Random generator and row indices
    Random r(seed);
    int n = x.rows();
    std::vector<int> row_index(n);
    for (int i = 0; i < n; ++i) {
        row_index[i] = i;
    }
    // Shuffle the rows of the matrix
    r.shuffle<int>(row_index);
    for (int i = 0; i < n; ++i) {
        this->x->row(i) = x.row(row_index[i]);
        this->y->row(i) = y.row(row_index[i]);
    }
    // Save some stats
    d = floor(n/folds);
    nmod = n % k;
}

// Returns the row index of the ith fold of cross-validation
int CrossValidation::fold_index(int i) {
    return i*d + std::min(i, nmod);
}

MatrixXd rbind(const MatrixXd& m1, const MatrixXd& m2) {
    assert(m1.cols() == m2.cols());
    MatrixXd out(m1.rows() + m2.rows(), m1.cols());
    out.block(0, 0, m1.rows(), out.cols()) = m1;
    out.block(m1.rows(), 0, m2.rows(), out.cols()) = m2;
    return out;
}

// Returns the training and testing x, y data for the ith fold of cross validation
CrossValidationData CrossValidation::get(int i) {
    int n = x->rows();
    int row1 = fold_index(i);
    int row2 = fold_index(i+1);
    int test_size = row2 - row1;
    int train_size = n - test_size;

    int x_cols = x->cols();
    int y_cols = y->cols();
    
    CrossValidationData cvd;
    cvd.test_x = x->block(row1, 0, test_size, x_cols);
    cvd.test_y = y->block(row1, 0, test_size, y_cols);

    // Combine the entries before and after the testing set
    cvd.train_x = rbind(
        x->block(0, 0, row1, x_cols),
        x->block(row1, n, n-row1, x_cols));
    cvd.train_y = rbind(
        y->block(0, 0, row1, y_cols),
        y->block(row1, n, n-row1, y_cols));
    return cvd;
}
