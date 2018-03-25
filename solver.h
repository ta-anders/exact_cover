#pragma once
#include "data.h"

typedef std::vector<int> ExactCoverSolution;

class ExactCoverSolver
{
 public:
  explicit ExactCoverSolver(const ExactCoverInputMatrix &input_matrix, int num_cols)
      : dlx_matrix_(input_matrix, num_cols) {}

  void Solve();
  std::vector<ExactCoverSolution> &GetSolutions() { return solutions_; }

 private:
  void Search(int k);
  void PrintSolution();

  DLXMatrix dlx_matrix_;
  // Temporary store for selected rows in current partial solution
  std::vector<int> solution_stack_;
  // Final store of any solutions found through the process
  std::vector<ExactCoverSolution> solutions_;
};
