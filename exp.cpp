#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
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

using namespace Rcpp;

// [[Rcpp::export]]
void outPut() {
    CSVData report("ProjectData.csv", 0, 5);
    vector<int> group = report.getGroup();
    vector<double> dist = report.getDist();
    Vars vars(group, dist);
    vector<int> ni = vars.ni;
    int n = vars.n;
    int m = vars.m;
    double ybar = vars.ybar;
    vector<double> ybarvec = vars.ybarvec;
    vector<vector<double>> yarr = vars.yarr2;
    print2DVec(yarr);
    //printVec(ybarvec);
    double stat = 2*n*log(ybar) - 2*sum(vecMult(ni, ybarvec));
    cout << "P-value for our likelihood ratio test = ";
    cout << R::pchisq(stat, m-1, false, false);
}