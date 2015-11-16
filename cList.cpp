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
    Node* centinel;
    Node* actualNode;
    
    static Node* copyNode(const Node* oNode, const Node* oSentinel, const Node* oActual, Node* &centinel, Node* &actual) {
      Node* newNode = new Node;
      if (oNode = oSentinel) {
				newNode->nextNode = newNode;
				newNode->prevNode = newNode;
				centinel = newNode;
				actual = newNode;
      }
      else {
				newNode.data = oNode.data;
				newNode->nextNode = copyNode(oNode->nextNode, oSentinel, oActual, centinel, actual);
				(newNode->nextNode)->prevNode = newNode;
				centinel->nextNode = newNode;
				newNode->prevNode = centinel;
				if (oActual == oNode) actual = newNode;
      }
      return newNode;
    }
    
    static void deleteNode(Node* actualNode, Node* centinel) {
      if(actualNode != centinel)
				deleteNode(actualNode->nextNode, centinel);
      delete actualNode;
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
  centinel = new Node;
  centinel->prevNode = centinel;
  centinel->nextNode = centinel;
  actualNode = centinel;
}

template <class T>
List<T>::List(const List& original) {
  dataSize = original.dataSize;
  Node* newNode = copyNode(original.centinel->nextNode, original.centinel, original.actualNode, centinel, actualNode);
}

template <class T>
List<T>::~List() {
  deleteNode(centinel->nextNode, centinel);
}

template <class T>
List<T>& List<T>::operator =(const List& original) {
  if (this != &original) {
    dataSize = original.dataSize;
    deleteNode(centinel->nextNode, centinel);
    Node* newNode = copyNode(original.centinel->nextNode, original.centinel, original.actualNode, centinel, actualNode);
  }
  return *this;
}

template <class T>
void List<T>::insert(const T& data) {
  Node* newNode = new Node;
  newNode->data = data;
  newNode->nextNode = actualNode;
  newNode->prevNode = actualNode->prevNode;
  (newNode->prevNode)->nextNode = newNode;
  actualNode->prevNode = newNode;
  dataSize = dataSize + 1;
}

template <class T>
void List<T>::erase() {
  Node* aux = actualNode;
  (actualNode->prevNode)->nextNode = actualNode->nextNode;
  (actualNode->nextNode)->prevNode = actualNode->prevNode;
  actualNode = actualNode->nextNode;
  delete aux;
  dataSize = dataSize-1;
}

template <class T>
void List<T>::concat(List& oldList) {
  if(oldList.dataSize > 0) {
    if(dataSize == 0) centinel = oldList.centinel;
    else {
      //Unimos las listas por el medio
      (centinel->prevNode)->nextNode = oldList.centinel->nextNode;
      (oldList.centinel->nextNode)->prevNode = centinel->prevNode;
      //Unimos el centinela con el primer elemento
      (centinel->nextNode)->prevNode = oldList.centinel;
      oldList.centinel->nextNode = centinel->nextNode;
      
      delete centinel;
      centinel = oldList.centinel;
    }
    actualNode = centinel->nextNode;
    dataSize += oldList.dataSize;
  }
}

template<class T>
void List<T>::clear() 
  deleteNode(centinel->nextNode, centinel);
  dataSize = 0;
  centinel = new Node;
  centinel->nextNode = centinel;
  centinel->prevNode = centinel;
  actualNode = centinel;
}

template<class T>
void List<T>::editActual(const T& data) {
  actualNode->data = data;
}

template<class T>
void List<T>::start() {
  actualNode = centinel->nextNode;
}

template<class T>
void List<T>::end() {
  actualNode = centinel;
}

template<class T>
void List<T>::goForward() {
  actualNode = actualNode->nextNode;
}

template<class T>
void List<T>::goBack() {
  actualNode = actualNode->prevNode;
}

template<class T>
bool List<T>::atFirst() const {
  return (actualNode == centinel->nextNode);
}

template<class T>
bool List<T>::atEnd() const {
  return (actualNode == centinel);
}

template<class T>
int List<T>::size() const {
  return dataSize;
}

template<class T>
bool List<T>::empty() const {
  return (dataSize == 0);
}

template<class T>
T List<T>::actual() const {
  return actualNode->data;
}