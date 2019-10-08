#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/AStar.h"
#include "../Algorithms/Astar.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
TEST_CLASS(UnitTest) {
public:
  TEST_METHOD(TestMethod1) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12, 13, 14, 15, 10 };
    std::vector<int> tiles(arr, arr + sizeof(arr) / sizeof(int));
    PuzzleBoard::Board board(tiles);
    Assert::AreEqual(board.is_goal(), false);
  }
};

}
