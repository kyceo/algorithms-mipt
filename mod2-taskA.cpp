#include <iostream>
#include <string>
#include <vector>
int j = 0;

struct Heap {
  std::vector<std::pair<long long, long long>> heap;
  static const int cInf = 1e6;
  long long queries[cInf];
  void ExtractMin() {
    std::swap(queries[heap[0].second], queries[heap[heap.size() - 1].second]);
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(int query_index, long long delta) {
    --query_index;
    heap[queries[query_index]].first -= delta;
    SiftUp(queries[query_index]);
  }

  void GetMin() { std::cout << heap[0].first << '\n'; }

  void Insert(long long value) {
    heap.push_back({value, j});
    queries[j] = heap.size() - 1;
    SiftUp(heap.size() - 1);
  }

  void SiftDown(int index) {
    int size = heap.size();
    if (2 * index > size - 1) {
      return;
    }
    int u = 2 * index;
    if (u + 1 < size && heap[u + 1].first < heap[u].first) {
      ++u;
    }
    if (heap[index].first > heap[u].first) {
      std::swap(queries[heap[u].second], queries[heap[index].second]);
      std::swap(heap[u], heap[index]);
      SiftDown(u);
    }
  }
  void SiftUp(int index) {
    if (index == 0) {
      return;
    }
    int p = index / 2;
    if (heap[p].first > heap[index].first) {
      std::swap(queries[heap[p].second], queries[heap[index].second]);
      std::swap(heap[p], heap[index]);
      return SiftUp(p);
    }
  }
};

void PrintSolution(Heap& heap, std::string tmp) {
  if (tmp == "insert") {
    long long x;
    std::cin >> x;
    heap.Insert(x);
  } else if (tmp == "getMin") {
    heap.GetMin();
  } else if (tmp == "extractMin") {
    heap.ExtractMin();
  } else if (tmp == "decreaseKey") {
    int query_index;
    long long delta;
    std::cin >> query_index >> delta;
    heap.DecreaseKey(query_index, delta);
  }
  ++j;
}

int main() {
  int q;
  std::cin >> q;
  std::string tmp;
  Heap heap;
  for (int i = 0; i < q; ++i) {
    std::cin >> tmp;
    PrintSolution(heap, tmp);
  }
}
