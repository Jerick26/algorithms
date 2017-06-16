/******************************************************************************
 *  Compilation:  g++ binary_search.cpp -std=c++0x -g
 *  Execution:    ./main n < input.txt
 *  Dependencies:
 *
 *  binary search
 *    - find the index in an array to a indicated v
 *  % cat imput.txt
 *  1 2 3 3 4 4 4 5
 *  % ./main 4 < input.txt
 *  lower bound is: 4
 *  upper bound is: 6
 *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;

int rank(int a[], int lo, int hi, int key) {
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if      (key > a[mid])  lo = mid + 1;
    else if (key < a[mid])  hi = mid - 1;
    else                    return mid;
  }
  return -1;
}

/*
 * recursive
 */
int rank_recursive(int a[], int lo, int hi, int key) {
  if (lo > hi)    return -1;
  int mid = (lo + hi) / 2;
  if      (key > a[mid])  rank(a, mid+1, hi, key);
  else if (key < a[mid])  rank(a, lo, mid-1, key);
  else                    return mid;
}

int lower_bound(const std::vector<int>& a, int v) {
  int lo = 0, hi = a.size() - 1;
  while (hi > lo) {
    int mid = (lo + hi) / 2;
    if      (a[mid] < v)  lo = mid + 1;
    else if (a[mid] > v)  hi = mid - 1;
    else                  hi = mid;
  }
  if (lo == a.size() || a[lo] != v)
    return -1;
  return lo;
}

int upper_bound(const std::vector<int>& a, int v) {
  int lo = 0, hi = a.size() - 1;
  while (hi > lo) {
    int mid = (lo + hi + 1) / 2;
    if      (a[mid] < v)  lo = mid + 1;
    else if (a[mid] > v)  hi = mid - 1;
    else                  lo = mid;
  }
  if (hi == -1 || a[hi] != v)
    return -1;
  return hi;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "too few arguments to main" << std::endl;
    return -1;
  }
  int v = std::atoi(argv[1]);
  std::vector<int> a;
  string s;
  while (std::cin >> s)
    a.push_back(std::atoi(s.c_str()));
  std::sort(a.begin(), a.end());
  int idx = lower_bound(a, v);
  std::cout << "lower bound is: " << idx << std::endl;
  idx = upper_bound(a, v);
  std::cout << "upper bound is: " << idx << std::endl;
}
