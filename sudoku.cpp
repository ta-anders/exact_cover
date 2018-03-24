#include <iostream>
#include <fstream>
#include "sudoku.h"
#include "utils.cpp"


void CreateRow(int x, int y, int value, ExactCoverInputMatrix *ec_input)
{
  std::vector<std::vector<bool>> row;
  row.reserve(5);

  row.push_back({true, true, false, true});

  std::cout << row[0].size();

//  int col_count = 0;
//
//  // Row column
//  bool row_col_constraints[9 * 9] = {};  // defaults them to false
//  for (int i = 0; i < 9; i++)
//  {
//    for (int j = 0; j < 9; j++)
//    {
//
//    }
//  }
}

// Constructor from file name
SudokuInputCreator::SudokuInputCreator(const std::string &filename)
    : input_data_()
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

// Conversion from sodoku input to exact cover matrix
ExactCoverInputMatrix *SudokuInputCreator::CreateExactCoverInputMatrix()
{
  auto ec_input = new ExactCoverInputMatrix;
  for (int i = 0; i < input_data_.size(); i++)
  {
    for (int j = 0; j < input_data_[0].size(); j++)
    {
      if (input_data_[i][j])
      {
        // This coordinate has a number in it already - only make the one row
        CreateRow(i, j, input_data_[i][j], ec_input);
      }
      else
      {
        for (int k = 0; k < 9; k++)
        {
          CreateRow(i, j, k, ec_input);
        }
      }
    }
  }
}

int main()
{
  SudokuInputCreator input_creator("sodoku_test.txt");

  input_creator.CreateExactCoverInputMatrix();
  return 0;
}