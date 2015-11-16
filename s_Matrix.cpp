#include <iostream>
  
using namespace std;
  
class Matriz {
  
	private:
		
		int nfilas;
		int ncolumnas;
		double **matr = NULL;
		
		void borrar();
		
	public:
		Matriz(int filas, int columnas);
		Matriz(const Matriz& m);
		~Matriz();
		
		//Consultoras
		int filas() const;
		int columnas() const;
		double consultar(int fila, int columna) const;
		
		//Modificadora
		void modificar(int fila, int columna, double x);
		
		//Operadores
		Matriz& operator =(const Matriz &b);
		
		void operator +=(const Matriz &mat);
		void operator -=(const Matriz &mat);
		
		Matriz operator +(const Matriz &b) const;
		Matriz operator -(const Matriz &b) const;
		Matriz operator *(const Matriz &b) const;
		Matriz operator *(int b) const;
		
		bool operator ==(const Matriz &b) const;
		bool operator !=(const Matriz &b) const;
		
		friend ostream& operator <<(ostream &salida, const Matriz &mat);
		friend istream& operator >>(istream &entrada, Matriz &mat);
};
  
Matriz::Matriz(int filas = 0, int columnas = 0) : nfilas(filas), ncolumnas(columnas) {
  if (nfilas > 0 and ncolumnas > 0) {
    matr = new double* [filas];
    for (int i = 0; i < filas; ++i) matr[i] = new double [columnas];
  }
}
  
Matriz::Matriz(const Matriz &m) { *this = m; }
  
Matriz::~Matriz() { borrar(); }
  
void Matriz::borrar() {
  if (this->matr != NULL) {
    for (int i = 0; i < nfilas; ++i) delete[] matr[i];
    delete[] matr;
    matr = NULL;
  }
}
  
int Matriz::filas() const { return nfilas;}
  
int Matriz::columnas() const { return ncolumnas;}
  
double Matriz::consultar(int fila, int columna) const { return matr[fila][columna];}
  
void Matriz::modificar(int fila, int columna, double x) { matr[fila][columna] = x;}
  
Matriz& Matriz::operator =(const Matriz &mat) {
  if (this != &mat) {
    this->borrar();
  
    if (mat.matr) {
      this->nfilas = mat.nfilas;
      this->ncolumnas = mat.ncolumnas;
  
      this->matr = new double* [nfilas];
      for (int i = 0; i < nfilas; ++i)
        this->matr[i] = new double [ncolumnas];
  
      for (int i = 0; i < nfilas; ++i) {
        for (int j = 0; j < ncolumnas; ++j)
          this->matr[i][j] = mat.matr[i][j];
      }
    }
  }
  return *this;
}
  
void Matriz::operator +=(const Matriz &mat) {
  if (this->nfilas != 0 and this->ncolumnas != 0 and mat.nfilas != 0 and mat.ncolumnas != 0) {
    for (int i = 0; i < nfilas; ++i)
      for (int j = 0; j < ncolumnas; ++j)
        this->matr[i][j] += mat.matr[i][j];
  }
}
  
void Matriz::operator -=(const Matriz &mat) {
  if (this->nfilas != 0 and this->ncolumnas != 0 and mat.nfilas != 0 and mat.ncolumnas != 0) {
    for (int i = 0; i < nfilas; ++i)
      for (int j = 0; j < ncolumnas; ++j)
        this->matr[i][j] -= mat.matr[i][j];
  }
}
  
Matriz Matriz::operator +(const Matriz &b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz res(filas, columnas);
  
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j)
      res.matr[i][j] = this->matr[i][j] + b.matr[i][j];
  
  return res;
}
  
Matriz Matriz::operator -(const Matriz &b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz res(filas, columnas);
  
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j)
      res.matr[i][j] = this->matr[i][j] - b.matr[i][j];
  
  return res;
}
  
Matriz Matriz::operator *(const Matriz &b) const {
  if (this->ncolumnas == b.nfilas) {
    int pos = this->ncolumnas;
  
    int filas = this->nfilas;
    int columnas = b.ncolumnas;
  
    Matriz res(filas, columnas);
    for (int i = 0; i < filas; ++i) {
      for (int j = 0; j < columnas; ++j) {
        double value = 0;
        for (int k = 0; k < pos; ++k) value += this->matr[i][k] * b.matr[k][j];
        res.matr[i][j] = value;
      }
    }
    return res;
  }
}
  
Matriz Matriz::operator *(int b) const {
  int filas = this->nfilas;
  int columnas = this->ncolumnas;
  
  Matriz res(filas, columnas);
  for (int i = 0; i < filas; ++i)
    for (int j = 0; j < columnas; ++j) res.matr[i][j] = this->matr[i][j] * b;
  
  return res;
}
  
Matriz operator *(int a, const Matriz &b) { return b*a; }
  
bool Matriz::operator ==(const Matriz &b) const {
  if (this->nfilas != b.nfilas or this->ncolumnas != b.ncolumnas) return false;
  for (int i = 0; i < this->nfilas; ++i)
    for (int j = 0; j < this->ncolumnas; ++j)
      if (this->matr[i][j] != b.matr[i][j]) return false;
  
  return true;
}
  
bool operator !=(const Matriz &a, const Matriz &b) { return !(a == b); }
  
ostream& operator <<(ostream &salida, const Matriz &mat) {
  for (int i = 0; i < mat.nfilas; ++i) {
    for (int j = 0; j < mat.ncolumnas; ++j) 
			salida << mat.matr[i][j] << " ";
    salida << endl;
  }
  return salida;
}
  
istream& operator >>(istream &entrada, Matriz &mat) {
  for (int i = 0; i < mat.nfilas; ++i)
    for (int j = 0; j < mat.ncolumnas; ++j) 
			entrada >> mat.matr[i][j];
  return entrada;
}