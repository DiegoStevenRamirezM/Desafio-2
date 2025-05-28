#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
#include "reservacion.h"
#include <string>

class GestorDatos {
public:
    //Constructor y destructor
    GestorDatos();
    ~GestorDatos();

    // Getters
    Huesped** getHuespedes() const;
    int getNumHuespedes() const;
    Anfitrion** getAnfitriones() const;
    int getNumAnfitriones() const;
    Alojamiento** getAlojamientos() const;
    int getNumAlojamientos() const;
    Reservacion** getReservaciones() const;
    int getNumReservaciones() const;
    Reservacion** getReservacionesHistoricas() const;
    int getNumReservacionesHistoricas() const;

    // Agregar entidades
    bool agregarHuesped(Huesped* h);
    bool agregarAnfitrion(Anfitrion* a);
    bool agregarAlojamiento(Alojamiento* a);
    bool agregarReservacion(Reservacion* r);
    bool agregarReservacionHistorica(Reservacion* r);

    // Búsqueda
    Huesped* buscarHuesped(std::string doc) const;
    Anfitrion* buscarAnfitrion(std::string doc) const;
    Alojamiento* buscarAlojamiento(std::string cod) const;
    Reservacion* buscarReservacion(std::string cod) const;

    // Operaciones con reservas
    bool verificarSolapamiento(std::string codAloj, Fecha inicio, int duracion, Fecha fechaCorte) const;
    bool crearReservacion(Reservacion* r, Fecha fechaCorte);
    bool cancelarReservacion(std::string cod);
    void moverReservasAHistorico(const Fecha& fechaCorte);
    std::string generarCodigoReserva();

private:
    Huesped** huespedes;
    int numHuespedes;
    Anfitrion** anfitriones;
    int numAnfitriones;
    Alojamiento** alojamientos;
    int numAlojamientos;
    Reservacion** reservaciones;
    int numReservaciones;
    Reservacion** historicas;
    int numHistoricas;
};

#endif // GESTORDATOS_H
