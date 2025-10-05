#include "Grid.h"
#include <cmath>
#include <limits>
#include <gtest/gtest.h>

class GridTest : public ::testing::Test {
protected:
    Grid grid{5, 5};
    inline static constexpr double EPSILON = 1e-6;
};

TEST_F(GridTest, NormalNeighbors) {
    auto neighbors = grid.getNeighbors(Node(2, 2));
    EXPECT_EQ(neighbors.size(), 8);
}

TEST_F(GridTest, AllNeighborsBlocked) {
    Node center(2, 2);
    for (auto neighbor : grid.getNeighbors(center)) 
        grid.setWalkable(neighbor, false);

    auto neighbors = grid.getNeighbors(center);
    EXPECT_EQ(neighbors.size(), 0); 
}

TEST_F(GridTest, CornerNodeNeighbors) {
    auto neighbors = grid.getNeighbors(Node(0, 0));
    EXPECT_EQ(neighbors.size(), 3);
}

TEST_F(GridTest, EdgeNodeNeighbors) {
    auto neighbors = grid.getNeighbors(Node(0, 2));
    EXPECT_EQ(neighbors.size(), 5);
}

TEST_F(GridTest, StraightAndDiagonalCosts) {
    EXPECT_NEAR(grid.getEdgeCost(Node(1, 1), Node(1, 2)), 1.0, EPSILON);
    EXPECT_NEAR(grid.getEdgeCost(Node(1, 1), Node(2, 2)), std::sqrt(2), EPSILON);
}

TEST_F(GridTest, BlockedEdgeCost) {
    grid.setWalkable(Node(1, 2), false);
    EXPECT_TRUE(std::isinf(grid.getEdgeCost(Node(1, 1), Node(1, 2))));
}

TEST_F(GridTest, NonNeighborEdgeCost) {
    EXPECT_TRUE(std::isinf(grid.getEdgeCost(Node(0, 0), Node(2, 2))));
}

TEST_F(GridTest, SameNodeEdgeCost) {
    EXPECT_NEAR(grid.getEdgeCost(Node(2, 2), Node(2, 2)), 0.0, EPSILON);
}

TEST_F(GridTest, ZeroDistance) {
    EXPECT_NEAR(grid.getEuclideanDistance(Node(2, 2), Node(2, 2)), 0.0, EPSILON);
}

TEST_F(GridTest, ArbitraryDistance) {
    EXPECT_NEAR(grid.getEuclideanDistance(Node(0, 0), Node(3, 4)), 5.0, EPSILON);
}

TEST_F(GridTest, ReverseDistance) {
    EXPECT_NEAR(grid.getEuclideanDistance(Node(3, 4), Node(0, 0)), 5.0, EPSILON);
}

TEST_F(GridTest, DiagonalDistanceDouble) {
    EXPECT_NEAR(grid.getEuclideanDistance(Node(0, 0), Node(1, 2)), std::sqrt(5), EPSILON);
}

TEST_F(GridTest, DistanceWithObstacle) {
    grid.setWalkable(Node(1, 2), false);
    EXPECT_NEAR(grid.getEuclideanDistance(Node(0, 0), Node(1, 2)), std::sqrt(5), EPSILON);
}
