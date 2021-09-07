#ifndef _PCA
#define _PCA

#include "Eigen.hpp"
#include "Scale.hpp"

// Principal components analysis
class PCA {
public:
	void fit(const MatrixXd& m, bool scale=true);
	MatrixXd transform(const MatrixXd& m) const;
	MatrixXd inverse_transform(const MatrixXd& pc) const;

	// Statistics of the matrix used to fit PCA	
	MatrixXd principal_directions() const;
	MatrixXd principal_components() const;
	VectorXd eigenvalues() const;
private:
	StandardScaler ss;
	MatrixXd u, v; // Singular vectors from SVD
	VectorXd sv; // Singular values

	int n, p; // Rows, columns of matrix used for fitting.
};

#endif
