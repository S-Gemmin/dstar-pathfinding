#pragma once
#include "IGraph.h"
#include <vector>
#include <unordered_map>
#include <cmath>

class Grid : public IGraph {
public:
    Grid(int rows, int cols);

    void setWalkable(const Node& node, bool walkable) override;
    bool isWalkable(const Node& node) const override;
    std::vector<Node> getNeighbors(const Node& node) const override;
    double getEdgeCost(const Node& node1, const Node& node2) const override;
    double getEuclideanDistance(const Node& node1, const Node& node2) const override;
private:
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    inline static constexpr double DIAGONAL_COST = std::sqrt(2);
    inline static constexpr double STRAIGHT_COST = 1.0;

    std::vector<std::vector<Node>> grid;
    int rows;
    int cols;
};
