#include <queue>
#include <string>
#include <iostream>

using std::string;

template <typename Value>
class TrieST {
 public:
  static const int R = 256; // radix
 public:
  class Node {
   public:
    Node() : val(nullptr) {
      for (int r=0; r<R; r++){
        next[r] = nullptr;
      }
    }
    ~Node() {
      if (val != nullptr)
        delete val;
      for (int r=0; r<R; r++)
        if (next[r] != nullptr)
          delete next[r];
    }
    Value* val;
    Node* next[R];
  };
  TrieST() : root(nullptr) {}
  ~TrieST() {
    if (root != nullptr)
      delete root;
  }
  Value* get(const string& key) {
    Node* x = get(root, key, 0);
    if (x == nullptr)
      return nullptr;
    return x->val;
  }
  void put(const string& key, Value* val) {
    root = put(root, key, val, 0);
  }
  std::queue<string>* keys() {
    return keysWithPrefix("");
  }
  std::queue<string>* keysWithPrefix(const string& pre) {
    std::queue<string>* q = new std::queue<string>();
    collect(get(root, pre, 0), pre, q);
    return q;
  }
 private:
  // return value associated with key in the subtrie rooted in x
  Node* get(Node* x, const string& key, int d) {
    if (x == nullptr)
      return nullptr;
    if (d == key.length())
      return x;
    // use dth key char to identify subtrie
    unsigned char c = key.at(d);
    return get(x->next[c], key, d+1);
  }
  // change value associated with key if in subtrie rooted in x
  Node* put(Node* x, const string& key, Value* val, int d) {
    if (x == nullptr)
      x = new Node();
    if (d == key.length()) {
      x->val = new Value(*val);
      return x;
    }
    unsigned char c = key.at(d);
    x->next[c] = put(x->next[c], key, val, d+1);
    return x;
  }
  void collect(Node* x, const string& pre, std::queue<string>* q) {
    if (x == nullptr)
      return;
    if (x->val != nullptr)
      q->push(pre);
    for (int c=0; c<R; c++)
      collect(x->next[c], pre+(char)c, q);
  }

 private:
  Node* root;  // root of trie
};

void test_get_put() {
  std::cout << "test get put begin ..." << std::endl;
  TrieST<int> trie;
  int k1 = 1, k2 = 2, k3 = 3;
  trie.put("a", &k1);
  trie.put("ab", &k2);
  trie.put("pi", &k3);
  int* pi = trie.get("pi");
  int* zh = trie.get("zh");
  std::cout << "pi: " << (pi?*pi:-1) << std::endl;
  std::cout << "zh: " << (zh?*zh:-1) << std::endl;
  std::cout << "test get put end" << std::endl;
}

void test_keys() {
  std::cout << "test keys begin ..." << std::endl;
  TrieST<int> trie;
  int k1 = 1, k2 = 2, k3 = 3;
  trie.put("a", &k1);
  trie.put("ab", &k2);
  trie.put("pi", &k3);
  std::cout << "test keys" << std::endl;
  std::queue<string>* q = trie.keys();
  while (!q->empty()) {
    std::cout << q->front() << std::endl;
    q->pop();
  }
  delete q;
  std::cout << "test keysWithPrefix" << std::endl;
  std::queue<string>* p = trie.keysWithPrefix("a");
  while (!p->empty()) {
    std::cout << p->front() << std::endl;
    p->pop();
  }
  delete p;
  std::cout << "test keys end" << std::endl;
}

int main(int argc, char* argv[]) {
  test_get_put();
  test_keys();
  return 0;
}
