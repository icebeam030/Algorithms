#pragma once

#include <string>
#include <vector>
#include <deque>
#include "Sorting.h"

// The board for the sliding puzzle problem
class Board {
private:
  std::vector<int> tiles;
  int N;
public:
  // Create a board from an array of tiles from 0 to N^2 - 1, where
  // tiles[i] is the tile at position i, and 0 represents the empty tile.
  // Make sure N is within [2, 128] and input is N^2 distinct integers.
  Board(const std::vector<int>& tiles);
  Board(const Board& other);
  Board& operator=(const Board& other);

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
  bool equals(const Board& other) const;

  // All neighbouring boards
  typename std::vector<Board> neighbours() const;

  // A board that is obtained by exchanging any pair of tiles
  typename Board twin() const;
};


// Using A* search algorithm to solve the sliding puzzle problem
class Solver {
private:
  class Node {
  public:
    Board board;
    Node* prev;
    int moves;
    int manhattan;

    Node(Board board, Node* prev, int moves, int manhattan)
      : board(board), prev(prev), moves(moves), manhattan(manhattan) {}
    Node(const Node& other)
      : board(other.board), prev(other.prev), moves(other.moves), manhattan(other.manhattan) {}
    Node& operator=(const Node& other) {
      board = other.board;
      prev = other.prev;
      moves = other.moves;
      manhattan = other.manhattan;
      return *this;
    }
    bool operator<(const Node& other) const {
      return moves + manhattan < other.moves + other.manhattan;
    }
    bool operator<=(const Node& other) const {
      return moves + manhattan <= other.moves + other.manhattan;
    }
  };

  bool solvable;
  int number_of_moves;
  Sorting::MinPriorityQueue<Node> pq;
  Sorting::MinPriorityQueue<Node> pq2;
  std::vector<Node> game_tree;
  std::vector<Node> game_tree2;
  std::deque<Board> solution_boards;

  void a_star();

public:
  Solver(const Board& initial);

  // Is the initial board solvable?
  bool is_solvable() const;

  // Minimum number of moves to solve the initial board.
  // Return -1 if the initial board is not solvable.
  int min_moves() const;

  // Sequence of boards in a shortest solution
  typename std::deque<Board> solution();
};
