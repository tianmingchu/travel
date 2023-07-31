#include "graph.h"
#include "edge.h"
#include <map>
#include <queue>
#include <algorithm>

void Graph::BFS(Vertex v) {
    unordered_map<Vertex, bool> visited;
    vector<Vertex> vertices = this->getVertices();
    for (auto i = vertices.begin(); i != vertices.end(); ++i) {  // keep track of vertices visited
        visited.insert(pair<Vertex, bool>(*i, false));
    }

    std::list<Vertex> queue;
    visited[v] = true;
    queue.push_back(v);
    while (!queue.empty()) {
        v = queue.front();
        cout << v << endl;
        queue.pop_front();
        unordered_map<Vertex, Edge> adjacentVertices = adjacency_list[v];
        for (auto i = adjacentVertices.begin(); i != adjacentVertices.end(); ++i) {
            if (!visited[i->first]) {   // add all unvisited adjacent vertices to queue
                visited[i->first] = true;
                queue.push_back(i->first);
            }
        }
    }
}

void Graph::insertVertex(Vertex v) {
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}

void Graph::insertEdge(Vertex v1, Vertex v2, int cases) {
    if(adjacency_list.find(v1)!= adjacency_list.end() 
    && adjacency_list[v1].find(v2)!= adjacency_list[v1].end())
    {
        //edge already exit
        return;
    }

    if(adjacency_list.find(v1)==adjacency_list.end())
    {
        adjacency_list[v1] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    Edge edge (v1, v2, cases);
    adjacency_list[v1][v2] = edge;
    
    if(adjacency_list.find(v2)== adjacency_list.end()) {
        adjacency_list[v2] = unordered_map<Vertex, Edge>();
    }
    adjacency_list[v2][v1] = Edge(v1, v2, cases);
}

vector<Vertex> Graph::incidentVertices(Vertex v) {
    auto lookup = adjacency_list.find(v);
    
    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[v];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }

}

vector<Vertex> Graph::getVertices() {
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return !(adjacency_list.find(v) == adjacency_list.end());
}

int Graph::getCasesByEdge(Vertex v1, Vertex v2) {
    return adjacency_list[v1][v2].getCases();
}

map<Vertex, vector<Vertex>> Graph::shortestPaths(Vertex v1) {
    
    std::map<Vertex,int> d;
    std::map<Vertex, Vertex> p;
    for (Vertex v : getVertices()) {
        d[v] = INT_MAX;
        p[v] = "NONE";
    }
    d[v1] = 0;
    std::priority_queue<intVertPair> q;
    q.push({0, v1});

    while (!q.empty()) {
        Vertex v = q.top().second;
        q.pop();

        for (Vertex v2 : incidentVertices(v)) {
            int cases = getCasesByEdge(v, v2);

            if (d[v2] > d[v] + cases) {
                d[v2] = d[v] + cases;
                p[v2] = v;
                q.push({(-1 * d[v2]), v2});
            }
        }
    }
    
    map<Vertex, vector<Vertex>> paths;
    for (Vertex v : getVertices()) {
        Vertex current = p[v];
        vector<Vertex> path;
        path.push_back(v);
        while(current != "NONE") {
            path.push_back(current);
            current = p[current];
        }
        paths.insert({v, path});
    }
    return paths;
}

std::string Graph::landmarkPath(Vertex source, Vertex dest, Vertex landmark) {
    map<Vertex, vector<Vertex>> paths= shortestPaths(landmark);
    vector<Vertex> sourceToLandmark = paths[source];
    vector<Vertex> landmarkToDest = paths[dest];
    std::reverse(landmarkToDest.begin(), landmarkToDest.end()); 
    std::string path = "Path: ";
    for (Vertex v : sourceToLandmark) {
        path += v;
        path += "->";
    }
    for (size_t i = 1; i < landmarkToDest.size() - 1; i++) {
        path += landmarkToDest[i];
        path += "->";
    }
    path += landmarkToDest[landmarkToDest.size() - 1];
    return path;
}

void Graph::printGraph() {
    for (auto i = adjacency_list.begin(); i != adjacency_list.end(); ++i) {
        cout << i->first << endl;
        for (auto it = i->second.begin(); it != i->second.end(); ++it) {
            std::stringstream ss;
            ss << it->first;
            string vertexColumn = "        => " + ss.str();
            vertexColumn += " ";
            cout << std::left << std::setw(30) << vertexColumn;
            cout << std::left << "case rate per 100k: " << it->second.getCases() << endl;
        }
        cout << endl;
    }
}