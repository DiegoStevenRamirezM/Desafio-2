#include "gestordatos.h"
#include <iostream>

// Constructor y destructor
GestorDatos::GestorDatos()
    : huespedes(nullptr), numHuespedes(0),
    anfitriones(nullptr), numAnfitriones(0),
    alojamientos(nullptr), numAlojamientos(0),
    reservaciones(nullptr), numReservaciones(0),
    historicas(nullptr), numHistoricas(0),
    iteraciones(0), invocacionesExternas(0) {}

GestorDatos::~GestorDatos() {
    for (int i = 0; i < numHuespedes; i++) delete huespedes[i];
    delete[] huespedes;
    for (int i = 0; i < numAnfitriones; i++) delete anfitriones[i];
    delete[] anfitriones;
    for (int i = 0; i < numAlojamientos; i++) delete alojamientos[i];
    delete[] alojamientos;
    for (int i = 0; i < numReservaciones; i++) delete reservaciones[i];
    delete[] reservaciones;
    for (int i = 0; i < numHistoricas; i++) delete historicas[i];
    delete[] historicas;
}

// GETTERS
Huesped** GestorDatos::getHuespedes() const { return huespedes; }
int GestorDatos::getNumHuespedes() const { return numHuespedes; }

Anfitrion** GestorDatos::getAnfitriones() const { return anfitriones; }
int GestorDatos::getNumAnfitriones() const { return numAnfitriones; }

Alojamiento** GestorDatos::getAlojamientos() const { return alojamientos; }
int GestorDatos::getNumAlojamientos() const { return numAlojamientos; }

Reservacion** GestorDatos::getReservaciones() const { return reservaciones; }
int GestorDatos::getNumReservaciones() const { return numReservaciones; }

Reservacion** GestorDatos::getReservacionesHistoricas() const { return historicas; }
int GestorDatos::getNumReservacionesHistoricas() const { return numHistoricas; }

// AGREGAR LAS ENTIDADES

bool GestorDatos::agregarHuesped(Huesped* h) {
    if (buscarHuesped(h->getDocumento())) return false;
    Huesped** nuevo = new Huesped*[numHuespedes + 1];
    for (int i = 0; i < numHuespedes; i++) {
        nuevo[i] = huespedes[i];
        iteraciones++;
    }
    nuevo[numHuespedes++] = h;
    delete[] huespedes;
    huespedes = nuevo;
    return true;
}

bool GestorDatos::agregarAnfitrion(Anfitrion* a) {
    if (buscarAnfitrion(a->getDocumento())) return false;
    Anfitrion** nuevo = new Anfitrion*[numAnfitriones + 1];
    for (int i = 0; i < numAnfitriones; i++) {
        nuevo[i] = anfitriones[i];
        iteraciones++;
    }
    nuevo[numAnfitriones++] = a;
    delete[] anfitriones;
    anfitriones = nuevo;
    return true;
}

bool GestorDatos::agregarAlojamiento(Alojamiento* a) {
    if (buscarAlojamiento(a->getCodigo())) return false;
    Alojamiento** nuevo = new Alojamiento*[numAlojamientos + 1];
    for (int i = 0; i < numAlojamientos; i++) {
        nuevo[i] = alojamientos[i];
        iteraciones++;
    }
    nuevo[numAlojamientos++] = a;
    delete[] alojamientos;
    alojamientos = nuevo;
    return true;
}

bool GestorDatos::agregarReservacion(Reservacion* r) {
    if (buscarReservacion(r->getCodigo())) return false;
    Reservacion** nuevo = new Reservacion*[numReservaciones + 1];
    for (int i = 0; i < numReservaciones; i++) {
        nuevo[i] = reservaciones[i];
        iteraciones++;
    }
    nuevo[numReservaciones++] = r;
    delete[] reservaciones;
    reservaciones = nuevo;
    return true;
}

bool GestorDatos::agregarReservacionHistorica(Reservacion* r) {
    if (buscarReservacion(r->getCodigo())) return false;
    Reservacion** nuevo = new Reservacion*[numHistoricas + 1];
    for (int i = 0; i < numHistoricas; i++) {
        nuevo[i] = historicas[i];
        iteraciones++;
    }
    nuevo[numHistoricas++] = r;
    delete[] historicas;
    historicas = nuevo;
    return true;
}

// BUSQUEDAS

Huesped* GestorDatos::buscarHuesped(std::string doc) const {
    for (int i = 0; i < numHuespedes; i++) {
        if (huespedes[i]->getDocumento() == doc) return huespedes[i];
    }
    return nullptr;
}

Anfitrion* GestorDatos::buscarAnfitrion(std::string doc) const {
    for (int i = 0; i < numAnfitriones; i++) {
        if (anfitriones[i]->getDocumento() == doc) return anfitriones[i];
    }
    return nullptr;
}

Alojamiento* GestorDatos::buscarAlojamiento(std::string cod) const {
    for (int i = 0; i < numAlojamientos; i++) {
        if (alojamientos[i]->getCodigo() == cod) return alojamientos[i];
    }
    return nullptr;
}

Reservacion* GestorDatos::buscarReservacion(std::string cod) const {
    for (int i = 0; i < numReservaciones; i++) {
        if (reservaciones[i]->getCodigo() == cod) return reservaciones[i];
    }
    return nullptr;
}

// OPERACIONES CON RESERVAS

bool GestorDatos::verificarSolapamiento(std::string codAloj, Fecha inicio, int duracion, Fecha fechaCorte) const {
    Alojamiento* a = buscarAlojamiento(codAloj);
    if (!a) return true;
    return !a->estaDisponible(inicio, duracion, fechaCorte);
}

bool GestorDatos::crearReservacion(Reservacion* r, Fecha fechaCorte) {
    if (!buscarHuesped(r->getDocumentoHuesped()) || !buscarAlojamiento(r->getCodigoAlojamiento())) return false;
    if (verificarSolapamiento(r->getCodigoAlojamiento(), r->getFechaEntrada(), r->getDuracion(), fechaCorte)) return false;
    return agregarReservacion(r);
}

bool GestorDatos::cancelarReservacion(std::string cod) {
    for (int i = 0; i < numReservaciones; i++) {
        iteraciones++;
        if (reservaciones[i]->getCodigo() == cod) {
            delete reservaciones[i];
            for (int j = i; j < numReservaciones - 1; j++) {
                reservaciones[j] = reservaciones[j + 1];
                iteraciones++;
            }
            numReservaciones--;
            return true;
        }
    }
    return false;
}

void GestorDatos::moverReservasAHistorico(const Fecha& fechaCorte) {
    if (numReservaciones <= 0 || reservaciones == nullptr) return;
    Reservacion** nuevasVigentes = new Reservacion*[numReservaciones];
    int nuevoNumVigentes = 0;
    for (int i = 0; i < numReservaciones; i++) {
        iteraciones++;
        if (reservaciones[i] == nullptr) continue;
        Fecha entrada = reservaciones[i]->getFechaEntrada();
        Fecha salida = reservaciones[i]->getFechaSalida();
        if (salida < fechaCorte) {
            Reservacion** nuevasHistoricas = new Reservacion*[numHistoricas + 1];
            for (int j = 0; j < numHistoricas; j++) {
                nuevasHistoricas[j] = historicas[j];
                iteraciones++;
            }
            nuevasHistoricas[numHistoricas] = reservaciones[i];
            delete[] historicas;
            historicas = nuevasHistoricas;
            numHistoricas++;
        } else {
            nuevasVigentes[nuevoNumVigentes++] = reservaciones[i];
        }
    }
    delete[] reservaciones;
    reservaciones = nuevasVigentes;
    numReservaciones = nuevoNumVigentes;
    std::cout << "Reservas vigentes e historicas actualizadas en memoria.\n";
}

std::string GestorDatos::generarCodigoReserva() {
    int n = 1;
    bool existe;
    std::string codigo;
    do {
        codigo = "r" + std::to_string(n++);
        existe = false;
        for (int i = 0; i < numReservaciones; i++) {
            iteraciones++;
            if (reservaciones[i]->getCodigo() == codigo) {
                existe = true;
                break;
            }
        }
        if (!existe) {
            for (int i = 0; i < numHistoricas; i++) {
                iteraciones++;
                if (historicas[i]->getCodigo() == codigo) {
                    existe = true;
                    break;
                }
            }
        }
    } while (existe);
    return codigo;
}

// MÉTODOS NUEVOS PARA CONTAR RECURSOS
int GestorDatos::getIteraciones() const {
    return iteraciones;
}

int GestorDatos::getInvocacionesExternas() const {
    return invocacionesExternas;
}

void GestorDatos::sumarIteraciones(int n) {
    iteraciones += n;
}

void GestorDatos::sumarInvocacionesExternas(int n) {
    invocacionesExternas++;
}


