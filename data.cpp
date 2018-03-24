#include <ctime>
#include <iostream>
#include "data.h"

// Constructor
DLXMatrix::DLXMatrix(const ExactCoverInputMatrix &input_matrix, int num_cols)
{
  clock_t start = clock();
  NodeId root_id = CreateNewNode(-1, -1);

  auto num_rows = input_matrix.size();

  list_headers_.reserve(num_cols);
  column_sizes_.reserve(num_cols);
  // Create list headers
  for (int i = 0; i < num_cols; i++)
  {
    NodeId n = CreateNewNode(-1, i);
    list_headers_.push_back(n);
    column_sizes_.push_back(0);

    nodes_[n].right = root_id;
    nodes_[n].left = L(root_id);
    nodes_[L(root_id)].right = n;
    nodes_[root_id].left = n;
  }

  for (int i = 0; i < num_rows; i++)
  {
    NodeId first_non_zero = 0;
    for (auto &j : input_matrix[i])
    {
      NodeId list_header = list_headers_[j];
      NodeId n = CreateNewNode(i, j);
      nodes_[n].down = list_header;
      nodes_[n].up = U(list_header);
      nodes_[U(list_header)].down = n;
      nodes_[list_header].up = n;

      column_sizes_[j] += 1;

      if (first_non_zero == 0)
      {
        first_non_zero = n;
      }
      else
      {
        nodes_[n].right = first_non_zero;
        nodes_[n].left = L(first_non_zero);
        nodes_[L(first_non_zero)].right = n;
        nodes_[first_non_zero].left = n;
      }
    }
  }

  clock_t end = clock();

  double time_spent = (double) (end - start) / CLOCKS_PER_SEC;

  std::cout << "Finished creating DLX matrix with "
            << id_count_
            << " nodes, took "
            << time_spent
            << " seconds\n";
}

// Node creation
NodeId DLXMatrix::CreateNewNode(int row_ind, int col_ind)
{
  Node new_node(id_count_, row_ind, col_ind);
  nodes_.push_back(new_node);
  id_count_++;

  return new_node.id;
}

// Column operations. Pretty much direct copies from Knuth's paper.
void DLXMatrix::Cover(NodeId id)
{
  NodeId col_node = C(id);

  // Remove link for this column header to its neighbours
  nodes_[L(col_node)].right = R(col_node);
  nodes_[R(col_node)].left = L(col_node);

  for (NodeId r = D(col_node); r != col_node; r = D(r))
  {
    for (NodeId rn = R(r); rn != r; rn = R(rn))
    {
      nodes_[U(rn)].down = D(rn);
      nodes_[D(rn)].up = U(rn);

      // Decrement the number of ones in this column
      column_sizes_[nodes_[rn].col_ind] -= 1;
    }
  }
}

void DLXMatrix::Uncover(NodeId id)
{
  NodeId col_node = C(id);

  for (NodeId r = U(col_node); r != col_node; r = U(r))
  {
    for (NodeId rn = L(r); rn != r; rn = L(rn))
    {
      nodes_[U(rn)].down = rn;
      nodes_[D(rn)].up = rn;

      // Increment the number of ones in this column
      column_sizes_[nodes_[rn].col_ind] += 1;
    }
  }

  // Link this column header back to its neighbours
  nodes_[L(col_node)].right = col_node;
  nodes_[R(col_node)].left = col_node;
}

NodeId DLXMatrix::ChooseColumn()
{
  NodeId root = get_root();

  NodeId best = R(root);
  for (NodeId i = R(root); i != root; i = R(i))
  {
    if (S(i) < S(best))
    {
      best = i;
    }
  }

  return best;
}