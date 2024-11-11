#include <algorithm>
#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& left,
           std::vector<std::pair<int, int>>& right,
           std::vector<std::pair<int, int>>& vec) {
  int left_size = left.size();
  int right_size = right.size();
  int index = 0;
  int i = 0;
  int j = 0;
  while (i < left_size || j < right_size) {
    if (j == right_size || (i < left_size && left[i].first <= right[j].first)) {
      vec[index].first = left[i].first;
      vec[index].second = left[i].second;
      ++i;
    } else {
      vec[index].first = right[j].first;
      vec[index].second = right[j].second;
      ++j;
    }
    ++index;
  }
}

void MergeSort(std::vector<std::pair<int, int>>& vec) {
  if (vec.size() == 1) {
    return;
  }
  int n = vec.size();
  std::vector<std::pair<int, int>> left;
  std::vector<std::pair<int, int>> right;
  int i = 0;
  while (i < n / 2) {
    left.push_back({vec[i].first, vec[i].second});
    ++i;
  }
  while (i < n) {
    right.push_back({vec[i].first, vec[i].second});
    ++i;
  }
  MergeSort(left);
  MergeSort(right);
  Merge(left, right, vec);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i].first >> vec[i].second;
  }
  MergeSort(vec);
  std::vector<std::pair<int, int>> ans;
  ans.push_back(vec[0]);
  int index = 0;
  for (int i = 1; i < n; ++i) {
    if (ans[index].second >= vec[i].first) {
      ans[index].second = std::max(ans[index].second, vec[i].second);
    }
    if (ans[index].second < vec[i].first) {
      ans.push_back(vec[i]);
      index++;
    }
  }
  std::cout << ans.size() << '\n';
  int ans_size = ans.size();
  for (int i = 0; i < ans_size; ++i) {
    std::cout << ans[i].first << " " << ans[i].second << '\n';
  }
}
