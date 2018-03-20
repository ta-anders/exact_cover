#pragma once
#include "data.h"

class ExactCoverSolver
{
 public:
  explicit ExactCoverSolver(const InputMatrix &input_matrix)
    : dlx_matrix_(input_matrix)
  {}

  void search(int k);
  void print_solution();

 private:
  DLXMatrix dlx_matrix_;
  // Temporary store for selected rows in current partial solution
  std::vector<NodeId> solution_stack_;
  // Final store of any solutions found through the process
  std::vector< std::vector<NodeId> > solutions_;
};

void solve_exact_cover_problem(const InputMatrix &input_matrix);
