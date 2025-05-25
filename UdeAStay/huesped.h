#ifndef HUESPED_H
#define HUESPED_H

#include <string>

class Huesped {
private:
    std::string documento;
    int antiguedad; // En meses
    double puntuacion; // De 0 a 5.0
    std::string contrasena;

public:
    // Constructores
    Huesped();
    Huesped(std::string doc, int ant, double punt, std::string pass);
    Huesped(const Huesped& otro);

    // Destructor
    ~Huesped();

    // Getters
    std::string getDocumento() const;
    int getAntiguedad() const;
    double getPuntuacion() const;
    std::string getContrasena() const;

    // Setters
    void setDocumento(std::string doc);
    void setAntiguedad(int ant);
    void setPuntuacion(double punt);
    void setContrasena(std::string pass);

    // Métodos
    void mostrarInfo() const; // Muestra los datos del huésped
};

#endif
