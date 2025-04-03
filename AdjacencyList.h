#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class AdjacencyList {
private:
    //Think about what member variables you need to initialize


public:

    unordered_map<string, int> pages;
    vector<vector<int>> list;

    unordered_map<string, int> getPages() {
        return pages;
    }

    vector<vector<int>> getList() {
        return list;
    }

    AdjacencyList();

    void addEdge(const string url1, const string url2);

    string pageRank(int &p);
    int getOutDegree(const string &url);
    int pageCount();

};


vector<double> powerIterator(const vector<vector<int>> &list, int &p);
vector<double> dot(const vector<vector<int>> &list, vector<double> &vector);


// This class and method are optional.