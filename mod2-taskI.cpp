#include <deque>
#include <iostream>
#include <string>

void ProcessTheRequest(std::deque<int>& dq) {
  std::string query;
  std::cin >> query;
  if (query == "+") {
    int value;
    std::cin >> value;
    dq.push_back(value);
  } else if (query == "-") {
    std::cout << dq.front() << '\n';
    dq.pop_front();
  } else {
    int value;
    std::cin >> value;
    auto middle = dq.begin() + dq.size() % 2 + dq.size() / 2;
    dq.insert(middle, value);
  }
}

int main() {
  std::deque<int> dq;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    ProcessTheRequest(dq);
  }
}