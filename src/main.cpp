#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "Player.h"

int main() {
    std::cout << "=== PRUEBA CLASE PLAYER ===\n\n";
    
    // Crear jugador
    Player jugador("Karen");
    
    std::cout << "Estado inicial:\n";
    jugador.displayCards();
    std::cout << "\n";
    
    // Crear algunas cartas
    Card rojo1("Rojo"), rojo2("Rojo"), rojo3("Rojo");
    Card azul1("Azul"), azul2("Azul");
    Card verde1("Verde");
    Card masDos1, masDos2;
    
    // Simular que el jugador toma cartas
    std::cout << "Agregando cartas al jugador...\n";
    jugador.addCard(&rojo1);
    jugador.addCard(&rojo2);
    jugador.addCard(&rojo3);
    jugador.addCard(&azul1);
    jugador.addCard(&azul2);
    jugador.addCard(&verde1);
    jugador.addCard(&masDos1);
    jugador.addCard(&masDos2);
    
    // Mostrar cartas recolectadas
    jugador.displayCards();
    std::cout << "\n";
    
    // Calcular puntuación
    std::cout << "Calculando puntuacion...\n";
    jugador.calculateScore();
    jugador.displayScore();
    std::cout << "\n";
    
    // Explicación de puntos
    std::cout << "Explicacion:\n";
    std::cout << "- Rojo (3 cartas): +6 puntos\n";
    std::cout << "- Azul (2 cartas): +3 puntos\n";
    std::cout << "- Verde (1 carta): -1 punto (4to color, resta)\n";
    std::cout << "- +2 (2 cartas): +4 puntos\n";
    std::cout << "Total: 6+3-1+4 = 12 puntos\n";
    
    return 0;
}