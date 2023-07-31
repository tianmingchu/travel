#include "graph.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <map>
#include <list>

using namespace std;

/**
 * @brief Checks if a string is one of the 50 states
 * 
 * @param s The string to check for
 * @return true 
 * @return false 
 */
bool isState(string s) {
    string states[50] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
                        "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
                        "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
                        "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", 
                        "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin" , "Wyoming"};
    for (int i = 0; i < 50; i++) {
        if (states[i] == s)
            return true;
    }
    return false;
}

/**
 * @brief Returns a map of (state, case rate) for each of the 50 states according to the .csv file
 * 
 * @param f The filename of the dataset
 * @return map<string, int> 
 */
map<string, int> readCovidData(string f) {
    ifstream file(f);
    map<string, int> data;
    int colCount;
    int cases;
    string line, cell, state;

    while (getline(file, line)) {
        stringstream lineStream(line);
        colCount = 0;

        while (getline(lineStream, cell, ',')) {    // separate columns by commas
            colCount++;
            if (colCount == 1) {
                if (!isState(cell)) // if not a state move to next line
                    break;
                state = cell;
            }
            if (colCount == 12) {    // column 12 is case rate per 10000 in the past week
                cases = stod(cell);
                data.insert(pair<string, int>(state, cases));   // insert data into map
                break;
            }
        }
    }
    return data;
}

/**
 * @brief Returns graph created by .csv file
 * 
 * @param f The filename of the dataset
 * @return Graph 
 */
Graph createGraph(string f) {
    Graph g;
    map<string, int> data = readCovidData("data/" + f);
    for (map<string, int>::iterator i = data.begin(); i != data.end(); ++i) {
        g.insertVertex(Vertex(i->first));
    }
    
    ifstream file("data/neighboringStates.csv");
    int colCount;
    string line, cell, state;

    while (getline(file, line)) {
        stringstream lineStream(line);
        colCount = 0;

        while (getline(lineStream, cell, ',')) {    // separate columns by commas
            colCount++;
            if (colCount == 1) {    // origin state
                state = cell;
            } else {    // neighboring state
                g.insertEdge(state, cell, data[state] + data[cell]);
            }
        }
    }
    return g;
}