#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <cassert>

using std::string;

void split2words(const string& s, std::map<string, int>& w) {
  int b = 0, e = 0;
  int len = s.length();
  while (b < len) {
    while (b < len && s.at(b) == ' ')
    { b++; }
    e = b + 1;
    while (e < len && s.at(e) != ' ')
    { e++; }
    w[s.substr(b, e-b)]++;
    b = e;
  }
}

void getTop(int k, std::map<string, int>& w,
            std::vector<std::pair<string, int>>* top_vec) {
  k = w.size() > k ? k : w.size();
  top_vec->clear();
  //top_vec->emplace_back({"!@#$%", 100000000});
  top_vec->push_back(std::pair<string, int>("@@@@", 100000000));
  for (int i=0; i<k; ++i) {
    top_vec->push_back(std::pair<string, int>("$$$$$", 0));
  }
  for (auto it=w.begin(); it!=w.end(); ++it) {
    for (int i=k; i >= 0; --i) {
      if (top_vec->at(i).second >= (*it).second) {
        top_vec->insert(top_vec->begin()+i+1, *it);
        top_vec->pop_back();
        break;
      }
    }
  }
  top_vec->erase(top_vec->begin());
}

template <typename pair_list_t>
void print_pair_list(const pair_list_t& list) {
  for (auto x : list) {
    std::cout << x.first << ":" << x.second << std::endl;
  }
}


int main(int argc, char* arg[])
{
  std::cout << "Hello, nice to meet you!" << std::endl;
  string s = "ef ab cd ef ab cd ab ef dd dd dd dd dd ab ab";
  std::vector<std::pair<string, int>> top_vec;
  std::map<string, int> w;
  split2words(s, w);
  print_pair_list(w);
  std::cout << "get top 2" << std::endl;
  getTop(2, w, &top_vec);
  print_pair_list(top_vec);

  return 0;
}
