#include <iostream>
#include <string>
#include <vector>

const int cInf = 1e6;

class Heap {
 public:
  void ExtractMin();
  void DecreaseKey(int query_index, int64_t delta);
  int64_t GetMin() const { return heap_[0].first; }
  void Insert(int64_t value, size_t index);

 private:
  void SiftUp(int index);
  void SiftDown(int index);

  std::vector<std::pair<int64_t, int64_t>> heap_;
  int64_t queries_[cInf];
};

void Heap::ExtractMin() {
  std::swap(queries_[heap_[0].second],
            queries_[heap_[heap_.size() - 1].second]);
  std::swap(heap_[0], heap_[heap_.size() - 1]);
  heap_.pop_back();
  SiftDown(0);
}

void Heap::DecreaseKey(int query_index, int64_t delta) {
  --query_index;
  heap_[queries_[query_index]].first -= delta;
  SiftUp(queries_[query_index]);
}

void Heap::Insert(int64_t value, size_t index) {
  heap_.push_back({value, index});
  queries_[index] = heap_.size() - 1;
  SiftUp(heap_.size() - 1);
}

void Heap::SiftDown(int index) {
  int size = heap_.size();
  if (2 * index > size - 1) {
    return;
  }
  int u = 2 * index;
  if (u + 1 < size && heap_[u + 1].first < heap_[u].first) {
    ++u;
  }
  if (heap_[index].first > heap_[u].first) {
    std::swap(queries_[heap_[u].second], queries_[heap_[index].second]);
    std::swap(heap_[u], heap_[index]);
    SiftDown(u);
  }
}
void Heap::SiftUp(int index) {
  if (index == 0) {
    return;
  }
  int p = index / 2;
  if (heap_[p].first > heap_[index].first) {
    std::swap(queries_[heap_[p].second], queries_[heap_[index].second]);
    std::swap(heap_[p], heap_[index]);
    return SiftUp(p);
  }
}

void ProcessTheRequest(Heap& heap, const std::string& tmp, size_t index) {
  if (tmp == "insert") {
    int64_t x;
    std::cin >> x;
    heap.Insert(x, index);
  } else if (tmp == "getMin") {
    std::cout << heap.GetMin() << '\n';
  } else if (tmp == "extractMin") {
    heap.ExtractMin();
  } else if (tmp == "decreaseKey") {
    int query_index;
    int64_t delta;
    std::cin >> query_index >> delta;
    heap.DecreaseKey(query_index, delta);
  }
}
int main() {
  size_t q;
  std::cin >> q;
  std::string tmp;
  Heap heap;
  for (size_t index = 0; index < q; ++index) {
    std::cin >> tmp;
    ProcessTheRequest(heap, tmp, index);
  }
}