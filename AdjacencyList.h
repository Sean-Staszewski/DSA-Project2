#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class AdjacencyList {
private:
    //Think about what member variables you need to initialize
    unordered_map<string, int> pages;
    vector<vector<int>> outList;
    vector<vector<int>> inList;

public:

    unordered_map<string, int> getPages();

    vector<vector<int>> getOutList();

    vector<vector<int>> getInList();

    AdjacencyList();

    void addEdge(const string url1, const string url2);

    string pageRank(int &p);
    int getOutDegree(const string &url);
    int getInDegree(const string &url);

};


vector<double> powerIterator(const vector<vector<int>> &outlist, const vector<vector<int>> &inlist, int &p);
vector<double> dot(const vector<vector<int>> &outlist, const vector<vector<int>> &inlist, vector<double> &vec);


// This class and method are optional.
