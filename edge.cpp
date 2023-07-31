#include "edge.h"

typedef string Vertex;

Edge::Edge() : source_("source"), destination_("dest"), cases_(0) {}

Edge::Edge(Vertex s, Vertex d, int cases) : source_(s), destination_(d), cases_(cases) {}


Vertex Edge::getSource() const {
    return source_;
}

Vertex Edge::getDestination() const {
    return destination_;
}

int Edge::getCases() const {
    return cases_;
}