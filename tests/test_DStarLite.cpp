#include "DStarLite.h"
#include "Grid.h"
#include <vector>
#include <gtest/gtest.h>

class DStarLiteTest : public ::testing::Test {
protected:
    Grid grid{5, 5};
};

TEST_F(DStarLiteTest, SmallGrid) {
    /*
        S 0 0 0 0 
        0 + 0 0 0
        0 0 + 0 0
        0 0 0 + 0 
        0 0 0 0 E
    */
    DStarLite dstar(grid);

    std::vector<Node> correctPath = { Node(0, 0), Node(1, 1), Node(2, 2), Node(3, 3), Node(4, 4) };
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));

    EXPECT_EQ(correctPath, actualPath);
}

TEST_F(DStarLiteTest, StartUnwalkableTest) {
    /*
        X 0 0 0 0
        0 0 0 0 0
        0 0 0 0 0
        0 0 0 0 0
        0 0 0 0 G
    */
    grid.setWalkable(Node(0, 0), false);
    DStarLite dstar(grid);
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_TRUE(actualPath.empty());
}

TEST_F(DStarLiteTest, GoalUnwalkableTest) {
    /*
        S 0 0 0 0
        0 0 0 0 0
        0 0 0 0 0
        0 0 0 0 0
        0 0 0 0 X
    */
    grid.setWalkable(Node(4, 4), false);
    DStarLite dstar(grid);
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_TRUE(actualPath.empty());
}

TEST_F(DStarLiteTest, NoPathTest) {
    /*
        S 0 X 0 0
        0 0 X 0 0
        0 0 X 0 0
        0 0 X 0 0
        0 0 X 0 G
    */
    std::vector<Node> obstacles = {
        Node(0, 2), 
        Node(1, 2), 
        Node(2, 2), 
        Node(3, 2), 
        Node(4, 2)
    };
    for (auto& obstacle : obstacles) grid.setWalkable(obstacle, false);

    DStarLite dstar(grid);
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_TRUE(actualPath.empty());
}

TEST_F(DStarLiteTest, ObstacleTest) {
    /*
        S 0 0 0 0 
        0 + + 0 0
        0 0 X + 0
        0 0 0 0 + 
        0 0 0 0 E
    */
    grid.setWalkable(Node(2, 2), false);
    DStarLite dstar(grid);

    std::vector<Node> correctPath = { Node(0, 0), Node(1, 1), Node(1, 2), Node(2, 3), Node(3, 4), Node(4, 4) };
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));

    EXPECT_EQ(correctPath, actualPath);
}

TEST_F(DStarLiteTest, BasicDynamicEnvironmentTest) {
    /*
        S 0 0 0 0  -> 0 0 0 0 0
        0 + 0 0 0	 0 S + 0 0 
        0 0 + 0 0	 0 0 X + 0 
        0 0 0 + 0     0 0 0 0 + 
        0 0 0 0 E     0 0 0 0 E
    */
    DStarLite dstar(grid);

    std::vector<Node> correctPath = { Node(0, 0), Node(1, 1), Node(2, 2), Node(3, 3), Node(4, 4) };
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_EQ(correctPath, actualPath);

    grid.setWalkable(Node(2, 2), false);
    actualPath = dstar.notifyEnvironmentChanges(Node(1, 1), { Node(2, 2) });

    correctPath = { Node(1, 1), Node(1, 2), Node(2, 3), Node(3, 4), Node(4, 4) };
    EXPECT_EQ(correctPath, actualPath);
}

TEST_F(DStarLiteTest, RemoveObstacleTest) {
    /*
        S 0 0 0 0  -> 0 0 0 0 0 
        0 + + 0 0     0 S 0 0 0
        0 0 X + 0     0 0 + 0 0
        0 0 0 0 +     0 0 0 + 0 
        0 0 0 0 E     0 0 0 0 E
    */
    grid.setWalkable(Node(2, 2), false);
    DStarLite dstar(grid);

    std::vector<Node> correctPath = { Node(0, 0), Node(1, 1), Node(1, 2), Node(2, 3), Node(3, 4), Node(4, 4) };
    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_EQ(correctPath, actualPath);

    grid.setWalkable(Node(2, 2), true);
    actualPath = dstar.notifyEnvironmentChanges(Node(1, 1), { Node(2, 2) });

    correctPath = { Node(1, 1), Node(2, 2), Node(3, 3), Node(4, 4) };
    EXPECT_EQ(correctPath, actualPath);
}

TEST_F(DStarLiteTest, GoalChangedTest) {
    /*
        S 0 0 0 0  -> E 0 0 0 0 
        0 + 0 0 0     0 + 0 0 0
        0 0 + 0 0     0 0 + 0 0
        0 0 0 + 0     0 0 0 + 0 
        0 0 0 0 E     0 0 0 0 S
    */
    DStarLite dstar(grid);
    dstar.findPath(Node(0, 0), Node(4, 4));

    std::vector<Node> correctPath = { Node(4, 4), Node(3, 3), Node(2, 2), Node(1, 1), Node(0, 0) };
    std::vector<Node> actualPath = dstar.findPath(Node(4, 4), Node(0, 0));
    EXPECT_EQ(correctPath, actualPath);
}

TEST_F(DStarLiteTest, ComplexTest) {
    /*
	    S X 0 + 0
	    + X + X +
	    + X + X + 
	    + X + X +
	    0 + 0 X E
    */
    std::vector<Node> obstacles = { 
        Node(0, 1), 
        Node(1, 1), 
        Node(2, 1), 
        Node(3, 1), 
        Node(1, 3),
        Node(2, 3), 
        Node(3, 3), 
        Node(4, 3),
    };
    for (auto& obstacle : obstacles) grid.setWalkable(obstacle, false);

    DStarLite dstar(grid);
    std::vector<Node> correctPath = { 
        Node(0, 0), 
        Node(1, 0), 
        Node(2, 0), 
        Node(3, 0), 
        Node(4, 1), 
        Node(3, 2), 
        Node(2, 2), 
        Node(1, 2), 
        Node(0, 3),
        Node(1, 4), 
        Node(2, 4), 
        Node(3, 4), 
        Node(4, 4) 
    };

    std::vector<Node> actualPath = dstar.findPath(Node(0, 0), Node(4, 4));
    EXPECT_EQ(correctPath, actualPath);
}
