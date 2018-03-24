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

  SolveExactCoverProblem(input_matrix, num_cols);

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

  SolveExactCoverProblem(input_matrix_2, num_cols_2);

  return 0;
}