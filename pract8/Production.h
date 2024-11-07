// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Daniel Palenzuela Álvarez
// Correo: alu0101140469@ull.edu.es
// Fecha: 5/11/2024
// Archivo: Production.h
// Descripción: Declaración de la clase Production que representa una regla de producción de la gramática.

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>

class Production {
public:
    Production(const std::string& left, const std::string& right); // Constructor

    std::string getLeft() const;     // Obtiene el lado izquierdo de la producción
    std::string getRight() const;    // Obtiene el lado derecho de la producción
    void setRight(const std::string& newRight); // Establece un nuevo lado derecho para la producción

private:
    std::string leftSide;            // Parte izquierda de la producción
    std::string rightSide;           // Parte derecha de la producción
};

#endif
