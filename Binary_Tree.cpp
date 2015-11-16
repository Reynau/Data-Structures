#include <cstddef>

template <class T>
class Tree {
	private:
		struct Node {
			T data;
			Node* lChild;
			Node* rChild;
		};

		Node* rootNode;

		static Node* copyNode(Node* oNode) {
			Node* newNode;
			if (oNode == NULL) newNode = NULL;
			else {
				newNode = new Node;
				newNode->data = oNode->data;
				newNode->lChild = copyNode(oNode->lChild);
				newNode->rChild = copyNode(oNode->rChild);
			}
			return newNode;
		}
		static void deleteNode(Node* oNode) {
			if(oNode != NULL) {
				deleteNode(oNode->lChild);
				deleteNode(oNode->rChild);
				delete oNode;
			}
		}
		
	public:
		Tree();
		Tree(const Tree& oTree);
		~Tree();
		Tree& operator =(const Tree& oTree);
		void clear();
		void plant(const T& data, Tree& a1, Tree& a2);
		void childs(Tree& a1, Tree& a2);
		T root();
		bool empty();
};

template<class T>
Tree<T>::Tree() {
  rootNode = NULL;
}

template<class T>
Tree<T>::Tree(const Tree& oTree) {
  rootNode = copyNode(oTree.rootNode);
}

template<class T>
Tree<T>::~Tree() {
  deleteNode(rootNode);
}

template<class T>
Tree<T>& Tree<T>::operator =(const Tree& oTree) {
  if(this != &oTree) {
    deleteNode(rootNode);
    rootNode = copyNode(oTree.rootNode);
  }
  return *this;
}

template<class T>
void Tree<T>::clear() {
  deleteNode(rootNode);
  rootNode = NULL;
}

template<class T>
void Tree<T>::plant(const T& data, Tree& a1, Tree& a2) {
  rootNode = new Node;
  rootNode->data = data;
  rootNode->lChild = a1.rootNode;
  if (a1.rootNode != a2.rootNode or a2.rootNode == NULL) rootNode->rChild = a2.rootNode;
  else rootNode->rChild = copyNode(a2.rootNode);
  a1.rootNode = NULL;
  a2.rootNode = NULL;
}

template<class T>
void Tree<T>::childs(Tree& a1, Tree& a2) {
  a1.rootNode = rootNode->lChild;
  a2.rootNode = rootNode->rChild;
  delete rootNode;
  rootNode = NULL;
}

template<class T>
T Tree<T>::root() {
  return rootNode->data;
}

template<class T>
bool Tree<T>::empty() {
  return (rootNode == NULL);
}
