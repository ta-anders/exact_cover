//
// Created by tom on 20/03/18.
//

#ifndef SODOKU_SOLVER_H
#define SODOKU_SOLVER_H

#include "data.h"
class ExactCoverSolver
{
 private:
  DLXMatrix dlx_matrix_;
  // Temporary store for selected rows in current partial solution
  std::vector<NodeId> solution_stack_;
  // Final store of any solutions found through the process
  std::vector<std::vector<NodeId>> solutions_;

 public:
  explicit ExactCoverSolver(const InputMatrix &input_matrix)
    : dlx_matrix_(input_matrix)
  {
  }

  void search(int k);
  void print_solution();
};


#endif //SODOKU_SOLVER_H
