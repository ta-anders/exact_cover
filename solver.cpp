//
// Created by tom on 20/03/18.
//

#include <iostream>
#include "vector"
#include "solver.h"

void ExactCoverSolver::search(int k) {
  NodeId root = dlx_matrix_.get_root();

  if (dlx_matrix_.R(root) == root) {
    solutions_.push_back(solution_stack_);
    return ;
  }

  // Choose column with least 1s
  NodeId col = dlx_matrix_.choose_column();

  // Cover it
  dlx_matrix_.cover(col);

  for (NodeId r = dlx_matrix_.D(col); r != col; r = dlx_matrix_.D(r)) {
    solution_stack_.push_back(r);

    for (NodeId rn = dlx_matrix_.R(r); rn != r; rn = dlx_matrix_.R(rn)) {
      dlx_matrix_.cover(rn);
    }

    search(k + 1);

    solution_stack_.pop_back();
    col = dlx_matrix_.C(r);

    for (NodeId ln = dlx_matrix_.L(r); ln != r; ln = dlx_matrix_.L(ln)) {
      dlx_matrix_.uncover(ln);
    }
  }

  dlx_matrix_.uncover(col);
}

void ExactCoverSolver::print_solution() {
  std::vector< std::vector<NodeId> >::iterator row;
  std::vector<NodeId >::iterator col;

  for (row = solutions_.begin(); row != solutions_.end(); row++) {
    for (col = row->begin(); col != row->end(); col++) {
      std::cout << dlx_matrix_.get_row(*col) << " ";
    }

    std::cout << "\n";
  }
}