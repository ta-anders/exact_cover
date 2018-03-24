#include <iostream>
#include "solver.h"

int main()
{
  const ExactCoverInputMatrix input_matrix = {
      {false, false, true, false, true, true, false},
      {true, false, false, true, false, false, true},
      {false, true, true, false, false, true, false},
      {true, false, false, true, false, false, false},
      {false, true, false, false, false, false, true},
      {false, false, false, true, true, false, true}
  };

  SolveExactCoverProblem(input_matrix);

  const ExactCoverInputMatrix input_matrix_2 = {
      {true, false, false, true, false, false, true},
      {true, false, false, true, false, false, false},
      {false, false, false, true, true, false, true},
      {false, false, true, false, true, true, false},
      {false, true, true, false, false, true, true},
      {false, true, false, false, false, false, true},
      {true, false, false, true, false, false, false}
  };

  SolveExactCoverProblem(input_matrix_2);

  return 0;
}