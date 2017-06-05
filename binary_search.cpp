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
