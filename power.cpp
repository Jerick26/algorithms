public int pow(double x, int n) {
  int k = n < 0 ? -n : n;
  bool inv = (n < 0);
  int y = 1;
  while (k > 0) {
    if (k % 2 != 0) y = y * x;
    x = x * x;
    k = k >> 1;
  }
  if (inv) y = 1 / y;
  return y;
}
