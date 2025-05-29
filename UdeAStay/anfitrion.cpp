#include "anfitrion.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Anfitrion::Anfitrion() : documento(""), antiguedad(0), puntuacion(0.0), contrasena("123456") {}

Anfitrion::Anfitrion(string doc, int ant, double punt, string pass)
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
    if (pass.empty() || pass.length() < 4) {
        contrasena = "123456";
    }
}

Anfitrion::Anfitrion(const Anfitrion& otro)
    : documento(otro.documento), antiguedad(otro.antiguedad),
    puntuacion(otro.puntuacion), contrasena(otro.contrasena) {}

Anfitrion::~Anfitrion() {}

string Anfitrion::getDocumento() const { return documento; }
int Anfitrion::getAntiguedad() const { return antiguedad; }
double Anfitrion::getPuntuacion() const { return puntuacion; }
string Anfitrion::getContrasena() const { return contrasena; }

void Anfitrion::setDocumento(string doc) {
    documento = doc.empty() ? "DESCONOCIDO" : doc;
}

void Anfitrion::setAntiguedad(int ant) {
    antiguedad = (ant < 0) ? 0 : ant;
}

void Anfitrion::setPuntuacion(double punt) {
    puntuacion = (punt < 0.0 || punt > 5.0) ? 0.0 : punt;
}

void Anfitrion::setContrasena(string pass) {
    contrasena = (pass.empty() || pass.length() < 4) ? "123456" : pass;
}

void Anfitrion::mostrarInfo() const {
    cout << "Informacion del Anfitrion" << endl;
    cout << "------------------------" << endl;
    cout << "Documento: " << documento << endl;
    cout << "Antiguedad: " << antiguedad << " meses" << endl;
    cout << "Puntuacion: " << fixed << setprecision(1) << puntuacion << "/5.0" << endl;
    cout << "Contrasena: ";
    for (int i = 0; i < contrasena.length(); i++) {
        cout << "*";
    }
    cout << endl;
}

