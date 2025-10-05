#include "MinHeapMap.h"
#include <stdexcept>
#include <gtest/gtest.h>

class MinHeapMapTest : public ::testing::Test {
protected:
    MinHeapMap heap;
    Node 
        n0{0,0}, n1{1,1}, n2{2,2}, n3{3,3}, n4{4,4},
        n5{5,5}, n6{6,6}, n7{7,7}, n8{8,8}, n9{9,9},
        n10{10,10}, n11{11,11}, n12{12,12}, n13{13,13}, n14{14,14},
        n15{15,15}, n16{16,16}, n17{17,17}, n18{18,18}, n19{19,19};
};

TEST_F(MinHeapMapTest, ConstructionAndBasicProperties) {
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(heap.count(), 0);
}

TEST_F(MinHeapMapTest, ConstructorWithNodes) {
    std::vector<HeapNode> nodes = {
        HeapNode(n1, Key(3.0, 1.0)),
        HeapNode(n2, Key(1.0, 2.0)),
        HeapNode(n3, Key(2.0, 3.0))
    };

    MinHeapMap localHeap(nodes);

    EXPECT_EQ(localHeap.count(), 3);
    EXPECT_EQ(localHeap.top(), n2);

    EXPECT_TRUE(localHeap.contains(n1));
    EXPECT_TRUE(localHeap.contains(n2));
    EXPECT_TRUE(localHeap.contains(n3));
}

TEST_F(MinHeapMapTest, InsertAndTopOperations) {
    heap.insert(n1, Key(5.0, 1.0));
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(heap.count(), 1);
    EXPECT_EQ(heap.top(), n1);
    EXPECT_EQ(heap.topKey().k1, 5.0);
    EXPECT_EQ(heap.topKey().k2, 1.0);

    heap.insert(n2, Key(3.0, 2.0));
    EXPECT_EQ(heap.count(), 2);
    EXPECT_EQ(heap.top(), n2);

    heap.insert(n3, Key(1.0, 3.0));
    EXPECT_EQ(heap.count(), 3);
    EXPECT_EQ(heap.top(), n3);
}

TEST_F(MinHeapMapTest, KeyComparisonLogic) {
    heap.insert(n1, Key(5.0, 1.0));
    heap.insert(n2, Key(3.0, 2.0));
    EXPECT_EQ(heap.top(), n2);

    heap.insert(n3, Key(3.0, 1.0));
    EXPECT_EQ(heap.top(), n3);

    heap.insert(n4, Key(3.0, 3.0));
    EXPECT_EQ(heap.top(), n3);
}

TEST_F(MinHeapMapTest, ContainsOperation) {
    EXPECT_FALSE(heap.contains(n1));

    heap.insert(n1, Key(1.0, 1.0));
    EXPECT_TRUE(heap.contains(n1));
    EXPECT_FALSE(heap.contains(n2));

    heap.insert(n2, Key(2.0, 2.0));
    EXPECT_TRUE(heap.contains(n1));
    EXPECT_TRUE(heap.contains(n2));
}

TEST_F(MinHeapMapTest, PopOperation) {
    heap.insert(n1, Key(5.0, 1.0));
    heap.insert(n2, Key(3.0, 2.0));
    heap.insert(n3, Key(1.0, 3.0));

    EXPECT_EQ(heap.count(), 3);

    Node popped = heap.pop();
    EXPECT_EQ(popped, n3);
    EXPECT_EQ(heap.count(), 2);
    EXPECT_FALSE(heap.contains(n3));

    popped = heap.pop();
    EXPECT_EQ(popped, n2);
    EXPECT_EQ(heap.count(), 1);

    popped = heap.pop();
    EXPECT_EQ(popped, n1);
    EXPECT_EQ(heap.count(), 0);
    EXPECT_TRUE(heap.isEmpty());
}

TEST_F(MinHeapMapTest, RemoveOperation) {
    heap.insert(n1, Key(4.0, 1.0));
    heap.insert(n2, Key(2.0, 2.0));
    heap.insert(n3, Key(1.0, 3.0));
    heap.insert(n4, Key(3.0, 4.0));

    EXPECT_EQ(heap.count(), 4);
    EXPECT_EQ(heap.top(), n3);

    heap.remove(n2);
    EXPECT_EQ(heap.count(), 3);
    EXPECT_FALSE(heap.contains(n2));
    EXPECT_EQ(heap.top(), n3);

    heap.remove(n3);
    EXPECT_EQ(heap.count(), 2);
    EXPECT_FALSE(heap.contains(n3));
    EXPECT_EQ(heap.top(), n4);
}

TEST_F(MinHeapMapTest, UpdateOperation) {
    heap.insert(n1, Key(5.0, 1.0));
    heap.insert(n2, Key(3.0, 2.0));
    heap.insert(n3, Key(4.0, 3.0));

    EXPECT_EQ(heap.top(), n2);

    heap.update(n1, Key(1.0, 1.0));
    EXPECT_EQ(heap.top(), n1);

    heap.update(n1, Key(10.0, 1.0));
    EXPECT_EQ(heap.top(), n2);
}

TEST_F(MinHeapMapTest, ResetOperation) {
    heap.insert(n1, Key(1.0, 1.0));
    heap.insert(n2, Key(2.0, 2.0));
    heap.insert(n3, Key(3.0, 3.0));

    EXPECT_EQ(heap.count(), 3);

    heap.reset();
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(heap.count(), 0);
    EXPECT_FALSE(heap.contains(n1));
    EXPECT_FALSE(heap.contains(n2));
    EXPECT_FALSE(heap.contains(n3));
}

TEST_F(MinHeapMapTest, EmptyHeapOperationsThrow) {
    EXPECT_THROW(heap.top(), std::runtime_error);
    EXPECT_THROW(heap.topKey(), std::runtime_error);
    EXPECT_THROW(heap.pop(), std::runtime_error);
}

TEST_F(MinHeapMapTest, DuplicateInsertionThrows) {
    heap.insert(n1, Key(1.0, 1.0));
    EXPECT_THROW(heap.insert(n1, Key(2.0, 2.0)), std::runtime_error);
}

TEST_F(MinHeapMapTest, NonExistentVertexOperationsThrow) {
    EXPECT_THROW(heap.remove(n2), std::runtime_error);
    EXPECT_THROW(heap.update(n2, Key(1.0, 1.0)), std::runtime_error);
}

TEST_F(MinHeapMapTest, HeapPropertyMaintenance) {
    std::vector<Node> nodes = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};

    heap.insert(nodes[5], Key(5.0, 5.0));
    heap.insert(nodes[2], Key(2.0, 2.0));
    heap.insert(nodes[8], Key(8.0, 8.0));
    heap.insert(nodes[1], Key(1.0, 1.0));
    heap.insert(nodes[9], Key(9.0, 9.0));
    heap.insert(nodes[3], Key(3.0, 3.0));
    heap.insert(nodes[7], Key(7.0, 7.0));
    heap.insert(nodes[4], Key(4.0, 4.0));
    heap.insert(nodes[6], Key(6.0, 6.0));
    heap.insert(nodes[0], Key(0.0, 0.0));

    std::vector<double> poppedKeys;
    while (!heap.isEmpty()) {
        poppedKeys.push_back(heap.topKey().k1);
        heap.pop();
    }

    for (size_t i = 1; i < poppedKeys.size(); ++i)
        EXPECT_LE(poppedKeys[i-1], poppedKeys[i]);
}

TEST_F(MinHeapMapTest, ComplexUpdateScenarios) {
    std::vector<Node> nodes = {n0,n1,n2,n3,n4};

    for (size_t i = 0; i < nodes.size(); ++i)
        heap.insert(nodes[i], Key(i*2.0, i*1.0));

    EXPECT_EQ(heap.top(), nodes[0]);

    heap.update(nodes[0], Key(20.0, 20.0));
    EXPECT_EQ(heap.top(), nodes[1]);

    heap.update(nodes[0], Key(-1.0, -1.0));
    EXPECT_EQ(heap.top(), nodes[0]);
}

TEST_F(MinHeapMapTest, SameK1ValuesK2Tiebreaker) {
    std::vector<Node> nodes = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12};

    heap.insert(nodes[0], Key(5.0, 15.3));
    heap.insert(nodes[1], Key(5.0, 8.7));
    heap.insert(nodes[2], Key(5.0, 2.1));
    heap.insert(nodes[3], Key(5.0, 22.9));
    heap.insert(nodes[4], Key(5.0, 0.5));
    heap.insert(nodes[5], Key(5.0, 12.4));
    heap.insert(nodes[6], Key(5.0, 3.8));
    heap.insert(nodes[7], Key(5.0, 1.2));
    heap.insert(nodes[8], Key(5.0, 18.6));
    heap.insert(nodes[9], Key(5.0, 0.7));

    heap.insert(nodes[10], Key(4.0, 100.0));
    heap.insert(nodes[11], Key(6.0, 0.1));
    heap.insert(nodes[12], Key(5.0, 0.3));

    EXPECT_EQ(heap.top(), nodes[10]);
    EXPECT_DOUBLE_EQ(heap.topKey().k1, 4.0);
    EXPECT_DOUBLE_EQ(heap.topKey().k2, 100.0);

    heap.pop();
    EXPECT_EQ(heap.top(), nodes[12]);
    EXPECT_DOUBLE_EQ(heap.topKey().k1, 5.0);
    EXPECT_DOUBLE_EQ(heap.topKey().k2, 0.3);

    heap.pop();
    EXPECT_EQ(heap.top(), nodes[4]);
    EXPECT_DOUBLE_EQ(heap.topKey().k2, 0.5);

    heap.pop();
    EXPECT_EQ(heap.top(), nodes[9]);
    EXPECT_DOUBLE_EQ(heap.topKey().k2, 0.7);

    heap.pop();
    EXPECT_EQ(heap.top(), nodes[7]);
    EXPECT_DOUBLE_EQ(heap.topKey().k2, 1.2);
}
