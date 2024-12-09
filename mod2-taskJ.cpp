// необходимо реализовать структуру данных, которая обрабатывает запросы вида:
// enqueue, dequeue, front, clear, size, min

#include <algorithm>
#include <iostream>
#include <stack>

const int cInf = 1e9 + 2;

class MinStack {
 public:
  void Push(int64_t value);
  void Pop() { stack_.pop(); }
  int64_t GetTop();
  int64_t GetMin();
  int64_t GetSize() { return stack_.size(); }
  void Clear();

 private:
  std::stack<std::pair<int64_t, int64_t>> stack_;
};

void MinStack::Push(int64_t value) {
  if (!stack_.empty()) {
    stack_.push({value, std::min(value, stack_.top().second)});
  } else {
    stack_.push({value, value});
  }
}

int64_t MinStack::GetTop() {
  if (stack_.empty()) {
    return cInf;
  }
  return stack_.top().first;
}

int64_t MinStack::GetMin() {
  if (stack_.empty()) {
    return cInf;
  }
  return stack_.top().second;
}

void MinStack::Clear() {
  while (!stack_.empty()) {
    stack_.pop();
  }
}

class MinQueue {
 public:
  void Enqueue(int64_t value);
  void Dequeue();
  void Clear();
  int64_t GetFront();
  int64_t GetMin() { return std::min(back_.GetMin(), front_.GetMin()); }
  size_t GetSize() const { return size_; };

 private:
  MinStack back_;
  MinStack front_;
  size_t size_ = 0;
};

void MinQueue::Enqueue(int64_t value) {
  back_.Push(value);
  ++size_;
}

void MinQueue::Dequeue() {
  if (front_.GetSize() == 0) {
    while (back_.GetSize() != 0) {
      front_.Push(back_.GetTop());
      back_.Pop();
    }
  }
  if (front_.GetSize() == 0) {
    std::cout << "error\n";
  } else {
    std::cout << front_.GetTop() << '\n';
    front_.Pop();
    --size_;
  }
}

int64_t MinQueue::GetFront() {
  if (front_.GetSize() == 0) {
    while (back_.GetSize() != 0) {
      front_.Push(back_.GetTop());
      back_.Pop();
    }
  }
  return front_.GetTop();
}

void MinQueue::Clear() {
  front_.Clear();
  back_.Clear();
  size_ = 0;
}

void ProcessTheRequest(MinQueue& queue) {
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "enqueue") {
    int64_t value;
    std::cin >> value;
    queue.Enqueue(value);
    std::cout << "ok\n";
  } else if (tmp == "front") {
    int64_t result = queue.GetFront();
    if (result == cInf) {
      std::cout << "error\n";
    } else {
      std::cout << result << '\n';
    }
  } else if (tmp == "dequeue") {
    queue.Dequeue();
  } else if (tmp == "size") {
    std::cout << queue.GetSize() << '\n';
  } else if (tmp == "min") {
    int64_t result = queue.GetMin();
    if (result == cInf) {
      std::cout << "error\n";
    } else {
      std::cout << result << '\n';
    }
  } else {
    queue.Clear();
    std::cout << "ok\n";
  }
}
int main() {
  MinQueue queue;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    ProcessTheRequest(queue);
  }
}