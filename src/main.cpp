// src/main.cpp

#include <SFML/Graphics.hpp>   // Para RenderWindow, clear() y display()
#include <iostream>

// Incluimos tus gestores tal cual
#include "gestorEntrada.cpp"

int main() {

    sf::RenderWindow ventana(
        sf::VideoMode({640, 480}),
        "Tetris",
        sf::Style::Close
    );

    ventana.setFramerateLimit(60);

    // Inicializamos el gestor de entrada (joystick)
    inicializarEstados();

    while (ventana.isOpen()) {
        // 1) Procesamos eventos de ventana y joystick
        procesarEventos(ventana);

        // 2) Imprimimos en consola solo las acciones detectadas
        if (fuePresionada(Accion::ABAJO))    std::cout << "ACCION: ARRIBA\n";
        if (fuePresionada(Accion::ARRIBA))     std::cout << "ACCION: ABAJO\n";
        if (fuePresionada(Accion::IZQUIERDA)) std::cout << "ACCION: IZQUIERDA\n";
        if (fuePresionada(Accion::DERECHA))   std::cout << "ACCION: DERECHA\n";
        if (fuePresionada(Accion::ACCION1))   std::cout << "ACCION: ACCION1\n";
        if (fuePresionada(Accion::ACCION2))   std::cout << "ACCION: ACCION2\n";
        //if (estaPresionada(Accion::ACCION2))   std::cout << "ACCION: ACCION2\n";
        actualizarEstadoAnterior();
        /*
        // Ver botones del primer joystick sin mapear:
        for (unsigned int b = 0; b < sf::Joystick::getButtonCount(0); ++b) {
            if (sf::Joystick::isButtonPressed(0, b)) {
                std::cout << "Joy0 Button " << b << " PRESIONADO\n";
            }
        }
        */
        // 3) Render (vacío)
        ventana.clear();
        ventana.display();

        // 4) Pequeña pausa para no saturar demasiado la consola
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
