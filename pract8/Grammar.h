// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Daniel Palenzuela Álvarez
// Correo: alu0101140469@ull.edu.es
// Fecha: 5/11/2024
// Archivo: Grammar.h
// Descripción: Declaración de la clase Grammar que representa una gramática y su conversión a CNF.

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include <string>
#include "Production.h"

class Grammar {
public:
    bool loadFromFile(const std::string& filename);  // Carga la gramática desde un archivo .gra
    bool saveToFile(const std::string& filename);    // Guarda la gramática en CNF en un archivo
    void toChomskyNormalForm();                      // Convierte la gramática a CNF

private:
    std::vector<char> terminals;                    // Conjunto de símbolos terminales
    std::vector<std::string> nonTerminals;          // Conjunto de símbolos no terminales
    std::string startSymbol;                        // Símbolo de arranque de la gramática
    std::vector<Production> productions;            // Reglas de producción de la gramática

    void removeUnitProductions();                   // Elimina producciones unitarias
    void removeEmptyProductions();                  // Elimina producciones vacías
    void breakLongProductions();                    // Descompone producciones largas en producciones binarias
};

#endif
