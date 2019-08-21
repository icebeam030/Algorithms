#include <math.h>
#include <random>
#include <chrono>
#include "AStar.h"

using namespace std;

// The Board class
Board::Board(const vector<int>& tiles)
  : tiles(tiles), N(sqrt(tiles.size())) {}

int Board::dimension() const {
  return N;
}

typename string Board::string_representation() const {
  string board_string;
  board_string += to_string(N) + "\n";

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      board_string += to_string(tiles[i * N + j]) + " ";
    }
    board_string += "\n";
  }
  return board_string;
}

int Board::hamming() const {
  int count = 0;
  for (int i = 0; i < N * N; ++i) {
    if (tiles[i] != 0 && tiles[i] != i + 1) {
      ++count;
    }
  }
  return count;
}

int Board::manhattan() const {
  int distance = 0;
  for (int i = 0; i < N * N; ++i) {
    if (tiles[i] == 0) { continue; }
    int row_distance = abs(i / N - (tiles[i] - 1) / N);
    int col_distance = abs(i % N - (tiles[i] - 1) % N);
    distance += row_distance + col_distance;
  }
  return distance;
}

bool Board::is_goal() const {
  return hamming() == 0;
}

bool Board::equals(Board other) const {
  return string_representation() == other.string_representation();
}

typename vector<Board> Board::neighbours() const {
  vector<Board> neighbours;

  // Find the index of 0
  int index = 0;
  for (int i = 0; i < N * N; ++i) {
    if (tiles[i] == 0) {
      index = i;
      break;
    }
  }
  int row = index / N + 1;
  int col = index % N + 1;

  // A neighbour is created by swapping 0 with its adjacent tile
  if (row > 1) {
    vector<int> new_tiles(tiles);
    swap(new_tiles[index], new_tiles[index - N]);
    Board neighbour(new_tiles);
    neighbours.push_back(neighbour);
  }
  if (row < N) {
    vector<int> new_tiles(tiles);
    swap(new_tiles[index], new_tiles[index + N]);
    Board neighbour(new_tiles);
    neighbours.push_back(neighbour);
  }
  if (col > 1) {
    vector<int> new_tiles(tiles);
    swap(new_tiles[index], new_tiles[index - 1]);
    Board neighbour(new_tiles);
    neighbours.push_back(neighbour);
  }
  if (col < N) {
    vector<int> new_tiles(tiles);
    swap(new_tiles[index], new_tiles[index + 1]);
    Board neighbour(new_tiles);
    neighbours.push_back(neighbour);
  }

  return neighbours;
}

typename Board Board::twin() const {
  vector<int> new_tiles(tiles);
  int i = 0;
  int j = new_tiles.size() - 1;
  while (new_tiles[i] == 0) { ++i; }
  while (new_tiles[j] == 0) { --j; }
  swap(new_tiles[i], new_tiles[j]);
  Board twin(new_tiles);
  return twin;
}


// The Solver class
Solver::Solver(Board initial) {
  solve(initial);
}

void Solver::solve(Board initial) {
  pq.insert()
}
