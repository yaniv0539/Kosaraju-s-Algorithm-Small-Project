#include "Main.h"

int main()
{
    try
    {
        int vertices = GetVertices();
        std::vector<std::vector<int>> edges = GetEdges();
        Graph graph = Graph::CreateGraph(vertices, edges);
        Graph supergraph = graph.CreateSupergraph();

        std::cout << "Number of vertices in the supergraph: " << supergraph.GetNumberOfVertices() << std::endl
            << "Number of edges in the supergraph: " << supergraph.GetNumberOfEdges() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Gets the number of vertices from the user.
 *
 * @return int The number of vertices.
 * @throws std::invalid_argument if the input is not a valid integer.
 */
static int GetVertices()
{
    int numberOfVertices;
    //std::cout << "Please enter the number of vertices" << std::endl;

    if (!(std::cin >> numberOfVertices))
    {
        throw std::invalid_argument("invalid input");
    }

    return numberOfVertices;
}

/**
 * @brief Gets the edges from the user.
 *
 * @return std::vector<std::vector<int>> A vector of edges where each edge is represented by a pair of vertices.
 * @throws std::invalid_argument if the input is not a valid integer.
 */
static std::vector<std::vector<int>> GetEdges()
{
    int numberOfEdges, firstVertex, secondVertex;
    //std::cout << "Please enter the number of edges" << std::endl;

    if (!(std::cin >> numberOfEdges))
    {
        throw std::invalid_argument("invalid input");
    }

    std::vector<std::vector<int>> edges(numberOfEdges);

    for (int i = 0; i < numberOfEdges; i++)
    {
        std::cout << "Edge " << i + 1 << ": ";
        if (!(std::cin >> firstVertex >> secondVertex))
        {
            throw std::invalid_argument("invalid input");
        }

        edges[i] = { --firstVertex, --secondVertex };
    }

    return edges;
}