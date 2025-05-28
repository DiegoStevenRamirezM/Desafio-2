#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "Fecha.h"
#include <string>

class Alojamiento
{
private:
    std::string codigo;
    std::string nombre;
    std::string direccion;
    std::string departamento;
    std::string municipio;
    std::string tipo; // Casa o Apartamento
    int precioPorNoche;
    std::string documentoAnfitrion;
    std::string* amenidades; // Arreglo dinámico
    int numAmenidades;
    int capacidadAmenidades;
    Fecha* fechasInicio; // Arreglo dinámico para inicios de reservas
    Fecha* fechasFin; // Arreglo dinámico para fines de reservas
    int numFechasReservadas;
    int capacidadFechas;

public:
    //Constructores
    Alojamiento();
    Alojamiento(std::string cod, std::string nom, std::string dir, std::string depto,
                std::string mun, std::string t, int precio, std::string docAnfitrion);
    Alojamiento(const Alojamiento& otro);

    // Destructor
    ~Alojamiento();

    // Getters
    std::string getCodigo() const;
    std::string getNombre() const;
    std::string getDireccion() const;
    std::string getDepartamento() const;
    std::string getMunicipio() const;
    std::string getTipo() const;
    int getPrecioPorNoche() const;
    std::string getDocumentoAnfitrion() const;
    std::string* getAmenidades() const;
    int getNumAmenidades() const;
    Fecha* getFechasInicio() const;
    Fecha* getFechasFin() const;
    int getNumFechasReservadas() const;

    // Setters
    void setCodigo(std::string cod);
    void setNombre(std::string nom);
    void setDireccion(std::string dir);
    void setDepartamento(std::string depto);
    void setMunicipio(std::string mun);
    void setTipo(std::string t);
    void setPrecioPorNoche(int precio);
    void setDocumentoAnfitrion(std::string docAnfitrion);

    // Métodos
    void mostrarInfo() const;
    bool agregarAmenidad(std::string amenidad);
    bool cargarAmenidades(const std::string* amenidades, int numAmenidades);
    bool agregarFechaReservada(Fecha inicio, Fecha fin);
    bool estaDisponible(Fecha inicio, int duracion, const Fecha& fechaCorte) const;
};

#endif // ALOJAMIENTO_H
