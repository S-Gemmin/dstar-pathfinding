#pragma once
#include <vector>
#include <functional>
#include <limits>
#include <iostream>

struct Node {
    int row; 
    int col;
    bool walkable;

    Node() : row(0), col(0), walkable(true) {}
    Node(int r, int c, bool w = true) : row(r), col(c), walkable(w) {}

    bool operator==(const Node& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Node& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << "(" << node.row << ", " << node.col << ")";
        return os;
    }
};

namespace std {
    template<>
    struct hash<Node> {
        std::size_t operator()(const Node& n) const {
            return std::hash<int>{}(n.row) ^ (std::hash<int>{}(n.col) << 1); // could be improved
        }
    };
}

class IGraph {
public:
    inline static constexpr double INF_COST = std::numeric_limits<double>::infinity();
    virtual ~IGraph() = default;
    virtual void setWalkable(const Node& node, bool walkable) = 0;
    virtual bool isWalkable(const Node& node) const = 0;
    virtual std::vector<Node> getNeighbors(const Node& n) const = 0;
    virtual double getEdgeCost(const Node& node1, const Node& node2) const = 0;
    virtual double getEuclideanDistance(const Node& node1, const Node& node2) const = 0;
};
