#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include "AdjacencyList.h"

using namespace std;

vector<vector<int> > AdjacencyList::getInList() {
    return inList;
}

vector<vector<int> > AdjacencyList::getOutList() {
    return outList;
}

unordered_map<string, int> AdjacencyList::getPages() {
    return pages;
}

AdjacencyList::AdjacencyList() {}

void AdjacencyList::addEdge(const string url1, const string url2) {

    if (pages.count(url1) == 0) {
        pages[url1] = pages.size();
        outList.push_back({});
        inList.push_back({});
    }
    if (pages.count(url2) == 0) {
        pages[url2] = pages.size();
        outList.push_back({});
        inList.push_back({});
    }
    outList[pages[url1]].push_back(pages[url2]);
    inList[pages[url2]].push_back(pages[url1]);
}

// prints the PageRank of all pages after p powerIterations in ascending
// alphabetical order of webpages and rounding rank to two decimal places
string AdjacencyList::pageRank(int &p){
    // optionally, store your output in a string/stringstream and then return it from this function after printing so that it is easier to test with Catch
    string result;

    vector<double> ranks = powerIterator(outList, inList, p);

    map<string, int> sorted;

    for (auto page : pages) {
        sorted.insert(page);
    }

    for (auto page : sorted) {
        string rounded = to_string(round(100*ranks[page.second])/100);

        rounded = rounded.substr(0,4);

        result += page.first + " " + rounded + "\n";
    }


    cout << result;
    return result;
}

int AdjacencyList::getOutDegree(const string &url) {
    return outList[pages[url]].size();
}

int AdjacencyList::getInDegree(const string &url) {
    return inList[pages[url]].size();
}

vector<double> powerIterator(const vector<vector<int>> &outlist, const vector<vector<int>> &inlist, int &p) {

    if (p == 1) {
        vector<double>output(outlist.size(), 1/(double)outlist.size());
        return output;
    }

    vector<double> vec = powerIterator(outlist, inlist, --p);
    return dot(outlist, inlist, vec);
}

vector<double> dot(const vector<vector<int>> &outList, const vector<vector<int>> &inList, vector<double> &vec) {

    vector<double> retVec(outList.size());

    for (int i = 0; i < outList.size(); i++) {
        for (int j = 0; j < inList[i].size(); j++) {
            retVec[i] += vec[i] / outList[inList[i][j]].size();
        }
    }

    return retVec;
}


