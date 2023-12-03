#include <iostream>
#include <queue>
#include <vector>

class Hat {
 private:
  std::queue<int> qw_;
  std::deque<int> values_;
  std::deque<int> mins_;

 public:
  Hat(){};
  void Enqueue(int elem) {
    qw_.push(elem);
    values_.push_back(elem);
    while (!mins_.empty() && mins_.back() > elem) {
      mins_.pop_back();
    }
    mins_.push_back(elem);
  }
  int Dequeue() {
    int last = qw_.front();
    qw_.pop();
    if (values_.front() == mins_.front()) {
      mins_.pop_front();
    }
    values_.pop_front();
    return last;
  }
  int Size() { return qw_.size(); }
  bool Checksize() { return !qw_.empty(); }
  void Pop() { qw_.pop(); }
  int Front() { return qw_.front(); }
  std::string Clear() {
    while (!qw_.empty()) {
      qw_.pop();
    }
    mins_.clear();
    values_.clear();
    return "ok";
  }
  int Min() { return mins_.front(); }
};

int main() {
  int number = 0;
  std::cin >> number;
  Hat hat;
  for (int i = 0; i < number; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "enqueue") {
      int elem = 0;
      std::cin >> elem;
      hat.Enqueue(elem);
      std::cout << "ok" << std::endl;
    }
    if ((command == "dequeue")) {
      if (hat.Checksize()) {
        std::cout << hat.Dequeue() << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
    if ((command == "front")) {
      if (hat.Checksize()) {
        std::cout << hat.Front() << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
    if (command == "size") {
      std::cout << hat.Size() << std::endl;
    }
    if (command == "clear") {
      std::cout << hat.Clear() << std::endl;
    }
    if (command == "min") {
      if (hat.Checksize()) {
        std::cout << hat.Min() << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
  }
}
