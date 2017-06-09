/******************************************************************************
 *  Compilation:  g++ SeparateChainingHashST.cpp -std=c++0x -g
 *  Execution:    ./a.out < tinyST.txt
 *  Dependencies:
 *  
 *  A symbol table implemented with a separate-chaining hash table.
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

#include <iostream>
#include <string>
#include <vector>
#include "SequentialSearchST.h"

using std::string;

template <typename Key, typename Value>
class SeparateChainingHashST {
public:
  SeparateChainingHashST(int m = kInitCapacity) {
    this->m = m;
    for (int i = 0; i < m; i++)
      st.push_back(new SequentialSearchST<Key, Value>());
  }
  ~SeparateChainingHashST() {
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
    int i = hash(key);
    return st[i]->get(key);
  }

  void put(const Key& key, const Value& val) {
    if (n > 10*m)
      resize(2*m);
    int i = hash(key);
    if (!st[i]->contains(key))
      n++;
    st[i]->put(key, val);
  }

  void remove(const Key& key) {
    int i = hash(key);
    if (!st[i]->contains(key))
      n--;
    st[i]->remove(key);
    if (m > kInitCapacity && n <= 2*m)
      resize(m/2);
  }

  void keys(std::vector<Key>& vec) {
    for (int i = 0; i < m; i++)
      st[i]->keys(vec);
  }

private:
  void resize(int chains) {
    SeparateChainingHashST<Key, Value>* temp =
        new SeparateChainingHashST<Key, Value>(chains);
    for (int i = 0; i < m; i++) {
      std::vector<Key> keys;
      st[i]->keys(keys);
      for (auto it = keys.begin(); it != keys.end(); ++it)
        temp->put(*it, st[i]->get(*it));
    }
    this->m = temp->m;
    this->n = temp->n;
    this->st = temp->st;
  }

  int hash(const Key& key) {
    return (key.hashCode() & 0x7fffffff) % m;
  }

private:
  int n;
  int m;
  std::vector<SequentialSearchST<Key, Value>* > st;
  const static int kInitCapacity = 4;
};

template<>
int SeparateChainingHashST<string, int>::hash(const string& key) {
  int hash = 0;
  for (int i = 0; i < key.length(); i++)
    hash = ((31 * hash) + key[i]) % m;
  return hash;
}

int main(int argc, char* argv[]) {
  std::cout << "hello world!" << std::endl;
  SeparateChainingHashST<string, int> sepHash;
  string s;
  for (int i = 0; std::cin >> s; i++)
    sepHash.put(s, i);
  // print keys
  std::vector<string> keys;
  sepHash.keys(keys);
  for (auto it = keys.begin(); it != keys.end(); ++it)
    std::cout << *it << " " << sepHash.get(*it) << std::endl;

  return 0;
}
