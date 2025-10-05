#include "MinHeapMap.h"

MinHeapMap::MinHeapMap() {}

MinHeapMap::MinHeapMap(const std::vector<HeapNode>& nodes) {
    for (const auto& node : nodes) // perhaps better to heapify
        insert(node.node, node.key);
}

int MinHeapMap::count() const { 
    return heap.size(); 
}

bool MinHeapMap::isEmpty() const { 
    return heap.empty(); 
}
    
const Node& MinHeapMap::top() const {
    if (isEmpty())
        throw std::runtime_error("Heap is empty!");

    return heap[0].node;
}

const Key& MinHeapMap::topKey() const {
    if (isEmpty())
        throw std::runtime_error("Heap is empty!");

    return heap[0].key;
}

bool MinHeapMap::contains(const Node& node) const {
    return nodeToIndex.find(node) != nodeToIndex.end();
}
    
void MinHeapMap::insert(const Node& node, const Key& key) {
    if (contains(node))
        throw std::runtime_error("Duplicate node!");
        
    heap.push_back(HeapNode(node, key));
    nodeToIndex[node] = heap.size() - 1;
    siftUp(heap.size() - 1);
}
    
Node MinHeapMap::pop() {
    if (isEmpty())
        throw std::runtime_error("Heap is empty!");
        
    Node topNode = top();
    remove(topNode);
    return topNode;
}
    
void MinHeapMap::remove(const Node& node) {
    if (!contains(node))
        throw std::runtime_error("Node not found!");
        
    int index = nodeToIndex[node];
    swap(index, heap.size() - 1);
    heap.pop_back();
    nodeToIndex.erase(node);
        
    if (index < heap.size()) {
        siftUp(index);
        siftDown(index);
    }
}
    
void MinHeapMap::update(const Node& node, const Key& newKey) {
    if (!contains(node))
        throw std::runtime_error("Node not found!");
        
    int index = nodeToIndex[node];
    heap[index].key = newKey;
    siftUp(index);
    siftDown(index);
}
    
void MinHeapMap::reset() {
    heap.clear();
    nodeToIndex.clear();
}
    
int MinHeapMap::left(int i) const { return 2 * i + 1; }
int MinHeapMap::right(int i) const { return 2 * i + 2; }
int MinHeapMap::parent(int i) const { return (i - 1) / 2; }
    
void MinHeapMap::siftUp(int i) {
    while (i > 0) {
        int p = parent(i);

        if (heap[p].key > heap[i].key) {
            swap(i, p);
            i = p;
        } else {
            break;
        }
    }
}

void MinHeapMap::siftDown(int i) {
    while (true) {
        int smallest = i;
        int l = left(i);
        int r = right(i);
            
        if (l < heap.size() && heap[l].key < heap[smallest].key)
            smallest = l;
        if (r < heap.size() && heap[r].key < heap[smallest].key)
            smallest = r;
            
        if (smallest != i) {
            swap(i, smallest);
            i = smallest;
        } else {
            break;
        }
    }
}
    
void MinHeapMap::swap(int i, int j) {
    std::swap(heap[i], heap[j]);
    nodeToIndex[heap[i].node] = i;
    nodeToIndex[heap[j].node] = j;
}
