#include "Grid.h"
#include <cmath>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<Node>(cols));

    for (int r = 0; r < rows; r++) 
        for (int c = 0; c < cols; c++) 
            grid[r][c] = Node(r, c, true);
}

void Grid::setWalkable(const Node& node, bool walkable) {
    if (!(0 <= node.row && node.row < rows && 0 <= node.col && node.col < cols)) return;

    Node& n = grid[node.row][node.col];
    n.walkable = walkable;
}

bool Grid::isWalkable(const Node& node) const {
    if (!(0 <= node.row && node.row < rows && 0 <= node.col && node.col < cols)) return false;
    return grid[node.row][node.col].walkable;
}

std::vector<Node> Grid::getNeighbors(const Node& n) const {
    const Node& node = grid[n.row][n.col];

    std::vector<Node> neighbors;

    for (const auto& [dr, dc] : directions) {
        int newRow = node.row + dr;
        int newCol = node.col + dc;

        if (0 <= newRow && newRow < rows && 0 <= newCol && newCol < cols && grid[newRow][newCol].walkable) 
            neighbors.push_back(grid[newRow][newCol]);
    }

    return neighbors;
}

double Grid::getEdgeCost(const Node& node1, const Node& node2) const {
    const Node& n1 = grid[node1.row][node1.col];
    const Node& n2 = grid[node2.row][node2.col];

    if (n1 == n2) return 0.0;

    if (!n1.walkable || !n2.walkable) 
        return std::numeric_limits<double>::infinity();

    int dr = std::abs(n1.row - n2.row);
    int dc = std::abs(n1.col - n2.col);

    if (dr + dc > 2) 
        return std::numeric_limits<double>::infinity();

    return dr == 1 && dc == 1 ? DIAGONAL_COST : STRAIGHT_COST;
}

double Grid::getEuclideanDistance(const Node& node1, const Node& node2) const {
    const Node& n1 = grid[node1.row][node1.col];
    const Node& n2 = grid[node2.row][node2.col];

    if (n1 == n2) return 0.0;

    int dr = n1.row - n2.row;
    int dc = n1.col - n2.col;
    return std::sqrt(dr * dr + dc * dc);
}
