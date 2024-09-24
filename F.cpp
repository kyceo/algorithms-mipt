#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  int m;
  int l;
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
    int i;
    int j;
    std::cin >> i >> j;
    --i;
    --j;
    int left = 0;
    int right = l - 1;
    int ans = l - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nmatrix[i][mid] >= mmatrix[j][mid]) {
        right = mid - 1;
        ans = mid;
      } else {
        left = mid + 1;
      }
    }
    std::cout << (ans > 0
                      ? nmatrix[i][ans] < mmatrix[j][ans - 1] ? ans + 1 : ans
                      : ans + 1)
              << '\n';
  }
}