class Vars {
    public:
        vector<double> ybarvec;
        vector<int> ni;
        double ybar;
        int n;
        int nimax;
        int m;
        vector<vector<double>> yarr2;
        Vars(vector<int>, vector<double>);
};

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

    auto nimaxIn = std::max_element(ni.begin(), ni.end());
    int nimax = *nimaxIn;
    vector<vector<double>> yarr(m, vector<double>(nimax, 0.0));
    for (int i = 0; i < m; i++) {
        ybarvec.push_back(0);
        for (int j = 0 ; j < n; j++) {
            if (group[j] == uniqGroups[i]) {
                ybarvec[i] += dist[j]/ni[i];
            }
        }
    }

    vector<int> counter(n, 0);
    for (int j = 0 ; j < m ; j++) {
        int k = -1;
        for (int i = 0 ; i < n ; i++) {
            if (group[i] == uniqGroups[j]) {
                counter[i] += 1;
                if (k != -1) {
                    counter[i] += counter[k];
                }
                k = i;
            }
        }
    }

    int k = 0;
    for (int i = 0 ; i < m ; i++) {
        for (int j = 0 ; j < ni[i]; j++) {
            yarr[group[k]-1][counter[k]-1] = dist[k];
            k++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        ybar += dist[i] / n;
    }
    yarr2 = yarr;
}