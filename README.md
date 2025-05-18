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





