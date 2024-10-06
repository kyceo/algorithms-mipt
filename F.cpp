#include <algorithm>
#include <iostream>
#include <vector>

int BinarySearch(std::vector<std::vector<int>>& nmatrix,
                 std::vector<std::vector<int>>& mmatrix, int i, int j) {
  int left = 0;
  int right = nmatrix[0].size() - 1;
  int ans = nmatrix[0].size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (nmatrix[i][mid] >= mmatrix[j][mid]) {
      right = mid - 1;
      ans = mid;
    } else {
      left = mid + 1;
    }
  }
  return ans;
}

void PrintAnswer(std::vector<std::vector<int>>& nmatrix,
                 std::vector<std::vector<int>>& mmatrix) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int i;
  int j;
  std::cin >> i >> j;
  --i;
  --j;
  int ans = BinarySearch(nmatrix, mmatrix, i, j);
  std::cout << (ans > 0 ? nmatrix[i][ans] < mmatrix[j][ans - 1] ? ans + 1 : ans
                        : ans + 1)
            << '\n';
}

int main() {
  int n;
  int l;
  int m;
  std::cin >> n >> m >> l;
  std::vector<std::vector<int>> nmatrix(n, std::vector<int>(l));
  std::vector<std::vector<int>> mmatrix(m, std::vector<int>(l));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> nmatrix[i][j];
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> mmatrix[i][j];
    }
  }
  int q;
  std::cin >> q;
  for (int k = 0; k < q; ++k) {
    PrintAnswer(nmatrix, mmatrix);
  }
}
