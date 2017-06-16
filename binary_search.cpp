#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;

int rank(int a[], int lo, int hi, int key) {
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (key > a[mid])       lo = mid + 1;
    else if (key < a[mid])  hi = mid - 1;
    else                    return mid;
  }
  return -1;
}

/*
 * recursive
 */
int rank(int a[], int lo, int hi, int key) {
  if (lo > hi)    return -1;
  int mid = (lo + hi) / 2;
  if (key > a[mid])       rank(a, mid+1, hi, key);
  else if (key < a[mid])  rank(a, lo, mid-1, key);
  else                    return mid;
}

int binary_search(const std::vector<int>& a, int lo, int hi, int v);
int binary_search(const std::vector<int>& a, int v);

int binary_search(const std::vector<int>& a, int v) {
  return binary_search(a, 0, a.size()-1, v);
}

int binary_search(const std::vector<int>& a, int lo, int hi, int v) {
  if (a.size() == 0)
    return -1;
  while (lo <= hi) {
    int mid = (hi + lo) / 2;
    if (a[mid] < v) {
      lo = mid + 1;
    } else if (a[mid] > v) {
      hi = mid - 1;
    } else {
      return mid;
    }
  }
  return -1;
}

int lower_bound(const std::vector<int>& a, int v) {
  int lo = 0, hi = a.size() - 1;
  while (hi > lo) {
    int mid = (lo + hi) / 2;
    if (a[mid] < v) {
      lo = mid + 1;
    } else if (a[mid] > v) {
      hi = mid - 1;
    } else {
      hi = mid;
    }
  }
  if (lo > hi || hi < 0 || lo >= a.size())
    return -1;
  return lo;
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
}
