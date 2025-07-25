// src/tableroFondo.cpp

#include <SFML/Graphics.hpp>

// Clase encargada de dibujar la cuadrícula base del juego
class TableroFondo {
public:
    static const int ancho = 10;
    static const int alto = 22;
    static const int tamCuadro = 24;

    TableroFondo() {
        // Configura una celda visual (gris con borde)
        celda.setSize(sf::Vector2f(tamCuadro - 2, tamCuadro - 2)); // deja margen
        celda.setFillColor(sf::Color(60, 60, 60)); // Gris oscuro
        celda.setOutlineThickness(1.f);
        celda.setOutlineColor(sf::Color(100, 100, 100)); // Bordes más claros
    }

    void dibujar(sf::RenderWindow& ventana) {
        for (int y = 0; y < alto; ++y) {
            for (int x = 0; x < ancho; ++x) {
                celda.setPosition(
                   { offsetX + x * tamCuadro,
                    offsetY + y * tamCuadro}
                );
                ventana.draw(celda);
            }
        }
    }

private:
    sf::RectangleShape celda;
    const float offsetX = 50.f;  // Posición de inicio horizontal
    const float offsetY = 50.f;  // Posición de inicio vertical
};
