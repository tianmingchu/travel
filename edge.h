#pragma once

#include <string>

using std::string;

typedef string Vertex;

class Edge {
    public:
        /**
         * @brief Construct a default Edge object
         * 
         */
        Edge();


        /**
         * @brief Construct an Edge object with specified source, destination, and weight
         * 
         * @param s 
         * @param d 
         * @param cases 
         */
        Edge(Vertex s, Vertex d, int cases);


        /**
         * @brief Gets the source vertex of an edge
         * 
         * @return The source vertex
         */
        Vertex getSource() const;


        /**
         * @brief Gets the destination vertex of an edge
         * 
         * @return The destination vertex 
         */
        Vertex getDestination() const;


        /**
         * @brief Gets the number of cases represented by an edge
         * 
         * @return The case count 
         */
        int getCases() const;

    private:
        Vertex source_;
        Vertex destination_;
        int cases_;
};