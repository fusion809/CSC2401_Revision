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

vector<double> vecMult(vector<int> ni, vector<double> ybarvec) {
    int m = ni.size();
    vector<double> result(m, 0);
    for (int i = 0 ; i < m ; i++) {
        result[i] = ni[i] * log(ybarvec[i]);
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