// необходимо реализовать структуру, которая поддерживает операции:
// вставка в конец, вставка в середину, удаление первого элемента

#include <deque>
#include <iostream>
#include <string>

class MidQueue {
 public:
  void PushBack(int64_t value);
  void PushMid(int64_t value);
  int64_t PopFront();

 private:
  std::deque<int64_t> left_;
  std::deque<int64_t> right_;
  void Balance();
};

void MidQueue::PushBack(int64_t value) {
  right_.push_back(value);
  Balance();
}

int64_t MidQueue::PopFront() {
  int64_t front = left_.front();
  left_.pop_front();
  Balance();
  return front;
}

void MidQueue::PushMid(int64_t value) {
  left_.push_back(value);
  Balance();
}

void ProcessTheQuery(MidQueue& midqueue) {
  char command;
  std::cin >> command;
  if (command == '+') {
    int64_t value;
    std::cin >> value;
    midqueue.PushBack(value);
  } else if (command == '*') {
    int64_t value;
    std::cin >> value;
    midqueue.PushMid(value);
  } else {
    std::cout << midqueue.PopFront() << '\n';
  }
}

void MidQueue::Balance() {
  if (left_.size() < right_.size()) {
    left_.push_back(right_.front());
    right_.pop_front();
  } else if (left_.size() - right_.size() >= 2) {
    right_.push_front(left_.back());
    left_.pop_back();
  }
}

int main() {
  int q;
  std::cin >> q;
  MidQueue midqueue;
  for (int i = 0; i < q; ++i) {
    ProcessTheQuery(midqueue);
  }
}