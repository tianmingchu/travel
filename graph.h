#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "edge.h"

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::to_string;
using std::make_pair;
using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::map;

typedef pair<int, Vertex> intVertPair;

//Uses code from graph.h in lab_ml
class Graph {
    public: 
        /**
         * @brief Prints out all states via BFS traversal
         * 
         * @param v The vertex to start with
         */
        void BFS(Vertex v);

        /**
         * @brief Inserts a vertex representative of a state in the US into the graph
         * 
         * @param v The vertex to insert
         */
        void insertVertex(Vertex v);

        /**
         * @brief Given two vertices and a weight, inserts an edge into the graph representing a path between two states and the number of cases representative of the path
         * 
         * @param v1 The starting vertex of the edge
         * @param v2 The destination vertex of the edge
         * @param cases The number of cases of the edge
         */
        void insertEdge(Vertex v1, Vertex v2, int cases);

        /**
         * @brief Given a vertex, returns all vertices adjacent to the specified vertex in a graph
         * 
         * @param v The vertex to return neighbors from
         * @return vector<Vertex> A vector of adjacent vertices
         */
        vector<Vertex> incidentVertices(Vertex v);

        /**
         * @brief Returns a vector containing all vertices in the graph
         * 
         * @return vector<Vertex> 
         */
        vector<Vertex> getVertices();

        /**
         * @brief Returns whether the specified vertex exists in the graph
         * 
         * @param v The vertex to check
         * @return true 
         * @return false 
         */
        bool vertexExists(Vertex v) const;


        /**
         * @brief Returns a map containing source destination as the key and a vector containing the ordered vertices of the path to the destination as the value.
         * 
         * @param v1 Vertex representing the desired destination of the path
         * @return map<Vertex, vector<Vertex>> 
         */
        map<Vertex, vector<Vertex>> shortestPaths(Vertex v1);


        /**
         * @brief Given a source, destination and landmark, returns a formatted path that starts at the source, ends at the destination, and includes the landmark vertex
         * 
         * @param source Vertex representing the desired starting point of the path
         * @param dest Vertex representing the desired destination of the path
         * @param landmark Vertex representing a point that must be included in the path
         * @return string 
         */
         
        string landmarkPath(Vertex source, Vertex dest, Vertex landmark);


        /**
         * @brief Returns case rate of the second vertex in the edge
         * 
         * @param v1 The starting point of the edge
         * @param v2 The ending point of the edge
         * @return int 
         */
        int getCasesByEdge(Vertex v1, Vertex v2);


        /**
         * @brief Prints all vertices, their neighbors, and edges
         * 
         */
        void printGraph();

    private:
        mutable unordered_map<Vertex, unordered_map<Vertex, Edge>> adjacency_list;
};