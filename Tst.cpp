#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>

using std::string;

template <typename Value>
class Tst {
 public:
  struct Node {
    Node() : val(NULL), left(NULL), mid(NULL), right(NULL) {}
    ~Node() {
      if (val != NULL)
        delete val;
      if (left != NULL)
        delete left;
      if (mid != NULL)
        delete mid;
      if (right != NULL)
        delete right;
    }
    char c;
    Value *val;
    Node *left, *mid, *right;
  };
  Tst() : root(NULL) {}
  ~Tst() {
    if (root != NULL)
      delete root;
  }
  int size() {
    return size(root);
  }
  int size(Node* x) {
    if (x == NULL)
      return 0;
    int cnt = 0;
    if (x->val != NULL)
      cnt++;
    cnt += size(x->left) + size(x->mid) + size(x->right);
    return cnt;
  }
  bool contains(const string& key) {
    return get(key) != NULL;
  }
  const Value* get(const string& key) const {
    Node* x = get(root, key, 0);
    if (x == NULL)
      return NULL;
    return x->val;
  }
  Value* get(const string& key) {
    Node* x = get(root, key, 0);
    if (x == NULL)
      return NULL;
    return x->val;
  }
  void put(const string& key, const Value& val) {
    root = put(root, key, val, 0);
  }
  std::queue<string>* keys() {
    std::queue<string>* q = new std::queue<string>();
    collect(root, "", q);
    return q;
  }
  std::queue<string>* keysWithPrefix(const string& pre) {
    std::queue<string>* q = new std::queue<string>();
    Node* x = get(root, pre, 0);
    if (x->val != NULL)
      q->push(pre);
    collect(x->mid, pre, q);
    return q;
  }
  string longestPrefixOf(const string& query) {
    if (query.length() == 0)
      return string();
    int i = 0;
    int length = 0;
    Node* x = root;
    while (i < query.length() && x != NULL) {
      char c = query.at(i);
      if (c < x->c) {
        x = x->left;
      } else if (c > x->c) {
        x = x->right;
      } else {
        i++;
        if (x->val != NULL)
          length = i;
        x = x->mid;
      }
    }
    return query.substr(0, length);
  }
  std::queue<string>* keysThatMatch(const string& pat) {
    if (pat.length() == 0)
      return NULL;
    std::queue<string>* q = new std::queue<string>();
    collect(root, "", pat, 0, q);
    return q;
  }

 private:
  Node* get(Node* x, const string& key, int d) {
    if (x == NULL)
      return NULL;
    char c = key.at(d);
    if (c < x->c)
      return get(x->left, key, d);
    else if (c > x->c)
      return get(x->right, key, d);
    else if (d < key.length() - 1)
      return get(x->mid, key, d+1);
    else
      return x;
  }
  Node* put(Node* x, const string& key, const Value& val, int d) {
    char c = key.at(d);
    if (x == NULL) {
      x = new Node();
      x->c = c;
    }
    if (c < x->c)
      x->left = put(x->left, key, val, d);
    else if (c > x->c)
      x->right = put(x->right, key, val, d);
    else if (d < key.length() - 1)
      x->mid = put(x->mid, key, val, d+1);
    else {
      if (x->val != NULL)
        delete x->val;
      x->val = new Value(val);
    }
    return x;
  }
  void collect(Node* x, const string& pre, std::queue<string>* q) {
    if (x == NULL)
      return;
    collect(x->left, pre, q);
    if (x->val != NULL) {
      q->push(pre + x->c);
    }
    collect(x->mid, pre + x->c, q);
    collect(x->right, pre, q);
  }
  void collect(Node* x, const string& pre, const string& pat, int d,
               std::queue<string>* q) {
    if (x == NULL)
      return;
    char c = pat.at(d);
    if (c != '.' || c < x->c)
      collect(x->left, pre,  pat, d, q);
    if (c == '.' || c == x->c) {
      if (d == pat.length()-1 && x->val != NULL)
        q->push(pre + x->c);
      if (d < pat.length() - 1)
        collect(x->mid, pre + x->c, pat, d+1, q);
    }
    if (c == '.' || c > x->c)
      collect(x->right, pre, pat, d, q);
  }
 private:
  Node* root;
};

void initTst(Tst<int>& tst) {
  int k1 = 1, k2 = 2, k3 = 3;
  int k4 = 4, k5 = 5, k6 = 6;
  tst.put("a", 1);
  tst.put("ab", 2);
  tst.put("pi", 3);
  tst.put("she", 4);
  tst.put("zhe", 5);
  tst.put("shells", 6);
  tst.put("their", 6);
}

void test_get_put(Tst<int>& tst) {
  std::cout << "test get put begin ..." << std::endl;
  int* pi = tst.get("pi");
  int* zh = tst.get("zh");
  std::cout << "pi: " << (pi?*pi:-1) << std::endl;
  std::cout << "zh: " << (zh?*zh:-1) << std::endl;
  std::cout << "test get put end" << std::endl;
}

void test_keys(Tst<int>& tst) {
  std::cout << "test keys begin ..." << std::endl;
  std::cout << "keys: " << std::endl;
  std::queue<string>* q = tst.keys();
  while (!q->empty()) {
    std::cout << q->front() << std::endl;
    q->pop();
  }
  delete q;
  std::cout << "keys with prefix: sh" << std::endl;
  std::queue<string>* p = tst.keysWithPrefix("sh");
  while (!p->empty()) {
    std::cout << p->front() << std::endl;
    p->pop();
  }
  delete p;
  std::cout << "test kyes end" << std::endl;
}

void test_longestPrefixOf(Tst<int>& tst) {
  std::cout << "test longestPrefixOf begin ..." << std::endl;
  std::cout << "longestPrefixOf shell is: "
      << tst.longestPrefixOf("shell") << std::endl;
  std::cout << "test longestPrefixOf end" << std::endl;
}

void test_keysThatMatch(Tst<int>& tst) {
  std::cout << "test keysThatMatch begin ..." << std::endl;
  std::queue<string>* q = tst.keysThatMatch(".h.");
  std::cout << "keysThatMatch is: " << std::endl;
  while (!q->empty()) {
    std::cout << q->front() << std::endl;
    q->pop();
  }
  delete q;
  std::cout << "test longestPrefixOf end" << std::endl;
}

int main(int argc, char* argv[]) {
  Tst<int> tst;
  initTst(tst);
  test_get_put(tst);
  test_keys(tst);
  test_longestPrefixOf(tst);
  test_keysThatMatch(tst);
  return 0;
}
