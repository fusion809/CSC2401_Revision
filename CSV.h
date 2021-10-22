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
