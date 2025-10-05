#pragma once
#include "IGraph.h"
#include "MinHeapMap.h" 
#include <unordered_map>

// You must call findPath() before calling notifyEnvironmentChanges()
class DStarLite {
public:
    DStarLite(const IGraph& graph);
    std::vector<Node> findPath(const Node& start, const Node& goal);
    std::vector<Node> notifyEnvironmentChanges(const Node& agentNode, const std::vector<Node>& updatedNodes);
private:
    inline static constexpr double EPSILON = 1e-6; // tolerance for floating-point comparisons

    const IGraph& graph;
    MinHeapMap heap;

    Node start;
    Node goal;
    Node last;
    double km;

    std::unordered_map<Node, double> gCosts;
    std::unordered_map<Node, double> rhsCosts;

    Key calculateKey(const Node& node);
    void updateNode(const Node& node);
    void computeShortestPath();
    double computeRhs(const Node& node);
    std::vector<Node> buildPath();
};
