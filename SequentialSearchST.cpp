/******************************************************************************
 *  Compilation:  g++ SequentialSearchST
 *  Execution:    ./a.out < tinyST.txt
 *  Dependencies:
 *  
 *  Symbol table implementation with sequential search in an
 *  unordered linked list of key-value pairs.
 *
 *  % more tinyST.txt
 *  S E A R C H E X A M P L E
 *
 *  % ./a.out < tiny.txt 
 *  L 11
 *  P 10
 *  M 9
 *  X 7
 *  H 5
 *  C 4
 *  R 3
 *  A 8
 *  E 12
 *  S 0
 *
 ******************************************************************************/

#include <string>
#include <iostream>
#include <vector>

using std::string;

template <typename Key, typename Value>
class SequentialSearchST {
  class Node {
  public:
    Key key;
    Value val;
    Node* next;
    Node(const Key& key, const Value& val, Node* next) {
      this->key = key;
      this->val = val;
      this->next = next;
    }
    ~Node() {
      if (next != NULL)
        delete next;
    }
  };
public:
  SequentialSearchST() : first(NULL) {
  }

  ~SequentialSearchST() {
    if (first != NULL)
      delete first;
  }

  int size() {
    return n;
  }

  bool isEmpty() {
    return n == 0;
  }

  bool contains(const Key& key) {
    return get(key) != NULL;
  }

  Value get(const Key& key) {
    for (Node* x = first; x != NULL; x = x->next) {
      if (x->key == key)
        return x->val;
    }
    return NULL;
  }

  void put(const Key& key, const Value& val) {
    for (Node* x = first; x != NULL; x = x->next) {
      if (x->key == key) {
        x->val = val;
        return;
      }
    }
    first = new Node(key, val, first);
    n++;
  }

  void remove(const Key& key) {
    first = remove(first, key);
  }

  Node* remove(Node* x, const Key& key) {
    if (x == NULL)
      return NULL;
    if (x->key == key) {
      n--;
      return x->next;
    }
    x->next = remove(x->next, key);
  }

  void keys(std::vector<Key>& vec) {
    for (Node* x = first; x != NULL; x = x->next)
      vec.push_back(x->key);
  }

private:
  int n;
  Node* first;
};

int main(int argc, char* argv[]) {
  SequentialSearchST<string, int> st;
  string s;
  for (int i = 0; std::cin >> s; i++) {
    st.put(s, i);
  }
  std::vector<string> keys;
  st.keys(keys);
  for (auto it = keys.begin(); it != keys.end(); ++it)
    std::cout << *it << " " << st.get(*it) << std::endl;
  return 0;
}
