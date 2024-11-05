#include <iostream>
#include <string>
#include <vector>

struct MinHeap {
  std::vector<int> heap;
  void ExtractMin() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    SiftDown(0);
  }

  int GetMin() { return heap[0]; }

  void Add(long long value) {
    heap.push_back(value);
    SiftUp(heap.size() - 1);
  }

  void SiftDown(int index) {
    int size = heap.size();
    if (2 * index > size - 1) {
      return;
    }
    int u = 2 * index;
    if (u + 1 < size && heap[u + 1] < heap[u]) {
      ++u;
    }
    if (heap[index] > heap[u]) {
      std::swap(heap[u], heap[index]);
      SiftDown(u);
    }
  }
  void SiftUp(int index) {
    if (index == 0) {
      return;
    }
    int p = index / 2;
    if (heap[p] > heap[index]) {
      std::swap(heap[p], heap[index]);
      return SiftUp(p);
    }
  }
};

struct MaxHeap {
  std::vector<int> heap;
  void ExtractMax() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    SiftDown(0);
  }

  int GetMax() { return heap[0]; }

  void Add(long long value) {
    heap.push_back(value);
    SiftUp(heap.size() - 1);
  }

  void SiftDown(int index) {
    int size = heap.size();
    if (2 * index > size - 1) {
      return;
    }
    int u = 2 * index;
    if (u + 1 < size && heap[u + 1] > heap[u]) {
      ++u;
    }
    if (heap[index] < heap[u]) {
      std::swap(heap[u], heap[index]);
      SiftDown(u);
    }
  }
  void SiftUp(int index) {
    if (index == 0) {
      return;
    }
    int p = index / 2;
    if (heap[p] < heap[index]) {
      std::swap(heap[p], heap[index]);
      return SiftUp(p);
    }
  }
};

struct MinMaxHeap {
  MinHeap min_heap;
  MaxHeap max_heap;
  MinHeap min_delete;
  MaxHeap max_delete;
  int size = 0;

  void Insert(long long value) {
    min_heap.Add(value);
    max_heap.Add(value);
    std::cout << "ok\n";
    ++size;
  }

  void Size() const { std::cout << size << "\n"; }

  void DeleteMin() {
    if (size == 0) {
      std::cout << "error\n";
    } else {
      while (!min_heap.heap.empty() && !min_delete.heap.empty()) {
        if (min_heap.GetMin() == min_delete.GetMin()) {
          min_heap.ExtractMin();
          min_delete.ExtractMin();
        } else {
          break;
        }
      }
      std::cout << min_heap.GetMin() << "\n";
      max_delete.Add(min_heap.GetMin());
      min_heap.ExtractMin();
      --size;
    }
  }

  void PrintMin() {
    if (size == 0) {
      std::cout << "error\n";
    } else {
      while (!min_heap.heap.empty() && !min_delete.heap.empty()) {
        if (min_heap.GetMin() == min_delete.GetMin()) {
          min_heap.ExtractMin();
          min_delete.ExtractMin();
        } else {
          break;
        }
      }
      std::cout << min_heap.GetMin() << "\n";
    }
  }

  void PrintMax() {
    if (size == 0) {
      std::cout << "error\n";
    } else {
      while (!max_heap.heap.empty() && !max_delete.heap.empty()) {
        if (max_heap.GetMax() == max_delete.GetMax()) {
          max_heap.ExtractMax();
          max_delete.ExtractMax();
        } else {
          break;
        }
      }
      std::cout << max_heap.GetMax() << "\n";
    }
  }

  void Clear() {
    while (!max_heap.heap.empty()) {
      max_heap.ExtractMax();
    }
    while (!min_delete.heap.empty()) {
      min_delete.ExtractMin();
    }
    while (!min_heap.heap.empty()) {
      min_heap.ExtractMin();
    }
    while (!max_delete.heap.empty()) {
      max_delete.ExtractMax();
    }
    size = 0;
    std::cout << "ok\n";
  }
  void DeleteMax() {
    if (size == 0) {
      std::cout << "error\n";
    } else {
      while (!max_heap.heap.empty() && !max_delete.heap.empty()) {
        if (max_heap.GetMax() == max_delete.GetMax()) {
          max_heap.ExtractMax();
          max_delete.ExtractMax();
        } else {
          break;
        }
      }
      min_delete.Add(max_heap.GetMax());
      std::cout << max_heap.GetMax() << "\n";
      max_heap.ExtractMax();
      --size;
    }
  }
};

void PrintSolution(MinMaxHeap& heap) {
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "insert") {
    long long x;
    std::cin >> x;
    heap.Insert(x);
  } else if (tmp == "get_min") {
    heap.PrintMin();
  } else if (tmp == "extract_min") {
    heap.DeleteMin();
  } else if (tmp == "extract_max") {
    heap.DeleteMax();
  } else if (tmp == "get_max") {
    heap.PrintMax();
  } else if (tmp == "size") {
    heap.Size();
  } else if (tmp == "clear") {
    heap.Clear();
  }
}

int main() {
  MinMaxHeap heap;
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    PrintSolution(heap);
  }
}
