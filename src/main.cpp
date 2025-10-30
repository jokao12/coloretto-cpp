#include <iostream>
#include "Card.h"
#include "Pile.h"

int main() {
    std::cout << "=== PRUEBA CLASE PILE ===\n\n";
    
    // Crear algunas cartas
    Card cartaRoja("Rojo");
    Card cartaAzul("Azul");
    Card cartaVerde("Verde");
    Card cartaMasDos;
    
    // Crear una pila
    Pile pila;
    
    std::cout << "Estado inicial: ";
    pila.display();
    std::cout << "\n\n";
    
    // Agregar cartas
    std::cout << "1. Agregando carta Roja...\n";
    pila.addCard(&cartaRoja);
    pila.display();
    std::cout << "\n\n";
    
    std::cout << "2. Agregando carta Azul...\n";
    pila.addCard(&cartaAzul);
    pila.display();
    std::cout << "\n\n";
    
    std::cout << "3. Agregando carta Verde...\n";
    pila.addCard(&cartaVerde);
    pila.display();
    std::cout << "\n\n";
    
    // Intentar agregar cuarta carta (debe dar advertencia)
    std::cout << "4. Intentando agregar +2 a pila llena...\n";
    pila.addCard(&cartaMasDos);
    std::cout << "\n";
    
    // Marcar como tomada
    std::cout << "5. Marcando pila como tomada...\n";
    pila.markAsTaken();
    pila.display();
    std::cout << "\n\n";
    
    // Intentar agregar a pila tomada (debe dar advertencia)
    std::cout << "6. Intentando agregar carta a pila tomada...\n";
    Card otraCarta("Amarillo");
    pila.addCard(&otraCarta);
    
    return 0;
}