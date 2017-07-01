/******************************************************************************
 *  Compilation:  g++ -o main.cpp -std=c++0x -g
 *  Execution:    ./main n < input.txt
 *  Dependencies: std::cin std::cout
 *  Data files:   https://github.com/Jerick26/algorithms/blob/master/word_freq_test.data
 *
 *  word freq count and get top N frequence words
 *    - parse a string to get the frequence information
 *    - get top N frequence words
 *
 *  % ./a.out 3 < word_freq_test.data
 *  the top 3 words is:
 *  nob: 6
 *  joy: 5
 *  ilk: 4
 *  tag: 4
 *  wee: 4
 *
 ******************************************************************************/

/*
 * Top K Frequent Elements
 * pass on leetcode
 */
#include <map>
#include <pair>
#include <vector>
#include <algorithm>

struct my_comp{
    bool operator() (pair<int, int> a, pair<int, int> b){
        if(a.first > b.first) return true;
        else if(a.first == b.first && a.second > b.second) return true;
        else return false;
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // the kernel is to use a minheap regrad of frequence, with size of K
        // firstly, use a map to count the numbers
        unordered_map<int, int> count; // <num, freq>
        for(auto i : nums){
            count[i]++;
        }
        // then pour them into the minheap, maitain the size of K
        priority_queue<pair<int, int>, vector<pair<int, int>>, my_comp> minheap; //<freq, num>
        for(auto p : count){
            if(minheap.size() < k){
                minheap.push(pair<int, int>(p.second, p.first));
            }
            else{
                if(minheap.top().first < p.second){
                    minheap.pop();
                    minheap.push(pair<int, int>(p.second, p.first));
                }
            }
        }
        // then pull the k elements stored in minheap into vector, and then return 
        vector<int> res;
        while(!minheap.empty()){
            res.push_back(minheap.top().second);
            minheap.pop();
        }
        return res;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> f;
        for (auto it=nums.begin(); it!=nums.end(); ++it)
            f[*it]++;
        vector<pair<int, int> > t;
        auto it = f.begin();
        for (int i=0; i<k; ++it, ++i)
            t.push_back(*it);
        std::sort(t.begin(), t.end(),
            [](pair<int, int>& a, pair<int, int>& b){return a.second < b.second;});
        for (; it!=f.end(); ++it) {
            if (it->second <= t.front().second)
                continue;
            auto pos = std::lower_bound(t.begin(), t.end(), it->second,
                [](pair<int, int>& a, int b){return a.second < b;});
            t.insert(pos, *it);
            t.erase(t.begin());
        }
        vector<int> r;
        for (auto it=t.begin(); it!=t.end(); ++it)
            r.push_back(it->first);
        std::reverse(r.begin(), r.end());
        return r;
    }
};


#include <string>
#include <map>
#include <list>
#include <iostream>

using std::string;

class WordFreq {
public:
  static void get_top(int k, const std::map<string, int>& w,
                      std::list<std::pair<string, int>>* li) {
    if (li == NULL)
      return;
    li->clear();
    for (int i=0; i<k; i++)
      li->push_back(std::make_pair("", i-k));
    for (auto it = w.begin(); it != w.end(); ++it)
      insert_top(*it, li);
  }

  static bool insert_top(const std::pair<string, int>& w,
                         std::list<std::pair<string, int>>* li) {
    auto it = li->begin();
    for (; it != li->end(); ++it) {
      if (w.second < it->second) {
        if (it == li->begin())
          return false;
        li->insert(it, w);
        remove_least(li);
        return true;
      } else if (w.second == it->second) {
        li->insert(it, w);
        return true;
      }
    }
    if (it == li->end()) {
      li->push_back(w);
      remove_least(li);
      return true;
    }
  }

  static void remove_least(std::list<std::pair<string, int>>* li) {
    int val = (li->front()).second;
    while (val == (li->front()).second)
      li->pop_front();
  }
};


template <typename pair_list_t>
void print_pair_list(const pair_list_t& li) {
  for (auto it=li.rbegin(); it!=li.rend(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
}

int main(int argc, char*arg[]) {
  int k = argc < 1 ? 3 : atoi(arg[1]);
  string s;
  std::map<string, int> w;
  while (std::cin >> s) {
    w[s]++;
  }
  // parse word from string
  //std::istringstream iss(str);
  //while (iss.good()) {
  //  string el;
  //  iss >> el;
  //  w[el]++;
  //}
  std::cout << "the top " << k << " words is:" << std::endl;
  std::list<std::pair<string, int>> top_key;
  WordFreq::get_top(k, w, &top_key);
  print_pair_list(top_key);
  return 0;
}

/******************************************************************************
 *  Copyright © 2000–2017, Jerick26. 
 *  Last updated: Tue Jan 6 EST 2017.
 ******************************************************************************/
