// необходимо реализовать структуру, которая сможет отвечать
// по заданным l, r, x, y находить количество элементов на отрезке массива с l-й
// по r-ю позицию, значения которых лежат в отрезке [x,y].

#include <algorithm>
#include <iostream>
#include <vector>
class SegmentTree {
 public:
  int FindLessThan(int index, int l, int r, int tl, int tr, int x);
  SegmentTree(const std::vector<int>& vec) : st_(4 * vec.size()) {
    Build(vec, 0, vec.size() - 1);
  }

 private:
  std::vector<std::vector<int>> st_;
  void Merge(const std::vector<int>& left, const std::vector<int>& right,
             int index);
  void Build(const std::vector<int>& vec, int l, int r, int index = 0);
};

int SegmentTree::FindLessThan(int index, int l, int r, int tl, int tr, int x) {
  if (tl >= l && tr <= r) {
    return std::upper_bound(st_[index].begin(), st_[index].end(), x) -
           st_[index].begin();
  }
  if (tl > r || tr < l) {
    return 0;
  }
  int tm = (tl + tr) / 2;
  return FindLessThan(2 * index + 1, l, r, tl, tm, x) +
         FindLessThan(2 * index + 2, l, r, tm + 1, tr, x);
}

void SegmentTree::Merge(const std::vector<int>& left,
                        const std::vector<int>& right, int index) {
  int left_size = left.size();
  int right_size = right.size();
  int i = 0;
  int j = 0;
  while (i < left_size || j < right_size) {
    if (j == right_size || (i < left_size && (left[i] <= right[j]))) {
      st_[index].push_back(left[i]);
      ++i;
    } else {
      st_[index].push_back(right[j]);
      ++j;
    }
  }
}
void SegmentTree::Build(const std::vector<int>& vec, int l, int r, int index) {
  if (l == r) {
    st_[index].push_back(vec[l]);
    return;
  }
  int m = (l + r) / 2;
  Build(vec, l, m, 2 * index + 1);
  Build(vec, m + 1, r, 2 * index + 2);
  Merge(st_[2 * index + 1], st_[2 * index + 2], index);
}

int main() {
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  SegmentTree st(vec);
  for (int i = 0; i < q; ++i) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    --l, --r;
    std::cout << st.FindLessThan(0, l, r, 0, n - 1, y) -
                     st.FindLessThan(0, l, r, 0, n - 1, x - 1)
              << "\n";
  }
}