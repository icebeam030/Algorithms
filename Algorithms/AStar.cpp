#include <math.h>
#include "AStar.h"

using namespace std;
using namespace PuzzleBoard;


#pragma region Board

Board::Board(const vector<int>& tiles)
    : tiles(tiles), N(static_cast<int>(sqrt(tiles.size())))
{
}

int Board::dimension() const
{
    return N;
}

string Board::string_representation() const
{
    string string_of_board;
    string_of_board += to_string(N) + "\n";

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            string_of_board += to_string(tiles[i * N + j]) + " ";
        }
        string_of_board += "\n";
    }

    return string_of_board;
}

int Board::hamming() const
{
    int count = 0;
    for (int i = 0; i < N * N; ++i) {
        if (tiles[i] != 0 && tiles[i] != i + 1) {
            ++count;
        }
    }

    return count;
}

int Board::manhattan() const
{
    int distance = 0;
    for (int i = 0; i < N * N; ++i) {
        if (tiles[i] == 0) {
            continue;
        }
        int row_distance = abs(i / N - (tiles[i] - 1) / N);
        int col_distance = abs(i % N - (tiles[i] - 1) % N);
        distance += row_distance + col_distance;
    }

    return distance;
}

bool Board::is_goal() const
{
    return hamming() == 0;
}

bool Board::equals(const Board& other) const
{
    return string_representation() == other.string_representation();
}

vector<Board> Board::neighbours() const
{
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
        vector<int> neighbour_tiles(tiles);
        swap(neighbour_tiles[index], neighbour_tiles[index - N]);

        Board neighbour(neighbour_tiles);
        neighbours.push_back(neighbour);
    }
    if (row < N) {
        vector<int> neighbour_tiles(tiles);
        swap(neighbour_tiles[index], neighbour_tiles[index + N]);

        Board neighbour(neighbour_tiles);
        neighbours.push_back(neighbour);
    }
    if (col > 1) {
        vector<int> neighbour_tiles(tiles);
        swap(neighbour_tiles[index], neighbour_tiles[index - 1]);

        Board neighbour(neighbour_tiles);
        neighbours.push_back(neighbour);
    }
    if (col < N) {
        vector<int> neighbour_tiles(tiles);
        swap(neighbour_tiles[index], neighbour_tiles[index + 1]);

        Board neighbour(neighbour_tiles);
        neighbours.push_back(neighbour);
    }

    return neighbours;
}

Board Board::twin() const
{
    vector<int> twin_tiles(tiles);

    int i = 0;
    int j = twin_tiles.size() - 1;
    while (twin_tiles[i] == 0) {
        ++i;
    }
    while (twin_tiles[j] == 0) {
        --j;
    }

    swap(twin_tiles[i], twin_tiles[j]);
    Board twin(twin_tiles);

    return twin;
}

#pragma endregion Board


#pragma region Solver

Solver::Solver(const Board& initial)
{
    Node node(initial, nullptr, 0, initial.manhattan());
    Node node2(initial.twin(), nullptr, 0, initial.twin().manhattan());
    pq.push(node);
    pq2.push(node2);

    a_star();
}

void Solver::a_star()
{
    while (true) {
        Node node = pq.pop_min();
        Node node2 = pq2.pop_min();

        if (node.board.is_goal()) {
            solvable = true;
            number_of_moves = node.moves;
            game_tree.push_back(node);
            break;
        }
        if (node2.board.is_goal()) {
            game_tree.clear();
            break;
        }

        game_tree.push_back(node);
        Node& current = game_tree.back();

        vector<Board> boards = current.board.neighbours();
        for (Board board : boards) {
            if (current.prev != nullptr && board.equals(current.prev->board)) {
                continue;
            }
            Node new_node(board, &current, current.moves + 1, board.manhattan());
            pq.push(new_node);
        }

        game_tree2.push_back(node2);
        Node& current2 = game_tree2.back();

        vector<Board> boards2 = current2.board.neighbours();
        for (Board board2 : boards2) {
            if (current2.prev != nullptr && board2.equals(current2.prev->board)) {
                continue;
            }
            Node new_node(board2, &current2, current2.moves + 1, board2.manhattan());
            pq2.push(new_node);
        }
    }
}

int Solver::min_moves() const
{
    return number_of_moves;
}

bool Solver::is_solvable() const
{
    return solvable;
}

deque<Board> Solver::solution() const
{
    deque<Board> solution_boards;

    if (is_solvable()) {
        Node goal = game_tree.back();
        solution_boards.push_front(goal.board);
        while (goal.prev != nullptr) {
            goal = *(goal.prev);
            solution_boards.push_front(goal.board);
        }
    }

    return solution_boards;
}

#pragma endregion Solver
