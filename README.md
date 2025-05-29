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

### 2.3 Justificación de la modularidad.

Esta estructura hace que el sistema sea fácil de usar y mantener, ya que cada clase tiene un propósito claro. También permite agregar nuevas funciones en el futuro en caso de que se me haya olvidado alguna, sin afectar el resto del programa. En general dividí las clases en estas 3:

***Clases de Entidades:*** Las clases Fecha, Huesped, Anfitrion, Alojamiento y Reservacion representan los objetos principales del sistema. Cada una guarda la información necesaria y ofrece funciones para trabajar con esos datos, como validar fechas o mostrar comprobantes.

***Clases de Gestión:*** GestorArchivos y GestorDatos se crearon para manejar tareas específicas. GestorArchivos trabaja con los archivos donde se guarda la información, mientras que GestorDatos organiza los datos en la memoria del programa, haciendo que las búsquedas y actualizaciones sean más rápidas.

***Clase Coordinadora:*** Portal actúa como el centro del sistema, conectando las demás clases. Por ejemplo, cuando un huésped quiere reservar, Plataforma usa GestorDatos para buscar alojamientos y GestorArchivos para guardar la nueva reserva.

Las clases están relacionadas de manera lógica. Por ejemplo, Alojamiento usa Fecha para manejar sus fechas reservadas, y Huesped guarda códigos de Reservacion para rastrear las reservas de un usuario.

### 2.4 Estructuras de datos
Usaré arreglos dinámicos de punteros. Esta estrategia es para el cumplimiento del desafío, además de proporcionar un control detallado sobre la gestión de memoria y la eficiencia computacional del sistema. Cada lista de objetos (como huéspedes, anfitriones, alojamientos o reservaciones) se representa mediante un arreglo de punteros a objetos, el cual se redimensiona cuando se agrega un nuevo elemento. La estructura será la siguiente:

| Entidad / Datos          | Clase responsable | Estructura utilizada               | Atributo / Rol de clase responsable       |
|--------------------------|-------------------|------------------------------------|------------------------------------------|
| Huéspedes                | GestorDatos       | `Huesped**` (punteros dinámicos)   | `Huesped** huespedes`                    |
| Anfitriones              | GestorDatos       | `Anfitrion**`                      | `Anfitrion** anfitriones`                |
| Alojamientos             | GestorDatos       | `Alojamiento**`                    | `Alojamiento** alojamientos`             |
| Reservaciones vigentes   | GestorDatos       | `Reservacion**`                    | `Reservacion** reservacionesVigentes`    |
| Reservaciones históricas | GestorDatos       | `Reservacion**`                    | `Reservacion** reservasHistoricas`       |
| Fechas reservadas (por alojamiento) | Alojamiento | `Fecha* fechasInicio`, `Fecha* fechasFin` | Interno a cada alojamiento          |
| Amenidades               | Alojamiento       | `string* amenidades`               | Interno                                 |
| Códigos de reservas      | Huesped           | `string* codigosReservaciones`     | Interno                                 |
| Códigos de alojamientos  | Anfitrion         | `string* codigosAlojamientos`        | Interno                                 |

### 2.5  Formato de los archivos 
Para el desarrollo del sistema UdeAStay se optó por utilizar archivos de texto plano (.txt) como método de almacenamiento persistente para las entidades clave del sistema: huéspedes, anfitriones, alojamientos y reservaciones (tanto vigentes como históricas). 

Esta decisión se basa en varias razones:

**1.** La primera razón es que los archivos .txt son fácilmente legibles y editables, lo que facilita la depuración, revisión y carga manual de datos en caso de pruebas o demostraciones. Además, los archivos de texto no requieren bibliotecas adicionales ni formatos binarios complejos, lo que nos ayudará a tener una mayor portabilidad del sistema entre distintos entornos o plataformas de desarrollo.

**2.** El uso de archivos .txt permite aplicar directamente conceptos de manejo básico de archivos en C++.

**3.** Dividir la información en archivos separados por entidad (uno por clase a excepción de Fecha) permite lograr una estructura modular y organizada, facilitando el mantenimiento y la escalabilidad del sistema. Al tener  una clase especializada (GestorArchivos), estos archivos pueden ser fácilmente reutilizados, reescritos o extendidos según futuras necesidades del sistema sin alterar la lógica del programa.

Estos serán los archivos .txt que usaré:

| Archivo               | Contenido principal                                                                 |
|-----------------------|------------------------------------------------------------------------------------|
| huespedes.txt         | Lista de huéspedes registrados en la plataforma.                                   |
| anfitriones.txt       | Lista de anfitriones registrados.                                                  |
| alojamientos.txt      | Detalles de los alojamientos disponibles.           |
| reservas_vigentes.txt     | Reservaciones activas o vigentes.                                                  |
| reservas_historicas.txt| Reservaciones vencidas trasladadas a histórico.                                    |

### 2.6 Diagrama UML

El diagrama de clases es la columna vertebral del diseño orientado a objetos en UdeAStay, ya que:

- **Clarifica la estructura**: Visualiza las entidades principales (`Plataforma`, `GestorDatos`, `Huesped`, etc.) y sus relaciones.  
- **Guía la implementación**: Define atributos, métodos y cardinalidades (ej: `1..*` para listas dinámicas).  
- **Evita redundancias**: Modela composiciones/agregaciones (como `GestorDatos` y `Huesped`) para optimizar memoria.  

---

### 🖼️ **Este es mi diagrama de clases**  

![Diagrama UML](./Diagrama%20UML%20Desafío%202.jpg)

### 2.7 Tabla de relaciones entre clases en el sistema UdeAStay

| Clase A       | Clase B       | Tipo de Relación       | ¿Por qué?  |
|---------------|---------------|------------------------|-----------------------------------|
| Portal    | GestorDatos       |       Asociación (1 a 1)    | Portal necesita un objeto de `GestorDatos` para ejecutar funciones como autenticación, manejo de usuarios, búsqueda de datos y creación de reservaciones. Sin embargo, `GestorDatos` es un módulo auxiliar independiente que no forma parte estructural de `Portal`. Por tanto, la relación es una asociación funcional. |
| Portal    | GestorArchivos|      Asociación (1 a 1)     | Portal delega las operaciones de entrada/salida a `GestorArchivos`, pero `GestorArchivos` puede funcionar por separado, y no se destruye junto con `Portal`. Por eeso la relación es de asociación y no de composición ni agregación. |
| GestorDatos   | Huesped       |      Agregación (0..N)      | `GestorDatos` contiene una colección dinámica de `Huespedes`, pero los huéspedes son objetos autónomos que pueden crearse, modificarse o incluso existir fuera del contexto de `GestorDatos` (por ejemplo, al cargarlos desde un archivo). Por ello, la relación es de agregación: `Huesped` es parte del sistema, pero no depende estructuralmente de `GestorDatos`. |
| GestorDatos   | Anfitrion     |      Agregación (0..N)      | Parecido a los huesped, los `Anfitriones` son gestionados por `GestorDatos` mediante un arreglo dinámico. Sin embargo, pueden existir sin él (por ejemplo, ser creados antes de guardar en el sistema). Eso significa una agregación: `GestorDatos` los administra, pero no los posee completamente. |
| GestorDatos   | Alojamiento      |  Agregación (0..N)       | Los `Alojamientos` son creados por los `Anfitriones`, pero gestionados globalmente por `GestorDatos`. No hay dependencia estructural fuerte: son objetos independientes. |
| GestorDatos   | Reservacion      |  Composición (0..N)  | Las `Reservaciones` son creadas y destruidas exclusivamente por `GestorDatos`. Si `GestorDatos` se elimina, todas sus reservaciones también se destruyen. |
| Reservacion   | Fecha            |  Asociación (1 a 1)      | Cada `Reservacion` usa objetos `Fecha` (entrada/salida), pero no los gestiona. Las fechas son valores compuestos, no dependen de la reserva. |
| Alojamiento   | Fecha (reservas) |  Composición (0..N) | Las fechas de reserva son parte integral del `Alojamiento`. Si se elimina el alojamiento, sus fechas reservadas también desaparecen . |
| Huesped       | Reservacion      |  Asociación débil (0..N) | El `Huesped` solo guarda códigos (strings) de reservas, no instancias. Relación indirecta sin dependencia estructural. |
| Anfitrion     | Alojamiento      |  Asociación débil (0..N) | El `Anfitrion` referencia alojamientos mediante códigos (strings), sin contener los objetos directamente. Relación lógica, no estructural. |

---
## Actualizacion final
### 3. Descripción de algoritmos clave

A continuación se describen, en alto nivel, algunos de los subprogramas más importantes del sistema:

- **crearReservacion():**  
  Verifica si el alojamiento está disponible para las fechas deseadas. Si no hay conflictos, crea el objeto `Reservacion`, lo agrega al arreglo dinámico y guarda la información en archivo. También calcula la fecha de salida sumando la duración a la fecha de entrada.

- **moverReservasAHistorico():**  
  Recorre las reservaciones activas y, si su fecha de entrada es anterior a la fecha de corte, las mueve al arreglo de reservas históricas. Además, actualiza los archivos eliminando esas reservas del archivo de vigentes y agregándolas al archivo histórico.

- **estaDisponible():**  
  Evalúa si un alojamiento tiene disponible el rango de fechas solicitado. Compara las fechas nuevas con cada intervalo existente para evitar solapamientos. Utiliza la fecha de corte como límite inferior válido.

- **mostrarResumenEficiencia():**  
  Se invoca al final del programa. Calcula la memoria total usada con base en el tamaño de los arreglos dinámicos y muestra el número total de iteraciones e invocaciones a métodos externos, como parte del análisis computacional.

---

### 4. Problemas de desarrollo y decisiones tomadas

Durante el desarrollo del sistema se presentaron varios desafíos técnicos:

- Inicialmente, los códigos de reservación estaban almacenados dentro de la clase `Huesped`, lo que causaba duplicación de datos y problemas de sincronización con los archivos. Por esta razón, se optó por eliminarlos y confiar en la búsqueda directa desde el archivo o desde `GestorDatos`.

- De forma similar, los códigos de alojamientos fueron eliminados de la clase `Anfitrion`, ya que el vínculo ya se establece a través del atributo `documentoAnfitrion` en la clase `Alojamiento`.

- Para garantizar la unicidad de los códigos de reserva sin utilizar STL, se implementó una función de generación automática que verifica contra los códigos existentes tanto en reservas vigentes como en las históricas.

- Medir la eficiencia del sistema sin alterar clases como `GestorArchivos` representó un reto. Para solucionarlo, se creó un sistema de contadores dentro de `GestorDatos`, que puede ser invocado por otras clases para reportar iteraciones e invocaciones externas sin romper la modularidad.

---

### 5. Medición del consumo de recursos y eficiencia

Como parte del análisis de eficiencia del sistema UdeAStay, se incluyó un mecanismo automático que evalúa el consumo de recursos computacionales. Al finalizar la ejecución del programa, se imprime un resumen con:

- **Número total de iteraciones:**  
  Se cuenta manualmente cada iteración importante dentro de los bucles que recorren arreglos dinámicos. Se suma mediante el método `sumarIteraciones(int)`.

- **Número de invocaciones externas:**  
  Se lleva un conteo específico de invocaciones a funciones como `getline`, `stoi`, `tolower`, entre otras. Estas se registran mediante `sumarInvocacionesExternas(int)` solo si impactan el procesamiento lógico.

- **Memoria usada:**  
  Se calcula manualmente estimando el tamaño ocupado por los arreglos dinámicos (cantidad de objetos multiplicado por su peso estimado en bytes). Esta cifra no es precisa a nivel de sistema operativo, pero permite un análisis proporcional del uso de memoria.

- **Costo computacional global:**  
  La complejidad del sistema es **O(n)** para la mayoría de sus operaciones, ya que utiliza estructuras simples como arreglos dinámicos y búsquedas secuenciales.

---

### 6. Formato detallado de archivos de texto

Para la persistencia de datos, el sistema utiliza archivos `.txt` legibles, organizados por entidad. A continuación se describen sus formatos:

- **huespedes.txt**  
documento,antiguedad,puntuacion,contrasena

- **anfitriones.txt**  
documento,antiguedad,puntuacion,contrasena

- **alojamientos.txt**  
codigo,nombre,direccion,departamento,municipio,tipo,precio,documentoAnfitrion,numAmenidades,amenidad1,...,amenidadN

- **reservas_vigentes.txt**  
codigo,fechaEntrada,duracion,codigoAlojamiento,documentoHuesped,metodoPago,fechaPago,monto,anotaciones

- **reservas_historicas.txt**  
codigo,fechaEntrada,duracion,codigoAlojamiento,documentoHuesped,metodoPago,fechaPago,monto,anotaciones

- **fecha_corte.txt**  
dd-mm-aaaa

