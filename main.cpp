#include <iostream>
#include "solver.h"

int main()
{
  const InputMatrix input_matrix = {
      {false, false, true, false, true, true, false},
      {true, false, false, true, false, false, true},
      {false, true, true, false, false, true, false},
      {true, false, false, true, false, false, false},
      {false, true, false, false, false, false, true},
      {false, false, false, true, true, false, true}
  };

  solve_exact_cover_problem(input_matrix);

  const InputMatrix input_matrix_2 = {
      {true, false, false, true, false, false, true},
      {true, false, false, true, false, false, false},
      {false, false, false, true, true, false, true},
      {false, false, true, false, true, true, false},
      {false, true, true, false, false, true, true},
      {false, true, false, false, false, false, true},
      {true, false, false, true, false, false, false}
  };

  solve_exact_cover_problem(input_matrix_2);


  return 0;
}