#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Pieza {
public:
    enum Tipo { I, J, L, O, S, T, Z, NUM_TIPOS };

    Pieza(Tipo tipo) {
        forma = obtenerFormas()[tipo];
        color = obtenerColores()[tipo];
        x = 3;
        y = 0;
    }

    void dibujar(sf::RenderWindow& ventana, float offsetX, float offsetY, int tamCuadro) {
        sf::RectangleShape cuadro(sf::Vector2f(tamCuadro - 2, tamCuadro - 2));
        cuadro.setFillColor(color);

        for (size_t fy = 0; fy < forma.size(); ++fy) {
            for (size_t fx = 0; fx < forma[fy].size(); ++fx) {
                if (forma[fy][fx]) {
                    cuadro.setPosition({
                        offsetX + (x + fx) * tamCuadro,
                        offsetY + (y + fy) * tamCuadro}
                    );
                    ventana.draw(cuadro);
                }
            }
        }
    }

    void rotarDerecha() {
        size_t n = forma.size();
        std::vector nueva(n, std::vector<int>(n));
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                nueva[j][n - 1 - i] = forma[i][j];
        forma = nueva;
    }
    void rotarIzquierda() {
        size_t n = forma.size();
        std::vector nueva(n, std::vector<int>(n));
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                nueva[n - 1 - j][i] = forma[i][j];
        forma = nueva;
    }


    void moverAbajo() { y++; }
    void moverIzquierda() { x--; }
    void moverDerecha() { x++; }

private:
    std::vector<std::vector<int>> forma;
    sf::Color color;
    int x, y;

    static const std::vector<std::vector<std::vector<int>>>& obtenerFormas() {
        static const std::vector<std::vector<std::vector<int>>> FORMAS = {
            { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }, // I
            { {1,0,0}, {1,1,1}, {0,0,0} },                 // J
            { {0,0,1}, {1,1,1}, {0,0,0} },                 // L
            { {1,1}, {1,1} },                              // O
            { {0,1,1}, {1,1,0}, {0,0,0} },                 // S
            { {0,1,0}, {1,1,1}, {0,0,0} },                 // T
            { {1,1,0}, {0,1,1}, {0,0,0} }                  // Z
        };
        return FORMAS;
    }

    static const std::vector<sf::Color>& obtenerColores() {
        static const std::vector<sf::Color> COLORES = {
            sf::Color::Cyan, sf::Color::Blue, sf::Color(255,140,0),
            sf::Color::Yellow, sf::Color::Green, sf::Color::Magenta, sf::Color::Red
        };
        return COLORES;
    }
};
