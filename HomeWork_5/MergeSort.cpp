#include "bits/stdc++.h"


// Сравнение с помощью оператора
/*

template<class T>
void mySort(T *arr, int from, int to) {
  for (int i = from; i < to; i++) {
    for (int j = from; j < to - 1; j++) {
      if (arr[j + 1] < arr[j]) {
        if (arr[j + 1] < arr[j])
          std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}
*/



// Сравнение с помощью функции

/*
template<class T>
void mySort(T *arr, int from, int to, bool* (isLess)(const T&, const T&)) {
  for (int i = from; i < to; i++) {
    for (int j = from; j < to - 1; j++) {
      if (isLess(arr[j + 1], arr[j])) {
        if (isLess(arr[j + 1], arr[j]))
          std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}
 */

// 3
template<class T>
bool isLessDefault(T &l, T& r){
  return l < r;
}

//4
template<class T>
class IsLess {
 public:
  bool operator()(const T& l, const T& r) { return l < r; }
};

// Сравнение с помощью функтора
template<class T, class Compare>
void mySort(T *arr, int from, int to, Compare cmp) {
  for (int i = from; i < to; i++) {
    for (int j = from; j < to - 1; j++) {
      if (cmp(arr[j + 1], arr[j]))
        std::swap(arr[j], arr[j + 1]);
    }
  }
}


struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
};

bool operator< (Point &a, Point &b){
  if(a.x == b.x)
    return a.y < b.y;
  return a.x < b.x;
}

bool isLessX (Point &a, Point &b){
  return a.x < b.x;
}


int main() {
  int n = 0;
  std::cin >> n;
  Point *arr = new Point[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i].x >> arr[i].y;
  }

  // 10 2 24 12 8989 1 2 3 6 3

  mySort(arr, 0, n);

  for (int i = 0; i < n; i++) {
    std::cout << "(" << arr[i].x << "," << arr[i].y << ")" << std::endl;
  }

  delete[] arr;

  return 0;
}