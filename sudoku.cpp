#include <fstream>
#include <ctime>
#include "sudoku.h"
#include "solver.h"

// Constructor from file name
SudokuInputCreator::SudokuInputCreator(const std::string &filename)
    : input_data_(),
      cell_occupied_(9 * 9, 0),
      row_occupied_(9 * 9, 0),
      column_occupied_(9 * 9, 0),
      grid_occupied_(9 * 9, 0)
{
  std::ifstream infile(filename);

  if (!infile)
  {
    std::cout << "No file found at " << filename;
    exit(1);
  }

  std::string str_input;
  while (infile.good())
  {
    std::getline(infile, str_input);
  }

  unsigned int count = 0;
  for (char &c : str_input)
  {
    Coords coords = GetCoordsFromPosition(count);
    input_data_[coords.x][coords.y] = (c == kEmptyCellCharacter ? 0 : c - '0');

    ++count;
  }

  std::cout << "Successfully loaded board as:\n";
  for (auto &i : input_data_)
  {
    for (auto &j : i)
    {
      std::cout << j << " ";
    }
    std::cout << "\n";
  }
}

void SudokuInputCreator::CreateRow(int x, int y, int value, bool preset)
{
  unsigned int cell = GetIndex(x, y);
  unsigned int row = GetIndex(x, value);
  unsigned int col = GetIndex(y, value);
  unsigned int grid = GetIndex((x / 3) * 3 + (y / 3), value);

  if (cell_occupied_[cell] ||
      row_occupied_[row] ||
      column_occupied_[col] ||
      grid_occupied_[grid])
  {
    return;
  }

  unsigned int row_constraint = 9 * 9 + row;
  unsigned int col_constraint = 2 * 9 * 9 + col;
  unsigned int grid_constraint = 3 * 9 * 9 + grid;

  ec_input_.push_back({cell, row_constraint, col_constraint, grid_constraint});
  mapper_.emplace_back(x, y, value);

  if (preset)
  {
    ++cell_occupied_[cell];
    ++row_occupied_[row];
    ++column_occupied_[col];
    ++grid_occupied_[grid];
  }
}

// Conversion from sodoku input to exact cover matrix
void SudokuInputCreator::PopulateExactCoverInputMatrix()
{
  clock_t start = clock();

  // Go through all the pre filled values to populate the occupied caches,
  // in order to cut down the number of possible assignments to blank cells.
  // TODO: this could be optimised by looping through in one pass,
  // but creating rows for the occupied ones first
  for (int i = 0; i < input_data_.size(); i++)
  {
    for (int j = 0; j < input_data_[0].size(); j++)
    {
      if (input_data_[i][j])
      {
        CreateRow(i, j, input_data_[i][j] - 1, true);
      }
    }
  }

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (input_data_[i][j] == 0)
      {
        for (int k = 0; k < 9; k++)
        {
          CreateRow(i, j, k, false);
        }
      }
    }
  }

  clock_t end = clock();
  double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
  std::cout << "Converted input to EC matrix with " << ec_input_.size() << " rows,";
  std::cout << " took " << time_spent << " seconds\n";
}


void SolveFromFile(const std::string &filename)
{
  clock_t start = clock();
  SudokuInputCreator input_creator(filename);

  ExactCoverInputMatrix &ec_input = input_creator.GetExactCoverInputMatrix();

  ExactCoverSolver solver(ec_input, 81 * 4);
  solver.Solve();

  clock_t end = clock();

  double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
  std::cout << "Total time to solve sudoku is " << time_spent << std::endl;

  std::vector<ExactCoverSolution> &solutions = solver.GetSolutions();

  for (auto &sol : solutions)
  {
    std::array<std::array<int, 9>, 9> ordered_sol;
    for (auto &row : sol)
    {
      std::tuple<int, int, int>key(input_creator.GetMappedValue(row));
      ordered_sol[std::get<0>(key)][std::get<1>(key)] = std::get<2>(key) + 1;
    }

    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        std::cout << ordered_sol[i][j] << " ";
      }
      std::cout << "\n";
    }
  }

}

int main()
{
  SolveFromFile("sodoku_test.txt");

  return 0;
}