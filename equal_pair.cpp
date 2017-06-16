#include <iostream>
#include <string>
#include <vector>

using std::string;

void get_pairs(const std::vector<int>& a,
               const std::vector<int>& b,
               const std::vector<int>& out) {
  int cnt = 0;
  int j = 0;
  for (int i = 0; i < a.size(); i++) {
    for (; j < b.size(); j++) {
      if (a[i] == b[j]) {
        cnt++;
        break;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<int> a;
  string s;
  while (std::cin >> s)
    a.push_back(std::atoi(s.c_str()));
  std::vector<int> b;
  while (std::cin >> s)
    b.push_back(std::atoi(s.c_str()));
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::vector<int> out;
  get_pairs(a, b, out);
  std::cout << "equal pairs count: " << out.size() << std::endl;
  for (auto i : out)
    std::cout << i << std::endl;
  return 0;
}
