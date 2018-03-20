//
// Created by tom on 18/03/18.
//

#include <ctime>
#include <iostream>
#include "data.h"

// Input matrix

// Constructor
InputMatrix::InputMatrix(int num_rows, int num_cols, bool *data)
  : num_rows_(num_rows), num_cols_(num_cols), data_(data)
{
}

// Lookup data by (row, col)
bool InputMatrix::lookup(int row, int col) const {
  return data_[row * num_cols_ + col];
}

// Set data by (row, col)
void InputMatrix::set(int row, int col, bool val) {
  data_[row * num_cols_ + col] = val;
}

// Set data by entire row
void InputMatrix::set_row(bool *row_vals, int row) {
  for (int i = 0; i < num_cols_; i++) {
    set(row, i, row_vals[i]);
  }
}

// Print a standard representation of the matrix out to console
void InputMatrix::display()
{
  for (int i = 0; i < get_num_rows(); i++) {
    for (int j = 0; j < get_num_cols(); j++) {
      std::cout << lookup(i, j);
    }
    std::cout << "\n";
  }
}

// DLX matrix

// Constructor
DLXMatrix::DLXMatrix(const InputMatrix &input)
{
  clock_t start = clock();
  NodeId root_id = create_new_node(-1, -1);

  int num_cols = input.get_num_cols();
  int num_rows = input.get_num_rows();

  list_headers_.reserve(num_cols);
  column_sizes_.reserve(num_cols);
  // Create list headers
  for (int i = 0; i < num_cols; i++) {
    NodeId n = create_new_node(-1, i);
    list_headers_.push_back(n);
    column_sizes_.push_back(0);

    nodes_[n].right = root_id;
    nodes_[n].left = L(root_id);
    nodes_[L(root_id)].right = n;
    nodes_[root_id].left = n;
  }

  for (int i = 0; i < num_rows; i++) {
    NodeId first_non_zero = 0;
    for (int j = 0; j < num_cols; j++) {
      NodeId list_header = list_headers_[j];
      if (input.lookup(i, j)) {
        NodeId n = create_new_node(i, j);
        nodes_[n].down = list_header;
        nodes_[n].up = U(list_header);
        nodes_[U(list_header)].down = n;
        nodes_[list_header].up = n;

        column_sizes_[j] += 1;

        if (first_non_zero == 0) {
          first_non_zero = n;
        }
        else {
          nodes_[n].right = first_non_zero;
          nodes_[n].left = L(first_non_zero);
          nodes_[L(first_non_zero)].right = n;
          nodes_[first_non_zero].left = n;
        }
      }
    }
  }

  clock_t end = clock();

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  std::printf(
      "Finished creating DLX matrix with %d nodes, took %f seconds\n",
      id_count_,
      time_spent);
}

// Node creation
NodeId DLXMatrix::create_new_node(int row_ind, int col_ind) {
  Node new_node(id_count_, row_ind, col_ind);
  nodes_.push_back(new_node);
  id_count_++;

  return new_node.id;
}

// Column operations. Pretty much direct copies from Knuth's paper.
void DLXMatrix::cover(NodeId id) {

  NodeId col_node = C(id);

  // Remove link for this column header to its neighbours
  nodes_[L(col_node)].right = R(col_node);
  nodes_[R(col_node)].left = L(col_node);

  for (NodeId r = D(col_node); r != col_node; r = D(r)) {
    for (NodeId rn = R(r); rn != r; rn = R(rn)) {
      nodes_[U(rn)].down = D(rn);
      nodes_[D(rn)].up = U(rn);

      // Decrement the number of ones in this column
      column_sizes_[nodes_[rn].col_ind] -= 1;
    }
  }
}

void DLXMatrix::uncover(NodeId id) {
  NodeId col_node = C(id);

  for (NodeId r = U(col_node); r != col_node; r = U(r)) {
    for (NodeId rn = L(r); rn != r; rn = L(rn)) {
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

NodeId DLXMatrix::choose_column() {
  NodeId root = get_root();

  NodeId best = R(root);
  for (NodeId i = R(root); i != root; i = R(i)) {
    if (S(i) < S(best)) {
      best = i;
    }
  }

  return best;

}