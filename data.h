//
// Created by tom on 18/03/18.
//

#ifndef SODOKU_DATA_H
#define SODOKU_DATA_H

#include <vector>
#include <array>

typedef unsigned int NodeId;

// Little data container to encapsulate a 2D 0-1 matrix.
// Stores all values in a flat chunk, where each row is essentially shifted down by the number of columns.
// I.e the second row starts at index num_columns, the third at 2 * num_columns and so on.
class InputMatrix
{
 private:
  int num_rows_;
  int num_cols_;
  bool *data_;

 public:
  InputMatrix(int num_rows, int num_cols, bool *data);

  ~InputMatrix() { delete[] data_; };

  bool lookup(int row, int col) const;

  void set(int row, int col, bool val);
  void set_row(bool *row_vals, int row);
  void display();

  int get_num_rows() const { return num_rows_; }
  int get_num_cols() const { return num_cols_; }
};

struct Node {
 public:
  NodeId id;
  NodeId left;
  NodeId right;
  NodeId up;
  NodeId down;
  int row_ind;
  int col_ind;

  // Convenience constructor that sets a node to point to itself
  Node(NodeId id_, int row_ind_, int col_ind_)
    : col_ind(col_ind_), row_ind(row_ind_), id(id_),
      left(id_), right(id_), up(id_), down(id_)
  {
  }
};

class DLXMatrix
{
 private:
  std::vector<unsigned int> column_sizes_;
  std::vector<Node> nodes_;
  std::vector<NodeId> list_headers_;
  NodeId id_count_ = 0;

  NodeId create_new_node(int row_ind, int col_ind);

 public:
  explicit DLXMatrix(const InputMatrix &input);

  int get_row(NodeId id) { return nodes_[id].row_ind; };

  NodeId get_root() { return 0; };
  NodeId L(NodeId id) { return nodes_[id].left ; };
  NodeId R(NodeId id) { return nodes_[id].right ; };
  NodeId U(NodeId id) { return nodes_[id].up ; };
  NodeId D(NodeId id) { return nodes_[id].down ; };
  NodeId C(NodeId id) { return list_headers_[nodes_[id].col_ind]; }
  NodeId S(NodeId id) { return column_sizes_[nodes_[id].col_ind]; };

  NodeId choose_column();
  void cover(NodeId id);
  void uncover(NodeId id);

};

#endif
