// AUTOR: Darío Fajardo Álvarez
// FECHA: 23/04/2023
// EMAIL: alu0101564630@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// TEMA: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
 rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);

 private: 
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T> const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) 	{
    char c = q.front();
    
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (isdigit(c)) {
      int i = c - '0';
      stack_.push(i);
      std::cout << " (es un dígito) " << std::endl
		<< "   Lo metemos en la pila..." << std::endl;
    } else {
      std::cout << " (es un operador)" << std::endl;
      operate_(c);
    }
  }
  return stack_.top();
}

template<class T> void rpn_t<T>::operate_(const char c) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r' || c == 'l' || c == 'c');
  int operando1;
  int operando2;

  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
    operando1 = stack_.top();
    stack_.pop();
    std::cout << "   Sacamos de la pila un operando: " << operando1 << std::endl;
  
    operando2 = stack_.top();
    stack_.pop();
    std::cout << "   Sacamos de la pila otro operando: " << operando2 << std::endl;
  } else if (c == 'r' || c == 'l' || c == 'c') {
    operando1 = stack_.top();
    stack_.pop();
    std::cout << "   Sacamos de la pila un operando: " << operando1 << std::endl;
  }
  switch (c) {
    case '+':
      stack_.push(operando1 + operando2);
      break;
    case '-':
      stack_.push(operando2 - operando1);
      break;
    case '*':
      stack_.push(operando1 * operando2);
      break;
    case '/':
      assert(operando2 != 0);
      if (operando1 > operando2) {
        stack_.push(operando1 / operando2);
      } else {
        stack_.push(operando2 / operando1);
      }
      break;
    case '^':
      stack_.push(pow(operando1, operando2));
      break;
    case 'r':
      stack_.push(sqrt(operando1));
      break;
    case 'l':
      stack_.push(log2(operando1));
      break;
    case 'c':
      stack_.push(operando1 * operando1);
      break;
  }
  std::cout << "   Metemos en la pila el resultado: " << stack_.top() << std::endl;
}

 
#endif  // RPNT_H_
