// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Daniel Palenzuela Álvarez
// Correo: alu0101140469@ull.edu.es
// Fecha: 5/11/2024
// Archivo: Production.cc
// Descripción: Implementación de la clase Production y sus métodos de acceso y modificación.

#include "Production.h"

// Constructor de la producción
Production::Production(const std::string& left, const std::string& right)
    : leftSide(left), rightSide(right) { }

// Obtiene el lado izquierdo de la producción
std::string Production::getLeft() const { return leftSide; }

// Obtiene el lado derecho de la producción
std::string Production::getRight() const { return rightSide; }

// Establece un nuevo lado derecho para la producción
void Production::setRight(const std::string& newRight) { rightSide = newRight; }
