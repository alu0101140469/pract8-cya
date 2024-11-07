// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Daniel Palenzuela Álvarez
// Correo: alu0101140469@ull.edu.es
// Fecha: 5/11/2024
// Archivo: Grammar2CNF.cc
// Descripción: Programa principal que convierte una gramática independiente del contexto (CFG) a su equivalente en Forma Normal de Chomsky (CNF).

#include <iostream>
#include <fstream>
#include <string>
#include "Grammar.h"

// Muestra el mensaje de ayuda para la ejecución del programa
void print_help() {
    std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n";
    std::cout << "Convierte una gramática CFG a la Forma Normal de Chomsky (CNF).\n";
    std::cout << "Pruebe ‘Grammar2CNF --help’ para más información.\n";
}

int main(int argc, char* argv[]) {
    // Verifica el número de argumentos proporcionados
    if (argc != 3) {
        print_help();
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    // Crear y cargar la gramática desde el archivo de entrada
    Grammar grammar;
    if (!grammar.loadFromFile(input_file)) {
        std::cerr << "Error al cargar el archivo de entrada.\n";
        return 1;
    }

    // Convertir la gramática cargada a forma normal de Chomsky
    grammar.toChomskyNormalForm();

    // Guardar la gramática en CNF en el archivo de salida especificado
    if (!grammar.saveToFile(output_file)) {
        std::cerr << "Error al guardar el archivo de salida.\n";
        return 1;
    }

    std::cout << "Conversión a CNF completada con éxito.\n";
    return 0;
}
