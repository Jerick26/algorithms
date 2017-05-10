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
    //top_vec->push_back(*it);
  }
  //top_vec->emplace_back({"%$#@!", 0});
  top_vec->push_back(std::pair<string, int>("$$$$$", 0));
  for (int i=k; i >= 0; --i) {
    for (auto it=w.begin(); it!=w.end(); ++it) {
      if (top_vec->at(i).second >= (*it).second) {
        top_vec->at(i+1) = *it;
        break;
      }
    }
  }
  top_vec->pop_back();
  top_vec->erase(top_vec->begin());
}


int main(int argc, char* arg[])
{
  std::cout << "Hello, nice to meet you!" << std::endl;
  string s = "ef ab cd ef ab cd ab ef dd dd dd dd dd";
  std::vector<std::pair<string, int>> top_vec;
  std::map<string, int> w;
  split2words(s, w);
  for (auto it=w.begin(); it!=w.end(); ++it) {
    std::cout << it->first << ":" << it->second << std::endl;
  }
  std::cout << "get top 2" << std::endl;
  getTop(2, w, &top_vec);
  for (auto it=top_vec.begin(); it!=top_vec.end(); ++it) {
    std::cout << it->first << ":" << it->second << std::endl;
  }

  return 0;
}
