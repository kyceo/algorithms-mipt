// реализовать структуру данных, которая поддерживает операции insert,
// extract_min, get_min extract_max, get_max, size, clear

#include <iostream>
#include <string>
#include <vector>

class MinHeap {
 public:
  void ExtractMin();
  int64_t GetMin() const { return heap_[0]; }
  int64_t GetSize() const { return heap_.size(); }
  void Insert(int64_t value);

 private:
  std::vector<int64_t> heap_;
  void SiftDown(int64_t index);
  void SiftUp(int64_t index);
};

void MinHeap::ExtractMin() {
  std::swap(heap_[0], heap_[heap_.size() - 1]);
  heap_.pop_back();
  SiftDown(0);
}

void MinHeap::Insert(int64_t value) {
  heap_.push_back(value);
  SiftUp(heap_.size() - 1);
}

void MinHeap::SiftDown(int64_t index) {
  int64_t size = heap_.size();
  if (2 * index > size - 1) {
    return;
  }
  int child = 2 * index;
  if (child + 1 < size && heap_[child + 1] < heap_[child]) {
    ++child;
  }
  if (heap_[index] > heap_[child]) {
    std::swap(heap_[child], heap_[index]);
    SiftDown(child);
  }
}

void MinHeap::SiftUp(int64_t index) {
  if (index == 0) {
    return;
  }
  int64_t parent = index / 2;
  if (heap_[parent] > heap_[index]) {
    std::swap(heap_[parent], heap_[index]);
    return SiftUp(parent);
  }
}

class MaxHeap {
 public:
  void ExtractMax();
  int64_t GetMax() const { return heap_[0]; }
  int64_t GetSize() const { return heap_.size(); }
  void Insert(int64_t value);

 private:
  std::vector<int> heap_;
  void SiftDown(int64_t index);
  void SiftUp(int64_t index);
};

void MaxHeap::ExtractMax() {
  std::swap(heap_[0], heap_[heap_.size() - 1]);
  heap_.pop_back();
  SiftDown(0);
}

void MaxHeap::Insert(int64_t value) {
  heap_.push_back(value);
  SiftUp(heap_.size() - 1);
}

void MaxHeap::SiftDown(int64_t index) {
  int64_t size = heap_.size();
  if (2 * index > size - 1) {
    return;
  }
  int64_t child = 2 * index;
  if (child + 1 < size && heap_[child + 1] > heap_[child]) {
    ++child;
  }
  if (heap_[index] < heap_[child]) {
    std::swap(heap_[child], heap_[index]);
    SiftDown(child);
  }
}

void MaxHeap::SiftUp(int64_t index) {
  if (index == 0) {
    return;
  }
  int64_t parent = index / 2;
  if (heap_[parent] < heap_[index]) {
    std::swap(heap_[parent], heap_[index]);
    return SiftUp(parent);
  }
}

class MinMaxHeap {
 public:
  void Insert(int64_t value);
  size_t Size() const { return size_; }
  void ExtractMin();
  void GetMin();
  void ExtractMax();
  void GetMax();
  void Clear();

 private:
  MinHeap min_heap_;
  MaxHeap max_heap_;
  MinHeap min_delete_;
  MaxHeap max_delete_;
  size_t size_ = 0;
};

void MinMaxHeap::Insert(int64_t value) {
  min_heap_.Insert(value);
  max_heap_.Insert(value);
  ++size_;
}

void MinMaxHeap::ExtractMin() {
  if (size_ == 0) {
    std::cout << "error\n";
  } else {
    while (min_heap_.GetSize() != 0 && min_delete_.GetSize() != 0) {
      if (min_heap_.GetMin() == min_delete_.GetMin()) {
        min_heap_.ExtractMin();
        min_delete_.ExtractMin();
      } else {
        break;
      }
    }
    std::cout << min_heap_.GetMin() << "\n";
    max_delete_.Insert(min_heap_.GetMin());
    min_heap_.ExtractMin();
    --size_;
  }
}

void MinMaxHeap::GetMin() {
  if (size_ == 0) {
    std::cout << "error\n";
  } else {
    while (min_heap_.GetSize() != 0 && min_delete_.GetSize() != 0) {
      if (min_heap_.GetMin() == min_delete_.GetMin()) {
        min_heap_.ExtractMin();
        min_delete_.ExtractMin();
      } else {
        break;
      }
    }
    std::cout << min_heap_.GetMin() << "\n";
  }
}

void MinMaxHeap::ExtractMax() {
  if (size_ == 0) {
    std::cout << "error\n";
  } else {
    while (max_heap_.GetSize() != 0 && max_delete_.GetSize() != 0) {
      if (max_heap_.GetMax() == max_delete_.GetMax()) {
        max_heap_.ExtractMax();
        max_delete_.ExtractMax();
      } else {
        break;
      }
    }
    min_delete_.Insert(max_heap_.GetMax());
    std::cout << max_heap_.GetMax() << "\n";
    max_heap_.ExtractMax();
    --size_;
  }
}

void MinMaxHeap::GetMax() {
  if (size_ == 0) {
    std::cout << "error\n";
  } else {
    while (max_heap_.GetSize() != 0 && max_delete_.GetSize() != 0) {
      if (max_heap_.GetMax() == max_delete_.GetMax()) {
        max_heap_.ExtractMax();
        max_delete_.ExtractMax();
      } else {
        break;
      }
    }
    std::cout << max_heap_.GetMax() << "\n";
  }
}

void MinMaxHeap::Clear() {
  while (max_heap_.GetSize() != 0) {
    max_heap_.ExtractMax();
  }
  while (min_delete_.GetSize() != 0) {
    min_delete_.ExtractMin();
  }
  while (min_heap_.GetSize() != 0) {
    min_heap_.ExtractMin();
  }
  while (max_delete_.GetSize() != 0) {
    max_delete_.ExtractMax();
  }
  size_ = 0;
}

void ProcessTheRequest(MinMaxHeap& heap) {
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "insert") {
    int64_t x;
    std::cin >> x;
    heap.Insert(x);
    std::cout << "ok\n";
  } else if (tmp == "get_min") {
    heap.GetMin();
  } else if (tmp == "extract_min") {
    heap.ExtractMin();
  } else if (tmp == "extract_max") {
    heap.ExtractMax();
  } else if (tmp == "get_max") {
    heap.GetMax();
  } else if (tmp == "size") {
    std::cout << heap.Size() << '\n';
  } else if (tmp == "clear") {
    heap.Clear();
    std::cout << "ok\n";
  }
}

int main() {
  MinMaxHeap heap;
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    ProcessTheRequest(heap);
  }
}