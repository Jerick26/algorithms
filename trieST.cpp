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
    Node() : val(NULL) {
      for (int r=0; r<R; r++){
        next[r] = NULL;
      }
    }
    ~Node() {
      if (val != NULL)
        delete val;
      for (int r=0; r<R; r++)
        if (next[r] != NULL)
          delete next[r];
    }
    Value* val;
    Node* next[R];
  };
  TrieST() : root(NULL) {}
  ~TrieST() {
    if (root != NULL)
      delete root;
  }
  Value* get(const string& key) {
    Node* x = get(root, key, 0);
    if (x == NULL)
      return NULL;
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
  std::queue<string>* keysThatMatch(const string& pat) {
    std::queue<string>* q = new std::queue<string>();
    collect(root, "", pat, q);
    return q;
  }
  string longestPrefixOf(const string& s) {
    int length = search(root, s, 0, 0);
    return s.substr(0, length);
  }
  void erase(const string& key) {
    root = erase(root, key, 0);
  }
 private:
  // return value associated with key in the subtrie rooted in x
  Node* get(Node* x, const string& key, int d) {
    if (x == NULL)
      return NULL;
    if (d == key.length())
      return x;
    // use dth key char to identify subtrie
    unsigned char c = key.at(d);
    return get(x->next[c], key, d+1);
  }
  // change value associated with key if in subtrie rooted in x
  Node* put(Node* x, const string& key, Value* val, int d) {
    if (x == NULL)
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
    if (x == NULL)
      return;
    if (x->val != NULL)
      q->push(pre);
    for (int c=0; c<R; c++)
      collect(x->next[c], pre+(char)c, q);
  }
  void collect(Node* x, const string& pre, const string& pat,
               std::queue<string>* q) {
    if (x == NULL)
      return;
    int d = pre.length();
    if (d == pat.length() && x->val != NULL)
      q->push(pre);
    if (d == pat.length())
      return;
    char c = pat.at(d);
    for (int r=0; r<R; r++)
      if (c == '.' || c == (char)r)
        collect(x->next[r], pre+(char)r, pat, q);
  }
  int search(Node* x, const string& s, int d, int length) {
    if (x == NULL)
      return length;
    if (x->val != NULL)
      length = d;
    if (d == s.length())
      return length;
    unsigned char c = s.at(d);
    return search(x->next[c], s, d+1, length);
  }
  Node* erase(Node* x, const string& key, int d) {
    if (x == NULL)
      return NULL;
    if (d == key.length()) {
      delete x->val;
      x->val = NULL;
    } else {
      unsigned char c = key.at(d);
      x->next[c] = erase(x->next[c], key, d+1);
    }
    if (x->val != NULL)
      return x;
    for (int r=0; r<R; r++)
      if (x->next[r] != NULL)
        return x;
    delete x;
    return NULL;
  }

 private:
  Node* root;  // root of trie
};

void initTrie(TrieST<int>& trie) {
  int k1 = 1, k2 = 2, k3 = 3;
  int k4 = 4, k5 = 5, k6 = 6;
  trie.put("a", &k1);
  trie.put("ab", &k2);
  trie.put("pi", &k3);
  trie.put("she", &k4);
  trie.put("zhe", &k5);
  trie.put("shells", &k6);
  trie.put("their", &k6);
}

void test_get_put(TrieST<int>& trie) {
  std::cout << "test get put begin ..." << std::endl;
  int* pi = trie.get("pi");
  int* zh = trie.get("zh");
  std::cout << "pi: " << (pi?*pi:-1) << std::endl;
  std::cout << "zh: " << (zh?*zh:-1) << std::endl;
  std::cout << "test get put end" << std::endl;
}

void test_keys(TrieST<int>& trie) {
  std::cout << "test keys begin ..." << std::endl;
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

void test_keysThatMatch(TrieST<int>& trie) {
  std::cout << "test keysThatMatch begin ..." << std::endl;
  std::queue<string>* q = trie.keysThatMatch(".he");
  while (!q->empty()) {
    std::cout << q->front() << std::endl;
    q->pop();
  }
  delete q;
  std::queue<string>* p = trie.keysThatMatch("she.ls");
  while (!p->empty()) {
    std::cout << p->front() << std::endl;
    p->pop();
  }
  delete p;
  std::cout << "test keysThatMatch end" << std::endl;
}

void test_longestPrefixOf(TrieST<int>& trie) {
  std::cout << "test longestPrefixOf begin ..." << std::endl;
  std::cout << trie.longestPrefixOf("shell") << std::endl;
  std::cout << "test longestPrefixOf end" << std::endl;
}

void test_erase(TrieST<int>& trie) {
  std::cout << "test delete begin ..." << std::endl;
  trie.erase("their");
  trie.erase("sheet");
  trie.erase("she");
  std::cout << "after delete, keys:" << std::endl;
  std::queue<string>* q = trie.keys();
  while (!q->empty()) {
    std::cout << q->front() << std::endl;
    q->pop();
  }
  delete q;
  std::cout << "test delete end" << std::endl;
}

int main(int argc, char* argv[]) {
  TrieST<int> trie;
  initTrie(trie);
  test_get_put(trie);
  test_keys(trie);
  test_keysThatMatch(trie);
  test_longestPrefixOf(trie);
  test_erase(trie);
  return 0;
}
