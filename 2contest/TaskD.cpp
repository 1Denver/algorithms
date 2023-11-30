#include <iostream>
#include <queue>
#include <vector>
void Enqueue(int elem, std::queue<int>& qw, std::deque<int>& values,
             std::deque<int>& mins) {
  qw.push(elem);
  values.push_back(elem);
  while (!mins.empty() && mins.back() > elem) {
    mins.pop_back();
  }
  mins.push_back(elem);
}
int Dequeue(std::queue<int>& qw, std::deque<int>& values,
            std::deque<int>& mins) {
  int last = qw.front();
  qw.pop();
  if (values.front() == mins.front()) {
    mins.pop_front();
  }
  values.pop_front();
  return last;
}
int Size(std::queue<int>& qw) { return qw.size(); }
void Pop(std::queue<int>& qw) { qw.pop(); }
int Front(std::queue<int>& qw) { return qw.front(); }
std::string Clear(std::queue<int>& qw) {
  while (!qw.empty()) {
    qw.pop();
  }
  return "ok";
}
int main() {
  std::queue<int> qw;
  int number = 0;
  std::cin >> number;
  std::deque<int> values;
  std::deque<int> mins;
  for (int i = 0; i < number; i++) {
    std::string command;
    std::cin >> command;
    if (command == "enqueue") {
      int elem = 0;
      std::cin >> elem;
      Enqueue(elem, qw, values, mins);
      std::cout << "ok" << std::endl;
    }
    if ((command == "dequeue")) {
      if (Size(qw) > 0) {
        std::cout << Dequeue(qw, values, mins) << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
    if ((command == "front")) {
      if (Size(qw) > 0) {
        std::cout << Front(qw) << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
    if (command == "size") {
      std::cout << Size(qw) << std::endl;
    }
    if (command == "clear") {
      std::cout << Clear(qw) << std::endl;
      mins.clear();
      values.clear();
    }
    if (command == "min") {
      if (Size(qw) > 0) {
        std::cout << mins.front() << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
  }
}
