#include <iostream>
#include <stack>
using namespace std;

template <typename T> class Queue {
private:
  stack<T> first;
  stack<T> second;
public:
  void push(T element) {
    first.push(element);
  }

  T pop() {
    if (second.empty())
      while(!first.empty()) {
        T element = first.top();
        second.push(element);
        first.pop();
      }
    T element = second.top();
    second.pop();
    return element;
  }
};

int main() {
  Queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  cout << queue.pop();
  cout << queue.pop();
  queue.push(4);
  queue.push(5);
  queue.push(6);
  queue.push(7);
  cout << queue.pop();
  cout << queue.pop();
  queue.push(8);
  cout << queue.pop();
  cout << queue.pop();
  cout << queue.pop();
  cout << queue.pop() << endl;
  return 0;
}