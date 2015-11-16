#include <cstddef>

template <class T>
class List {
  private:
    struct Node {
      T data;
      Node* nextNode;
      Node* prevNode;
    };
    
    int dataSize;
    Node* firstNode;
    Node* lastNode;
    Node* actualNode;

    static Node* copyNode(const Node* originalNode, const Node* oActNode, Node* &actualNode, Node* &lastNode) {
      Node* newNode;
      if (!originalNode) {
				newNode = NULL;
				actualNode = NULL;
				lastNode = NULL;
      }
      else {
				newNode = new Node;
				newNode->data = originalNode.data;
				newNode->prevNode = NULL;
				newNode->nextNode = copyNode(originalNode.nextNode, oActNode, actualNode, lastNode);
				if (newNode->nextNode != NULL) (newNode->nextNode)->prevNode = newNode;
				else lastNode = newNode;
				if(oActNode == originalNode) actualNode = newNode;
      }
      return newNode;
    }
    
    static void deleteNode(const Node* oldNode) {
      if(!oldNode) {
				deleteNode(oldNode->nextNode);
				delete oldNode;
      }
    }

  public:
    List();
    List(const List& original);
    ~List();
    
    void insert(const T& data);
    void erase();
    void concat(List& oldList);
    void clear();
    void editActual(const T& data);
    void start();
    void end();
    void goForward();
    void goBack();
    
    bool atFirst() const;
    bool atEnd() const;
    int size() const;
    bool empty() const;
    T actual() const;
    
    List& operator =(const List& original);
};

template <class T>
List<T>::List() {
  dataSize = 0;
  firstNode = NULL;
  lastNode = NULL;
  actualNode = NULL;
}

template <class T>
List<T>::List(const List& original) {
  dataSize = original.dataSize;
  firstNode = copyNode(original.firstNode, original.actualNode, actualNode, lastNode);
}

template <class T>
List<T>::~List() {
  deleteNode(firstNode);
}

template <class T>
void List<T>::insert(const T& data) { 
  Node* newNode = new Node;
  newNode->data = data;
  newNode->nextNode = actualNode;
  if(dataSize == 0) {
    firstNode = newNode;
    lastNode = newNode;
  }
  else if (actualNode == firstNode) {
    newNode->prevNode = NULL;
    actualNode->prevNode = newNode;
    firstNode = newNode;
  }
  else if (actualNode == NULL) {
    lastNode->nextNode = newNode;
    newNode->prevNode = lastNode;
    lastNode = newNode;
  }
  else {
    (actualNode->prevNode)->nextNode = newNode;
    newNode->prevNode = actualNode->prevNode;
    actualNode->prevNode = newNode;
  }
  dataSize = dataSize + 1;
}

template <class T>
void List<T>::erase() {
  Node* oldNode = actualNode;
  if (dataSize == 1) {
    firstNode = NULL;
    lastNode = NULL;
  }
  else if (actualNode == firstNode) {
    firstNode = actualNode->nextNode;
    firstNode->prevNode = NULL;
  }
  else if (actualNode == lastNode) {
    lastNode = actualNode->prevNode;
    lastNode->nextNode = NULL;
  }
  else {
    (actualNode->prevNode)->nextNode = actualNode->nextNode;
    (actualNode->nextNode)->prevNode = actualNode->prevNode;
  }
  actualNode = actualNode->nextNode;
  delete oldNode;
  dataSize = dataSize - 1;
}

template<class T>
void List<T>::concat(List<T>& oldList) {
  if (oldList.dataSize != 0) {
    if(dataSize == 0) {
      firstNode = oldList.firstNode;
      lastNode = oldList.lastNode;
      dataSize = oldList.dataSize;
    }
    else {
      lastNode->nextNode = oldList.firstNode;
      oldList.firstNode->prevNode = lastNode;
      lastNode = oldList.lastNode;
      dataSize += oldList.dataSize;
    }
    oldList.firstNode = NULL;
    oldList.lastNode = NULL;
    oldList.actualNode = NULL;
    oldList.dataSize = 0;
  }
  actualNode = firstNode;
}

template<class T>
void List<T>::clear() {
  deleteNode(firstNode);
  firstNode = NULL;
  lastNode = NULL;
  actualNode = NULL;
  dataSize = 0;
}

template<class T>
void List<T>::editActual(const T& data) {
  actualNode->data = data;
}

template<class T>
void List<T>::start() {
  actualNode = firstNode;
}

template<class T>
void List<T>::end() {
  actualNode = lastNode;
}

template<class T>
void List<T>::goForward() {
  actualNode = actualNode->nextNode;
}

template<class T>
void List<T>::goBack() {
  if (actualNode == NULL) actualNode = lastNode;
  else actualNode = actualNode->prevNode;
}

template<class T>
bool List<T>::atFirst() const {
  return (actualNode == firstNode);
}

template<class T>
bool List<T>::atEnd() const {
  return (actualNode == lastNode);
}

template<class T>
int List<T>::size() const {
  return dataSize;
}

template<class T>
bool List<T>::empty() const {
  return (firstNode == NULL);
}

template<class T>
T List<T>::actual() const {
  return actualNode->data;
}

template<class T>
List<T>& List<T>::operator =(const List& original) {
  if(this != &original) {
    dataSize = original.dataSize;
    deleteNode(firstNode);
    firstNode = copyNode(original.firstNode, original.actualNode, actualNode, lastNode);
  }
  return *this;
}