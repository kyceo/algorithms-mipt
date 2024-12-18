// в этой задаче надо реализовать структуру, которая сможет по логину выдавать
// пароль и наоборот

#include <algorithm>
#include <iostream>
#include <vector>

class Map {
 public:
  void Insert(std::string key, std::string value) { Insert(root_, key, value); }
  bool IsPresent(std::string key) { return IsPresent(root_, key); }
  std::string LowerBound(std::string key) { return LowerBound(root_, key); }
  Map() : root_(nullptr) {}
  ~Map() { delete root_; }

 private:
  struct Node {
    static size_t GetDepth(const Node* node);
    int64_t GetDelta() const;
    void UpdateDepth();
    void TurnRight();
    void TurnLeft();
    void Balance();

    std::string key;
    std::string value;
    size_t depth;
    Node* left;
    Node* right;

    Node(std::string key, std::string value)
        : key(key), value(value), depth(1), left(nullptr), right(nullptr) {}
    ~Node() {
      delete left;
      delete right;
    }
  };

  void Insert(Node*& node, std::string key, std::string value);
  bool IsPresent(const Node* node, std::string key) const;
  std::string LowerBound(const Node* node, std::string key) const;
  Node* root_;
};

size_t Map::Node::GetDepth(const Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->depth;
}

int64_t Map::Node::GetDelta() const { return GetDepth(left) - GetDepth(right); }

void Map::Node::UpdateDepth() {
  depth = std::max(GetDepth(left), GetDepth(right)) + 1;
}

void Map::Node::TurnLeft() {
  std::swap(key, right->key);
  std::swap(value, right->value);
  std::swap(right, left);
  std::swap(left->right, right);
  std::swap(left->right, left->left);
  left->UpdateDepth();
  UpdateDepth();
}

void Map::Node::TurnRight() {
  std::swap(key, left->key);
  std::swap(value, left->value);
  std::swap(left, right);
  std::swap(right->left, left);
  std::swap(right->right, right->left);
  right->UpdateDepth();
  UpdateDepth();
}

void Map::Node::Balance() {
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

void Map::Insert(Node*& node, std::string key, std::string value) {
  if (root_ == nullptr) {
    root_ = new Node(key, value);
    return;
  }
  if (node == nullptr) {
    node = new Node(key, value);
    return;
  }
  if (node->key == key) {
    return;
  }
  if (key < node->key) {
    Insert(node->left, key, value);
  } else {
    Insert(node->right, key, value);
  }
  node->UpdateDepth();
  node->Balance();
}

bool Map::IsPresent(const Node* node, std::string key) const {
  if (node == nullptr) {
    return false;
  }
  if (node->key == key) {
    return true;
  }
  if (key < node->key) {
    return IsPresent(node->left, key);
  }
  return IsPresent(node->right, key);
}

std::string Map::LowerBound(const Node* node, std::string key) const {
  if (node == nullptr) {
    return " ";
  }
  if (node->key >= key) {
    std::string left_result = LowerBound(node->left, key);
    if (left_result == " ") {
      return node->value;
    }
    return left_result;
  }
  return LowerBound(node->right, key);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  Map login_password;
  Map password_login;
  for (int i = 0; i < n; ++i) {
    std::string login;
    std::string password;
    std::cin >> login >> password;
    login_password.Insert(login, password);
    password_login.Insert(password, login);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string key;
    std::cin >> key;
    if (login_password.IsPresent(key)) {
      std::cout << login_password.LowerBound(key) << '\n';
    } else {
      std::cout << password_login.LowerBound(key) << '\n';
    }
  }
}