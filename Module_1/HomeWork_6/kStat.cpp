#include "bits/stdc++.h"


/*

 Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n).
Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент.
Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

*/

template<class T>
class Compare {
 public:
  bool operator()(const T &l, const T &r) {
    return l <= r;
  }
};

template<class T, class Compare>
int Partition(T *part, int n, Compare cmp) {
  if (n <= 1) {
    return 0;
  }
  int pos_pivot = rand() % n;
  const T pivot = part[pos_pivot];
  std::swap(part[pos_pivot], part[n - 1]);

  int i = 0, j;

  for (; i < n - 1 && cmp(part[i], pivot); ++i) {}
  j = i + 1;
  while (j < n - 1) {
    if (cmp(part[j], pivot)) {
      std::swap(part[i++], part[j]);
    }
    j++;
  }
  std::swap(part[i], part[n - 1]);

  return i;

}

template<class T, class Compare>
T kStatDC(T *source, int n, int k, Compare cmp) {

  while (1) {
    int part = Partition(source, n, cmp);

    if(part == k){
      return source[part];
    }
    else if (part > k) {
      n = part;
    } else {
      part++;
      source += part;
      n -= part;
      k -= part;
    }
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