#pragma once

#include <list>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "DFS.h"

/**
 * @class Graph
 * @brief Represents a directed graph using adjacency lists.
 */
class Graph
{
    int m_NumberOfVertices;
    int m_NumberOfEdges;
    std::vector<std::list<int>> m_VerticesAdjListsVector;

public:
    /**
     * @brief Gets the number of vertices in the graph.
     * @return int The number of vertices.
     */
    int GetNumberOfVertices() const;

    /**
     * @brief Gets the number of edges in the graph.
     * @return int The number of edges.
     */
    int GetNumberOfEdges() const;

    /**
     * @brief Creates an empty graph with the specified number of vertices.
     * @param i_NumberOfVertices The number of vertices.
     * @return Graph The empty graph.
     * @throws std::invalid_argument If the number of vertices is negative.
     */
    static Graph CreateEmptyGraph(int i_NumberOfVertices);

    /**
     * @brief Checks if two vertices are adjacent.
     * @param i_VertexU The first vertex.
     * @param i_VertexV The second vertex.
     * @return bool True if the vertices are adjacent, false otherwise.
     * @throws std::out_of_range If the vertex indices are out of range.
     */
    bool IsAdjacent(int i_VertexU, int i_VertexV) const;

    /**
     * @brief Gets the adjacency list of a vertex.
     * @param i_VertexU The vertex.
     * @return const std::list<int>& The adjacency list.
     * @throws std::out_of_range If the vertex index is out of range.
     */
    const std::list<int>& GetAdjList(int i_VertexU) const;

    /**
         * @brief Adds an edge between two vertices.
         * @param i_VertexU The first vertex.
         * @param i_VertexV The second vertex.
         * @throws std::out_of_range If the vertex indices are out of range.
         */
    void AddEdge(int i_VertexU, int i_VertexV);

    /**
     * @brief Removes an edge between two vertices.
     * @param i_VertexU The first vertex.
     * @param i_VertexV The second vertex.
     * @throws std::out_of_range If the vertex indices are out of range.
     */
    void RemoveEdge(int i_VertexU, int i_VertexV);

    /**
     * @brief Creates a graph with the specified vertices and edges.
     * @param i_Vertices The number of vertices.
     * @param i_Edges The edges of the graph.
     * @return Graph The created graph.
     * @throws std::invalid_argument If the edge list is invalid.
     */
    static Graph CreateGraph(int i_Vertices, const std::vector<std::vector<int>>& i_Edges);

    /**
     * @brief Creates the transposed graph.
     * @return Graph The transposed graph.
     */
    Graph CreateTransposedGraph() const;

    /**
     * @brief Creates the supergraph.
     * @return Graph The supergraph.
     */
    Graph CreateSupergraph() const;

private:
    /**
     * @brief Constructs a graph with the specified number of vertices.
     * @param i_NumberOfVertices The number of vertices.
     */
    Graph(int i_NumberOfVertices);
};