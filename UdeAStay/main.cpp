#include <iostream>
#include "portal.h"
#include "Fecha.h"
#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
#include "reservacion.h"

int main() {
    std::cout << "Iniciando sistema UdeAStay..." << std::endl;

    // Crear el portal
    Portal portal;

    // Ejecutar el sistema (esto abre el menú principal en Portal)
    portal.iniciarSistema();

    std::cout << "Finalizando sistema." << std::endl;
    return 0;
}
