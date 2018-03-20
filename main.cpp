#include <iostream>
#include "data.h"
#include "solver.h"

int
main()
{
  // From Knuth's paper
  int num_rows = 6;
  int num_cols = 7;

  bool *matrix_data = new bool[num_rows * num_cols];

  InputMatrix input_matrix(num_rows, num_cols, matrix_data);

  bool in_data[num_rows][num_cols] = {
      {false, false, true, false, true, true, false},
      {true, false, false, true, false, false, true},
      {false, true, true, false, false, true, false},
      {true, false, false, true, false, false, false},
      {false, true, false, false, false, false, true},
      {false, false, false, true, true, false, true}
  };

  for (int i = 0; i < num_rows; i++) {
    input_matrix.set_row(in_data[i], i);
  }

  std::cout << "Input matrix looks like:" << std::endl;
  input_matrix.display();

  ExactCoverSolver solver(input_matrix);

  solver.search(0);

  solver.print_solution();

//  int num_rows = 7;
//  int num_cols = 7;
//
//  bool *matrix_data = new bool[num_rows * num_cols];
//
//  InputMatrix input_matrix(num_rows, num_cols, matrix_data);
//
//  bool in_data[num_rows][num_cols] = {
//      {true, false, false, true, false, false, true},
//      {true, false, false, true, false, false, false},
//      {false, false, false, true, true, false, true},
//      {false, false, true, false, true, true, false},
//      {false, true, true, false, false, true, true},
//      {false, true, false, false, false, false, true},
//      {true, false, false, true, false, false, false}
//  };
//
//  for (int i = 0; i < num_rows; i++) {
//    input_matrix.set_row(in_data[i], i);
//  }
//
//  std::cout << "Input matrix looks like:" << std::endl;
//  input_matrix.display();
//
//  ExactCoverSolver solver(input_matrix);
//
//  solver.search(0);
//
//  solver.print_solution();


  return 0;
}