#include<assert.h>
#include<iostream>
#include<vector>
#include<string>

using std::vector;
using std::string;
using std::cin;
using std::cout;

const int DefaultHashTableSize = 8;
const int MaxAlpha = 3;
const int GrowFactor = 2;

int Hash( const string& key, int tableSize )
{
  int hash = 0;
  for( int i = 0; i < key.size(); i++ )
    hash = (hash * 127 + key[i]) % tableSize;
  return hash;
}

template<class T>
struct HashTableNode {
  T Data;
  HashTableNode<T>* Next;

  HashTableNode() : Next(nullptr) {}
  HashTableNode( const T& data, HashTableNode<T>* next ) : Data(data), Next(next) {}
};

template<class T>
class HashTable {
 public:
  HashTable();
  ~HashTable();

  bool Has( const T& key ) const;
  bool Add( const T& key );
  bool Delete( const T& key );

 private:

  vector<HashTableNode<T>*> table;
  int keysCount;

  bool has( int hash, const T& key ) const;
  void growTable();
};

template<class T>
HashTable<T>::HashTable() : keysCount(0)
{
  table.resize( DefaultHashTableSize, nullptr );
}

template<class T>
HashTable<T>::~HashTable()
{
  for( int i = 0; i < table.size(); i++ ) {
    HashTableNode<T>* node = table[i];
    while( node != nullptr ) {
      HashTableNode<T>* nextNode = node->Next;
      delete node;
      node = nextNode;
    }
  }
}

template<class T>
bool HashTable<T>::Has( const T& key ) const
{
  int hash = Hash( key, table.size() );
  return has( hash, key );
}

template<class T>
bool HashTable<T>::has( int hash, const T& key ) const
{
  HashTableNode<T>* node = table[hash];
  while( node != nullptr ) {
    if( node->Data == key ) {
      return true;
    }
    node = node->Next;
  }
  return false;
}

template<class T>
bool HashTable<T>::Add( const T& key )
{
  int hash = Hash( key, table.size() );
  if( has( hash, key ) )
    return false;

  if( keysCount + 1 > MaxAlpha * table.size() )
    growTable();

  table[hash] = new HashTableNode<T>( key, table[hash] );
  keysCount++;
  return true;
}

template<class T>
void HashTable<T>::growTable()
{
  vector<HashTableNode<T>*> newTable(table.size() * GrowFactor, nullptr);
  for( int i = 0; i < table.size(); i++ ) {
    HashTableNode<T>* node = table[i];
    while( node != nullptr ) {
      HashTableNode<T>* nextNode = node->Next;
      int newHash = Hash( node->Data, newTable.size() );
      node->Next = newTable[newHash];
      newTable[newHash] = node;
      node = nextNode;
    }
  }
  table = newTable;
}

template<class T>
bool HashTable<T>::Delete( const T& key )
{
  int hash = Hash( key, table.size() );
  HashTableNode<T>* prevNode = nullptr;
  HashTableNode<T>* node = table[hash];
  while( node != nullptr && node->Data != key ) {
    prevNode = node;
    node = node->Next;
  }

  if( node == nullptr )
    return false;

  if( prevNode == nullptr )
    table[hash] = node->Next;
  else
    prevNode->Next = node->Next;

  delete node;
  keysCount--;
  return true;
}

int main()
{
  HashTable<string> table;
  char command = 0;
  string key;
  while( cin >> command >> key ) {
    switch( command ) {
      case '+':
        cout << (table.Add( key ) ? "OK" : "FAIL") << "\n";
        break;
      case '-':
        cout << (table.Delete( key ) ? "OK" : "FAIL") << "\n";
        break;
      case '?':
        cout << (table.Has( key ) ? "OK" : "FAIL") << "\n";
        break;
      default:
        assert( false );
    }
  }
  return 0;
}