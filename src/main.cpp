// src/main.cpp

#include <SFML/Graphics.hpp>   // Para RenderWindow, clear() y display()
#include <iostream>

// Incluimos tus gestores tal cual
#include "gestorEntrada.cpp"
#include "gestorOpciones.cpp"

int main() {

    sf::RenderWindow ventana(
        sf::VideoMode({640, 480}),
        "Debug Controles",
        sf::Style::Close
    );

    ventana.setFramerateLimit(60);

    // Inicializamos el gestor de entrada (joystick)
    inicializarEstados();

    while (ventana.isOpen()) {
        // 1) Procesamos eventos de ventana y joystick
        procesarEventos(ventana);

        // 2) Imprimimos en consola solo las acciones detectadas
        if (estaPresionada(Accion::ARRIBA)) {
            std::cout << "ACCION: ARRIBA\n";
        }
        if (estaPresionada(Accion::ABAJO)) {
            std::cout << "ACCION: ABAJO\n";
        }
        if (estaPresionada(Accion::IZQUIERDA)) {
            std::cout << "ACCION: IZQUIERDA\n";
        }
        if (estaPresionada(Accion::DERECHA)) {
            std::cout << "ACCION: DERECHA\n";
        }
        if (estaPresionada(Accion::ACCION1)) {
            std::cout << "ACCION: ACCION1\n";
        }
        if (estaPresionada(Accion::ACCION2)) {
            std::cout << "ACCION: ACCION2\n";
        }
        /*
        // (Opcional) Si quieres ver botones del primer joystick sin mapear:
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
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
