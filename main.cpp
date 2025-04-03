#include <iostream>

#include "AdjacencyList.h"

using namespace std;

int main() {

    AdjacencyList web;

    int no_of_lines, power_iterations;
    string url1, url2;
    cin >> no_of_lines >> power_iterations;
    for (int i = 0; i < no_of_lines; i++) {
        cin >> url1;
        cin >> url2;
        web.addEdge(url1, url2);
    }

    web.pageRank(power_iterations);
    //Create a graph object
    // Created_Graph.PageRank(power_iterations);}
}