#include <gsl/gsl_statistics_double.h>
#include <Eigen/QR>

#include "Eigen.hpp"
#include "Scale.hpp"

double mean(const VectorXd& x) {
	return gsl_stats_mean(x.data(), 1, x.size());
}

double standard_deviation(const VectorXd& x) {
	return gsl_stats_sd(x.data(), 1, x.size());
}

void StandardScaler::fit(const MatrixXd& m, bool scale) {
    means = VectorXd(m.cols());
    sds = VectorXd(m.cols());
    for (int i = 0; i < m.cols(); ++i) {
        means[i] = mean(m.col(i));
	if (scale) {
	        sds[i] = standard_deviation(m.col(i));
	} else {
		sds[i] = 1;
	}
    }
}

MatrixXd StandardScaler::transform(const MatrixXd& m) const {
    MatrixXd m2 = m;
    for (int i = 0; i < m.cols(); ++i) {
        m2.col(i) = (m.col(i).array() - means[i]) / sds[i];
    }
    return m2;
}

MatrixXd StandardScaler::inverse_transform(const MatrixXd& m) const {
    MatrixXd m2 = m;
    for (int i = 0; i < m.cols(); ++i) {
        m2.col(i) = (m.col(i).array() * sds[i]) + means[i];
    }
    return m2;
}

