#include <iostream>
#include <vector>

int Partition(std::vector<int>& vec, int l, int r) {
  int pivot = vec[r];
  int i = l;
  for (int j = l; j < r; ++j) {
    if (vec[j] <= pivot) {
      std::swap(vec[i], vec[j]);
      ++i;
    }
  }
  std::swap(vec[i], vec[r]);
  return i;
}

int QuickSelect(std::vector<int>& vec, int l, int r, int k) {
  while (l <= r) {
    int pivot_index = Partition(vec, l, r);
    if (pivot_index == k) {
      return vec[pivot_index];
    }
    if (pivot_index > k) {
      r = pivot_index - 1;
    } else {
      l = pivot_index + 1;
    }
  }
  return -1;
}

int main() {
  int n;
  int k;
  std::cin >> n;
  std::vector<int> vec(n);
  std::cin >> k >> vec[0] >> vec[1];
  --k;
  const int cInf = 1e7;
  const int c1 = 123;
  const int c2 = 45;
  const int c3 = 4321;
  for (int i = 2; i < n; ++i) {
    vec[i] = (vec[i - 1] * c1 + vec[i - 2] * c2) % (cInf + c3);
  }
  std::cout << QuickSelect(vec, 0, n - 1, k);
}