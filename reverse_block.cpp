/******************************************************************************
 *  Compilation:  g++ -o reverse_block.cpp -std=c++0x -g
 *  Execution:    ./a.out [n]
 *  Dependencies:
 *
 *  block reverse in list
 *  % ./a.out 3
 *  abcdefghijk
 *  c
 *  b
 *  a
 *  f
 *  e
 *  d
 *  j
 *  i
 *  h
 *  k
 *
 ******************************************************************************/
 
#include <cstdlib>
#include <iostream>
#include <string>

using std::string;

template <typename T>
class Node {
public:
  T item;
  Node* next;
  Node() : item(T()), next(NULL) {}
};

template <typename T>
void print_node_list(Node<T>* x) {
  while (x != NULL) {
    std::cout << x->item << std::endl;
    x = x->next;
  }
}

template <typename T>
Node<T>* block_reverse(Node<T>* first, int k) {
  Node<T>* current = first;
  Node<T>* prev = NULL;
  int count = 0;
  while (count < k && current != NULL) {
    Node<T>* next = current->next;
    current->next = prev;
    prev = current;
    current = next;
    count++;
  }
  if (current != NULL)
    first->next = block_reverse(current, k);
  return prev;
}

public Node reverse(Node first) {
  if (first == null) return null;
  if (first.next == null) return first;
  Node second = first.next;
  Node rest = reverse(second);
  second.next = first;
  first.next  = null;
  return rest;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "arguments to main is insufficient!" << std::endl;
    return -1;
  }
  int block_size = std::atoi(argv[1]);
  string s;
  std::getline(std::cin, s);
  Node<char>* prev = new Node<char>();
  prev->item = s[0];
  Node<char>* first = prev;
  for (int i = 1; i < s.length(); i++) {
    Node<char>* current = new Node<char>();
    current->item = s[i];
    prev->next = current;
    prev = current;
  }
  first = block_reverse(first, block_size);
  print_node_list(first);
}
