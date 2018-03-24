#pragma once
#include "data.h"

class ExactCoverSolver
{
 public:
  explicit ExactCoverSolver(const ExactCoverInputMatrix &input_matrix, int num_cols)
      : dlx_matrix_(input_matrix, num_cols) {}

  void Search(int k);
  void PrintSolution();

 private:
  DLXMatrix dlx_matrix_;
  // Temporary store for selected rows in current partial solution
  std::vector<NodeId> solution_stack_;
  // Final store of any solutions found through the process
  std::vector<std::vector<NodeId> > solutions_;
};

void SolveExactCoverProblem(const ExactCoverInputMatrix &input_matrix, int num_cols);
