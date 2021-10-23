#include <eigen3/Eigen/Dense>
using namespace Eigen;

class funjacObj {
    public:
        Eigen::MatrixXd fun;
        Eigen::MatrixXd jacob;
        funjacObj(Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd);
};

funjacObj::funjacObj(Eigen::MatrixXd param, Eigen::MatrixXd niMat, 
Eigen::MatrixXd y2dMat, Eigen::MatrixXd ybarMat) {
    int m = param.rows();
    double mu = param(0);
    Eigen::MatrixXd vars = param.segment(1, m+1);
    Eigen::MatrixXd muhat = niMat * ybarMat;
    //fun(0) = mu - muhat;
}