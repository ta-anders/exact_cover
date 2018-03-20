#pragma once
#include <vector>

typedef unsigned int NodeId;
typedef std::vector< std::vector<bool> > InputMatrix;

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
  {}
};

class DLXMatrix
{
 public:
  explicit DLXMatrix(const InputMatrix &input_matrix);

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

 private:
  std::vector<unsigned int> column_sizes_;
  std::vector<Node> nodes_;
  std::vector<NodeId> list_headers_;
  NodeId id_count_ = 0;

  NodeId create_new_node(int row_ind, int col_ind);
};
