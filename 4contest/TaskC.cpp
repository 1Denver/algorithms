#include <iostream>
#include <string>

class Avl {
 private:
  struct Node {
    std::string key;
    std::string value;
    unsigned char height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const std::string& first, const std::string& second)
        : key(first), value(second) {}
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

  Node* Insert(Node* nd, const std::string& key, const std::string& value) {
    if (nd == nullptr) {
      return new Node(key, value);
    }
    if (key < nd->key) {
      nd->left = Insert(nd->left, key, value);
    } else {
      nd->right = Insert(nd->right, key, value);
    }
    return Balance(nd);
  }

  std::string Find(Node* nd, const std::string& key) {
    if (nd == NULL) {
      return "";
    }
    if (nd->key < key) {
      if (nd->right == NULL) {
        return "";
      }
      return Find(nd->right, key);
    }
    if (nd->key == key) {
      return nd->value;
    }
    if (nd->left != NULL) {
      return Find(nd->left, key);
    }
    return nd->value;
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
  void Insert(const std::string& key, const std::string& value) {
    root_ = Insert(root_, key, value);
  }
  std::string Find(const std::string& key) { return Find(root_, key); }
  ~Avl() { Delete(root_); }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  Avl tree;
  int number;
  std::cin >> number;
  for (int i = 0; i < number; ++i) {
    std::string key;
    std::string value;
    std::cin >> key >> value;
    tree.Insert(key, value);
    std::string transfer = key;
    key = value;
    value = transfer;
    tree.Insert(key, value);
  }
  int request;
  std::cin >> request;
  for (int i = 0; i < request; ++i) {
    std::string key;
    std::cin >> key;
    std::cout << tree.Find(key) << std::endl;
  }
}
