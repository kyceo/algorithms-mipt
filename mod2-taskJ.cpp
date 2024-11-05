#include <algorithm>
#include <iostream>
#include <stack>

const int cInf = 1e9 + 2;

struct StackMin {
  std::stack<std::pair<int, int>> stack;
  void StackClear() {
    while (!stack.empty()) {
      stack.pop();
    }
  }

  void Push(int value) {
    if (!stack.empty()) {
      stack.push({value, std::min(value, stack.top().second)});
    } else {
      stack.push({value, value});
    }
  }

  void Pop() { stack.pop(); }

  int Top() { return stack.top().first; }

  int GetMin() {
    if (stack.empty()) {
      return cInf;
    }
    return stack.top().second;
  }
};

struct Queue {
  StackMin back;
  StackMin front;
  int size = 0;

  void Enqueue(int value) {
    back.Push(value);
    std::cout << "ok\n";
    ++size;
  }

  void Dequeue() {
    if (front.stack.empty()) {
      while (!back.stack.empty()) {
        front.Push(back.Top());
        back.Pop();
      }
    }
    if (front.stack.empty()) {
      std::cout << "error\n";
    } else {
      std::cout << front.Top() << '\n';
      front.Pop();
      --size;
    }
  }

  void Front() {
    if (front.stack.empty()) {
      while (!back.stack.empty()) {
        front.Push(back.Top());
        back.Pop();
      }
    }
    if (front.stack.empty()) {
      std::cout << "error\n";
    } else {
      std::cout << front.Top() << '\n';
    }
  }

  int Size() const { return size; }

  void Min() {
    int ans = std::min(back.GetMin(), front.GetMin());
    if (ans == cInf) {
      std::cout << "error\n";
    } else {
      std::cout << ans << '\n';
    }
  }

  void Clear() {
    front.StackClear();
    back.StackClear();
    size = 0;
    std::cout << "ok\n";
  }
};

void PrintSolution(Queue& queue) {
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "enqueue") {
    int value;
    std::cin >> value;
    queue.Enqueue(value);
  } else if (tmp == "front") {
    queue.Front();
  } else if (tmp == "dequeue") {
    queue.Dequeue();
  } else if (tmp == "size") {
    std::cout << queue.Size() << '\n';
  } else if (tmp == "min") {
    queue.Min();
  } else {
    queue.Clear();
  }
}

int main() {
  Queue queue;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    PrintSolution(queue);
  }
}
