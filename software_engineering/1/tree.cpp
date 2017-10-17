#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Tree {
  Tree* parent;
  Tree* leftChild;
  Tree* rightSibling;
  char content;
};

void setParent(Tree* child, Tree* parent) {
  if (child != NULL) {
    child->parent = parent;
    setParent(child->rightSibling, parent);
  }
}

Tree* createNode(Tree* leftChild, Tree* rightSibling, char content) {
  Tree* t = new Tree;
  t->parent = NULL;
  t->leftChild = leftChild;
  setParent(leftChild, t);
  t->rightSibling = rightSibling;
  t->content = content;
  return t;
}

Tree* initializeTree() {
  Tree* nodeB = createNode(NULL, NULL, 'B');
  Tree* nodeF = createNode(NULL, NULL, 'F');
  Tree* nodeO = createNode(NULL, NULL, 'O');
  Tree* nodeG = createNode(nodeF, NULL, 'G');
  Tree* nodeT = createNode(nodeO, nodeG, 'T');
  Tree* nodeD = createNode(NULL, nodeT, 'D');
  Tree* nodeE = createNode(nodeD, NULL, 'E');
  Tree* nodeA = createNode(nodeB, nodeE, 'A');
  Tree* nodeC = createNode(nodeA, NULL, 'C');
  return nodeC;
}

namespace recursive {
  void preorderTraversal(Tree* node) {
    cout << node->content;
    if (node->leftChild != NULL) 
      preorderTraversal(node->leftChild);
    if (node->rightSibling != NULL)
      preorderTraversal(node->rightSibling);
  }

  void postorderTraversal(Tree* node) {
    if (node->leftChild != NULL) 
      postorderTraversal(node->leftChild);
    cout << node->content;
    if (node->rightSibling != NULL)
      postorderTraversal(node->rightSibling); 
  }

  void traverseLevel(queue<Tree*> nodeQueue) {
    if (!nodeQueue.empty()) {
      Tree* node = nodeQueue.front();
      nodeQueue.pop();
      cout << node->content;
      if (node->rightSibling != NULL)
        nodeQueue.push(node->rightSibling);
      if (node->leftChild != NULL)
        nodeQueue.push(node->leftChild);
      traverseLevel(nodeQueue);
    }
  }

  void levelTraversal(Tree* node) {
    queue<Tree*> nodeQueue;
    nodeQueue.push(node);
    traverseLevel(nodeQueue);
  }
}

namespace iterative {
  void preorderTraversal(Tree* node) {
    stack<Tree*> nodeStack;
    nodeStack.push(node);
    while(!nodeStack.empty()) {
      node = nodeStack.top();
      cout << node->content;
      nodeStack.pop();
      if (node->rightSibling != NULL)
        nodeStack.push(node->rightSibling);
      if (node->leftChild != NULL)
        nodeStack.push(node->leftChild);
    }
  }

  void postorderTraversal(Tree* node) {
    bool descent = true;
    while (true) {
      if (descent == true) {
        if (node->leftChild != NULL)
          node = node->leftChild;
        else {
          cout << node->content;
          if (node->rightSibling != NULL)
            node = node->rightSibling;
          else {
            node = node->parent;
            descent = false;
          }
        }
      } else {
        cout << node->content;
        if (node->rightSibling != NULL) {
          node = node->rightSibling;
          descent = true;
        } else {
          if (node->parent != NULL)
            node = node->parent;
          else break;
        }
      }
    }
  }

  void levelTraversal(Tree* node) {
    queue<Tree*> nodeQueue;
    nodeQueue.push(node);
    while(!nodeQueue.empty()) {
      node = nodeQueue.front();
      nodeQueue.pop();
      cout << node->content;
      node = node->leftChild;
      while(node != NULL) {
        nodeQueue.push(node);
        node = node->rightSibling;
      }
    }
  }
}

int main() {
  //    C
  //  /    \
  // A      E
  //  \   / | \
  //   B D  T  G
  //       /  /
  //      O  F
  Tree* root = initializeTree();
  // C A B E D T O G F
  recursive::preorderTraversal(root);
  cout << endl;
  iterative::preorderTraversal(root);
  cout << endl;
  // B A D O T F G E C 
  recursive::postorderTraversal(root);
  cout << endl;
  iterative::postorderTraversal(root);
  cout << endl;
  // C A E B D T G O F
  recursive::levelTraversal(root);
  cout << endl;
  iterative::levelTraversal(root);
  cout << endl;
  
  return 0;
}