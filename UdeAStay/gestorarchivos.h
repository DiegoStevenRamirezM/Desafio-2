#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include "gestordatos.h"
#include <string>

class GestorArchivos {
public:
    GestorArchivos();
    ~GestorArchivos();

    // Manejo de fecha de corte
    bool leerFechaCorte(Fecha& fecha);
    bool guardarFechaCorte(const Fecha& fecha);

    // Carga de datos desde archivos
    bool cargarHuespedes(const std::string& archivo, GestorDatos* gestor);
    bool cargarAnfitriones(const std::string& archivo, GestorDatos* gestor);
    bool cargarAlojamientos(const std::string& archivo, GestorDatos* gestor);
    bool cargarReservaciones(const std::string& archivo, GestorDatos* gestor);
    bool cargarReservasHistoricas(const std::string& archivo, GestorDatos* gestor);

    // Guardado de datos a archivos
    bool guardarHuespedes(const std::string& archivo, const GestorDatos* gestor);
    bool guardarAnfitriones(const std::string& archivo, const GestorDatos* gestor);
    bool guardarAlojamientos(const std::string& archivo, const GestorDatos* gestor);
    bool guardarReservacionesVigentes(const std::string& archivo, const GestorDatos* gestor);
    bool guardarReservacionesHistoricas(const std::string& archivo, const GestorDatos* gestor);

    // Actualización del histórico
    bool moverReservasHistorico(Fecha fechaCorte, GestorDatos* gestor);
};

#endif // GESTORARCHIVOS_H
