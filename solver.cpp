#include <iostream>
#include "solver.h"

void ExactCoverSolver::Search(int k)
{
  NodeId root = dlx_matrix_.get_root();

  if (dlx_matrix_.R(root) == root)
  {
    solutions_.push_back(solution_stack_);
    return;
  }

  // Choose column with least 1s
  NodeId col = dlx_matrix_.ChooseColumn();

  // Cover it
  dlx_matrix_.Cover(col);

  for (NodeId r = dlx_matrix_.D(col); r != col; r = dlx_matrix_.D(r))
  {
    solution_stack_.push_back(dlx_matrix_.get_row(r));

    for (NodeId rn = dlx_matrix_.R(r); rn != r; rn = dlx_matrix_.R(rn))
    {
      dlx_matrix_.Cover(rn);
    }

    Search(k + 1);

    solution_stack_.pop_back();
    col = dlx_matrix_.C(r);

    for (NodeId ln = dlx_matrix_.L(r); ln != r; ln = dlx_matrix_.L(ln))
    {
      dlx_matrix_.Uncover(ln);
    }
  }

  dlx_matrix_.Uncover(col);
}

void ExactCoverSolver::Solve()
{
  std::cout << "Starting solver..." << std::endl;

  clock_t start = clock();

  Search(0);

  clock_t end = clock();
  double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
  std::cout << "Finished solving in " << time_spent << " seconds, printing solution\n";
  PrintSolution();
}


void ExactCoverSolver::PrintSolution()
{
  for (auto &sol : solutions_)
  {
    for (auto &row : sol)
    {
      std::cout << row << " ";
    }

    std::cout << "\n";
  }
}
