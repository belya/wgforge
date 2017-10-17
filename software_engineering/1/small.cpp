#include <iostream>
using namespace std;

namespace binary {
  bool checkBinary(int number) {
    return !((number - 1) & number);
  }

  void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
  }

  void print(int number) {
    cout << "0x";
    for (int i = 7; i >= 0; i--)
      cout << ((number & (1 << i)) >> i);
    cout << endl;
  }

  int insert(int number, int insertion, int beginning, int end) {
    int mask = ((1 << end) - 1) - ((1 << beginning) - 1);
    int piece = (insertion << (beginning)) & mask;
    return (number & ~mask) + piece;
  }
}

namespace list {
  struct List {
    List* next;
    char content;
  };

  List* createNode(char content, List* next) {
    List* l = new List();
    l->content = content;
    l->next = next;
    return l;
  }

  // A -> B -> C -> D
  List* createSimple() {
    List* nodeD = createNode('D', NULL);
    List* nodeC = createNode('C', nodeD);
    List* nodeB = createNode('B', nodeC);
    List* nodeA = createNode('A', nodeB);
    return nodeA;
  }

  // A -> B -> C -> D -> B
  List* createLooped() {
    List* nodeD = createNode('D', NULL);
    List* nodeC = createNode('C', nodeD);
    List* nodeB = createNode('B', nodeC);
    List* nodeA = createNode('A', nodeB);
    nodeD->next = nodeB;
    return nodeA;
  }

  List* reverse(List* list) {
    List* previous = NULL;
    List* current = list;
    while(current != NULL) {
      List* next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    return previous;
  }

  void print(List* list) {
    while(list != NULL) {
      cout << list->content;
      list = list->next;
    }
    cout << endl;
  }

  List* remove(List* list, List* element) {
    if (list == element) {
      List* next = list->next;
      delete list;
      return next;
    } else {

    }
  }

  bool containsLoop(List* list) {
    if (list == NULL) return false;
    List* slow = list;
    List* fast = list;
    do {
      slow = slow->next;
      fast = fast->next;
      if (fast == NULL) return false;
      fast = fast->next;
      if (fast == NULL) return false;
    } while (slow != fast);
    return true;
  }
}

int main() {
  list::List* list;
  cout << "Reverse a list" << endl;
  list = list::createSimple();
  list::print(list);
  list = list::reverse(list);
  list::print(list);

  cout << endl << "Check if number is 2^n" << endl;
  cout << 124124 << ": " << binary::checkBinary(124124) << endl;
  cout << (1 << 7) << ": " << binary::checkBinary(1 << 7) << endl;

  cout << endl << "Swap variables" << endl;
  int a = 1;
  int b = 2;
  cout << "Before: " << a << " " << b << endl;
  binary::swap(a, b);
  cout << "After: " << a << " " << b << endl;

  // cout << endl << "Remove element from a list" << endl;
  // list = list::createSimple();
  // list::print(list);
  // list = list::remove(list, list);
  // list::print(list);
  // list = list::createSimple();
  // list::print(list);
  // list = list::remove(list, list->next);
  // list::print(list);
  // list = list::createSimple();
  // list::print(list);
  // list = list::remove(list, list->next->next->next);
  // list::print(list);

  cout << endl << "Check list loop" << endl;
  list = list::createSimple();
  list::print(list);
  cout << list::containsLoop(list) << endl;
  list = list::createLooped();
  cout << list::containsLoop(list) << endl;
  
  cout << endl << "Insert number into number" << endl;
  binary::print(10);
  binary::print(121);
  binary::print(binary::insert(127, 10, 3, 6));
  binary::print(binary::insert(127, 10, 3, 5));
  return 0;
}