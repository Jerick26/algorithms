/******************************************************************************
 *  Compilation:  g++ sum_zero_fast.cpp -std=c++0x -g
 *  Execution:    ./main n < input.txt
 *  Dependencies:
 *
 *  sum_zero_fast
 *    - find count of pairs or triples sum to 0
 *  % cat imput.txt
 *  -2 -1 0 1 2 3
 *  % ./main n < input.txt
 *  the result to count2 is: 2
 *  the result to count3 is: 3
 *
 ******************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::string;

class SumZeroFast {
public:
  // count pairs that sum to 0
  static int count2(std::vector<int>& a) {
    std::sort(a.begin(), a.end());
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
      if (std::binary_search(a.begin()+i+1, a.end(), -a[i]))
        cnt++;
    }
    return cnt;
  }
  // count triples that sum to 0
  static int count3(std::vector<int>& a) {
    std::sort(a.begin(), a.end());
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
      for (int j = i+1; j < a.size(); j++) {
        if (std::binary_search(a.begin()+j+1, a.end(), -a[i]-a[j]))
          cnt++;
      }
    }
    return cnt;
  }
};

int main(int argc, char* argv[]) {
  std::vector<int> a;
  string s;
  while (std::cin >> s)
    a.push_back(std::atoi(s.c_str()));
  std::cout << "the result to count2 is: " << SumZeroFast::count2(a)
      << std::endl;
  std::cout << "the result to count3 is: " << SumZeroFast::count3(a)
      << std::endl;
  return 0;
}
