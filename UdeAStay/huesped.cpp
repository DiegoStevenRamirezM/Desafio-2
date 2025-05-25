#include "huesped.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Huesped::Huesped() : documento(""), antiguedad(0), puntuacion(0.0), contrasena("123456") {}

Huesped::Huesped(string doc, int ant, double punt, string pass)
    : documento(doc), antiguedad(ant), puntuacion(punt), contrasena(pass) {
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
    puntuacion(otro.puntuacion), contrasena(otro.contrasena) {}

Huesped::~Huesped() {}

string Huesped::getDocumento() const { return documento; }
int Huesped::getAntiguedad() const { return antiguedad; }
double Huesped::getPuntuacion() const { return puntuacion; }
string Huesped::getContrasena() const { return contrasena; }

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

void Huesped::mostrarInfo() const {
    cout << "Informacion del Huesped" << endl;
    cout << "----------------------" << endl;
    cout << "Documento: " << documento << endl;
    cout << "Antiguedad: " << antiguedad << " meses" << endl;
    cout << "Puntuacion: " << fixed << setprecision(1) << puntuacion << "/5.0" << endl;
    cout << "Contrasena: ";
    for (int i = 0; i < contrasena.length(); i++) {
        cout << "*";
    }
    cout << endl;
}

