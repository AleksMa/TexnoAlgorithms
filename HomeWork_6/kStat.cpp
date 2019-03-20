#include "bits/stdc++.h"

template<class T>
class Compare {
 public:
  bool operator()(const T &l, const T &r) {
    return l <= r;
  }
};

template<class T, class Compare>
int Partition(T *a, int n, Compare cmp) {
  if (n <= 1) {
    return 0;
  }
  int pos_pivot = rand() % n;
  //std::cout << pos_pivot << std::endl;
  const T pivot = a[pos_pivot];
  std::swap(a[pos_pivot], a[n - 1]);

  int i = 0, j;

  for (; i < n - 1 && cmp(a[i], pivot); ++i) {}
  j = i + 1;
  while (j < n - 1) {
    if (cmp(a[j], pivot)) {
      std::swap(a[i++], a[j]);
    }
    j++;
  }

  std::swap(a[i], a[n - 1]);

  /*
  std::cout << "& " << i << " " << n - 1 << std::endl;

  for (int l = 0; l < n; l++) {
    if (l == i)
      std::cout << "{" << a[l] << "}" << " ";
    else
      std::cout << a[l] << " ";
  }
  std::cout << std::endl;
*/

  return i;


}

template<class T, class Compare>
T kStatDC(T *source, int n, int k, Compare cmp) {

  int part = Partition(source, n, cmp);

  if (part == k) {
    return source[part];
  } else if (part > k) {
    return kStatDC(source, part, k, cmp);
  } else {
    part++;
    return kStatDC(source + part, n - part, k - part, cmp);
  }
}

int main() {
  int n = 0, k;
  std::cin >> n >> k;
  int *arr = new int[n];

  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  std::cout << kStatDC(arr, n, k, Compare<int>());

  delete[] arr;

  return 0;
}