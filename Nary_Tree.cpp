#include <cstddef>
#include <vector>

using namespace std;

template<class T>
class Tree {
	private:
		struct Node {
			T data;
			vector<Node*> cVect;
		};
		int N;
		Node* rootNode;

		static Node* copyNode(const Node* oNode) {
			Node* newNode;
			if (oNode != NULL) {
				newNode = new Node;
				newNode->data = oNode->data;
				int N = oNode->cVect.size();
				newNode->cVect = vector<Node*>(N);
				for(int i=0; i<N; ++i)
					newNode->cVect[i] = copyNode(oNode->cVect[i]);
			}
			else newNode = NULL;
			return newNode;
		}

		static void deleteNode(Node* oNode) {
			if (oNode != NULL) {
				int N = oNode->cVect.size();
				for(int i=0; i<N; ++i) deleteNode(oNode->cVect[i]);
				delete oNode;
			}
		}

	public:
		Tree(int n);
		Tree(const T& data, int n);
		Tree(const Tree& oTree);
		~Tree();
		Tree& operator =(const Tree& oTree);
		void clear();
		void plant(const T& data, vector<Tree>& oVect);
		void childs(vector<Tree>& tVect);
		T root();
		bool empty();
		int cNumb();
};

template<class T>
Tree<T>::Tree(int n) {
  N = n;
  rootNode = NULL;
}

template<class T>
Tree<T>::Tree(const T& data, int n) {
  N = n;
  rootNode = new Node;
  rootNode->data = data;
  rootNode->cVect = vector<Node*>(N);
}

template<class T>
Tree<T>::Tree(const Tree& oTree) {
  int N = oTree.rootNode.size();
  rootNode = copyNode(oTree.rootNode);
}

template<class T>
Tree<T>::~Tree() {
  deleteNode(rootNode);
}

template<class T>
Tree<T>& Tree<T>::operator =(const Tree& oTree) {
  if (this != &oTree) {
    N = oTree.N;
    deleteNode(rootNode);
    rootNode = copyNode(oTree.rootNode);
  }
  return *this;
}

template<class T>
void Tree<T>::clear() {
  N = 0;
  deleteNode(rootNode);
  rootNode = NULL;
}

template<class T>
void Tree<T>::plant(const T& data, vector<Tree>& oVect) {
  rootNode = new Node;
  rootNode->data = data;
  int N = oVect.size();
  rootNode->cVect = vector<Node*>(N);
  for(int i=0; i<N; ++i) {
    rootNode->cVect[i] = oVect[i].rootNode;
    oVect[i].rootNode = NULL;
  }
}

template<class T>
void Tree<T>::childs(vector<Tree>& tVect) {
  tVect = vector<Tree>(N, Tree(N));
  for(int i=0; i<N; ++i) tVect.rootNode = rootNode->cVect[i];
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

template<class T>
int Tree<T>::cNumb() {
  return N;
}
