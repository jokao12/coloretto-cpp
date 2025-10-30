#include <iostream>
#include "Card.h"

int main() {
    std::cout << "=== PRUEBA CLASE CARD ===\n";
    
    // Crear carta de color
    Card cartaRoja("Rojo");
    std::cout << "Carta 1: " << cartaRoja.toString() << "\n";
    std::cout << "Es +2? " << (cartaRoja.isPlusTwo() ? "Si" : "No") << "\n\n";
    
    // Crear carta +2
    Card cartaMasDos;
    std::cout << "Carta 2: " << cartaMasDos.toString() << "\n";
    std::cout << "Es +2? " << (cartaMasDos.isPlusTwo() ? "Si" : "No") << "\n";
    
    return 0;
}