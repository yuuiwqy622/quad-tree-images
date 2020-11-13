#include <stdio.h>

char line1[400], line2[400], inter[800];
int len, idx1, idx2;

void fill(char line[400]) {
  char buf[102];
  fgets(buf, 101, stdin);
  int digit;
  for (int i = 0; sscanf(buf + i, "%1x", &digit) == 1; ++i) {
    line[4 * i] = digit >> 3 & 1;
    line[4 * i + 1] = digit >> 2 & 1;
    line[4 * i + 2] = digit >> 1 & 1;
    line[4 * i + 3] = digit & 1;
  }
}

void intersection(char het1, char het2) {
  if (line1[idx1] && line2[idx2]) {
    inter[len++] = 1, inter[len++] = line1[idx1 + 1] & line2[idx2 + 1];
    idx1 += 2 * het1, idx2 += 2 * het2;
    return;
  }

  inter[len++] = 0;
  int het3 = line1[idx1] == 0, het4 = line2[idx2] == 0;
  idx1 += het3, idx2 += het4;
  int q1 = len;
  intersection(het3, het4);
  int q2 = len;
  intersection(het3, het4);
  int q3 = len;
  intersection(het3, het4);
  int q4 = len;
  intersection(het3, het4);
  idx1 += 2 * (het1 && het4 && !het3);
  idx2 += 2 * (het2 && het3 && !het4);

  if (inter[q1] && inter[q2] && inter[q3] && inter[q4] &&
      inter[q1 + 1] == inter[q2 + 1] && inter[q1 + 1] == inter[q3 + 1] &&
      inter[q1 + 1] == inter[q4 + 1]) {
    inter[q1 - 1] = 1, inter[q1] = inter[q1 + 1];
    len -= 7;
  }
}

int main(void) {
  for (int im = 1;; ++im) {
    int c = getchar();
    if (c == '0') {
      getchar();
      getchar();
      getchar();
      return 0;
    }

    ungetc(c, stdin);
    fill(line1);
    fill(line2);

    len = idx1 = idx2 = 0;
    for (; line1[idx1] == 0; ++idx1)
      ;
    for (; line2[idx2] == 0; ++idx2)
      ;
    ++idx1, ++idx2;
    intersection(0, 0);
    printf("Image %d:\n", im);

    int digit = 0, idx = 0;
    int r = len % 4;

    digit |= 1 << r;
    while (r--)
      digit |= inter[idx++] << r;
    printf("%X", digit);

    for (; idx < len;) {
      digit = 0;
      digit |= inter[idx++] << 3;
      digit |= inter[idx++] << 2;
      digit |= inter[idx++] << 1;
      digit |= inter[idx++];
      printf("%X", digit);
    }
    printf("\n\n");
  }

  return 0;
}