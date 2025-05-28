#ifndef PORTAL_H
#define PORTAL_H

#include "gestordatos.h"
#include "gestorarchivos.h"
#include "Fecha.h"
#include <string>

class Portal {
public:
    // constructor y destructor
    Portal();
    ~Portal();

    // entrada al sistema
    void iniciarSistema();

    // autenticación
    bool loginHuesped(std::string documento, std::string contrasena);
    bool loginAnfitrion(std::string documento, std::string contrasena);

private:
    GestorDatos gestorDatos;
    GestorArchivos gestorArchivos;
    Fecha fechaCorte;

    // menús según el perfil
    void mostrarMenuPrincipal();
    void mostrarMenuHuesped(const std::string& documento);
    void mostrarMenuAnfitrion(const std::string& documento);

    // gestión de reservas
    void crearReservacionConCodigo(const std::string& documento, const std::string& codAloj, Fecha entrada, int duracion);
    void cancelarReservacionComoHuesped(const std::string& documento);
    void cancelarReservacionComoAnfitrion(const std::string& documento);
    void mostrarReservasVigentesHuesped(const std::string& documento);
    void verReservasDeAlojamientos(const std::string& docAnfitrion);

    // búsquedas
    void buscarAlojamientoConFiltros(const std::string& documento);
    void buscarAlojamientoPorCodigo(const std::string& documento);

    // actualización de datos
    void actualizarFechaCorte();
};

#endif // PORTAL_H
