#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

bool im[4][4];

vector<bool> repr(int y, int x, int size) {
  if (size == 1)
    return {1, im[y][x]};

  size >>= 1;
  vector<bool> res = repr(y, x, size);
  vector<bool> q2 = repr(y, x + size, size);
  vector<bool> q3 = repr(y + size, x, size);
  vector<bool> q4 = repr(y + size, x + size, size);

  if (res[0] && q2[0] && q3[0] && q4[0] && res[1] == q2[1] && res[1] == q3[1] &&
      res[1] == q4[1])
    return res;

  res.insert(res.begin(), 0);
  res.insert(res.end(), q2.begin(), q2.end());
  res.insert(res.end(), q3.begin(), q3.end());
  res.insert(res.end(), q4.begin(), q4.end());
  return res;
}

int main() {
  srand(time(NULL));

  int cnt = rand() % 50;
  while (cnt--) {
    int i = rand() % 4, j = rand() % 4;
    im[i][j] = !im[i][j];
  }

  vector<bool> res = repr(0, 0, 4);

  res.insert(res.begin(), 1);
  size_t r = res.size() % 4;
  while (r--)
    res.insert(res.begin(), 0);

  for (size_t i = 0; i < res.size();) {
    int digit = 0;
    digit |= res[i++] << 3;
    digit |= res[i++] << 2;
    digit |= res[i++] << 1;
    digit |= res[i++];
    printf("%X", digit);
  }
  printf("\n");
  return 0;
}