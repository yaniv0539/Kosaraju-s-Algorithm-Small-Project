#pragma once

#include <iostream>
#include <stdexcept>
#include "Graph.h"

/**
 * @brief Gets the number of vertices from the user.
 *
 * @return int The number of vertices.
 * @throws std::invalid_argument if the input is not a valid integer.
 */
static int GetVertices();

/**
 * @brief Gets the edges from the user.
 *
 * @return std::vector<std::vector<int>> A vector of edges where each edge is represented by a pair of vertices.
 * @throws std::invalid_argument if the input is not a valid integer.
 */
static std::vector<std::vector<int>> GetEdges();