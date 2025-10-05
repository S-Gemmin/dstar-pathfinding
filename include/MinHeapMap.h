#pragma once
#include "Grid.h"
#include <stdexcept>
#include <vector>
#include <unordered_map>

struct Key {   // Sorted lexicographically.
    double k1; // min(g, rhs) + h + km
    double k2; // min(g, rhs)

    Key() : k1(0.0), k2(0.0) {}

    Key(double k1, double k2) : k1(k1), k2(k2) {}

    bool operator<(const Key& other) const {
        return k1 < other.k1 || (k1 == other.k1 && k2 < other.k2);
    }

    bool operator>(const Key& other) const {
        return k1 > other.k1 || (k1 == other.k1 && k2 > other.k2);
    }
};

struct HeapNode {
    Node node;
    Key key;

    HeapNode(const Node& n, const Key& k) : node(n), key(k) {}
};

// Tailored for D* Lite
class MinHeapMap {
public:
    MinHeapMap();
    MinHeapMap(const std::vector<HeapNode>& nodes);

    int count() const;
    bool isEmpty() const;
    const Node& top() const;
    const Key& topKey() const;
    bool contains(const Node& node) const;
    void insert(const Node& node, const Key& key);
    Node pop();
    void remove(const Node& node);
    void update(const Node& node, const Key& newKey);
    void reset();
private:
    int left(int i) const;
    int right(int i) const;
    int parent(int i) const;
    void siftUp(int i);
    void siftDown(int i);
    void swap(int i, int j);
private:
    std::vector<HeapNode> heap;
    std::unordered_map<Node, int> nodeToIndex;
};
