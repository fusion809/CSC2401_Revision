#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <sstream>
using std::cout; 
using std::cerr;
using std::endl;
using std::string;
using std::ifstream; 
using std::vector;
using std::getline;
using std::stoi;
using std::stod;
using std::unique;
using std::sort;
using std::ostringstream;
using std::istringstream;
#include <CSV.h>
#include <vecOps.h>
#include <vars.h>
#include <newtons.h>

using namespace Rcpp;
using namespace Eigen;

// [[Rcpp::export]]
void outPut() {
    CSVData report("ProjectData.csv", 0, 5);
    vector<int> group = report.getGroup();
    vector<double> dist = report.getDist();
    Vars vars(group, dist);
    vector<int> ni = vars.ni;
    vector<double> nidoub = convertToDouble(ni);
    double nimax = vars.nimax;
    int n = vars.n;
    int m = vars.m;
    double ybar = vars.ybar;
    vector<double> ybarvec = vars.ybarvec;
    vector<vector<double>> yarr = vars.yarr2;
    vector<vector<double>> result = vec2DSq(vec2D1DSub(yarr, ybarvec));
    vector<double> num = vecColSum(result);
    double num1 = vecProd(power(num, scalMult(ni, 0.5)));

    Eigen::MatrixXd y1dMat = Eigen::Map<Eigen::MatrixXd>(&dist[0], n, 1);
    Eigen::MatrixXd ybarMat = Eigen::Map<Eigen::MatrixXd>(&ybarvec[0], m, 1);
    Eigen::MatrixXd y2dMat = convert_vvd_to_matrix(yarr);
    Eigen::MatrixXd niMat = Eigen::Map<Eigen::MatrixXd>(&nidoub[0], m, 1);
    Eigen::MatrixXd param(m+1, 1);
    param(0) = ybar;
    for (int i = 1; i < m + 1; i++) {
        param(i) = 1000;
    }

    funjacObj funjac(param, niMat, y2dMat, ybarMat);

    // Exponential test
    double stat = 2*n*log(ybar) - 2*sum(vecLogMult(ni, ybarvec));
    cout << "P-value for our likelihood ratio test = ";
    cout << R::pchisq(stat, m-1, false, false);
}