#ifndef FECHA_H
#define FECHA_H

#include <string>

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    // Constructores
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(const Fecha& otra);

    // Destructor
    ~Fecha();

    // Getters y setters
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // Métodos
    bool esValida() const; // Valida que la fecha sea valida
    Fecha sumarDias(int n) const; // Suma n días (suma la cantidad de noches)
    std::string toString() const; // Lo pasa al Formato "nombreDia, día de nombreMes del año"

    //  Sobrecarga de operadores que serviran para las comparaciones entre fechas
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const; // Añadido
    Fecha operator+(int dias) const;
};

#endif
