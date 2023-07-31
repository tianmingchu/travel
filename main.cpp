#include "graph.h"
#include "readFromFile.cpp"

int main() {
    cout << "Drop the .csv file into the 'data' folder then enter its file name: ";
    string s, state, departing, destination;
    getline(cin, s);
    Graph g;
    if (s.compare(s.size() - 4, 4, ".csv") == 0) {
        g = createGraph(s);   // create weighted graph based on data
    } else {
        g = createGraph(s + ".csv");
    }
    do {
        cout << "\nPress 1 for BFS traversal from a state, 2 for landmark path, 3 for printed graph, 4 to exit." << endl;
        getline(cin, s);
        if (s == "1") {
            do {
                cout << "\nWhich state would you like to traverse from? ";
                getline(cin, state);
                if (isState(state)) {
                    g.BFS(state);
                    break;
                } else {
                    cout << "\nSorry, invalid state";
                }
            } while (1);
        } else if (s == "2") {
            do {
                cout << "\nWhat is your departing state? ";
                getline(cin, departing);
                if (isState(departing)) {
                    break;
                } else {
                    cout << "\nSorry, invalid state";
                }
            } while (1);
            do {
                cout << "\nWhich state is your destination? ";
                getline(cin, destination);
                if (isState(destination)) {
                    break;
                } else {
                    cout << "\nSorry, invalid state";
                }
            } while (1);
            do {
                cout << "\nWhat state would you like to visit along the way? ";
                getline(cin, state);
                if (isState(state)) {
                    break;
                } else {
                    cout << "\nSorry, invalid state";
                }
            } while (1);
            cout << "Safest path to " + destination + " starting at " + departing + " and visiting " + state + " along the way: " << endl;
            cout << g.landmarkPath(departing, destination, state) << endl;
        } else if (s == "3") {
            g.printGraph();
        } else if (s == "4") {
            break;
        } else {
            cout << "\nInvalid option";
        }
    } while (1);

    
    //nayonika's stuff
    /*
    Graph g;
    Vertex v1 = "illinois";
    Vertex v2 = "wisconsin";
    Vertex v3 = "minnesota";
    Vertex v4 = "north dakota";
    Vertex v5 = "south dakota";
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v3);
    g.insertVertex(v4);
    g.insertVertex(v5);
    g.insertEdge(v1, v2, 300);
    g.insertEdge(v2, v3, 200);
    g.insertEdge(v3, v4, 50);
    g.insertEdge(v4, v5, 50);
    g.insertEdge(v2, v5, 400);
    g.insertEdge(v1, v5, 100);
    std::cout << g.landmarkPath(v1, v5, v3) << std::endl;
    */
}