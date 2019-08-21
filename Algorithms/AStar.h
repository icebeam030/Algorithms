#pragma once

#include <string>
#include <vector>
#include "Sorting.h"

// The board for the sliding puzzle problem
class Board {
private:
  std::vector<int> tiles;
  const int N;
public:
  // Create a board from an array of tiles from 0 to N^2 - 1, where
  // tiles[i] is the tile at position i, and 0 represents the empty tile.
  // Make sure N is within [2, 128] and input is N^2 distinct integers.
  Board(const std::vector<int>& tiles);

  // Board dimension n
  int dimension() const;

  // String representation of this board
  typename std::string string_representation() const;

  // Number of tiles out of place
  int hamming() const;

  // Sum of Manhattan distances between tiles and goal
  int manhattan() const;

  // Is this board the goal board?
  bool is_goal() const;

  // Does this board equal the other board?
  bool equals(Board other) const;

  // All neighbouring boards
  typename std::vector<Board> neighbours() const;

  // A board that is obtained by exchanging any pair of tiles
  typename Board twin() const;
};


// Using A* search algorithm to solve the sliding puzzle problem
class Solver {
private:
  class Node {
  private:
    Board board;
    Node* prev;
    int number_of_moves;
    int manhattan;
  public:
    bool operator<(Node other) {
      return number_of_moves + manhattan < other.number_of_moves + other.manhattan;
    }
  };

  Sorting::MinPriorityQueue<Node> pq;
  void solve(Board initial);
public:
  Solver(Board initial);

  // Is the initial board solvable?
  bool is_solvable() const;

  // Minimum number of moves to solve the initial board
  int min_moves();

  // Sequence of boards in a shortest solution
  typename std::vector<Board> solution();
};
