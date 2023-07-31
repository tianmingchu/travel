#include "../catch/catch.hpp"
#include "../graph.h"

TEST_CASE("Graph_insertVertex()") {
    Graph g;
    Vertex v = "illinois";
    g.insertVertex(v);
    REQUIRE(g.getVertices().size() == 1);
    REQUIRE(g.getVertices()[0] == "illinois");
    Vertex v1 = "wisconsin";
    Vertex v2 = "minnesota";
    Vertex v3 = "north dakota";
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v3);
    REQUIRE(g.getVertices().size() == 4);
    REQUIRE(g.getVertices()[0] == "minnesota");
    REQUIRE(g.getVertices()[1] == "north dakota");
    REQUIRE(g.getVertices()[2] == "wisconsin");
}

TEST_CASE("Graph_test_edges") {
    Graph g;
    Vertex v1 = "illinois";
    Vertex v2 = "wisconsin";
    g.insertVertex(v1);
    g.insertVertex(v2);
    REQUIRE(g.getVertices().size() == 2);
    REQUIRE(g.incidentVertices(v1).size() == 0);
    REQUIRE(g.incidentVertices(v2).size() == 0);
    g.insertEdge(v1, v2, 50000);
    REQUIRE(g.getCasesByEdge(v1, v2) == 50000);
    REQUIRE(g.incidentVertices(v1).size() == 1);
    REQUIRE(g.incidentVertices(v2).size() == 1);
    Vertex v3 = "minnesota";
    g.insertVertex(v3);
    REQUIRE(g.getVertices().size() == 3);
    g.insertEdge(v1, v3, 10000);
    REQUIRE(g.getCasesByEdge(v1, v3) == 10000);
    REQUIRE(g.incidentVertices(v1).size() == 2);
    REQUIRE(g.incidentVertices(v3).size() == 1);
}

TEST_CASE("Graph_shortest_path") {
    Graph g;
    Vertex v1 = "illinois";
    Vertex v2 = "wisconsin";
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertEdge(v1, v2, 50);
    map<Vertex, vector<Vertex>> paths = g.shortestPaths(v2);
    REQUIRE(paths[v1][0] == "illinois");
    REQUIRE(paths[v1][1] == "wisconsin");
    Vertex v3 = "minnesota";
    g.insertEdge(v2, v3, 100);
    g.insertEdge(v1, v3, 100);
    paths = g.shortestPaths(v3);
    REQUIRE(paths[v1][0] == "illinois");
    REQUIRE(paths[v1][1] == "minnesota");
}

TEST_CASE("Graph_landmark_path") {
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
    REQUIRE(g.landmarkPath(v1, v5, v3) == "Path: illinois->wisconsin->minnesota->north dakota->south dakota");
    g.insertEdge(v2, v5, 400);
    g.insertEdge(v1, v5, 100);
    REQUIRE(g.landmarkPath(v1, v5, v3) == "Path: illinois->south dakota->north dakota->minnesota->north dakota->south dakota");
    g.insertEdge(v1, v3, 10);
    REQUIRE(g.landmarkPath(v1, v5, v3) == "Path: illinois->minnesota->north dakota->south dakota");
}