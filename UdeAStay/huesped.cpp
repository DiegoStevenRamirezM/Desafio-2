#include "huesped.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Huesped::Huesped() : documento(""), antiguedad(0), puntuacion(0.0), contrasena("123456"),
    codigosReservaciones(nullptr), numReservaciones(0) {}

Huesped::Huesped(string doc, int ant, double punt, string pass)
    : documento(doc), antiguedad(ant), puntuacion(punt), contrasena(pass),
    codigosReservaciones(nullptr), numReservaciones(0) {
    // Validar documento
    if (documento.empty()) {
        documento = "DESCONOCIDO";
    }
    // Validar antigüedad
    if (antiguedad < 0) {
        antiguedad = 0;
    }
    // Validar puntuación
    if (puntuacion < 0.0 || puntuacion > 5.0) {
        puntuacion = 0.0;
    }
    // Validar contraseña
    if (pass.empty() || pass.length() < 6) {
        contrasena = "123456";
    }
}

Huesped::Huesped(const Huesped& otro)
    : documento(otro.documento), antiguedad(otro.antiguedad),
    puntuacion(otro.puntuacion), contrasena(otro.contrasena),
    numReservaciones(otro.numReservaciones) {
    codigosReservaciones = nullptr;
    if (numReservaciones > 0) {
        codigosReservaciones = new string[numReservaciones];
        for (int i = 0; i < numReservaciones; i++) {
            codigosReservaciones[i] = otro.codigosReservaciones[i];
        }
    }
}

Huesped::~Huesped() {
    delete[] codigosReservaciones;
}

string Huesped::getDocumento() const { return documento; }
int Huesped::getAntiguedad() const { return antiguedad; }
double Huesped::getPuntuacion() const { return puntuacion; }
string Huesped::getContrasena() const { return contrasena; }
string* Huesped::getCodigosReservaciones() const { return codigosReservaciones; }
int Huesped::getNumReservaciones() const { return numReservaciones; }

void Huesped::setDocumento(string doc) {
    documento = doc.empty() ? "DESCONOCIDO" : doc;
}

void Huesped::setAntiguedad(int ant) {
    antiguedad = (ant < 0) ? 0 : ant;
}

void Huesped::setPuntuacion(double punt) {
    puntuacion = (punt < 0.0 || punt > 5.0) ? 0.0 : punt;
}

void Huesped::setContrasena(string pass) {
    contrasena = (pass.empty() || pass.length() < 6) ? "123456" : pass;
}

bool Huesped::agregarReservacion(string codigo) {
    // Validar que el código no esté ya en la lista
    for (int i = 0; i < numReservaciones; i++) {
        if (codigosReservaciones[i] == codigo) {
            cout << "Error: La reservacion " << codigo << " ya esta registrada." << endl;
            return false;
        }
    }
    // Redimensionar el arreglo
    string* nuevo = new string[numReservaciones + 1];
    for (int i = 0; i < numReservaciones; i++) {
        nuevo[i] = codigosReservaciones[i];
    }
    nuevo[numReservaciones] = codigo;
    delete[] codigosReservaciones;
    codigosReservaciones = nuevo;
    numReservaciones++;
    return true;
}

void Huesped::mostrarInfo() const {
    cout << "Informacion del Huesped" << endl;
    cout << "----------------------" << endl;
    cout << "Documento: " << documento << endl;
    cout << "Antiguedad: " << antiguedad << " meses" << endl;
    cout << "Puntuacion: " << fixed << setprecision(1) << puntuacion << "/5.0" << endl;
    cout << "Contrasena: ";
    for (size_t i = 0; i < contrasena.length(); i++) {
        cout << "*";
    }
    cout << endl;
    cout << "Reservaciones: ";
    if (numReservaciones == 0) {
        cout << "Ninguna" << endl;
    } else {
        cout << endl;
        for (int i = 0; i < numReservaciones; i++) {
            cout << "  - " << codigosReservaciones[i] << endl;
        }
    }
}

