#pragma once
#include <iostream>
#include <array>
#include <tuple>
#include <vector>
#include "data.h"
#include "utils.h"

typedef std::array<std::array<int, 9>, 9> SudokuInputData;

const char kEmptyCellCharacter = '.';

class SudokuInputCreator
{
 public:
  explicit SudokuInputCreator(const SudokuInputData &input_data)
      : input_data_(input_data) {};

  explicit SudokuInputCreator(const std::string &filename);

  ExactCoverInputMatrix &GetExactCoverInputMatrix() { PopulateExactCoverInputMatrix(); return ec_input_; };

  std::tuple<int, int, int> &GetMappedValue(int row_index) { return mapper_[row_index]; }

 private:
  void CreateRow(int x, int y, int value, bool preset);
  unsigned int GetIndex(unsigned int i, unsigned int j) { return 9 * i + j; };
  void PopulateExactCoverInputMatrix();

  SudokuInputData input_data_;
  ExactCoverInputMatrix ec_input_;
  std::vector<std::tuple<int, int, int>> mapper_;
  std::vector<unsigned int> cell_occupied_;
  std::vector<unsigned int> row_occupied_;
  std::vector<unsigned int> column_occupied_;
  std::vector<unsigned int> grid_occupied_;
};
