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

// The CSV reading parts of this file were inspired by 
// https://www.delftstack.com/howto/cpp/read-csv-file-in-cpp/
string readFileIntoString(const string& path) {
    auto oss = ostringstream{};
    ifstream inputFile(path);
    if (!inputFile.is_open()) {
        cerr << "Could not open the file: " << path << endl;
    }
    oss << inputFile.rdbuf();
    return oss.str();
}

class CSVData {
    public:
        void setGroup(std::vector<int>);
        void setDist(std::vector<double>);
        vector<int> getGroup();
        vector<double> getDist();
        CSVData(vector<int>, vector<double>);
        CSVData(string, int, int);

    private:
        vector<int> group;
        vector<double> dist;
};

vector<int> CSVData::getGroup() {
    return group;
}

vector<double> CSVData::getDist() {
    return dist;
}

void CSVData::setGroup(vector<int> vec) {
    group = vec;
}

void CSVData::setDist(vector<double> vec) {
    dist = vec;
}

CSVData::CSVData(vector<int> groupIn, vector<double> distIn) {
    group = groupIn;
    dist = distIn;
}

CSVData::CSVData(string filename, int groupCol, int distCol) {
    string fileCont;
    char delimiter = ',';

    fileCont = readFileIntoString(filename);

    istringstream sstream(fileCont);
    vector<int> group;
    vector<double> dist;
    string record;

    int counter = 0;
    while (getline(sstream, record)) {
        istringstream line(record);
        int secCount = 0;
        while (getline(line, record, delimiter)) {
            if (counter > 0 && secCount == groupCol) {
                group.push_back(stoi(record));
            } else if (counter > 0 && secCount == distCol) {
                dist.push_back(stod(record));
            }
            secCount++;
        }

        counter += 1;
    }

    this->setGroup(group);
    this->setDist(dist);
}

using namespace Rcpp;
//using namespace std;

template<typename T>
T vecProd(vector<T> vec) {
    T result = static_cast<T>(1);
    for (int i = 0; i < vec.size(); i++) {
        result *= vec[i];
    }
    return result;
}

double sum(vector<double> vec) {
    double result = 0.0;
    for (int i = 0; i < vec.size(); i++) {
        result += vec[i];
    }
    return result;
}

class Vars {
    public:
        vector<double> ybarvec;
        vector<int> ni;
        double ybar;
        int n;
        int m;
        Vars(vector<int>, vector<double>);
};

template<typename T>
void printVec(vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << " = " << vec[i] << endl;
    }
}
Vars::Vars(vector<int> group, vector<double> dist) {
    vector<int> uniqGroups(group);
    auto last = unique(uniqGroups.begin(), uniqGroups.end());
    uniqGroups.erase(last, uniqGroups.end());
    sort(uniqGroups.begin(), uniqGroups.end());
    last = unique(uniqGroups.begin(), uniqGroups.end());
    uniqGroups.erase(last, uniqGroups.end());
    m = uniqGroups.size();
    n = group.size();
    ybar = 0;

    for (int i = 0 ; i < m; i++) {
        ni.push_back(0);
        for (int j = 0 ; j < n; j++) {
            if (group[j] == uniqGroups[i]) {
                ni[i] += 1;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        ybarvec.push_back(0);
        for (int j = 0 ; j < n; j++) {
            if (group[j] == uniqGroups[i]) {
                ybarvec[i] += dist[j]/ni[i];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        ybar += dist[i] / n;
    }
}

vector<double> vecMult(vector<int> ni, vector<double> ybarvec) {
    int m = ni.size();
    vector<double> result(m, 0);
    for (int i = 0 ; i < m ; i++) {
        result[i] = ni[i] * log(ybarvec[i]);
    }
    return result;
}

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
    double stat = 2*n*log(ybar) - 2*sum(vecMult(ni, ybarvec));
    cout << "P-value for our likelihood ratio test = ";
    cout << R::pchisq(stat, m-1, false, false);
}