// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Daniel Palenzuela Álvarez
// Correo: alu0101140469@ull.edu.es
// Fecha: 5/11/2024
// Archivo: Grammar.cc
// Descripción: Implementación de la clase Grammar y sus métodos de carga, guardado y conversión a CNF.

#include "Grammar.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <algorithm> 

// Carga la gramática desde un archivo en formato .gra
bool Grammar::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    int numTerminals, numNonTerminals, numProductions;
    std::string symbol;

    // Leer terminales
    file >> numTerminals;
    for (int i = 0; i < numTerminals; ++i) {
        file >> symbol;
        terminals.push_back(symbol[0]);
    }

    // Leer no terminales
    file >> numNonTerminals;
    for (int i = 0; i < numNonTerminals; ++i) {
        file >> symbol;
        nonTerminals.push_back(symbol);
    }

    // El primer símbolo no terminal se toma como símbolo de arranque
    startSymbol = nonTerminals[0];

    // Leer producciones
    file >> numProductions;
    for (int i = 0; i < numProductions; ++i) {
        std::string left, right;
        file >> left >> right;
        productions.emplace_back(left, right);
    }

    file.close();
    return true;
}

// Guarda la gramática en CNF en un archivo .gra
bool Grammar::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Guardar terminales
    file << terminals.size() << "\n";
    for (const char& terminal : terminals) {
        file << terminal << "\n";
    }

    // Guardar no terminales
    file << nonTerminals.size() << "\n";
    for (const std::string& nonTerminal : nonTerminals) {
        file << nonTerminal << "\n";
    }

    // Guardar producciones
    file << productions.size() << "\n";
    for (const Production& production : productions) {
        file << production.getLeft() << " " << production.getRight() << "\n";
    }

    file.close();
    return true;
}

// Convierte la gramática a Forma Normal de Chomsky (CNF)
void Grammar::toChomskyNormalForm() {
    removeUnitProductions();
    removeEmptyProductions();
    breakLongProductions();
}

// Elimina producciones unitarias de la gramática
void Grammar::removeUnitProductions() {
    // Itera sobre las producciones buscando producciones unitarias (A -> B)
    for (const auto& production : productions) {
        if (production.getRight().size() == 1 && isupper(production.getRight()[0])) {
            std::string unitSymbol = production.getRight();
            std::string left = production.getLeft();

            // Encuentra las producciones derivadas de unitSymbol y las agrega al símbolo actual
            for (const auto& p : productions) {
                if (p.getLeft() == unitSymbol && p.getLeft() != left) {
                    productions.emplace_back(left, p.getRight());
                }
            }
        }
    }
    // Elimina las producciones unitarias
    productions.erase(std::remove_if(productions.begin(), productions.end(),
                                      [](const Production& p) {
                                          return p.getRight().size() == 1 && isupper(p.getRight()[0]);
                                      }),
                      productions.end());
}

// Elimina producciones vacías (que derivan a ε) de la gramática
void Grammar::removeEmptyProductions() {
    std::unordered_set<std::string> nullable; // Conjunto de símbolos que pueden derivar en ε

    // Identifica los símbolos que derivan a ε
    for (const auto& production : productions) {
        if (production.getRight() == "&") {  // Se asume "&" representa ε
            nullable.insert(production.getLeft());
        }
    }

    // Propaga la nulabilidad a otras producciones
    bool changed;
    do {
        changed = false;
        for (const auto& production : productions) {
            std::string right = production.getRight();
            if (right != "&") {
                bool isNullable = true;
                for (char symbol : right) {
                    if (nullable.find(std::string(1, symbol)) == nullable.end()) {
                        isNullable = false;
                        break;
                    }
                }
                if (isNullable && nullable.insert(production.getLeft()).second) {
                    changed = true;
                }
            }
        }
    } while (changed);

    // Genera nuevas producciones reemplazando las producciones vacías en el conjunto de producciones
    std::vector<Production> newProductions;
    for (const auto& production : productions) {
        if (production.getRight() == "&") continue;

        // Genera todas las combinaciones posibles reemplazando los nullable por vacío
        std::string left = production.getLeft();
        std::string right = production.getRight();

        // Agrega la producción actual sin cambios
        newProductions.emplace_back(left, right);

        // Genera producciones eliminando símbolos nullable
        for (size_t i = 0; i < right.size(); ++i) {
            if (nullable.find(std::string(1, right[i])) != nullable.end()) {
                std::string newRight = right;
                newRight.erase(i, 1);
                if (!newRight.empty()) {
                    newProductions.emplace_back(left, newRight);
                }
            }
        }
    }
    productions = newProductions;
}

// Descompone producciones largas en producciones binarias
void Grammar::breakLongProductions() {
    std::vector<Production> newProductions;
    int newVarIndex = 1;

    for (const auto& production : productions) {
        std::string left = production.getLeft();
        std::string right = production.getRight();

        // Si la producción ya es binaria o unitaria, se agrega sin cambios
        if (right.size() <= 2) {
            newProductions.push_back(production);
        } else {
            // Divide la producción larga en producciones binarias
            std::string currentLeft = left;
            for (size_t i = 0; i < right.size() - 2; ++i) {
                // Crea un nuevo símbolo no terminal para descomponer la producción
                std::string newVar = "D" + std::to_string(newVarIndex++);
                newProductions.emplace_back(currentLeft, std::string(1, right[i]) + newVar);
                currentLeft = newVar;
            }
            // Agrega la última producción binaria
            newProductions.emplace_back(currentLeft, right.substr(right.size() - 2));
        }
    }
    productions = newProductions;
}
