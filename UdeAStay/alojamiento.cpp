#include "alojamiento.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Alojamiento::Alojamiento()
    : codigo(""), nombre("Sin nombre"), direccion("Sin direccion"), departamento("Sin departamento"),
    municipio("Sin municipio"), tipo("Casa"), precioPorNoche(0.0), documentoAnfitrion(""),
    numAmenidades(0), capacidadAmenidades(10), numFechasReservadas(0), capacidadFechas(10) {
    amenidades = new string[capacidadAmenidades];
    fechasInicio = new Fecha[capacidadFechas];
    fechasFin = new Fecha[capacidadFechas];
}

Alojamiento::Alojamiento(string cod, string nom, string dir, string depto, string mun, string t, double precio, string docAnfitrion)
    : codigo(cod), nombre(nom), direccion(dir), departamento(depto), municipio(mun),
    precioPorNoche(precio), documentoAnfitrion(docAnfitrion),
    numAmenidades(0), capacidadAmenidades(10), numFechasReservadas(0), capacidadFechas(10) {
    if (codigo.empty()) codigo = "DESCONOCIDO";
    if (nombre.empty()) nombre = "Sin nombre";
    if (direccion.empty()) direccion = "Sin direccion";
    if (departamento.empty()) departamento = "Sin departamento";
    if (municipio.empty()) municipio = "Sin municipio";
    tipo = (t == "Casa" || t == "Apartamento") ? t : "Casa";
    precioPorNoche = (precio >= 0) ? precio : 0.0;
    if (documentoAnfitrion.empty()) documentoAnfitrion = "DESCONOCIDO";
    amenidades = new string[capacidadAmenidades];
    fechasInicio = new Fecha[capacidadFechas];
    fechasFin = new Fecha[capacidadFechas];
}

Alojamiento::Alojamiento(const Alojamiento& otro) : codigo(otro.codigo), nombre(otro.nombre), direccion(otro.direccion),
    departamento(otro.departamento), municipio(otro.municipio), tipo(otro.tipo),
    precioPorNoche(otro.precioPorNoche), documentoAnfitrion(otro.documentoAnfitrion),
    numAmenidades(otro.numAmenidades), capacidadAmenidades(otro.capacidadAmenidades),
    numFechasReservadas(otro.numFechasReservadas), capacidadFechas(otro.capacidadFechas) {
    amenidades = new string[capacidadAmenidades];
    for (int i = 0; i < numAmenidades; i++) {
        amenidades[i] = otro.amenidades[i];
    }
    fechasInicio = new Fecha[capacidadFechas];
    fechasFin = new Fecha[capacidadFechas];
    for (int i = 0; i < numFechasReservadas; i++) {
        fechasInicio[i] = otro.fechasInicio[i];
        fechasFin[i] = otro.fechasFin[i];
    }
}

Alojamiento::~Alojamiento() {
    delete[] amenidades;
    delete[] fechasInicio;
    delete[] fechasFin;
}

string Alojamiento::getCodigo() const { return codigo; }
string Alojamiento::getNombre() const { return nombre; }
string Alojamiento::getDireccion() const { return direccion; }
string Alojamiento::getDepartamento() const { return departamento; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getTipo() const { return tipo; }
double Alojamiento::getPrecioPorNoche() const { return precioPorNoche; }
string Alojamiento::getDocumentoAnfitrion() const { return documentoAnfitrion; }
string* Alojamiento::getAmenidades() const { return amenidades; }
int Alojamiento::getNumAmenidades() const { return numAmenidades; }
Fecha* Alojamiento::getFechasInicio() const { return fechasInicio; }
Fecha* Alojamiento::getFechasFin() const { return fechasFin; }
int Alojamiento::getNumFechasReservadas() const { return numFechasReservadas; }

void Alojamiento::setCodigo(string cod) {
    codigo = cod.empty() ? "DESCONOCIDO" : cod;
}

void Alojamiento::setNombre(string nom) {
    nombre = nom.empty() ? "Sin nombre" : nom;
}

void Alojamiento::setDireccion(string dir) {
    direccion = dir.empty() ? "Sin direccion" : dir;
}

void Alojamiento::setDepartamento(string depto) {
    departamento = depto.empty() ? "Sin departamento" : depto;
}

void Alojamiento::setMunicipio(string mun) {
    municipio = mun.empty() ? "Sin municipio" : mun;
}

void Alojamiento::setTipo(string t) {
    tipo = (t == "Casa" || t == "Apartamento") ? t : "Casa";
}

void Alojamiento::setPrecioPorNoche(double precio) {
    precioPorNoche = (precio >= 0) ? precio : 0.0;
}

void Alojamiento::setDocumentoAnfitrion(string docAnfitrion) {
    documentoAnfitrion = docAnfitrion.empty() ? "DESCONOCIDO" : docAnfitrion;
}

bool Alojamiento::agregarAmenidad(string amenidad) {
    if (amenidad.empty() || amenidad.length() > 1000) return false;
    if (numAmenidades >= capacidadAmenidades) {
        capacidadAmenidades *= 2;
        string* nuevo = new string[capacidadAmenidades];
        for (int i = 0; i < numAmenidades; i++) {
            nuevo[i] = amenidades[i];
        }
        delete[] amenidades;
        amenidades = nuevo;
    }
    amenidades[numAmenidades++] = amenidad;
    return true;
}

bool Alojamiento::cargarAmenidades(const string* amenidades, int numAmenidades) {
    if (numAmenidades < 0 || amenidades == nullptr) {
        return false;
    }
    for (int i = 0; i < numAmenidades; i++) {
        if (!agregarAmenidad(amenidades[i])) {
            return false;
        }
    }
    return true;
}
bool Alojamiento::agregarFechaReservada(Fecha inicio, Fecha fin) {
    Fecha hoy(17, 5, 2025);
    Fecha limite(17, 5, 2026);

    // Validar fechas futuras y dentro de un año
    if (inicio < hoy || fin < hoy || inicio > limite || fin > limite) {
        return false;
    }

    // Validar que inicio sea antes que fin
    if (!(inicio < fin)) {
        return false;
    }

    // Validar solapamiento
    for (int i = 0; i < numFechasReservadas; i++) {
        Fecha resInicio = fechasInicio[i];
        Fecha resFin = fechasFin[i];
        if (!(fin < resInicio || inicio > resFin)) {
            return false;
        }
    }

    // Redimensionar si necesario
    if (numFechasReservadas >= capacidadFechas) {
        capacidadFechas *= 2;
        Fecha* nuevoInicio = new Fecha[capacidadFechas];
        Fecha* nuevoFin = new Fecha[capacidadFechas];
        for (int i = 0; i < numFechasReservadas; i++) {
            nuevoInicio[i] = fechasInicio[i];
            nuevoFin[i] = fechasFin[i];
        }
        delete[] fechasInicio;
        delete[] fechasFin;
        fechasInicio = nuevoInicio;
        fechasFin = nuevoFin;
    }

    // Añadir rango
    fechasInicio[numFechasReservadas] = inicio;
    fechasFin[numFechasReservadas] = fin;
    numFechasReservadas++;
    return true;
}

bool Alojamiento::estaDisponible(Fecha inicio, int duracion) const {
    if (duracion <= 0) {
        return false;
    }
    Fecha fin = inicio.sumarDias(duracion - 1);
    if (!inicio.esValida() || !fin.esValida()) {
        return false;
    }
    Fecha hoy(17, 5, 2025);
    Fecha limite(17, 5, 2026);
    if (inicio < hoy || fin < hoy || inicio > limite || fin > limite) {
        return false;
    }
    if (inicio > fin) {
        return false;
    }
    for (int i = 0; i < numFechasReservadas; i++) {
        Fecha resInicio = fechasInicio[i];
        Fecha resFin = fechasFin[i];
        if (!(fin < resInicio || inicio > resFin)) {
            return false;
        }
    }
    return true;
}

void Alojamiento::mostrarInfo() const {
    cout << "Informacion del Alojamiento" << endl;
    cout << "--------------------------" << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Precio por noche: $" << fixed << setprecision(2) << precioPorNoche << endl;
    cout << "Documento del Anfitrion: " << documentoAnfitrion << endl;
    cout << "Amenidades: ";
    if (numAmenidades == 0) {
        cout << "Ninguna";
    } else {
        for (int i = 0; i < numAmenidades; i++) {
            cout << amenidades[i];
            if (i < numAmenidades - 1) cout << ", ";
        }
    }
    cout << endl;
    cout << "Fechas reservadas: ";
    if (numFechasReservadas == 0) {
        cout << "Ninguna";
    } else {
        for (int i = 0; i < numFechasReservadas; i++) {
            cout << fechasInicio[i].toString() << " al " << fechasFin[i].toString();
            if (i < numFechasReservadas - 1) cout << ", ";
        }
    }
    cout << endl;
}
