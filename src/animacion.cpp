#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp>
using namespace ftxui;

int main() {
    // Crear la ventana
    auto screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(24));

    // Dibujar la "mesa" de billar
    const std::vector<std::u32string> mesa = {
        U"  +----------------------------------------------------------+",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  |                                                          |",
        U"  +----------------------------------------------------------+",
    };

    // Bolas ASCII simples (visibles)
    const std::vector<std::u32string> bola1 = { U"(6)" };  // negra
    const std::vector<std::u32string> bola2 = { U" O " };  // blanca
    const std::vector<std::u32string> bola3 = { U"(1)" };  // amarilla
    const std::vector<std::u32string> bola4 = { U"(2)" };  // azul
    const std::vector<std::u32string> bola5 = { U"(3)" };  // roja
    const std::vector<std::u32string> bola6 = { U"(4)" };  // violeta
    const std::vector<std::u32string> bola7 = { U"(5)" };  // naranja

    const std::vector<std::u32string> taco = {
        U"----------------------====O"}; // taco de billar

    // Gestor de dibujos
    GestorDibujos gestor;
    gestor.Agregar(Dibujo(2, 2, mesa, ftxui::Color::Green)); // mesa verde
    gestor.Agregar(Dibujo(10, 6, bola1, ftxui::Color::Black));     // bola negra
    gestor.Agregar(Dibujo(15, 8, bola2, ftxui::Color::White));     // bola blanca
    gestor.Agregar(Dibujo(20, 10, bola3, ftxui::Color::Yellow));   // bola amarilla
    gestor.Agregar(Dibujo(25, 12, bola4, ftxui::Color::Blue));     // bola azul
    gestor.Agregar(Dibujo(30, 14, bola5, ftxui::Color::Red));      // bola roja
    gestor.Agregar(Dibujo(35, 10, bola6, ftxui::Color::Magenta));  // bola violeta
    gestor.Agregar(Dibujo(40, 8, bola7, ftxui::Color::Orange1));    // bola naranja
    gestor.Agregar(Dibujo(55, 12, taco, ftxui::Color::RosyBrown));// taco

    int frames = 200;
    for (int frame = 0; frame < frames; ++frame) {
        screen.Clear();

        // Movimiento de las bolas dentro de la mesa
        gestor.dibujos[1].x = 10 + (frame % 20);               // bola1 va de izquierda a derecha
        gestor.dibujos[2].x = 35 - (frame % 20);               // bola2 va en sentido contrario
        gestor.dibujos[3].x = 15 + (frame % 10);               // bola3 avanza y regresa
        gestor.dibujos[3].y = 8 + ((frame / 3) % 4);           // bola3 también baja un poco
        gestor.dibujos[4].x = 25 + ((frame % 15) - 7);         // bola4 oscila
        gestor.dibujos[5].x = 30 + ((frame % 18) - 9);         // bola5 rebota
        gestor.dibujos[5].y = 10 + ((frame / 2) % 6);          // bola5 cambia altura
        gestor.dibujos[6].x = 35 + ((frame % 12) - 6);         // bola6 vibra
        gestor.dibujos[7].x = 40 + ((frame % 10) - 5);         // bola7 movimiento leve
        gestor.dibujos[8].x = 55 - (frame % 8);                // taco se mueve como si golpeara

        // Dibujar todo
        gestor.DibujarTodos(screen);

        // Mostrar en consola
        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }

    return 0;
}
