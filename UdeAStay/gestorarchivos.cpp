#include "gestorarchivos.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor vacío
GestorArchivos::GestorArchivos() {}

// Destructor vacío
GestorArchivos::~GestorArchivos() {}


// MANEJO DE LA FECHA DE CORTE

//Lee la fecha de corte
bool GestorArchivos::leerFechaCorte(Fecha& fecha) {
    std::ifstream file("fecha_corte.txt");
    if (!file.is_open()) {
        fecha = Fecha(11, 5, 2025);
        return false;
    }

    std::string linea;
    std::getline(file, linea);
    file.close();

    if (linea.size() != 10 || linea[2] != '-' || linea[5] != '-') {
        fecha = Fecha(11, 5, 2025);
        return false;
    }

    int d = std::stoi(linea.substr(0, 2));
    int m = std::stoi(linea.substr(3, 2));
    int a = std::stoi(linea.substr(6, 4));
    Fecha f(d, m, a);

    if (!f.esValida()) {
        fecha = Fecha(17, 5, 2025);
        return false;
    }

    fecha = f;
    return true;
}

// Guarda la fecha de corte actual en el archivo
bool GestorArchivos::guardarFechaCorte(const Fecha& fecha) {
    std::ofstream file("fecha_corte.txt");
    if (!file.is_open()) return false;

    file << (fecha.getDia() < 10 ? "0" : "") << fecha.getDia() << "-"
         << (fecha.getMes() < 10 ? "0" : "") << fecha.getMes() << "-"
         << fecha.getAnio();

    file.close();
    return true;
}

// CARGA DE DATOS DESDE ARCHIVOS

//Carga los huespedes
bool GestorArchivos::cargarHuespedes(const std::string& archivo, GestorDatos* gestor) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo de huespedes.\n";
        return false;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string doc, pass;
        int ant;
        double punt;

        std::getline(ss, doc, ',');
        ss >> ant;
        ss.ignore(1);
        ss >> punt;
        ss.ignore(1);
        std::getline(ss, pass);

        gestor->agregarHuesped(new Huesped(doc, ant, punt, pass));
    }

    file.close();
    return true;
}

// Carga los anfitriones y los agrega al GestorDatos
bool GestorArchivos::cargarAnfitriones(const std::string& archivo, GestorDatos* gestor) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    std::string linea;
    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string doc, pass;
        int ant;
        double punt;

        getline(ss, doc, ',');
        ss >> ant;
        ss.ignore();
        ss >> punt;
        ss.ignore();
        getline(ss, pass);

        gestor->agregarAnfitrion(new Anfitrion(doc, ant, punt, pass));
    }

    file.close();
    return true;
}

// Carga los alojamientos y agrega sus amenidades si las tiene
bool GestorArchivos::cargarAlojamientos(const std::string& archivo, GestorDatos* gestor) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo de alojamientos.\n";
        return false;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string codigo, nombre, direccion, depto, municipio, tipo, docAnfitrion, amenidades;
        double precio;

        std::getline(ss, codigo, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, direccion, ',');
        std::getline(ss, depto, ',');
        std::getline(ss, municipio, ',');
        std::getline(ss, tipo, ',');
        ss >> precio;
        ss.ignore(1);
        std::getline(ss, docAnfitrion, ',');
        std::getline(ss, amenidades);

        Alojamiento* a = new Alojamiento(codigo, nombre, direccion, depto, municipio, tipo, precio, docAnfitrion);

        if (!amenidades.empty()) {
            std::stringstream ssAmenidades(amenidades);
            std::string amenidad;
            while (std::getline(ssAmenidades, amenidad, ';')) {
                a->agregarAmenidad(amenidad);
            }
        }

        gestor->agregarAlojamiento(a);
    }

    file.close();
    return true;
}

// Carga reservas vigentes y las asocia al huesped y al alojamiento si estan disponibles
bool GestorArchivos::cargarReservaciones(const std::string& archivo, GestorDatos* gestor) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo de reservas.\n";
        return false;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string codigo, fechaEntradaStr, codAloj, docHuesped, metodo, fechaPagoStr, anotaciones;
        int duracion;
        double monto;

        std::getline(ss, codigo, ',');
        std::getline(ss, fechaEntradaStr, ',');
        ss >> duracion;
        ss.ignore(1);
        std::getline(ss, codAloj, ',');
        std::getline(ss, docHuesped, ',');
        std::getline(ss, metodo, ',');
        std::getline(ss, fechaPagoStr, ',');
        ss >> monto;
        ss.ignore(1);
        std::getline(ss, anotaciones);

        Fecha fEntrada(stoi(fechaEntradaStr.substr(0, 2)),
                       stoi(fechaEntradaStr.substr(3, 2)),
                       stoi(fechaEntradaStr.substr(6, 4)));

        Fecha fPago(stoi(fechaPagoStr.substr(0, 2)),
                    stoi(fechaPagoStr.substr(3, 2)),
                    stoi(fechaPagoStr.substr(6, 4)));

        Reservacion* r = new Reservacion(codigo, fEntrada, duracion, codAloj, docHuesped, metodo, fPago, monto, anotaciones);

        Huesped* h = gestor->buscarHuesped(docHuesped);
        Alojamiento* a = gestor->buscarAlojamiento(codAloj);
        Fecha fSalida = fEntrada.sumarDias(duracion);

        if (h && a && a->agregarFechaReservada(fEntrada, fSalida)) {
            gestor->agregarReservacion(r);
        } else {
            delete r; // Se descarta si hay inconsistencia
        }
    }

    file.close();
    return true;
}

// Carga reservas historicas y las guarda directamente en memoria
bool GestorArchivos::cargarReservasHistoricas(const std::string& archivo, GestorDatos* gestor) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo de reservas historicas.\n";
        return false;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string codigo, fechaEntradaStr, codAloj, docHuesped, metodo, fechaPagoStr, anotaciones;
        int duracion;
        double monto;

        std::getline(ss, codigo, ',');
        std::getline(ss, fechaEntradaStr, ',');
        ss >> duracion;
        ss.ignore(1);
        std::getline(ss, codAloj, ',');
        std::getline(ss, docHuesped, ',');
        std::getline(ss, metodo, ',');
        std::getline(ss, fechaPagoStr, ',');
        ss >> monto;
        ss.ignore(1);
        std::getline(ss, anotaciones);

        Fecha fEntrada(stoi(fechaEntradaStr.substr(0, 2)),
                       stoi(fechaEntradaStr.substr(3, 2)),
                       stoi(fechaEntradaStr.substr(6, 4)));

        Fecha fPago(stoi(fechaPagoStr.substr(0, 2)),
                    stoi(fechaPagoStr.substr(3, 2)),
                    stoi(fechaPagoStr.substr(6, 4)));

        Reservacion* r = new Reservacion(codigo, fEntrada, duracion, codAloj, docHuesped, metodo, fPago, monto, anotaciones);
        gestor->agregarReservacionHistorica(r);
    }

    file.close();
    return true;
}

//GUARDADO DE DATOS A ARCHIVOS

// Guarda todos los huespedes en el archivo
bool GestorArchivos::guardarHuespedes(const std::string& archivo, const GestorDatos* gestor) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    Huesped** h = gestor->getHuespedes();
    int n = gestor->getNumHuespedes();
    for (int i = 0; i < n; i++) {
        file << h[i]->getDocumento() << "," << h[i]->getAntiguedad() << ","
             << h[i]->getPuntuacion() << "," << h[i]->getContrasena() << "\n";
    }

    file.close();
    return true;
}

// Guarda todos los anfitriones registrados
bool GestorArchivos::guardarAnfitriones(const std::string& archivo, const GestorDatos* gestor) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    Anfitrion** a = gestor->getAnfitriones();
    int n = gestor->getNumAnfitriones();
    for (int i = 0; i < n; i++) {
        file << a[i]->getDocumento() << "," << a[i]->getAntiguedad() << ","
             << a[i]->getPuntuacion() << "," << a[i]->getContrasena() << "\n";
    }

    file.close();
    return true;
}

// Guarda todos los alojamientos registrados
bool GestorArchivos::guardarAlojamientos(const std::string& archivo, const GestorDatos* gestor) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    Alojamiento** a = gestor->getAlojamientos();
    int n = gestor->getNumAlojamientos();
    for (int i = 0; i < n; i++) {
        file << a[i]->getCodigo() << "," << a[i]->getNombre() << ","
             << a[i]->getDireccion() << "," << a[i]->getDepartamento() << ","
             << a[i]->getMunicipio() << "," << a[i]->getTipo() << ","
             << a[i]->getPrecioPorNoche() << "," << a[i]->getDocumentoAnfitrion() << "\n";
    }

    file.close();
    return true;
}

// Guarda las reservas vigentes en archivo
bool GestorArchivos::guardarReservacionesVigentes(const std::string& archivo, const GestorDatos* gestor) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    Reservacion** r = gestor->getReservaciones();
    int n = gestor->getNumReservaciones();
    for (int i = 0; i < n; i++) {
        Fecha entrada = r[i]->getFechaEntrada();
        Fecha pago = r[i]->getFechaPago();

        file << r[i]->getCodigo() << ","
             << (entrada.getDia() < 10 ? "0" : "") << entrada.getDia() << "-"
             << (entrada.getMes() < 10 ? "0" : "") << entrada.getMes() << "-"
             << entrada.getAnio() << ","
             << r[i]->getDuracion() << ","
             << r[i]->getCodigoAlojamiento() << ","
             << r[i]->getDocumentoHuesped() << ","
             << r[i]->getMetodoPago() << ","
             << (pago.getDia() < 10 ? "0" : "") << pago.getDia() << "-"
             << (pago.getMes() < 10 ? "0" : "") << pago.getMes() << "-"
             << pago.getAnio() << ","
             << r[i]->getMonto() << ","
             << r[i]->getAnotaciones() << "\n";
    }

    file.close();
    return true;
}

// Guarda las reservas historicas en archivo
bool GestorArchivos::guardarReservacionesHistoricas(const std::string& archivo, const GestorDatos* gestor) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    Reservacion** r = gestor->getReservacionesHistoricas();
    int n = gestor->getNumReservacionesHistoricas();
    for (int i = 0; i < n; i++) {
        if (!r[i]) {
            std::cout << "Reserva historica en posicion " << i << " es null, se ignora.\n";
            continue;
        }

        Fecha entrada = r[i]->getFechaEntrada();
        Fecha pago = r[i]->getFechaPago();

        file << r[i]->getCodigo() << ","
             << (entrada.getDia() < 10 ? "0" : "") << entrada.getDia() << "-"
             << (entrada.getMes() < 10 ? "0" : "") << entrada.getMes() << "-"
             << entrada.getAnio() << ","
             << r[i]->getDuracion() << ","
             << r[i]->getCodigoAlojamiento() << ","
             << r[i]->getDocumentoHuesped() << ","
             << r[i]->getMetodoPago() << ","
             << (pago.getDia() < 10 ? "0" : "") << pago.getDia() << "-"
             << (pago.getMes() < 10 ? "0" : "") << pago.getMes() << "-"
             << pago.getAnio() << ","
             << r[i]->getMonto() << ","
             << r[i]->getAnotaciones() << "\n";
    }

    file.close();
    return true;
}

// Mueve las reservas vencidas al archivo historico segun la fecha de corte
bool GestorArchivos::moverReservasHistorico(Fecha fechaCorte, GestorDatos* gestor) {
    gestor->moverReservasAHistorico(fechaCorte);

    bool exitoVigentes = guardarReservacionesVigentes("reservas_vigentes.txt", gestor);
    bool exitoHistoricas = guardarReservacionesHistoricas("reservas_historicas.txt", gestor);

    return exitoVigentes && exitoHistoricas;
}
