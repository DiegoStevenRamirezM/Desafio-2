# 🧾 Informe del Desafío 2

**Materia:** Informática II  
**Universidad:** Universidad de Antioquia  
**Estudiante:** Diego Steven Ramírez Molina   
**Profesores:** Aníbal Guerra y Augusto Salazar  
**Semestre:** 2025-1   

---

##  1. Introducción
El presente informe presenta el análisis y diseño de la solución del Desafío 2 , el cual consiste en desarrollar una solución de software basada en programación orientada a objetos (POO), que permita modelar el funcionamiento de un mercado digital de estadías hogareñas, llamado UdeAStay.

Este sistema simula una plataforma donde anfitriones ofrecen alojamientos (casas o apartamentos) con distintas características, y huéspedes pueden consultar la disponibilidad de estas propiedades y realizar reservaciones según criterios de búsqueda como municipio, precio o puntuación del anfitrión. Además, el sistema debe permitir cancelar reservaciones, registrar fechas reservadas, mover información a un archivo histórico, e incluso medir el consumo de recursos (memoria e iteraciones).


## 2. Metodología

### 2.1 Análisis del diseño
Para diseñar este sistema primero se identificaron las principales entidades involucradas: fechas, huéspedes, anfitriones, alojamientos, reservaciones y el portal que las coordina. Además, voy a incluir dos componentes para manejar los datos y los archivos, asegurando que el sistema sea organizado, fácil de usar y que ninguna entidad se sobrecargue. El diseño se basará en los siguientes puntos:

**Entidades Claras:** Cada entidad se representará con una clase que almacena sus datos y acciones específicas. 

**Organización de Tareas:** Las responsabilidades se dividirán entre las clases para que cada una tenga un propósito definido. 

**Facilidad de Uso:** Todo se va a controlar con un menú sencillo que permita interactuar a los huéspedes y anfitriones facilmente.

**Almacenamiento Permanente:** Los datos se van a guardar en archivos de texto para que la información mantenga un registro ordenado.

**Eficiencia:** Se usará memoria dinámica, por ejemplo con arreglos dinámicos para almacenar datos.

### 2.2 Estructura modular del sistema

El sistema estará organizado en ocho clases, cada una con un rol específico para que el programa sea claro y fácil de mantener. Esta estructura permite que cada parte del sistema funcione de manera independiente, pero todas se conectan a través de la clase principal que actúa como coordinadora. La descripción de cómo está organizado el sistema y las responsabilidades de cada clase se podrá ver en la siguiente tabla:


| Clase          | Rol principal                                                                 |
|----------------|-------------------------------------------------------------------------------|
| Fecha          | Manejar fechas, permitiendo validarlas, sumar días, compararlas y mostrarlas en un formato claro (por ejemplo, “Lunes, 12 de Mayo del 2025”).                                              |
| Reservacion    | Gestionar los detalles de una reserva, incluyendo código, fechas, duración, alojamiento, huésped, pago y notas. Genera comprobantes y calcula la fecha de salida.    |
| Huesped        | Representar a un huésped, guardando su documento, antigüedad, puntuación, contraseña y lista de reservaciones. Permite añadir reservas y mostrar sus datos.         |
| Anfitrion      | Representar a un anfitrión, almacenando su documento, antigüedad, puntuación, contraseña y lista de alojamientos. Permite añadir propiedades y mostrar sus datos.          |
| Alojamiento    | Administrar la información de un alojamiento, como su código, nombre, dirección, tipo, precio, amenidades y fechas reservadas. Verifica si está disponible para nuevas reservas.             |
| Portal     | Coordinar el sistema, manejando el inicio de sesión, los menús para huéspedes y anfitriones, y las acciones principales como reservar o cancelar. Conecta todas las clases.    |
| GestorDatos    | Administrar la información en memoria, almacenando y buscando huéspedes, anfitriones, alojamientos y reservas, y asegurando que no haya datos repetidos o errores.      |
| GestorArchivos | Se va a encargar de leer y escribir los datos en archivos de texto, asegurando que la información de huéspedes, anfitriones, alojamientos y reservas se guarde correctamente.|





