#include "bits/stdc++.h"

/*
 * Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
 * а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
 * 2 ≤ n ≤ 10000.
 */

int peak(int *A, int n) {
  if (A[0] > A[1])                   // Вырожденный случай - строго убывающий массив
    return 0;
  if (A[n - 2] < A[n - 1])           // Вырожденный случай - строго возрастающий массив
    return n - 1;
  int i = 1;
  bool fl = false;
  while (i < n - 1) {                 // За O(log m) находим интревал, содержаищий m, вида 2^i <= m <= 2^(i+1) или 2^i <= m < n
    if (A[i] > A[i + 1]) {            // Длина интревала - log m

      if (A[i - 1] < A[i])            // Нашли пик
        return i;
      fl = true;                      // fl = 1, если m <= 2^(i+1) < n
      break;
    }
    i *= 2;
  }
  int first = i / 2, last = i - 1;
  if (!fl) {
    last = n - 1;
  }
  while (first <= last) {             // За O(log m) классическим бинарным поиском находим m в интревале
    int mid = (first + last) / 2;
    if (A[mid] > A[mid + 1]) {
      if (A[mid - 1] < A[mid])
        return mid;
      else
        last = mid - 1;
    } else {                          // A[mid] < A[mid + 1]
      first = mid + 1;
    }
  }

}

int main(int argc, char **argv) {
  int n = 0;
  std::cin >> n;
  int *A = new int[n];

  for (int i = 0; i < n; i++) {
    std::cin >> A[i];
  }

  std::cout << peak(A, n);

  delete[]A;
}