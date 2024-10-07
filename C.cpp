#include <stdint.h>

#include <cmath>
#include <iostream>
#include <vector>
const int cInf = 64;
void RadixSort(std::vector<uint64_t>& vec) {
  for (int i = 0; i < cInf; ++i) {
    std::vector<std::vector<uint64_t>> b(2);
    long long p = std::pow(2, i);
    for (uint64_t t : vec) {
      b[(t / p) % 2].push_back(t);
    }
    int index = 0;
    for (int j = 0; j < 2; ++j) {
      for (size_t k = 0; k < b[j].size(); ++k) {
        vec[index] = b[j][k];
        ++index;
      }
    }
  }
  for (auto t : vec) {
    std::cout << t << " ";
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  RadixSort(vec);
}
