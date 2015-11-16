#include <iostream>
  
using namespace std;

/*ostream y iostream no son templates, no entienden los cast dinámicos que se hacen con un template,
 *es por esto que se necesita redefinir la clase y el método antes que el template, para convertirlo en template
 *http://www.elrincondelc.com/nuevorincon/foros/viewtopic.php?t=13415&view=next&sid=02c39e45352bd867b56de65ebb1afd22
 */
template <class T> class Matriz;
template <class T> ostream& operator <<(ostream &salida, const Matriz<T> &mat);
template <class T> istream& operator >>(istream &entrada, Matriz<T> &mat);
/* --- */

template <class T> class Matriz {
  
private:
  
  int nfilas;
  int ncolumnas;
  T **matr = NULL;
  
  void borrar();
  
public:
  Matriz(int filas, int columnas);
  Matriz(const Matriz& m);
  ~Matriz();
  
  //Consultoras
  int filas() const;
  int columnas() const;
  T consultar(int fila, int columna) const;
  
  //Modificadora
  void modificar(int fila, int columna, T x);
  
  //Operadores
  Matriz<T>& operator =(const Matriz &b);
  
  void operator +=(const Matriz &mat);
  void operator -=(const Matriz &mat);
  
  Matriz<T> operator +(const Matriz &b) const;
  Matriz<T> operator -(const Matriz &b) const;
  Matriz<T> operator *(const Matriz &b) const;
  
  Matriz<T> operator *(int b) const;
  
  bool operator ==(const Matriz &b) const;
  bool operator !=(const Matriz &b) const;
  
  friend ostream& operator << <>(ostream &salida, const Matriz<T> &mat);
  friend istream& operator >> <>(istream &entrada, Matriz<T> &mat);
};

template <class T>
Matriz<T>::Matriz(int filas = 0, int columnas = 0) : nfilas(filas), ncolumnas(columnas) {
  if (nfilas > 0 and ncolumnas > 0) {
    matr = new T* [filas];
    for (int i = 0; i < filas; ++i) matr[i] = new T [columnas];
  }
}
  
template <class T>
Matriz<T>::Matriz(const Matriz &m) { 
  *this = m;
}
  
template <class T>
Matriz<T>::~Matriz() {
  borrar();
}
  
template <class T>
void Matriz<T>::borrar() {
  if (this->matr != NULL) {
    for (int i = 0; i < nfilas; ++i) delete[] matr[i];
    delete[] matr;
    matr = NULL;
  }
}
  
template <class T>
int Matriz<T>::filas() const { 
  return nfilas;
}
  
template <class T>
int Matriz<T>::columnas() const { 
  return ncolumnas;
}
  
template <class T>
T Matriz<T>::consultar(int fila, int columna) const {
  return matr[fila][columna];
}
  
template <class T>
void Matriz<T>::modificar(int fila, int columna, T x) {
  matr[fila][columna] = x;
}
  
template <class T>
Matriz<T>& Matriz<T>::operator =(const Matriz &mat) {
  if (this != &mat) {
    this->borrar();
  
    if (mat.matr) {
      this->nfilas = mat.nfilas;
      this->ncolumnas = mat.ncolumnas;
  
      this->matr = new T* [nfilas];
      for (int i = 0; i < nfilas; ++i)
        this->matr[i] = new T [ncolumnas];
  
      for (int i = 0; i < nfilas; ++i) {
        for (int j = 0; j < ncolumnas; ++j)
          this->matr[i][j] = mat.matr[i][j];
      }
    }
  }
  return *this;
}
  
template <class T>
void Matriz<T>::operator +=(const Matriz &mat) {
  if (this->nfilas != 0 and this->ncolumnas != 0 and mat.nfilas != 0 and mat.ncolumnas != 0) {
    for (int i = 0; i < nfilas; ++i)
      for (int j = 0; j < ncolumnas; ++j)
        this->matr[i][j] += mat.matr[i][j];
  }
}
  
template <class T>
void Matriz<T>::operator -=(const Matriz &mat) {
  if (this->nfilas != 0 and this->ncolumnas != 0 and mat.nfilas != 0 and mat.ncolumnas != 0) {
    for (int i = 0; i < nfilas; ++i)
      for (int j = 0; j < ncolumnas; ++j)
        this->matr[i][j] -= mat.matr[i][j];
  }
}
  
template <class T>
Matriz<T> Matriz<T>::operator +(const Matriz &b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz<T> res(filas, columnas);
  
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j)
      res.matr[i][j] = this->matr[i][j] + b.matr[i][j];
  
  return res;
}
  
template <class T>
Matriz<T> Matriz<T>::operator -(const Matriz &b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz<T> res(filas, columnas);
  
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j)
      res.matr[i][j] = this->matr[i][j] - b.matr[i][j];
  
  return res;
}
  
template <class T>
Matriz<T> Matriz<T>::operator *(const Matriz &b) const {
  if (this->ncolumnas == b.nfilas) {
    int pos = this->ncolumnas;
  
    int filas = this->nfilas;
    int columnas = b.ncolumnas;
  
    Matriz<T> res(filas, columnas);
    for (int i = 0; i < filas; ++i) {
      for (int j = 0; j < columnas; ++j) {
        T value = 0;
        for (int k = 0; k < pos; ++k) value += this->matr[i][k] * b.matr[k][j];
        res.matr[i][j] = value;
      }
    }
    return res;
  }
}
  
template <class T>
Matriz<T> Matriz<T>::operator *(int b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz res(filas, columnas);
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j)
			res.matr[i][j] = this->matr[i][j] * b;
  
  return res;
}
  
template <class T>
Matriz<T> operator *(int a, const Matriz<T> &b) { 
  return b*a;
}
  
template <class T>
bool Matriz<T>::operator ==(const Matriz &b) const {
  if (this->nfilas != b.nfilas or this->ncolumnas != b.ncolumnas) return false;
  for (int i = 0; i < this->nfilas; ++i)
    for (int j = 0; j < this->ncolumnas; ++j)
      if (this->matr[i][j] != b.matr[i][j]) return false;
  
  return true;
}
  
template <class T>
bool Matriz<T>::operator !=(const Matriz<T> &b) const {
  if (this->nfilas != b.nfilas or this->ncolumnas != b.ncolumnas) return true;
  for (int i = 0; i < this->nfilas; ++i)
    for (int j = 0; j < this->ncolumnas; ++j)
      if (this->matr[i][j] != b.matr[i][j]) return true;
  
  return false;
}
  
template <class T>
ostream& operator <<(ostream &salida, const Matriz<T> &mat) {
  for (int i = 0; i < mat.nfilas; ++i) {
    for (int j = 0; j < mat.ncolumnas; ++j) salida << mat.matr[i][j] << " ";
    salida << endl;
  }
  return salida;
}
  
template <class T>
istream& operator >>(istream &entrada, Matriz<T> &mat) {
  for (int i = 0; i < mat.nfilas; ++i)
    for (int j = 0; j < mat.ncolumnas; ++j) entrada >> mat.matr[i][j];
  return entrada;
}