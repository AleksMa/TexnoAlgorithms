#include "bits/stdc++.h"

/*
 *
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка [Li, Ri].
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 * N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
 *
 *
 */


struct Segment {
  int l;
  int r;
  Segment() : l(0), r(0) {}
};

struct Delta {
  int x;
  int diff;
  Delta() : x(0), diff(0) {}
};



template<class T>
class Compare {
 public:
  bool operator()(const T &l, const T &r) {
    return l < r;
  }
};



template<class T, class Compare>
void merge(T *first_l, T *first_r, T *second_l, T *second_r, T *dest, Compare cmp) {
  while (first_l != first_r && second_l != second_r) {
    T min = *first_l++;
    if (!cmp(*(first_l - 1), *second_l)) {
      min = *second_l++;
      first_l--;
    }
    *dest++ = min;
  }
  T *left = first_l, *right = first_r;
  if (first_l == first_r){
    left = second_l, right = second_r;
  }

  while(left != right){
    *dest++ = *left++;
  }
}

template<class T, class Compare>
void msort(T *from, T *to, Compare cmp) {
  ptrdiff_t len = to - from;
  if (len <= 1)
    return;
  T *mid = from + len / 2;

  msort(from, mid, Compare());
  msort(mid, to, Compare());

  T *temp = new T[len];
  merge(from, mid, mid, to, temp, cmp);

  memcpy(from, temp, len * sizeof(Delta));

  delete[] temp;

}

bool operator<(const Delta &a, const Delta &b) {
  return a.x < b.x;
}

int one_layer(Segment *source, int n) {
  int count = 0;
  Delta *arr = new Delta[2 * n];

  for (int i = 0; i < n; i++) {
    arr[2 * i].x = source[i].l;
    arr[2 * i].diff = 1;

    arr[2 * i + 1].x = source[i].r;
    arr[2 * i + 1].diff = -1;
  }

  msort(arr, arr + 2 * n, Compare<Delta>());

  int current_layer = 0, left = -1;

  for (int i = 0; i < 2 * n; i++) {
    current_layer += arr[i].diff;
    if (left < 0 && current_layer)
      left = arr[i].x;
    else if (left >= 0 && !current_layer) {
      count += arr[i].x - left;
      left = -1;
    }
  }



  delete[] arr;
  return count;
}

int main() {
  int n = 0;
  std::cin >> n;
  Segment *arr = new Segment[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i].l >> arr[i].r;
  }

  std::cout << one_layer(arr, n);

  delete[] arr;

  return 0;
}