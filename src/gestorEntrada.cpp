
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>
#include <string>

// --- Definición de acciones de Tetris ---
enum class Accion { ARRIBA, ABAJO, IZQUIERDA, DERECHA, ACCION1, ACCION2 };
static std::unordered_map<Accion, bool> estadoAnterior;

// Alias para Axis
using Axis = sf::Joystick::Axis;

// Mapeo acción → eje o botón
static std::unordered_map<Accion, unsigned int> mapaBotones = {
    {Accion::ARRIBA,    static_cast<unsigned int>(Axis::PovY)},
    {Accion::ABAJO,     static_cast<unsigned int>(Axis::PovY)},
    {Accion::IZQUIERDA, static_cast<unsigned int>(Axis::PovX)},
    {Accion::DERECHA,   static_cast<unsigned int>(Axis::PovX)},
    {Accion::ACCION1,   0},  // Botón 0
    {Accion::ACCION2,   1}   // Botón 1
};

// Estado actual de cada acción
static std::unordered_map<Accion, bool> estadoAccion;

// Umbral para considerar que un eje está “movido”
static float umbral = 50.f;

// Inicializa los estados a false
void inicializarEstados() {
    for (auto &p : mapaBotones) {
        estadoAccion[p.first] = false;
        estadoAnterior[p.first] = false;
    }
}
void actualizarEstadoAnterior() {
    for (auto &p : estadoAccion)
        estadoAnterior[p.first] = p.second;
}

// Actualiza estados leyendo directamente el estado actual del joystick
void actualizarEstados() {
    for (unsigned int id = 0; id < sf::Joystick::Count; ++id) {
        if (!sf::Joystick::isConnected(id)) continue;

        float py = sf::Joystick::getAxisPosition(id, Axis::PovY);
        estadoAccion[Accion::ARRIBA]   = (py < -umbral);
        estadoAccion[Accion::ABAJO]    = (py > +umbral);

        float px = sf::Joystick::getAxisPosition(id, Axis::PovX);
        estadoAccion[Accion::IZQUIERDA] = (px < -umbral);
        estadoAccion[Accion::DERECHA]   = (px > +umbral);

        for (auto &p : mapaBotones) {
            if (p.first == Accion::ACCION1 || p.first == Accion::ACCION2) {
                unsigned int b = p.second;
                if (b < sf::Joystick::getButtonCount(id))
                    estadoAccion[p.first] = sf::Joystick::isButtonPressed(id, b);
            }
        }

        break;  // solo primer joystick
    }
}

void procesarEventos(sf::Window& ventana) {
    // Recorremos todos los eventos pendientes
    while (auto eventoOpt = ventana.pollEvent()) {
        // *eventoOpt es tu sf::Event
        const auto& evento = *eventoOpt;

        // Cierre de ventana
        if (evento.is<sf::Event::Closed>()) {
            ventana.close();
        }
        // Joystick conectado
        else if (auto jc = evento.getIf<sf::Event::JoystickConnected>()) {
            std::cout << "Joystick conectado ID=" << jc->joystickId << "\n";
        }
        // Joystick desconectado
        else if (auto jd = evento.getIf<sf::Event::JoystickDisconnected>()) {
            std::cout << "Joystick desconectado ID=" << jd->joystickId << "\n";
        }
    }

    // Una vez procesados todos los eventos, actualizamos estados de ejes y botones
    actualizarEstados();
}

bool fuePresionada(Accion a) {
    return (!estadoAnterior[a] && estadoAccion[a]);
}

// Consulta si la acción está activa
bool estaPresionada(Accion a) {
    auto it = estadoAccion.find(a);
    return (it != estadoAccion.end()) && it->second;
}
bool hayJoystickConectado() {
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
        if (sf::Joystick::isConnected(i))
            return true;
    }
    return false;
}
std::string nombreJoystick() {
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
        if (sf::Joystick::isConnected(i)) {
            return sf::Joystick::getIdentification(i).name;
        }
    }
    return "Ninguno";
}