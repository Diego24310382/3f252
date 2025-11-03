#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Dibujo.hpp>
#include <GestorDibujos.hpp>

using namespace std;
using namespace ftxui;

int main() {
    srand(time(nullptr));
    auto screen = Screen::Create(Dimension::Fixed(80), Dimension::Fixed(24));

    // ======= ELEMENTOS ESTÁTICOS =======
    const vector<u32string> nombre_max = {
        U"                               ",
        U"                               ",
        U"                               ",
        U"                               ",
        U"                               ",
        U"███╗   ███╗   █████╗   ██╗  ██╗",
        U"███╗   ███╗   █████╗   ██╗  ██╗",
        U"████╗ ████║  ██╔══██╗  ██║ ██╔╝",
        U"██╔████╔██║  ███████║   █████╔╝ ",
        U"██║╚██╔╝██║  ██╔══██║  ██╔═██╗ ",
        U"██║ ╚═╝ ██║  ██║  ██║  ██║  ██╗",
        U"╚═╝     ╚═╝  ╚═╝  ╚═╝  ╚═╝  ╚═╝"
    };

    const vector<u32string> luna = {
        U"          _.._",
        U"       .' .-'`",
        U"      /  /",
        U"      |  |",
        U"      \\  \\",
        U"       '._'-._",
        U"          ```"
    };

    const vector<u32string> arbol = {
        U"   ▲   ",
        U"  ▲▲▲  ",
        U" ▲▲▲▲▲ ",
        U"▲▲▲▲▲▲▲",
        U"   │   "
    };

    const vector<u32string> suelo = {
        U"────────────────────────────────────────────────────────────────────────────────",
        U"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    };

    const vector<u32string> persona1 = {
        U"  o",
        U" /|\\",
        U"  |",
        U" / \\"
    };

    const vector<u32string> persona2 = {
        U"  o",
        U" /|\\",
        U"  |",
        U"  /\\"
    };

    const vector<u32string> perro = {
        U"  __      _",
        U"o'')}____//",
        U" `_/      )",
        U" (_(_/-(_/"
    };

    const vector<u32string> correa = { U"───────" };

    // ======= GESTOR DE DIBUJOS =======
    GestorDibujos gestor;
    gestor.Agregar(Dibujo(20, 0, nombre_max, ftxui::Color::LightSkyBlue1)); // MAX en el cielo
    gestor.Agregar(Dibujo(65, 2, luna, ftxui::Color::Yellow1));              // luna
    gestor.Agregar(Dibujo(5, 10, arbol, ftxui::Color::Green));               // árbol 1
    gestor.Agregar(Dibujo(60, 9, arbol, ftxui::Color::Green));               // árbol 2
    gestor.Agregar(Dibujo(0, 21, suelo, ftxui::Color::DarkOliveGreen3));     // suelo

    // Dibujos animados
    Dibujo d_persona1(10, 17, persona1, ftxui::Color::White);
    Dibujo d_persona2(10, 17, persona2, ftxui::Color::White);
    Dibujo d_correa(16, 19, correa, ftxui::Color::GrayLight);
    Dibujo d_perro(23, 19, perro, ftxui::Color::White);

    // Copos de nieve
    const int num_copos = 40;
    vector<pair<int, int>> copos(num_copos);
    for (auto& c : copos)
        c = {rand() % 80, rand() % 20};

    int frames = 200;
    for (int frame = 0; frame < frames; ++frame) {
        screen.Clear();

        // Mover copos de nieve hacia abajo
        for (auto& c : copos) {
            c.second += 1;
            if (c.second >= 21) {
                c.first = rand() % 80;
                c.second = 0;
            }
            screen.PixelAt(c.first, c.second).character = U'*';
            screen.PixelAt(c.first, c.second).foreground_color = Color::White;
        }

        // Movimiento horizontal
        int offset = frame % 40;
        d_persona1.x = 10 + offset;
        d_persona2.x = 10 + offset;
        d_correa.x = 16 + offset;
        d_perro.x = 23 + offset;

        // Alternar piernas
        if (frame % 8 < 4) {
            gestor.Agregar(d_persona1);
        } else {
            gestor.Agregar(d_persona2);
        }

        gestor.Agregar(d_correa);
        gestor.Agregar(d_perro);

        // Dibujar todo
        gestor.DibujarTodos(screen);

        // Limpiar dibujos dinámicos
        gestor.dibujos.erase(gestor.dibujos.end() - 3, gestor.dibujos.end());

        // Mostrar en consola
        cout << screen.ToString();
        cout << screen.ResetPosition();
        cout << flush;

        this_thread::sleep_for(chrono::milliseconds(150));
    }

    cout << "Animación terminada. Presiona Enter para salir...\n";
    cin.get();
    return 0;
}
