#include "Fecha.h"

Fecha::Fecha() : dia(1), mes(1), anio(2025) {}

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

Fecha::Fecha(const Fecha& otra) : dia(otra.dia), mes(otra.mes), anio(otra.anio) {}

Fecha::~Fecha() {}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

bool Fecha::esValida() const {
    if (mes < 1 || mes > 12 || dia < 1 || anio < 2025) return false;
    int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasMes[1] = 29;
    }
    return dia <= diasMes[mes - 1];
}

Fecha Fecha::sumarDias(int n) const {
    Fecha resultado = *this;
    int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((resultado.anio % 4 == 0 && resultado.anio % 100 != 0) || (resultado.anio % 400 == 0)) {
        diasMes[1] = 29;
    }
    resultado.dia += n;
    while (resultado.dia > diasMes[resultado.mes - 1]) {
        resultado.dia -= diasMes[resultado.mes - 1];
        resultado.mes++;
        if (resultado.mes > 12) {
            resultado.mes = 1;
            resultado.anio++;
            if ((resultado.anio % 4 == 0 && resultado.anio % 100 != 0) || (resultado.anio % 400 == 0)) {
                diasMes[1] = 29;
            } else {
                diasMes[1] = 28;
            }
        }
    }
    return resultado;
}

std::string Fecha::toString() const {
    const char* dias[] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
    const char* meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                           "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int diasDesdeInicio = (anio - 2025) * 365 + (mes - 1) * 30 + dia;
    int diaSemana = (2 + diasDesdeInicio) % 7;
    if (diaSemana < 0) diaSemana += 7;
    std::string resultado = dias[diaSemana];
    resultado += ", ";
    resultado += std::to_string(dia);
    resultado += " de ";
    resultado += meses[mes - 1];
    resultado += " del ";
    resultado += std::to_string(anio);
    return resultado;
}

bool Fecha::operator==(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

bool Fecha::operator>(const Fecha& otra) const {
    return !(*this < otra || *this == otra);
}

bool Fecha::operator>=(const Fecha& otra) const {
    return *this > otra || *this == otra;
}

Fecha Fecha::operator+(int dias) const {
    return sumarDias(dias);
}
