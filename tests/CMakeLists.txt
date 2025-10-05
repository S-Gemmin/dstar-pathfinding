include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    test_DStarLite.cpp
    test_Grid.cpp
    test_MinHeapMap.cpp
)

target_link_libraries(unit_tests PRIVATE pathfinding gtest gtest_main)
add_test(NAME AllTests COMMAND unit_tests)
