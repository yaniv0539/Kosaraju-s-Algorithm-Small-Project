#include "Graph.h"

Graph::Graph(int i_NumberOfVertices) : m_NumberOfVertices(i_NumberOfVertices),
                                       m_NumberOfEdges(0),
                                       m_VerticesAdjListsVector(i_NumberOfVertices)
{

}

int Graph::GetNumberOfVertices() const
{
    return m_NumberOfVertices;
}

int Graph::GetNumberOfEdges() const
{
    return m_NumberOfEdges;
}

Graph Graph::CreateEmptyGraph(int i_NumberOfVertices)
{
    if (i_NumberOfVertices < 0)
    {
        throw std::invalid_argument("invalid input");
    }
    return Graph(i_NumberOfVertices);
}

bool Graph::IsAdjacent(int i_VertexU, int i_VertexV) const
{
    if (i_VertexU >= m_NumberOfVertices || i_VertexV >= m_NumberOfVertices || i_VertexU < 0 || i_VertexV < 0)
    {
        throw std::out_of_range("invalid input");
    }

    auto it = std::find(m_VerticesAdjListsVector[i_VertexU].begin(), m_VerticesAdjListsVector[i_VertexU].end(), i_VertexV);

    return it != m_VerticesAdjListsVector[i_VertexU].end();
}

const std::list<int>& Graph::GetAdjList(int i_VertexU) const
{
    if (i_VertexU >= m_NumberOfVertices || i_VertexU < 0)
    {
        throw std::out_of_range("invalid input");
    }
    return m_VerticesAdjListsVector[i_VertexU];
}

void Graph::AddEdge(int i_VertexU, int i_VertexV)
{
    if (i_VertexU >= m_NumberOfVertices || i_VertexV >= m_NumberOfVertices || i_VertexU < 0 || i_VertexV < 0)
    {
        throw std::out_of_range("invalid input");
    }

    m_VerticesAdjListsVector[i_VertexU].push_back(i_VertexV);
    m_NumberOfEdges++;
}

void Graph::RemoveEdge(int i_VertexU, int i_VertexV)
{
    if (i_VertexU >= m_NumberOfVertices || i_VertexV >= m_NumberOfVertices || i_VertexU < 0 || i_VertexV < 0)
    {
        throw std::out_of_range("invalid input");
    }

    auto it = std::find(m_VerticesAdjListsVector[i_VertexU].begin(), m_VerticesAdjListsVector[i_VertexU].end(), i_VertexV);

    if (it != m_VerticesAdjListsVector[i_VertexU].end())
    {
        m_VerticesAdjListsVector[i_VertexU].erase(it);
        m_NumberOfEdges--;
    }
}

Graph Graph::CreateGraph(int i_Vertices, const std::vector<std::vector<int>>& i_Edges)
{
    Graph graph = Graph::CreateEmptyGraph(i_Vertices);

    for (const std::vector<int>& edge : i_Edges)
    {
        if (edge.size() != 2)
        {
            throw std::invalid_argument("Each edge must connect exactly two vertices.");
        }
        graph.AddEdge(edge[0], edge[1]);
    }

    return graph;
}

Graph Graph::CreateTransposedGraph() const
{
    Graph transposedGraph = CreateEmptyGraph(m_NumberOfVertices);

    for (int vertexU = 0; vertexU < m_NumberOfVertices; vertexU++)
    {
        for (int vertexV : m_VerticesAdjListsVector[vertexU])
        {
            transposedGraph.AddEdge(vertexV, vertexU);
        }
    }

    return transposedGraph;
}

Graph Graph::CreateSupergraph() const
{
    // Creating the DFS running order for the normal graph
    std::vector<int> graphDFSRunningOrder(m_NumberOfVertices);
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        graphDFSRunningOrder[i] = i;
    }

    // Running DFS on the normal graph with the running order that was created.
    DFS graphDFS = DFS::RunDFS(*this, graphDFSRunningOrder);

    // Extracting the finish list from the DFS run.
    std::vector<int> transposedGraphDFSRunningOrder = graphDFS.GetFinishList();

    // Reverse the finish list.
    std::reverse(transposedGraphDFSRunningOrder.begin(), transposedGraphDFSRunningOrder.end());

    // Creating transposed graph.
    Graph transposedGraph = this->CreateTransposedGraph();

    // Running DFS on the transposed graph with the reversed finish list from the normal graph DFS run.
    DFS transposedGraphDFS = DFS::RunDFS(transposedGraph, transposedGraphDFSRunningOrder);

    // Extracting the vector that includes for each vertex its "Tree Root".
    std::list<std::vector<int>> crossArrowsInTransposedGraphDFS = transposedGraphDFS.GetCrossArrows();

    std::vector<int> verticesRootsInTransposedGraphDFS = transposedGraphDFS.GetVerticesRoots();

    // Creating set that includes only the "Tree Roots".
    std::set<int> uniqueValues(verticesRootsInTransposedGraphDFS.begin(), verticesRootsInTransposedGraphDFS.end());

    // Creating vector that includes only the "Tree Roots".
    std::vector<int> treeRoots(uniqueValues.begin(), uniqueValues.end());

    // Creating empty graph with number of vertices as the number of "Tree Roots".
    Graph supergraph = Graph::CreateEmptyGraph(uniqueValues.size());

    // Creating map so it will map from the "Tree Roots" original vertices to the supergraph vertices.
    std::map<int, int> rootMapping;

    // Creating vector that contains for each "Tree Root" u the last "Tree Root" v that has the common edge (v,u)
    std::vector<int> lastEdgeThatGotIn(uniqueValues.size(), -1);

    for (int i = 0; i < treeRoots.size(); ++i)
    {
        rootMapping[treeRoots[i]] = i;
    }

    // Adding the edges from one tree to another in the supergraph.
    for (const std::vector<int>& edge : crossArrowsInTransposedGraphDFS)
    {
        int from = rootMapping[verticesRootsInTransposedGraphDFS[edge[1]]];
        int to = rootMapping[verticesRootsInTransposedGraphDFS[edge[0]]];
        
        if (lastEdgeThatGotIn[from] != to)
        {
            supergraph.AddEdge(from, to);
            lastEdgeThatGotIn[from] = to;
        }
    }

    return supergraph;
}