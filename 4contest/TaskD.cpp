#include <cstdint>
#include <iostream>
#include <string>

const int kE = 15;
const int kMax = 1'000'000'001;

class Dekart {
 private:
  struct Node {
    Node* left;
    Node* right;
    long long key;
    long long sum;
    long long prior;
    int capacity;
    Node(long long key1) {
      left = nullptr;
      right = nullptr;
      key = key1;
      sum = key1;
      prior = (rand() << kE) ^ rand();
      capacity = 1;
    }
  };

  typedef std::pair<Node*, Node*> Pair;
  Node* root_ = 0;

  static int GetSize(Node* nd) {
    if (nd == nullptr) {
      return 0;
    }
    return nd->capacity;
  }

  static void Update(Node* nd) {
    if (nd != nullptr) {
      if (nd->left != nullptr && nd->right != nullptr) {
        nd->sum = nd->key + nd->left->sum + nd->right->sum;
        nd->capacity = GetSize(nd->left) + GetSize(nd->right) + 1;
      }
      if (nd->left != nullptr && nd->right == nullptr) {
        nd->sum = nd->key + nd->left->sum;
        nd->capacity = GetSize(nd->left) + 1;
      }
      if (nd->right != nullptr && nd->left == nullptr) {
        nd->capacity = GetSize(nd->right) + 1;
      }
      if (nd->right == nullptr && nd->left == nullptr) {
        nd->sum = nd->key;
        nd->capacity = 1;
      }
    }
  }

  Node* Merge(Node* nd1, Node* nd2) {
    if (nd2 == nullptr && nd1 != nullptr) {
      return nd1;
    }
    if (nd1 == nullptr && nd2 != nullptr) {
      return nd2;
    }
    if (nd1 == nullptr && nd2 == nullptr) {
      return nullptr;
    }
    if (nd1->prior <= nd2->prior) {
      nd2->left = Merge(nd1, nd2->left);
      Update(nd2);
      return nd2;
    }
    nd1->right = Merge(nd1->right, nd2);
    Update(nd1);
    return nd1;
  }

  Pair Split(Node* nd, long long key) {
    if (nd == nullptr) {
      return {nullptr, nullptr};
    }
    if (nd->key <= key) {
      Pair nd1 = Split(nd->right, key);
      nd->right = nd1.first;
      Update(nd);
      return {nd, nd1.second};
    }
    Pair nd1 = Split(nd->left, key);
    nd->left = nd1.second;
    Update(nd);
    return {nd1.first, nd};
  }

  Node* DeleteElem(Node*& nd, int key) {
    if (FindNotLower(nd, key) != key) {
      return nd;
    }
    Pair first_pair = Split(nd, key);
    Pair second_pair = Split(first_pair.first, key - 1);
    Node* result = Merge(second_pair.first, first_pair.second);
    delete second_pair.second;
    nd = result;
    Update(nd);
    return nd;
  }

  Node* Insert(Node* nd, long long key) {
    Pair result = Split(nd, key);
    Pair equalkey = Split(result.first, key - 1);
    if (equalkey.second == nullptr) {
      Node* nd1 = new Node(key);
      return Merge(Merge(equalkey.first, nd1), result.second);
    }
    return Merge(Merge(equalkey.first, equalkey.second), result.second);
  }

  long long FindNotLower(Node* nd, long long elem) {
    if (nd == nullptr) {
      return kMax;
    }
    if (nd->key < elem) {
      if (nd->right == nullptr) {
        return kMax;
      }
      return FindNotLower(nd->right, elem);
    }
    if (nd->key == elem) {
      return elem;
    }
    if (nd->left != nullptr) {
      long long result = FindNotLower(nd->left, elem);
      if (result >= elem) {
        return result;
      }
    }
    return nd->key;
  }

  long long Higher(Node* nd, long long elem) {
    if (nd == nullptr) {
      return kMax;
    }
    if (nd->key < elem) {
      if (nd->right == nullptr) {
        return kMax;
      }
      return Higher(nd->right, elem);
    }
    if (nd->left != nullptr) {
      long long result = Higher(nd->left, elem);
      if (result >= elem) {
        return result;
      }
    }
    return nd->key;
  }

  long long FindNotHigher(Node* nd, long long elem) {
    if (nd == nullptr) {
      return kMax;
    }
    if (nd->key > elem) {
      if (nd->left == nullptr) {
        return kMax;
      }
      return FindNotHigher(nd->left, elem);
    }
    if (nd->right != nullptr) {
      long long result = FindNotHigher(nd->right, elem);
      if (result <= elem) {
        return result;
      }
    }
    return nd->key;
  }

  void Delete(Node* nd) {
    if (nd == nullptr) {
      return;
    }
    Delete(nd->left);
    Delete(nd->right);
    delete nd;
  }

  static Node* MaxNode(Node* nd) {
    if (nd == nullptr) {
      return nullptr;
    }
    while (nd->right != nullptr) {
      nd = nd->right;
    }
    return nd;
  }

  Node* KStat(Node* nd, long long key) {
    if (nd == nullptr) {
      return nullptr;
    }
    if (GetSize(nd) <= key) {
      return nullptr;
    }
    if (GetSize(nd->left) == key) {
      return nd;
    }
    if (GetSize(nd->left) > key) {
      return KStat(nd->left, key);
    }
    return KStat(nd->right, key - GetSize(nd->left) - 1);
  }

 public:
  std::string Exists(long long elem) {
    if (root_ == nullptr) {
      return "false";
    }
    if (FindNotLower(root_, elem) == elem) {
      return "true";
    }
    return "false";
  }

  std::string Next(long long elem) {
    if (root_ == nullptr) {
      return "none";
    }
    long long result = Higher(root_, elem);
    if (result == kMax) {
      return "none";
    }
    return std::to_string(result);
  }

  std::string Prev(long long elem) {
    if (root_ == nullptr) {
      return "none";
    }
    long long result = FindNotHigher(root_, elem);
    if (result == kMax) {
      return "none";
    }
    return std::to_string(result);
  }

  void Insert(long long key) {
    if (root_ == nullptr) {
      root_ = new Node(key);
    } else {
      root_ = Insert(root_, key);
    }
  }

  void DeleteElem(long long key) {
    if (root_ == nullptr) {
      return;
    }
    DeleteElem(root_, key);
  }

  std::string KStat(long long key) {
    if (root_ == nullptr) {
      return "none";
    }
    Node* result = KStat(root_, key);
    if (result == nullptr) {
      return "none";
    }
    return std::to_string(result->key);
  }

  void Deletetree() { Delete(root_); }
};

int main() {
  Dekart tree;
  std::string command;
  while (std::cin >> command) {
    long long elem;
    std::cin >> elem;
    if (command == "insert") {
      tree.Insert(elem);
    }
    if (command == "exists") {
      std::cout << tree.Exists(elem) << std::endl;
    }
    if (command == "next") {
      std::cout << tree.Next(elem) << std::endl;
    }
    if (command == "prev") {
      std::cout << tree.Prev(elem) << std::endl;
    }
    if (command == "delete") {
      tree.DeleteElem(elem);
    }
    if (command == "kth") {
      std::cout << tree.KStat(elem) << std::endl;
    }
  }
  tree.Deletetree();
}
