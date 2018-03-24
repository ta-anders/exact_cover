#pragma once
#include <iostream>
#include <array>
#include "data.h"

typedef std::array<std::array<int, 9>, 9> SudokuInputData;

const char kEmptyCellCharacter = '.';
const int kNumSudokuConstraintSets = 324;

class SudokuInputCreator
{
 public:
  explicit SudokuInputCreator(const SudokuInputData &input_data)
      : input_data_(input_data) {};
  explicit SudokuInputCreator(const std::string &filename);

  ExactCoverInputMatrix *CreateExactCoverInputMatrix();

 private:
  SudokuInputData input_data_;
};