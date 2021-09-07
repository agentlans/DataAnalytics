#include "PCA.hpp"

MatrixXd PCA::transform(const MatrixXd& m) const {
	MatrixXd x = ss.transform(m);
	return x * v;
}

// Returns matrix containing the first k columns of m
MatrixXd get_cols(const MatrixXd& m, int k) {
	return m.block(0,0, m.rows(), k);
}

MatrixXd PCA::inverse_transform(const MatrixXd& pc) const {
	int c = std::min(pc.cols(), v.cols());
	MatrixXd x = get_cols(pc, c) * get_cols(v, c).transpose();
	return ss.inverse_transform(x);
}

MatrixXd PCA::principal_directions() const {
	return v;
}

MatrixXd PCA::principal_components() const {
	return u * sv.asDiagonal();
}

VectorXd PCA::eigenvalues() const {
	ArrayXd arr = ArrayXd(sv);
	return arr*arr/(n-1);
}

void PCA::fit(const MatrixXd& m, bool scale) {
	ss.fit(m, scale);
	MatrixXd m2 = ss.transform(m);

	int n = m.rows(), p = m.cols();

	JacobiSVD<MatrixXd> svd(m2, ComputeThinU | ComputeThinV);
	sv = svd.singularValues();
	u = svd.matrixU();
	v = svd.matrixV();
}

