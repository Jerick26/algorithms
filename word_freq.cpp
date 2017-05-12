/******************************************************************************
 *  Compilation:  g++ -o main main.cpp -std=c++0x -g
 *  Execution:    ./main n < input.txt
 *  Dependencies: std::cin std::cout
 *  Data files:   https://github.com/Jerick26/algorithms/blob/master/word_freq_test.data
 *
 *  word freq count and get top N frequence words
 *    - parse a string to get the frequence information
 *    - get top N frequence words
 *
 *  % ./main 3 < word_freq_test.data
 *  the top 3 words is:
 *  nob: 6
 *  joy: 5
 *  ilk: 4
 *
 ******************************************************************************/
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <climits>
#include <cstdlib>

using std::string;

void split_to_words(const string& s, std::map<string, int>* w) {
  int b = 0, e = 0;
  int len = s.length();
  while (b < len) {
    while (b < len && s.at(b) == ' ')
      b++;
    e = b + 1;
    while (e < len && s.at(e) != ' ')
      e++;
    (*w)[s.substr(b,  e - b)]++;
    b = e + 1;
  }
}

void get_top(int k, const std::map<string, int>& w,
             std::vector<std::pair<string, int>>* vec) {
  vec->clear();
  vec->emplace(vec->begin(), "@@@@", INT_MAX);
  k = w.size() > k ? k : w.size();
  for (int i=0; i<k; ++i) {
    vec->emplace_back("@@@@", 0);
  }
  for (auto it=w.begin(); it!=w.end(); ++it) {
    for (int i=k; i>=0; --i) {
      if (vec->at(i).second >= it->second) {
        vec->insert(vec->begin()+i+1, *it);
        vec->pop_back();
        break;
      }
    }
  }
  vec->erase(vec->begin());
}

template <typename pair_list_t>
void print_pair_list(const pair_list_t& li) {
  for (auto it=li.begin(); it!=li.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
}

int main(int argc, char*arg[]) {
  if (argc < 2) {
    std::cout << "argument to main is insufficient!" << std::endl;
    return -1;
  }
  int k = atoi(arg[1]);
  string s;
  string data;
  while (std::cin >> data) {
    s.append(data).append(" ");
  }
  std::map<string, int> w;
  split_to_words(s, &w);
  print_pair_list(w);
  std::cout << "the top " << k << " words is:" << std::endl;
  std::vector<std::pair<string, int>> top_key;
  get_top(k, w, &top_key);
  print_pair_list(top_key);
  return 0;
}

/******************************************************************************
 *  Copyright © 2000–2017, Jerick26. 
 *  Last updated: Thu May 11 EST 2017.
 ******************************************************************************/
