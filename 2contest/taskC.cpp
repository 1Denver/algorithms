#include <deque>
#include <iostream>
int main() {
  char command;
  long long number;
  long long index;
  std::deque<long long> left;
  std::deque<long long> right;
  std::cin >> number;
  for (long long i = 0; i < number; ++i) {
    std::cin >> command;
    if (command != '-') {
      std::cin >> index;
    }
    if (command == '+') {
      right.push_back(index);
    } else if (command == '*') {
      right.push_front(index);
    } else {
      std::cout << left.front() << std::endl;
      left.pop_front();
    }
    if (left.size() < right.size()) {
      left.push_back(right.front());
      right.pop_front();
    }
  }
  return 0;
}
