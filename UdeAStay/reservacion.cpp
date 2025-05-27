#include "reservacion.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Reservacion::Reservacion() : codigo(""), fechaEntrada(), duracion(1), codigoAlojamiento(""),
    documentoHuesped(""), metodoPago("PSE"), fechaPago(), monto(0), anotaciones("") {}

Reservacion::Reservacion(string cod, Fecha entrada, int dur, string codAloj, string docHuesped,
                         string metodo, Fecha pago, double m, string anot)
    : codigo(cod), fechaEntrada(entrada), duracion(dur), codigoAlojamiento(codAloj),
    documentoHuesped(docHuesped), fechaPago(pago), monto(m) {
    // Validar metodoPago
    if (metodo == "PSE" || metodo == "TCredito") {
        metodoPago = metodo;
    } else {
        metodoPago = "PSE"; // Valor por defecto
    }
    // Validar anotaciones (máximo 1000 caracteres)
    if (anot.length() > 1000) {
        anotaciones = anot.substr(0, 1000);
    } else {
        anotaciones = anot;
    }
}

//Constructor de copia
Reservacion::Reservacion(const Reservacion& otra)
    : codigo(otra.codigo), fechaEntrada(otra.fechaEntrada), duracion(otra.duracion),
    codigoAlojamiento(otra.codigoAlojamiento), documentoHuesped(otra.documentoHuesped),
    metodoPago(otra.metodoPago), fechaPago(otra.fechaPago), monto(otra.monto),
    anotaciones(otra.anotaciones) {}

Reservacion::~Reservacion() {}

string Reservacion::getCodigo() const { return codigo; }
Fecha Reservacion::getFechaEntrada() const { return fechaEntrada; }
int Reservacion::getDuracion() const { return duracion; }
string Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
string Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
string Reservacion::getMetodoPago() const { return metodoPago; }
Fecha Reservacion::getFechaPago() const { return fechaPago; }
int Reservacion::getMonto() const { return monto; }
string Reservacion::getAnotaciones() const { return anotaciones; }

void Reservacion::setCodigo(string cod) { codigo = cod; }
void Reservacion::setFechaEntrada(Fecha entrada) { fechaEntrada = entrada; }
void Reservacion::setDuracion(int dur) { duracion = dur; }
void Reservacion::setCodigoAlojamiento(string codAloj) { codigoAlojamiento = codAloj; }
void Reservacion::setDocumentoHuesped(string docHuesped) { documentoHuesped = docHuesped; }
void Reservacion::setMetodoPago(string metodo) {
    if (metodo == "PSE" || metodo == "TCrédito") {
        metodoPago = metodo;
    } else {
        metodoPago = "PSE"; // metodo de pago por defecto
    }
}
void Reservacion::setFechaPago(Fecha pago) { fechaPago = pago; }
void Reservacion::setMonto(int m) { monto = m; }
void Reservacion::setAnotaciones(string anot) {
    if (anot.length() > 1000) {
        anotaciones = anot.substr(0, 1000);
    } else {
        anotaciones = anot;
    }
}

Fecha Reservacion::getFechaSalida() const {
    return fechaEntrada.sumarDias(duracion);
}

void Reservacion::mostrarComprobante() const {
    cout << "Comprobante de Reservacion" << endl;
    cout << "-------------------------" << endl;
    cout << "Codigo de Reservacion: " << codigo << endl;
    cout << "Fecha de Entrada: " << fechaEntrada.toString() << endl;
    cout << "Fecha de Salida: " << getFechaSalida().toString() << endl;
    cout << "Duracion: " << duracion << " noches" << endl;
    cout << "Codigo de Alojamiento: " << codigoAlojamiento << endl;
    cout << "Documento del Huesped: " << documentoHuesped << endl;
    cout << "Metodo de Pago: " << metodoPago << endl;
    cout << "Fecha de Pago: " << fechaPago.toString() << endl;
    cout << "Monto: $" << monto << endl;
    cout << "Anotaciones: ";
    if (anotaciones.empty()) {
        cout << "Ninguna" << endl;
    } else {
        cout << anotaciones << endl;
    }
}
