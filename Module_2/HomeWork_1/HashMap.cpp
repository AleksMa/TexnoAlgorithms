/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 * когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 * 1_2. Для разрешения коллизий используйте двойное хеширование.
 */



#include "bits/stdc++.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;

const int DefaultHashTableSize = 8;
const int MaxAlphaNum = 3,
          MaxAlphaDen = 4;

const int GrowFactor = 2;

int Hash(const string &key, int tableSize) {
  int hash = 0;
  for (int i = 0; i < key.size(); i++)
    hash = (hash * 127 + key[i]) % tableSize;
  if (hash < 0)
    hash *= -1;
  return hash;
}

int DoubleHash(const string &key, int tableSize) {
  int hash = 0;
  for (int i = key.size() - 1; i >= 0; i--)
    hash = (hash * 127 + key[i]) % tableSize;
  hash = hash | 1;
  if (hash < 0)
    hash *= -1;
  return hash;
}

template<class T>
class HashTable {
 public:
  HashTable();

  bool Has(const T &key) const;
  bool Add(const T &key);
  bool Delete(const T &key);

 private:

  vector<T> table;
  vector<int> status;
  int keysCount;

  bool has(int hash, const T &key) const;
  void growTable();
};

template<class T>
HashTable<T>::HashTable() : keysCount(0) {
  table.resize(DefaultHashTableSize);
  status.resize(DefaultHashTableSize, 0);
}

template<class T>
bool HashTable<T>::Has(const T &key) const {
  int hash = Hash(key, table.size());
  return has(hash, key);
}

template<class T>
bool HashTable<T>::has(int hash, const T &key) const {
  int i = hash;
  int double_hash = DoubleHash(key, table.size());
  while (true) {
    if (table[i] == key && status[i] > 0) {
      return true;
    }
    if (status[i] == 0)
      return false;
    i += double_hash;
    if (i >= table.size())
      i -= table.size();
    if (i == hash)
      break;
  }
  return false;
}


template<class T>
bool HashTable<T>::Add(const T &key) {

  if (keysCount + 1 > table.size() * MaxAlphaNum / MaxAlphaDen);
    growTable();

  int hash = Hash(key, table.size());
  int firstDel = -1;

  int i = hash, double_hash = DoubleHash(key, table.size());
  while (true) {
    if (status[i] == 0)
      break;
    if(status[i] < 0 && firstDel < 0){
      firstDel = i;
    }
    if(table[i] == key)
      return false;
    i += double_hash;
    if (i >= table.size())
      i -= table.size();
    if (i == hash)
      return false;
  }
  i = firstDel >= 0 ? firstDel : i;
  table[i] = key;
  status[i] = 1;
  keysCount++;
  return true;
}

template<class T>
void HashTable<T>::growTable() {
  vector<T> newTable(table.size() * GrowFactor);
  vector<int> newStatus(status.size() * GrowFactor, 0);
  for (int i = 0; i < table.size(); i++) {
    if (status[i] == 0)
      continue;
    T t = table[i];
    int st = status[i];
    int newHash = Hash(t, newTable.size());
    int j = newHash, double_hash = DoubleHash(t, newTable.size());
    while (true) {
      if (newStatus[j] == 0)
        break;
      j += double_hash;
      if (j >= newTable.size())
        j -= newTable.size();
    }
    newTable[j] = t;
    newStatus[j] = st;
  }
  table = newTable;
  status = newStatus;
}

template<class T>
bool HashTable<T>::Delete(const T &key) {
  int hash = Hash(key, table.size());
  int i = hash;
  int double_hash = DoubleHash(key, table.size());
  while (true) {
    if (table[i] == key && status[i] > 0) {
      break;
    }
    if (status[i] == 0)
      return false;
    i += double_hash;
    if (i >= table.size())
      i -= table.size();
    if (i == hash)
      return false;
  }
  status[i] = -1;
  keysCount--;
  return true;
}

int main() {
  HashTable<string> table;
  char command = 0;
  string key;
  while (cin >> command >> key) {
    switch (command) {
      case '+':cout << (table.Add(key) ? "OK" : "FAIL") << "\n";
        break;
      case '-':cout << (table.Delete(key) ? "OK" : "FAIL") << "\n";
        break;
      case '?':cout << (table.Has(key) ? "OK" : "FAIL") << "\n";
        break;
      default:assert(false);
    }
  }
  return 0;
}