#include <iostream>
#include "solver.h"

int main()
{
  int num_cols = 7;
  const ExactCoverInputMatrix input_matrix = {
      {2, 4, 5},
      {0, 3, 6},
      {1, 2, 5},
      {0, 3},
      {1, 6},
      {3, 4, 6}
  };

  ExactCoverSolver solver(input_matrix, num_cols);
  solver.Solve();

  int num_cols_2 = 7;
  const ExactCoverInputMatrix input_matrix_2 = {
      {0, 3, 6},
      {0, 3},
      {3, 4, 6},
      {2, 4, 5},
      {1, 2, 5, 6},
      {1, 6},
      {0, 3}
  };

  ExactCoverSolver solver_2(input_matrix_2, num_cols_2);
  solver_2.Solve();

  return 0;
}