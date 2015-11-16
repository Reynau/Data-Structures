#include <cstddef>

template <class T>
class Stack {
  private:
    struct Node {
      T data;
      Node* nextNode;
    };
    
    Node* topNode = NULL;
    int dataSize = 0;
    
    static Node* copyNode(Node* node) {
      Node* newNode = NULL;
      if (node) {
				newNode = new Node;
				newNode->data = node->data;
				newNode->nextNode = copy(node->nextNode);
      }
      return newNode;
    }
    static void deleteNode(Node* node) {
      if (node) {
				deleteNode(node->nextNode);
				delete node;
      }
    }
    
  public:
    Stack();
    Stack(const Stack& original);
    ~Stack();

    T top() const;
    bool empty() const;
    int size() const;
    
    void push(const T& data);
    void pop();
    void clear();
    
    Stack& operator =(const Stack& original);
};

template <class T>
Stack<T>::Stack() {}

template <class T>
Stack<T>::Stack(const Stack &original) {
  if (this != &original) {
    dataSize = original.dataSize;
    topNode = copy(original.topNode);
  }
}

template <class T>
Stack<T>::~Stack() {
  deleteNode(this->topNode);
}

template <class T>
Stack<T>& Stack<T>::operator =(const Stack& original) {
  if (this != &original) {
    dataSize = original.dataSize;
    deleteNode(topNode);
    topNode = copyNode(original.topNode);
  }
  return *this;
}

template <class T>
T Stack<T>::top() const {
  return topNode->data;
}

template <class T>
void Stack<T>::push(const T& data) {
  Node* newTop = new Node;
  newTop->data = data;
  newTop->nextNode = topNode;
  topNode = newTop;
  
  dataSize = dataSize + 1;
}

template <class T>
void Stack<T>::pop() {  
  Node* auxNode = topNode;
  topNode = topNode->nextNode;
  delete auxNode;
  
  dataSize = dataSize - 1;
}

template <class T>
bool Stack<T>::empty() const {
  return (topNode == NULL);
}

template <class T>
int Stack<T>::size() const {
  return dataSize;
}

template <class T>
void Stack<T>::clear() {
  deleteNode(topNode);
  topNode = NULL;
  dataSize = 0;
}