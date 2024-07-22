#include "DFS.h"

DFS::DFS(const Graph& i_Graph) : m_Graph(i_Graph),
                                 m_VerticesColors(i_Graph.GetNumberOfVertices(), "White"),
                                 m_FinishList(),
                                 m_VerticesRoots(i_Graph.GetNumberOfVertices())
{

}

DFS DFS::RunDFS(const Graph& i_Graph, const std::vector<int>& runningOrder)
{
    DFS dfs(i_Graph);

    for (int vertexU : runningOrder)
    {
        if (dfs.m_VerticesColors[vertexU] == "White")
        {
            dfs.m_VerticesRoots[vertexU] = vertexU;
            Visit(vertexU, dfs);
        }
    }

    return dfs;
}

const std::vector<int>& DFS::GetFinishList() const
{
    return m_FinishList;
}

const std::vector<int>& DFS::GetVerticesRoots() const
{
    return m_VerticesRoots;
}

const std::list<std::vector<int>>& DFS::GetCrossArrows() const
{
    return m_CrossArrows;
}

void DFS::Visit(int i_VertexU, DFS& i_DFS)
{
    i_DFS.m_VerticesColors[i_VertexU] = "Gray";

    for (int vertexV : i_DFS.m_Graph.GetAdjList(i_VertexU))
    {
        if (i_DFS.m_VerticesColors[vertexV] == "White")
        {
            i_DFS.m_VerticesRoots[vertexV] = i_DFS.m_VerticesRoots[i_VertexU];
            Visit(vertexV, i_DFS);
        }

        else if (i_DFS.m_VerticesColors[vertexV] == "Black" && i_DFS.m_VerticesRoots[i_VertexU] != i_DFS.m_VerticesRoots[vertexV])
            i_DFS.m_CrossArrows.push_back({ i_VertexU, vertexV });
    }

    i_DFS.m_VerticesColors[i_VertexU] = "Black";
    i_DFS.m_FinishList.push_back(i_VertexU);
}