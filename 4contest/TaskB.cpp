#include <deque>
#include <iostream>

class Avl {
 private:
  struct Node {
    int key;
    unsigned char height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int el) : key(el) {}
  };

  Node* root_ = nullptr;

  static unsigned char Height(Node* nd) {
    return (nd != nullptr) ? nd->height : 0;
  }

  static int Bfactor(Node* nd) { return Height(nd->right) - Height(nd->left); }

  static void Fixheight(Node* nd) {
    unsigned char hl = Height(nd->left);
    unsigned char hr = Height(nd->right);
    nd->height = (hl > hr ? hl : hr) + 1;
  }

  static Node* Rotateright(Node* p_node) {
    Node* q_node = p_node->left;
    p_node->left = q_node->right;
    q_node->right = p_node;
    Fixheight(p_node);
    Fixheight(q_node);
    return q_node;
  }

  static Node* Rotateleft(Node* q_node) {
    Node* p_node = q_node->right;
    q_node->right = p_node->left;
    p_node->left = q_node;
    Fixheight(q_node);
    Fixheight(p_node);
    return p_node;
  }

  static Node* Balance(Node* nd) {
    Fixheight(nd);
    if (Bfactor(nd) == 2) {
      if (Bfactor(nd->right) < 0) {
        nd->right = Rotateright(nd->right);
      }
      return Rotateleft(nd);
    }
    if (Bfactor(nd) == -2) {
      if (Bfactor(nd->left) > 0) {
        nd->left = Rotateleft(nd->left);
      }
      return Rotateright(nd);
    }
    return nd;
  }

  Node* Insert(Node* nd, int el) {
    if (nd == nullptr) {
      return new Node(el);
    }
    if (el < nd->key) {
      nd->left = Insert(nd->left, el);
    } else {
      nd->right = Insert(nd->right, el);
    }
    return Balance(nd);
  }

  int FindNotLower(Node* nd, int elem) {
    if (nd == NULL) {
      return -1;
    }
    if (nd->key < elem) {
      if (nd->right == NULL) {
        return -1;
      }
      return FindNotLower(nd->right, elem);
    }
    if (nd->key == elem) {
      return elem;
    }
    if (nd->left != NULL) {
      int result = FindNotLower(nd->left, elem);
      if (result >= elem) {
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

 public:
  Avl() = default;
  void Insert(int value) { root_ = Insert(root_, value); }

  int Find(int elem) { return FindNotLower(root_, elem); }

  ~Avl() { Delete(root_); }
};

int main() {
  const int kKconst = 1'000'000'000;
  Avl tree;
  int number;
  std::cin >> number;
  char previous_str = '0';
  int previous_result = -2;
  for (int i = 0; i < number; ++i) {
    char str = '1';
    int elem;
    std::cin >> str >> elem;
    if (str == '+') {
      if (i >= 0 && previous_str != '?' && tree.Find(elem) != elem) {
        tree.Insert(elem);
      }
      if (i > 0 && previous_str == '?') {
        tree.Insert((elem + previous_result) % kKconst);
      }
    }
    if (str == '?') {
      int result = tree.Find(elem);
      std::cout << result << std::endl;
      previous_result = result;
    }
    previous_str = str;
  }
}

