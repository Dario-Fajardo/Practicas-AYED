// AUTOR: Darío Fajardo Álvarez 
// FECHA: 06/04/2023
// EMAIL: alu0101564630@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Archivo de cabecera con la definición de la clase SllPolynomial

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  for (int i{v.get_size() - 1}; i >= 0; --i) {
    if (IsNotZero(v[i], eps)) {
      push_front(new SllPolyNode{pair_double_t(v[i], i)});
    }
  }
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  SllPolyNode* aux{get_head()};
  while (aux != NULL){
    result += aux->get_data().get_val() * pow(x, aux->get_data().get_inx());
    aux = aux->get_next();
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol, 
                            const double eps) const {
  bool differents = false;
  SllPolyNode* aux1{get_head()};
  SllPolyNode* aux2{sllpol.get_head()};
  while (aux1 != NULL && aux2 != NULL) {
    if ((aux1 != NULL && aux2 == NULL) || (aux1 == NULL && aux2 != NULL)){
      return false;
    }
    if (fabs(aux1->get_data().get_val() - aux2->get_data().get_val() >= eps)) {
      differents = true;
    }
    aux1 = aux1->get_next();
    aux2 = aux2->get_next();
  }
  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  // poner el código aquí
  SllPolynomial auxSllPolSum;             // Polinomio auxiliar para la suma
  SllPolyNode* auxiliar = get_head();          // TÃ©rmino del polinomio 1
  SllPolyNode* auxiliar2 = sllpol.get_head();  // TÃ©rmino del polinomio 2
  pair_double_t pareja;                     // Par de nÃºmeros para crear nodo suma
  double sum = 0.0;                       // Variable para almacenar la suma

//si tienen los mismos exponentes se suman
  while (auxiliar != NULL || auxiliar2 != NULL) {
    if (auxiliar != NULL && auxiliar2 != NULL) {
      if (auxiliar->get_data().get_inx() == auxiliar2->get_data().get_inx()) {
        sum = auxiliar->get_data().get_val() + auxiliar2->get_data().get_val();
        if (IsNotZero(sum, eps)) {
          pareja.set(sum, auxiliar->get_data().get_inx());
          auxSllPolSum.push_front(new SllPolyNode (pareja));
        }
        if (auxiliar != NULL)
          auxiliar = auxiliar->get_next();
        if (auxiliar2 != NULL)
          auxiliar2 = auxiliar2->get_next();
//si el indice del primer polinomio es mayor se suma solo el segundo aux
      } else if (auxiliar->get_data().get_inx() > auxiliar2->get_data().get_inx()) {
        sum = auxiliar2->get_data().get_val();
        if (IsNotZero(sum, eps)) {
          pareja.set(sum, auxiliar2->get_data().get_inx());
          auxSllPolSum.push_front(new SllPolyNode (pareja));
        }
        if (auxiliar2 != NULL)
          auxiliar2 = auxiliar2->get_next();
      } else {
        sum = auxiliar->get_data().get_val();
        if (IsNotZero(sum, eps)) {
          pareja.set(sum, auxiliar->get_data().get_inx());
          auxSllPolSum.push_front(new SllPolyNode (pareja));
        }

        // Siempre que no estemos al final de la lista, apuntamos al next nodo
        // del pol que tenÃ­a el menor Ã­ndice para asÃ­ intentar llegar al mismo
        // Ã­ndice que el otro pol.
        if (auxiliar != NULL)
          auxiliar = auxiliar->get_next();
      }

      //Si uno llego al final
    } else if (auxiliar == NULL) {
      sum = auxiliar2->get_data().get_val();
      if (IsNotZero(sum, eps)) {
        pareja.set(sum, auxiliar2->get_data().get_inx());
        auxSllPolSum.push_front(new SllPolyNode (pareja));
      }
      if (auxiliar2 != NULL)
        auxiliar2 = auxiliar2->get_next();

    } else if (auxiliar2 == NULL) {
      sum = auxiliar->get_data().get_val();
      if (IsNotZero(sum, eps)) {
        pareja.set(sum, auxiliar2->get_data().get_inx());
        auxSllPolSum.push_front(new SllPolyNode (pareja));
      }

      if (auxiliar != NULL)
        auxiliar = auxiliar->get_next();
    }
  }

  while (!auxSllPolSum.empty()) {
    sllpolsum.push_front(auxSllPolSum.pop_front());
  }
}

#endif  // SLLPOLYNOMIAL_H_