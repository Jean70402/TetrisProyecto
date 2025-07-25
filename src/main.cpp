// src/main.cpp

#include <SFML/Graphics.hpp>   // Para RenderWindow, clear() y display()
#include <iostream>
#include <string>
#include <sstream>
// Incluimos tus gestores tal cual
#include "gestorEntrada.cpp"
#include "tableroFondo.cpp"
//Carga de clases

TableroFondo fondo;


void cargarFuente(sf::Font&font,const std::string& str ) {
    if (!font.openFromFile(str)) {
        std::cerr<< "No se pudo cargar la fuente::"<<"!!!"<< std::endl;
    }
}
int main() {

    sf::RenderWindow ventana(
        sf::VideoMode({640, 480}),
        "Tetris",
        sf::Style::Close
    );

    ventana.setFramerateLimit(60);
    sf::Font font;
    cargarFuente(font,"res/arial.ttf");
    sf::Text text(font);
    text.setString("Dispositivo:");
    text.setPosition(sf::Vector2f(320,240));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(14);
    text.setPosition({10.f, 10.f});


    while (ventana.isOpen()) {
        std::stringstream sStream;
        if (hayJoystickConectado()) {
            sStream << "CONECTADO: " << nombreJoystick();
            text.setFillColor(sf::Color::Green);
        } else {
            sStream << "DESCONECTADO";
            text.setFillColor(sf::Color::Red);
        }
        text.setString(sStream.str());
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
        //Aqui van los eventos de dibujo
        ventana.draw(text);
        fondo.dibujar(ventana);

        //Aqui terminan los eventos de dibujo
        ventana.display();

        // 4) Pequeña pausa para no saturar demasiado la consola
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
