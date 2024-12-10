// в этой задаче необходимо реализовать структуру данных, которая по индексам l,
// r сможет находить вторую порядковую статистику на этом отрезке в массиве

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 public:
  SparseTable(const std::vector<int>& vec);
  int64_t GetMin(int l, int r, bool fl = false);

 private:
  std::vector<std::vector<std::pair<int, int>>> table_;
};

SparseTable::SparseTable(const std::vector<int>& vec)
    : table_(static_cast<int>(log2(vec.size())) + 1) {
  size_t deg = static_cast<int>(log2(vec.size()));
  for (size_t i = 0; i < vec.size(); ++i) {
    table_[0].push_back({vec[i], i});
  }
  for (size_t i = 1; i < deg + 1; ++i) {
    for (size_t j = 0; j < table_[i - 1].size() - std::pow(2, i - 1); ++j) {
      table_[i].push_back(
          std::min(table_[i - 1][j], table_[i - 1][j + std::pow(2, i - 1)]));
    }
  }
}

int64_t SparseTable::GetMin(int l, int r, bool fl) {
  int deg = static_cast<int>(log2(r - l + 1));
  std::pair<int, int> min;
  if (r - l + 1 == std::pow(2, deg)) {
    min = table_[deg][l];
  } else {
    min = std::min(table_[deg][l], table_[deg][r - std::pow(2, deg) + 1]);
  }
  if (fl) {
    return min.first;
  }
  if (min.second - 1 >= l && min.second + 1 <= r) {
    int left = GetMin(l, min.second - 1, true);
    int right = GetMin(min.second + 1, r, true);
    return std::min(left, right);
  }
  if (min.second - 1 >= l) {
    int left = GetMin(l, min.second - 1, true);
    return left;
  }
  int right = GetMin(min.second + 1, r, true);
  return right;
}

int main() {
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  SparseTable table(vec);
  for (int i = 0; i < q; ++i) {
    int r;
    int l;
    std::cin >> l >> r;
    --l;
    --r;
    std::cout << table.GetMin(l, r) << "\n";
  }
}