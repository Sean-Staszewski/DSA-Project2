#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>

// change if you choose to use a different header name
#include "AdjacencyList.h"
#include <unordered_set>

#include "catch2/matchers/catch_matchers_container_properties.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

using namespace std;

TEST_CASE("Input Parsing") {
  string input = R"(9 10
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com
amazon.com google.com
amazon.com facebook.com)";

  AdjacencyList web;

  istringstream s(input);

  string line;
  getline(s, line);

  int no_of_lines, power_iterations;
  istringstream(line) >> no_of_lines >> power_iterations;

  string url1, url2;
  for (int i = 0; i < no_of_lines; i++) {
    getline(s, line);
    istringstream(line) >> url1 >> url2;
    web.addEdge(url1, url2);
  }

  unordered_map<string, int> pages = {{"google.com", 0}, {"facebook.com", 3}, {"ufl.edu", 4}, {"maps.com", 2}, {"gmail.com", 1}, {"amazon.com", 5}};

  REQUIRE(web.getPages() == pages);
}

TEST_CASE("Create Web/Graph") {
  string input = R"(10 2
google.com facebook.com
google.com ufl.edu
google.com maps.com
google.com gmail.com
facebook.com ufl.edu
facebook.com maps.com
facebook.com gmail.com
ufl.edu maps.com
ufl.edu gmail.com
maps.com gmail.com)";

  AdjacencyList web;

  istringstream s(input);

  string line;
  getline(s, line);

  int no_of_lines, power_iterations;
  istringstream(line) >> no_of_lines >> power_iterations;

  string url1, url2;
  for (int i = 0; i < no_of_lines; i++) {
    getline(s, line);
    istringstream(line) >> url1 >> url2;
    web.addEdge(url1, url2);
  }

  vector<vector<int>> expectedList = {{1,2,3,4}, {2,3,4}, {3,4}, {4}, {}};

  REQUIRE(web.getOutList() == expectedList);
}

TEST_CASE("Find Outdegrees of nodes") {
  string input = R"(10 2
google.com gmail.com
google.com maps.com
google.com facebook.com
facebook.com gmail.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com google.com
gmail.com maps.com)";

  AdjacencyList web;

  istringstream s(input);

  string line;
  getline(s, line);

  int no_of_lines, power_iterations;
  istringstream(line) >> no_of_lines >> power_iterations;

  string url1, url2;
  for (int i = 0; i < no_of_lines; i++) {
    getline(s, line);
    istringstream(line) >> url1 >> url2;
    web.addEdge(url1, url2);
  }

  REQUIRE(web.getOutDegree("google.com") == 3);
  REQUIRE(web.getOutDegree("facebook.com") == 2);
  REQUIRE(web.getOutDegree("ufl.edu") == 2);
  REQUIRE(web.getOutDegree("maps.com") == 2);
  REQUIRE(web.getOutDegree("gmail.com") == 1);
}

TEST_CASE("Power Iteration") {
  vector<vector<int>> inList = {{1, 2}, {2, 3}, {3,4}, {4}, {}};
  vector<vector<int>> outList = {{}, {0}, {0,1},{1,2},{2,3}};

  int p = 1;
  REQUIRE_THAT(powerIterator(inList, outList, p), Catch::Matchers::Approx(vector<double>{0.2, 0.2, 0.2, 0.2, 0.2}));

  p = 2;
  REQUIRE_THAT(powerIterator(inList, outList, p), Catch::Matchers::Approx(vector<double>{0.0, 0.1, 0.2, 0.2, 0.3}));

  p = 3;
  REQUIRE_THAT(powerIterator(inList,outList, p), Catch::Matchers::Approx(vector<double>{0.0, 0.05, 0.2, 0.2, 0.45}));

  p = 4;
  REQUIRE_THAT(powerIterator(inList, outList, p), Catch::Matchers::Approx(vector<double>{0.0, 0.025, 0.2, 0.2, 0.675}));
}

TEST_CASE("Example PageRank Output Test") {
  // the following is a "raw string" - you can write the exact input (without
  //   any indentation!) and it should work as expected
  string input = R"(7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com)";

  string expectedOutput = R"(facebook.com 0.20
gmail.com 0.20
google.com 0.10
maps.com 0.30
ufl.edu 0.20
)";

  string actualOutput;

  // somehow pass your input into your AdjacencyList and parse it to call the
  // correct functions, for example:
  AdjacencyList web;

  istringstream s(input);

  string line;
  getline(s, line);

  int no_of_lines, power_iterations;
  istringstream(line) >> no_of_lines >> power_iterations;

  string url1, url2;
  for (int i = 0; i < no_of_lines; i++) {
    getline(s, line);
    istringstream(line) >> url1 >> url2;
    web.addEdge(url1, url2);
  }

  REQUIRE(web.pageRank(power_iterations) == expectedOutput);
}

//Name: Sean Staszewski
//UFID: 22169901
