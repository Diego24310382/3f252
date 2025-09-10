#pragma once
#include <EstadoFoco.hpp>
class Foco
{
private:
    EstadoFoco estado;

public:
    Foco() {}
    ~Foco() {}
    void Encender() { estado = true; }
    void Apagar() { estado = false; }
    EstadoFoco LeerEstado()
    {
        return estado;
    }
};