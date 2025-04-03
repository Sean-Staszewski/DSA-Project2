#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include "AdjacencyList.h"

using namespace std;

AdjacencyList::AdjacencyList() {

}


void AdjacencyList::addEdge(const string url1, const string url2) {

    if (pages.count(url1) == 0) {
        pages[url1] = pages.size();
        list.resize(pages[url1] + 1);
        list[pages[url1]] = {};
    }
    if (pages.count(url2) == 0) {
        pages[url2] = pages.size();
        list.resize(pages[url2] + 1);
        list[pages[url2]] = {};
    }
    list[pages[url1]].push_back(pages[url2]);
}

// prints the PageRank of all pages after p powerIterations in ascending
// alphabetical order of webpages and rounding rank to two decimal places
string AdjacencyList::pageRank(int &p){
    // optionally, store your output in a string/stringstream and then return it from this function after printing so that it is easier to test with Catch
    string result;

    vector<double> ranks = powerIterator(list, p);

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
    return list[pages[url]].size();
}

int AdjacencyList::pageCount() {
    return pages.size();
}

vector<double> powerIterator(const vector<vector<int>> &list, int &p) {

    if (p == 1) {
        vector<double>output(list.size(), 1/(double)list.size());
        return output;
    }

    vector<double> vec = powerIterator(list, --p);
    return dot(list, vec);
}

vector<double> dot(const vector<vector<int> > &list, vector<double> &vector) {

    for (int i = 0; i < list.size(); i++) {

        double weightSum = 0;

        for (int j = 0; j < list.size(); j++) {

            for (int k = 0; k < list[j].size(); k++) {

                if (list[j][k] == i) {
                    weightSum += vector[i]/list[j].size();
                    break;
                }
            }
        }

        vector[i] = weightSum;
    }

    return vector;
}


