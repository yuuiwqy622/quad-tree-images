#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int SIZE = 4;

bool im[SIZE][SIZE];

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

void print_image(FILE *in) {
  int cnt = rand() % 50;
  while (cnt--) {
    int i = rand() % SIZE, j = rand() % SIZE;
    im[i][j] = !im[i][j];
  }

  vector<bool> res = repr(0, 0, SIZE);

  res.insert(res.begin(), 1);
  size_t z = 4 - res.size() % 4;
  while (z != 4 && z--)
    res.insert(res.begin(), 0);

  for (size_t i = 0; i < res.size();) {
    int digit = 0;
    digit |= res[i++] << 3;
    digit |= res[i++] << 2;
    digit |= res[i++] << 1;
    digit |= res[i++];
    fprintf(in, "%X", digit);
  }
  fprintf(in, "\n");
}

int main() {
  srand(time(NULL));

  FILE *in = fopen("9.in", "w");
  const int cnt = 40;
  for (int i = 0; i < cnt; ++i)
    print_image(in);

  fprintf(in, "0\n0\n");
  fclose(in);
  return 0;
}