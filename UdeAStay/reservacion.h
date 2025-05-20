#ifndef RESERVACION_H
#define RESERVACION_H

#include "Fecha.h"

class Reservacion {
private:
    std::string codigo;
    Fecha fechaEntrada;
    int duracion;
    std::string codigoAlojamiento;
    std::string documentoHuesped;
    std::string metodoPago; // PSE o TCrédito
    Fecha fechaPago;
    double monto;
    std::string anotaciones; // Máximo 1000 caracteres

public:
    // Constructores
    Reservacion();
    Reservacion(std::string cod, Fecha entrada, int dur, std::string codAloj, std::string docHuesped,
                std::string metodo, Fecha pago, double m, std::string anot);
    Reservacion(const Reservacion& otra);

    // Destructor
    ~Reservacion();

    // Getters
    std::string getCodigo() const;
    Fecha getFechaEntrada() const;
    int getDuracion() const;
    std::string getCodigoAlojamiento() const;
    std::string getDocumentoHuesped() const;
    std::string getMetodoPago() const;
    Fecha getFechaPago() const;
    double getMonto() const;
    std::string getAnotaciones() const;

    // Setters
    void setCodigo(std::string cod);
    void setFechaEntrada(Fecha entrada);
    void setDuracion(int dur);
    void setCodigoAlojamiento(std::string codAloj);
    void setDocumentoHuesped(std::string docHuesped);
    void setMetodoPago(std::string metodo);
    void setFechaPago(Fecha pago);
    void setMonto(double m);
    void setAnotaciones(std::string anot);

    // Métodos
    Fecha getFechaSalida() const; // Calcula fechaEntrada + duracion
    void mostrarComprobante() const; // Muestra detalles
};

#endif
