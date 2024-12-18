// в этой задаче надо реализовать структуру, которая будет отвечать на запросы
// lowerbound, insert за O(logn)

#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 1e9;

class Set {
 public:
  void Insert(int64_t value) { Insert(root_, value); }
  int64_t LowerBound(int64_t value) { return LowerBound(root_, value); }

  Set() : root_(nullptr) {}
  ~Set() { delete root_; }

 private:
  struct Node {
    static size_t GetDepth(const Node* node);
    int64_t GetDelta() const;
    void UpdateDepth();
    void TurnRight();
    void TurnLeft();
    void Balance();

    int64_t value;
    size_t depth;
    Node* left;
    Node* right;

    Node(int64_t value)
        : value(value), depth(1), left(nullptr), right(nullptr) {}
    ~Node() {
      delete left;
      delete right;
    }
  };

  Node* root_;
  void Insert(Node*& node, int64_t value);
  int64_t LowerBound(const Node* node, int64_t value) const;
};

size_t Set::Node::GetDepth(const Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->depth;
}

int64_t Set::Node::GetDelta() const { return GetDepth(left) - GetDepth(right); }

void Set::Node::UpdateDepth() {
  depth = std::max(GetDepth(left), GetDepth(right)) + 1;
}

void Set::Node::TurnLeft() {
  std::swap(value, right->value);
  std::swap(right, left);
  std::swap(left->right, right);
  std::swap(left->right, left->left);
  left->UpdateDepth();
  UpdateDepth();
}

void Set::Node::TurnRight() {
  std::swap(value, left->value);
  std::swap(left, right);
  std::swap(right->left, left);
  std::swap(right->right, right->left);
  right->UpdateDepth();
  UpdateDepth();
}

void Set::Node::Balance() {
  int64_t delta = GetDelta();
  if (delta == -2) {
    if (right->GetDelta() <= 0) {
      TurnLeft();
    } else {
      right->TurnRight();
      TurnLeft();
    }
  }
  if (delta == 2) {
    if (left->GetDelta() >= 0) {
      TurnRight();
    } else {
      left->TurnLeft();
      TurnRight();
    }
  }
}

void Set::Insert(Node*& node, int64_t value) {
  if (node == nullptr) {
    node = new Node(value);
    return;
  }
  if (node->value == value) {
    return;
  }
  if (value < node->value) {
    Insert(node->left, value);
  } else {
    Insert(node->right, value);
  }
  node->UpdateDepth();
  node->Balance();
}

int64_t Set::LowerBound(const Node* node, int64_t value) const {
  if (node == nullptr) {
    return -1;
  }
  if (node->value >= value) {
    int64_t left_result = LowerBound(node->left, value);
    if (left_result == -1) {
      return node->value;
    }
    return left_result;
  }
  return LowerBound(node->right, value);
}

void ProcessTheQuery(Set& st, int64_t& tmp, bool& flag) {
  char command;
  int64_t value;
  std::cin >> command >> value;
  if (command == '+') {
    if (flag) {
      st.Insert((value + tmp) % cInf);
      flag = false;
    } else {
      st.Insert(value);
    }
  } else {
    tmp = st.LowerBound(value);
    flag = true;
    std::cout << tmp << '\n';
  }
}

int main() {
  int q;
  std::cin >> q;
  Set st;
  bool flag = false;
  int64_t tmp;
  for (int i = 0; i < q; ++i) {
    ProcessTheQuery(st, tmp, flag);
  }
}