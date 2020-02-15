#pragma once

#include <string>
#include <vector>
#include <deque>
#include "Sorting.h"

namespace PuzzleBoard
{

#pragma region Board

    class Board {
    public:
        // Create a board from an array of tiles from 0 to N^2 - 1, where
        // tiles[i] is the tile at position i, and 0 represents the empty tile.
        // Make sure N is within [2, 128] and input is N^2 distinct integers.
        Board(const std::vector<int>& tiles);

        // Board dimension n
        int dimension() const;

        // String representation of this board
        std::string string_representation() const;

        // Number of tiles out of place
        int hamming() const;

        // Sum of Manhattan distances between tiles and goal
        int manhattan() const;

        // Is this board the goal board?
        bool is_goal() const;

        // Does this board equal the other board?
        bool equals(const Board& other) const;

        // All neighbouring boards
        std::vector<Board> neighbours() const;

        // A board that is obtained by exchanging any pair of tiles
        Board twin() const;

    private:
        std::vector<int> tiles;
        int N;
    };

#pragma endregion Board


#pragma region A* Solver

    class Solver {
    public:
        // Create a solver for the initial board passed in
        Solver(const Board& initial);

        // Is the initial board solvable?
        bool is_solvable() const;

        // Minimum number of moves to solve the initial board.
        // Return -1 if the initial board is not solvable.
        int min_moves() const;

        // Sequence of boards in a shortest solution
        // Return an empty vector if the initial board is not solvable
        std::deque<Board> solution() const;

    private:
        class Node {
        public:
            Board board;
            Node* prev;
            int moves;
            int manhattan;

            Node(const Board& board, Node* prev, int moves, int manhattan)
                : board(board), prev(prev), moves(moves), manhattan(manhattan) {}
            bool operator<(const Node& other) const {
                return moves + manhattan < other.moves + other.manhattan;
            }
            bool operator<=(const Node& other) const {
                return moves + manhattan <= other.moves + other.manhattan;
            }
        };

        bool solvable = false;
        int number_of_moves = -1;
        Sorting::MinPriorityQueue<Node> pq;
        Sorting::MinPriorityQueue<Node> pq2;
        std::deque<Node> game_tree;
        std::deque<Node> game_tree2;

        void a_star();
    };

#pragma endregion A* Solver

}
