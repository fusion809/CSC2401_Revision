template<typename T>
void printVec(vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << " = " << vec[i] << endl;
    }
}

void print2DVec(vector<vector<double>> vec2D) {
    for (int i = 0; i < vec2D.size(); i++) {
        cout << "Row " << i << " = ";
        printVec(vec2D[i]);
    }
}

vector<double> vecLogMult(vector<int> ni, vector<double> ybarvec) {
    int m = ni.size();
    vector<double> result(m, 0);
    for (int i = 0 ; i < m ; i++) {
        result[i] = ni[i] * log(ybarvec[i]);
    }
    return result;
}

vector<double> vecMult(vector<double> a, vector<double> b) {
    vector<double> result(a.size(), 0);
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] * b[i];
    }
    return result;
}

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

int specSum(vector<int> vec, int begin, int end) {
    int result = 0;
    if (end > vec.size()) {
        cout << "Error: end is greater than vec.size()" << endl;
    }
    for (int i = begin; i < end; i++) {
        result += vec[i];
    }
    return result;
}

void printVecPair(vector<std::pair<int, int>> vecPair) {
    for (int i = 0 ; i < vecPair.size(); i++) {
        cout << "Group = " << vecPair[i].first << ", ";
        cout << "Counter = " << vecPair[i].second << endl;
    }
}

vector<vector<double>> vec2D1DSub(const vector<vector<double>> vec2D, const vector<double> vec1D) {
    vector<vector<double>> result = vec2D;
    for (int i = 0 ; i < vec2D.size(); i++) {
        for (int j = 0 ; j < vec2D[0].size(); j++) {
            result[i][j] -= vec1D[j];
        }
    }
    return result;
}

vector<vector<double>> vec2DScalSub(const vector<vector<double>> vec2D, const double scal) {
    vector<vector<double>> result = vec2D;
    for (int i = 0 ; i < vec2D.size(); i++) {
        for (int j = 0 ; j < vec2D[0].size(); j++) {
            result[i][j] -= scal;
        }
    }
    return result;
}

vector<vector<double>> vec2DSq(const vector<vector<double>> vec2D) {
    vector<vector<double>> result = vec2D;
    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[0].size(); j++) {
            result[i][j] = vec2D[i][j] * vec2D[i][j];
        }
    }
    return result;
}

vector<double> vecColSum(vector<vector<double>> vec2D) {
    vector<double> result(vec2D.size(), 0);
    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[0].size(); j++) {
            result[i] += vec2D[i][j];
        }
    }
    return result;
}

vector<double> power(vector<double> vec, vector<double> exp) {
    vector<double> result(vec.size(), 0);
    for (int i = 0 ; i < vec.size(); i++) {
        result[i] = pow(vec[i], exp[i]);
    }
    return result;
}

vector<double> scalMult(vector<int> vec, double scalar) {
    vector<double> result(vec.size(), 0);
    for (int i = 0 ; i < vec.size(); i++) {
        result[i] = scalar * vec[i];
    }
    return result;
}

// Copied from https://stackoverflow.com/a/69170736/1876983
Eigen::MatrixXd convert_vvd_to_matrix(vector<vector<double> > vvd) {

    std::size_t n_rows = vvd.size();
    std::size_t n_cols = vvd.at(0).size();

    Eigen::MatrixXd result(n_rows, n_cols);
    result.row(0) = Eigen::VectorXd::Map(&vvd[0][0], n_cols);

    // Add each vector row to the MatrixXd. 
    for (std::size_t i = 1; i < n_rows; i++) {

        // Make sure that every row of vvd has the same size.
        if (n_cols != vvd.at(i).size()) {
            char buffer[200];
            snprintf(buffer, 200, 
                        "vvd[%ld] size (%ld) does not match vvd[0] size (%ld)",
                        i, vvd.at(i).size(), n_cols);
            string err_mesg(buffer);
            throw std::invalid_argument(err_mesg);
        }

        result.row(i) = Eigen::VectorXd::Map(&vvd[i][0], n_cols);
    }

    return result;
}

vector<double> convertToDouble(vector<int> vec) {
    vector<double> result(vec.size(), 0);
    for (int i = 0 ; i < vec.size(); i++) {
        result[i] = static_cast<double>(vec[i]);
    }
    return result;
}