#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>

class Anfitrion
{
private:
    std::string documento;
    int antiguedad; // En meses
    double puntuacion; // De 0 a 5.0
    std::string contrasena;
    std::string* codigosAlojamientos; // Arreglo dinámico de códigos
    int numAlojamientos; // Número de alojamientos

public:
    //Constructores
    Anfitrion();
    Anfitrion(std::string doc, int ant, double punt, std::string pass);
    Anfitrion(const Anfitrion& otro);

    // Destructor
    ~Anfitrion();

    // Getters
    std::string getDocumento() const;
    int getAntiguedad() const;
    double getPuntuacion() const;
    std::string getContrasena() const;
    std::string* getCodigosAlojamientos() const;
    int getNumAlojamientos() const;

    // Setters
    void setDocumento(std::string doc);
    void setAntiguedad(int ant);
    void setPuntuacion(double punt);
    void setContrasena(std::string pass);

    // Métodos
    bool agregarAlojamiento(std::string codigo); // Añade un alojamiento
    void mostrarInfo() const; // Muestra los datos del anfitrión
};

#endif // ANFITRION_H
