#pragma once

#include <string>
#include <list>
#include <vector>
#include <stdexcept>
#include "Graph.h"

class Graph;

/**
 * @class DFS
 * @brief Implements Depth-First Search on a graph.
 */
class DFS
{
private:
    const Graph& m_Graph;
    std::vector<std::string> m_VerticesColors;
    std::vector<int> m_FinishList;
    std::vector<int> m_VerticesRoots;
    std::list<std::vector<int>> m_CrossArrows;

public:
    /**
     * @brief Runs DFS on the graph with the given running order.
     * @param i_Graph The graph to run DFS on.
     * @param runningOrder The order in which to visit the vertices.
     * @return DFS The DFS result.
     */
    static DFS RunDFS(const Graph& i_Graph, const std::vector<int>& runningOrder);

    /**
     * @brief Gets the finish list of the DFS run.
     * @return const std::vector<int>& The finish list.
     */
    const std::vector<int>& GetFinishList() const;

    /**
     * @brief Gets the roots of the vertices from the DFS run.
     * @return const std::vector<int>& The vertices roots.
     */
    const std::vector<int>& GetVerticesRoots() const;

    /**
     * @brief Gets the cross arrows from the DFS run.
     * @return const std::list<std::vector<int>>& The cross arrows.
     */
    const std::list<std::vector<int>>& GetCrossArrows() const;

private:
    DFS(const Graph& i_Graph);

    /**
     * @brief Visits a vertex in the DFS run.
     * @param i_VertexU The vertex to visit.
     * @param i_DFS The DFS object.
     */
    static void Visit(int i_VertexU, DFS& i_DFS);
};