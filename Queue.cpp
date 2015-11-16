#include <cstddef>

template <class T>
class Queue {
  private:
    struct Node {
      T data;
      Node* prevNode;
    };
    
    int dataSize;
    Node* frontNode;
    Node* lastNode;
    
    static Node* copyNode(Node* node, Node* last) {
      Node* newNode = NULL;
      if(node) {
				newNode = new Node;
				newNode->data = node->data;
				newNode->prevNode = copyNode(node->prevNode);
				if (newNode->nextNode == NULL) last = newNode;
      }
      return newNode;
    }
    
    static void deleteNode(Node* node) {
      if(node) {
				deleteNode(node->prevNode);
				delete node;
      }
    }

  public:
    Queue();
    Queue(const Queue& original);
    ~Queue();
    
    T front() const;
    bool empty() const;
    int size() const;
    
    void push(const T &data);
    void pop();
    void clear();
    
    Queue& operator =(const Queue& original);
};

template <class T>
Queue<T>::Queue() {
  dataSize = 0;
  frontNode = NULL;
  lastNode = NULL;
}

template <class T>
Queue<T>::Queue(const Queue& original) {
  if (this != &original) {
    dataSize = original.dataSize;
    frontNode = copyNode(original.frontNode);
  }
}

template <class T>
Queue<T>::~Queue() {
  deleteNode(frontNode);
}

template <class T>
T Queue<T>::front() const {
  return frontNode->data;
}

template <class T>
bool Queue<T>::empty() const {
  return (frontNode == NULL);
}

template <class T>
int Queue<T>::size() const {
  return dataSize;
}

template <class T>
void Queue<T>::push(const T &data) { 
  Node* newNode = new Node;
  newNode->data = data;
  newNode->prevNode = NULL;
  if (!frontNode) frontNode = newNode;
  else lastNode->prevNode = newNode;
  lastNode = newNode;
  
  dataSize = dataSize + 1;
}

template <class T>
void Queue<T>::pop() { 
  Node* aux = frontNode;
  frontNode = frontNode->prevNode;
  delete aux;
  
  dataSize = dataSize - 1;
}

template <class T>
void Queue<T>::clear() { 
  deleteNode(frontNode);
  frontNode = NULL;
  lastNode = NULL;
  dataSize = 0;
}

template <class T>
Queue<T>& Queue<T>::operator =(const Queue& original) {
  if (this != &original) {
    dataSize = original.dataSize;
    deleteNode(frontNode);
    frontNode = copyNode(original.frontNode);
  }
  return *this;
}