#include "DStarLite.h"
#include <algorithm>
#include <vector>
#include <unordered_set>

DStarLite::DStarLite(const IGraph& graph) : graph(graph), km(0.0) {
    heap = MinHeapMap();
}

std::vector<Node> DStarLite::findPath(const Node& start, const Node& goal) {
    if (!start.walkable || !goal.walkable) 
        return std::vector<Node>();

    this->heap.reset();
    this->gCosts.clear();
    this->rhsCosts.clear();

    this->start = start;
    this->last = last;
    this->goal = goal;
    this->km = 0.0;

    this->gCosts[goal] = IGraph::INF_COST;
    this->rhsCosts[goal] = 0.0;
    this->heap.insert(goal, calculateKey(goal));

    computeShortestPath();
    return buildPath();
}

std::vector<Node> DStarLite::notifyEnvironmentChanges(const Node& agentNode, const std::vector<Node>& updatedNodes) {
    this->km += graph.getEuclideanDistance(last, agentNode);
    this->start = agentNode;
    this->last = agentNode;

    for (const Node& node : updatedNodes) {
        rhsCosts[node] = graph.isWalkable(node) ? computeRhs(node) : IGraph::INF_COST;
        updateNode(node);
    }

    computeShortestPath();
    return buildPath();
}

Key DStarLite::calculateKey(const Node& node) {
    double g = gCosts.find(node) != gCosts.end() ? gCosts[node] : IGraph::INF_COST;
    double rhs = rhsCosts.find(node) != rhsCosts.end() ? rhsCosts[node] : IGraph::INF_COST;
    double minCost = std::min(g, rhs);
    return Key(minCost + graph.getEuclideanDistance(start, node) + km, minCost);
}

void DStarLite::updateNode(const Node& node) {
    double g = gCosts.find(node) != gCosts.end() ? gCosts[node] : IGraph::INF_COST;
    double rhs = rhsCosts.find(node) != rhsCosts.end() ? rhsCosts[node] : IGraph::INF_COST;

    if (heap.contains(node) && g != rhs) {
        heap.update(node, calculateKey(node));
    } else if (!heap.contains(node) && g != rhs) {
        heap.insert(node, calculateKey(node));
    } else if (heap.contains(node) && std::fabs(g - rhs) < EPSILON) {
        heap.remove(node);
    }
}

void DStarLite::computeShortestPath() {
    Key startKey = calculateKey(start);

    while (!heap.isEmpty()) {

        double startG = gCosts.find(start) != gCosts.end() ? gCosts[start] : IGraph::INF_COST;
        double startRhs = rhsCosts.find(start) != rhsCosts.end() ? rhsCosts[start] : IGraph::INF_COST;

        if (!(heap.topKey() < startKey || startG != startRhs))
            break;
        
        Node node = heap.top();
        Key oldKey = heap.topKey();
        Key newKey = calculateKey(node);

        double g = gCosts.find(node) != gCosts.end() ? gCosts[node] : IGraph::INF_COST;
        double rhs = rhsCosts.find(node) != rhsCosts.end() ? rhsCosts[node] : IGraph::INF_COST;

        if (oldKey < newKey) {
            heap.update(node, newKey);
        } else if (g > rhs) { 
            gCosts[node] = rhs;
            heap.pop();
                
            std::vector<Node> neighbors = graph.getNeighbors(node);
            
            for (const Node& neighbor : neighbors) {
                if (!neighbor.walkable) continue;

                double neighborRhs = rhsCosts.find(neighbor) != rhsCosts.end() ? rhsCosts[neighbor] : IGraph::INF_COST;
                double newRhs = gCosts[node] + graph.getEdgeCost(node, neighbor);
                    
                if (newRhs < neighborRhs) 
                    rhsCosts[neighbor] = newRhs;
    
                updateNode(neighbor);
            }
        } else if (g < rhs) {
            double oldG = g;
            gCosts[node] = IGraph::INF_COST;
            heap.pop();
                
            std::vector<Node> neighbors = graph.getNeighbors(node);

            for (const Node& neighbor : neighbors) {
                double neighborRhs = rhsCosts.find(neighbor) != rhsCosts.end() ? rhsCosts[neighbor] : IGraph::INF_COST;

                if (std::fabs(neighborRhs - (oldG + graph.getEdgeCost(node, neighbor))) < EPSILON) 
                    rhsCosts[neighbor] = computeRhs(neighbor);

                updateNode(neighbor);
            }

            updateNode(node);
        }
    }
}

double DStarLite::computeRhs(const Node& node) {
    if (node == goal) return 0.0;
    
    std::vector<Node> neighbors = graph.getNeighbors(node);
    double minRhs = IGraph::INF_COST;
    
    for (Node neighbor : neighbors) {
        if (!neighbor.walkable) continue;

        double neighborG = gCosts.find(neighbor) != gCosts.end() ? gCosts[neighbor] : IGraph::INF_COST;

        if (neighborG < IGraph::INF_COST) 
            minRhs = std::min(minRhs, neighborG + graph.getEdgeCost(node, neighbor));
    }
    
    return minRhs;
}

std::vector<Node> DStarLite::buildPath() {  
    std::unordered_set<Node> visited;
    std::vector<Node> path;
    
    Node current = start;
    double startG = gCosts.find(start) != gCosts.end() ? gCosts[start] : IGraph::INF_COST;

    if (startG == IGraph::INF_COST) 
        return path; 

    while (current != goal) {
        if (visited.find(current) != visited.end()) 
            break;

        visited.insert(current);
        path.push_back(current);

        double currentG = gCosts.find(current) != gCosts.end() ? gCosts[current] : IGraph::INF_COST;
        if (currentG == IGraph::INF_COST)
            break;

        std::vector<Node> neighbors = graph.getNeighbors(current);
        double minCost = IGraph::INF_COST;

        for (const Node& neighbor : neighbors) {
            if (!neighbor.walkable) continue;

            double neighborG = gCosts.find(neighbor) != gCosts.end() ? gCosts[neighbor] : IGraph::INF_COST;

            if (neighborG != IGraph::INF_COST) {
                double totalCost = neighborG + graph.getEdgeCost(current, neighbor);

                if (totalCost < minCost) {
                    minCost = totalCost;
                    current = neighbor;
                }
            }
        }
    }
    
    if (current == goal) 
        path.push_back(goal);
    
    return path;
}
