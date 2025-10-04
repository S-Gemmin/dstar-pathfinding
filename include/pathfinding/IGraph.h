#pragma once
#include <vector>
#include <functional>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1,T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;  
    }
};

struct Node {
    int row; 
    int col;
    bool walkable;

    bool operator==(const Node& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Node& other) const {
        return !(*this == other);
    }
};

class IGraph {
public:
    virtual ~IGraph() = default;
    virtual std::vector<Node> getNeighbors(const Node& n) const = 0;
    virtual double getCost(const Node& a, const Node& b) const = 0;
    virtual bool isGoal(const Node& n) const = 0;
};
