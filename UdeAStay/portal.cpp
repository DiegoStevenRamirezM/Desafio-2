#include "portal.h"
#include <iostream>

using namespace std;

//Constructor y destructor
Portal::Portal(){
    gestorArchivos.leerFechaCorte(fechaCorte);
    gestorArchivos.cargarHuespedes("huespedes.txt", &gestorDatos);
    gestorArchivos.cargarAnfitriones("anfitriones.txt", &gestorDatos);
    gestorArchivos.cargarAlojamientos("alojamientos.txt", &gestorDatos);
    gestorArchivos.cargarReservaciones("reservas_vigentes.txt", &gestorDatos);
    gestorArchivos.cargarReservasHistoricas("reservas_historicas.txt", &gestorDatos);
}

Portal::~Portal() {}

//Entrada al sistema
void Portal::iniciarSistema() {
    mostrarMenuPrincipal();
}

//Autenticación de los huespedes
bool Portal::loginHuesped( string documento,  string contrasena) {
    Huesped* h = gestorDatos.buscarHuesped(documento);
    return h && h->getContrasena() == contrasena;
}

//Autenticación de los anfitriones
bool Portal::loginAnfitrion( string documento,  string contrasena) {
    Anfitrion* a = gestorDatos.buscarAnfitrion(documento);
    return a && a->getContrasena() == contrasena;
}

//MENUS SEGUN EL PERFIL

//Mostrar el menu principal
void Portal::mostrarMenuPrincipal() {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n==================================\n";
        cout << "         BIENVENIDO A UdeAStay     \n";
        cout << "==================================\n";
        cout << "1. Iniciar sesion como huesped\n";
        cout << "2. Iniciar sesion como anfitrion\n";
        cout << "3. Salir del sistema\n";
        cout << "----------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        string doc, pass;

        switch (opcion) {
        case 1:
            cout << "\n--- Inicio de sesion (Huesped) ---\n";
            cout << "Documento: ";
            getline( cin, doc);
            gestorDatos.sumarInvocacionesExternas(1); // getline
            cout << "Contrasena: ";
            getline( cin, pass);
            gestorDatos.sumarInvocacionesExternas(1); // getline
            if (loginHuesped(doc, pass)) {
                mostrarMenuHuesped(doc);
            } else {
                cout << "Credenciales incorrectas. Intente de nuevo.\n";
            }
            break;

        case 2:
            cout << "\n--- Inicio de sesion (Anfitrion) ---\n";
            cout << "Documento: ";
            getline( cin, doc);
            gestorDatos.sumarInvocacionesExternas(1); // getline
            cout << "Contrasena: ";
            getline( cin, pass);
            gestorDatos.sumarInvocacionesExternas(1); // getline
            if (loginAnfitrion(doc, pass)) {
                mostrarMenuAnfitrion(doc);
            } else {
                cout << "Credenciales incorrectas. Intente de nuevo.\n";
            }
            break;

        case 3:
            cout << "\nGuardando datos...\n";
            gestorArchivos.guardarReservacionesVigentes("reservas_vigentes.txt", &gestorDatos);
            gestorArchivos.guardarReservacionesHistoricas("reservas_historicas.txt", &gestorDatos);
            gestorArchivos.guardarFechaCorte(fechaCorte);
            cout << "Datos guardados correctamente.\n";
            mostrarResumenEficiencia();
            cout << "Gracias por usar UdeAStay. Hasta pronto.\n";
            salir = true;
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    }
}

//Mostrar el menu del huesped
void Portal::mostrarMenuHuesped(const  string& documento) {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n----------- MENU HUESPED -----------\n";
        cout << "1. Ver reservas activas\n";
        cout << "2. Crear nueva reservacion\n";
        cout << "3. Cancelar una reservacion\n";
        cout << "4. Cerrar sesion\n";
        cout << "------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            mostrarReservasVigentesHuesped(documento);
            break;

        case 2: {
            int subopcion;
            cout << "\n--- Opciones de busqueda ---\n";
            cout << "1. Buscar con filtros (municipio, precio, puntuacion)\n";
            cout << "2. Buscar por codigo de alojamiento\n";
            cout << "Seleccione una opcion: ";
            cin >> subopcion;
            cin.ignore();

            if (subopcion == 1) {
                buscarAlojamientoConFiltros(documento);
            } else if (subopcion == 2) {
                buscarAlojamientoPorCodigo(documento);
            } else {
                cout << "Opcion invalida.\n";
            }
            break;
        }

        case 3:
            cancelarReservacionComoHuesped(documento);
            break;

        case 4:
            salir = true;
            cout << "Sesion cerrada.\n";
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    }
}

//Mostrar el menu del anfitrion
void Portal::mostrarMenuAnfitrion(const  string& documento) {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n-------- MENU ANFITRION --------\n";
        cout << "1. Ver reservas de mis alojamientos\n";
        cout << "2. Cancelar una reservacion\n";
        cout << "3. Actualizar fecha de corte y mover al historico\n";
        cout << "4. Cerrar sesion\n";
        cout << "--------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            verReservasDeAlojamientos(documento);
            break;

        case 2:
            cancelarReservacionComoAnfitrion(documento);
            break;

        case 3:
            actualizarFechaCorte();
            break;

        case 4:
            salir = true;
            cout << "Sesion cerrada.\n";
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    }
}


//GESTION DE RESERVAS

//Crear una reserva
void Portal::crearReservacionConCodigo(const string& documento, const string& codAloj, Fecha entrada, int duracion) {
    string codigo = gestorDatos.generarCodigoReserva();
    string metodo, anotacion;
    int monto;

    cout << "\n--- CREAR RESERVACION ---\n";
    cout << "Codigo generado automaticamente: " << codigo << "\n";

    cout << "Metodo de pago: ";
    getline(cin, metodo);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    cout << "Monto (COP): ";
    cin >> monto;
    cin.ignore();

    cout << "Anotaciones (opcional): ";
    getline(cin, anotacion);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    Fecha fechaPago = fechaCorte;

    Huesped* h = gestorDatos.buscarHuesped(documento);
    Alojamiento* a = gestorDatos.buscarAlojamiento(codAloj);
    if (!h || !a) {
        cout << "Error: Huesped o alojamiento no valido.\n";
        return;
    }

    if (!a->estaDisponible(entrada, duracion, fechaCorte)) {
        cout << "Error: El alojamiento no esta disponible en esas fechas.\n";
        return;
    }

    int minimoEsperado = a->getPrecioPorNoche() * duracion;

    if (monto < minimoEsperado) {
        cout << "\nEl monto ingresado (" << monto << " COP) es inferior al valor esperado (" << minimoEsperado << " COP).\n";
        cout << "Desea continuar? (s/n): ";
        char r;
        cin >> r;
        cin.ignore();
        if (tolower(r) != 's') {
            gestorDatos.sumarInvocacionesExternas(1); // tolower
            cout << "Reservacion cancelada.\n";
            return;
        }
    }

    if (monto > minimoEsperado) {
        cout << "\nHa ingresado un monto superior al valor esperado (" << minimoEsperado << " COP).\n";
        cout << "Desea continuar con ese monto? (s/n): ";
        char r;
        cin >> r;
        cin.ignore();
        if (tolower(r) != 's') {
            gestorDatos.sumarInvocacionesExternas(1); // tolower
            cout << "Reservacion cancelada.\n";
            return;
        }
    }

    Reservacion* r = new Reservacion(codigo, entrada, duracion, codAloj, documento, metodo, fechaPago, monto, anotacion);

    if (!r) {
        cout << "Error: No se pudo crear la reservacion.\n";
        return;
    }

    if (gestorDatos.crearReservacion(r, fechaCorte)) {
        cout << "\nReservacion creada exitosamente.\n";
        r->mostrarComprobante();
        gestorArchivos.guardarReservacionesVigentes("reservas_vigentes.txt", &gestorDatos);
    } else {
        delete r;
        cout << "No se pudo crear la reservacion (posiblemente ya existe).\n";
    }
}

//Cancelar una reservacion (huesped)
void Portal::cancelarReservacionComoHuesped(const string& documento) {
    Reservacion** todas = gestorDatos.getReservaciones();
    int n = gestorDatos.getNumReservaciones();
    Fecha hoy = fechaCorte;

    bool hayActivas = false;
    cout << "\n----- TUS RESERVAS ACTIVAS -----\n";

    for (int i = 0; i < n; i++) {
        if (todas[i]->getDocumentoHuesped() == documento &&
            todas[i]->getFechaEntrada() >= hoy) {
            todas[i]->mostrarComprobante();
            cout << "-------------------------------\n";
            hayActivas = true;
        }
    }

    if (!hayActivas) {
        cout << "No tienes reservas activas para cancelar.\n";
        return;
    }

    string codigo;
    cout << "\nIngrese el codigo de la reservacion que desea cancelar: ";
    getline(cin, codigo);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    Reservacion* r = gestorDatos.buscarReservacion(codigo);
    if (!r) {
        cout << "Reservacion no encontrada.\n";
        return;
    }

    if (r->getDocumentoHuesped() != documento) {
        cout << "Solo puedes cancelar tus propias reservaciones.\n";
        return;
    }

    if (gestorDatos.cancelarReservacion(codigo)) {
        cout << "Reservacion cancelada exitosamente.\n";
        gestorArchivos.guardarReservacionesVigentes("reservas_vigentes.txt", &gestorDatos);
    } else {
        cout << "Error al cancelar la reservacion.\n";
    }
}
//Cancelar una reservacion (Anfitrion)
void Portal::cancelarReservacionComoAnfitrion(const string& documento) {
    Alojamiento** todos = gestorDatos.getAlojamientos();
    int totalAlojamientos = gestorDatos.getNumAlojamientos();

    string* codigosAlojamientos = nullptr;
    int numAlojamientos = 0;

    for (int i = 0; i < totalAlojamientos; i++) {
        if (todos[i]->getDocumentoAnfitrion() == documento) {
            string* nuevo = new string[numAlojamientos + 1];
            for (int j = 0; j < numAlojamientos; j++) {
                nuevo[j] = codigosAlojamientos[j];
            }
            nuevo[numAlojamientos] = todos[i]->getCodigo();
            delete[] codigosAlojamientos;
            codigosAlojamientos = nuevo;
            numAlojamientos++;
        }
    }

    if (numAlojamientos == 0) {
        cout << "No tienes alojamientos registrados.\n";
        return;
    }

    Reservacion** todasReservas = gestorDatos.getReservaciones();
    int totalReservas = gestorDatos.getNumReservaciones();
    Fecha hoy = fechaCorte;

    bool hayActivas = false;
    cout << "\n--- RESERVAS ACTIVAS DE TUS ALOJAMIENTOS ---\n";

    for (int i = 0; i < totalReservas; i++) {
        string codAloj = todasReservas[i]->getCodigoAlojamiento();
        Fecha entrada = todasReservas[i]->getFechaEntrada();

        for (int j = 0; j < numAlojamientos; j++) {
            if (codAloj == codigosAlojamientos[j] && entrada >= hoy) {
                todasReservas[i]->mostrarComprobante();
                cout << "-------------------------------------------\n";
                hayActivas = true;
                break;
            }
        }
    }

    delete[] codigosAlojamientos;

    if (!hayActivas) {
        cout << "No hay reservas activas para cancelar.\n";
        return;
    }

    string codigo;
    cout << "\nIngrese el codigo de la reservacion que desea cancelar: ";
    getline(cin, codigo);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    Reservacion* r = gestorDatos.buscarReservacion(codigo);
    if (!r) {
        cout << "Reservacion no encontrada.\n";
        return;
    }

    string codAloj = r->getCodigoAlojamiento();
    Alojamiento* a = gestorDatos.buscarAlojamiento(codAloj);
    if (!a || a->getDocumentoAnfitrion() != documento) {
        cout << "No tienes permiso para cancelar esta reservacion.\n";
        return;
    }

    if (gestorDatos.cancelarReservacion(codigo)) {
        cout << "Reservacion cancelada exitosamente.\n";
        gestorArchivos.guardarReservacionesVigentes("reservas_vigentes.txt", &gestorDatos);
    } else {
        cout << "Error al cancelar la reservacion.\n";
    }
}

//Mostrar las reservas vigentes (Huesped)
void Portal::mostrarReservasVigentesHuesped(const string& documento) {
    Huesped* h = gestorDatos.buscarHuesped(documento);
    if (!h) {
        cout << "Huesped no encontrado.\n";
        return;
    }

    cout << "\n--- RESERVAS ACTIVAS DE " << documento << " ---\n";

    Reservacion** todas = gestorDatos.getReservaciones();
    int n = gestorDatos.getNumReservaciones();
    Fecha hoy = fechaCorte;

    bool hayActivas = false;

    for (int i = 0; i < n; i++) {
        if (todas[i]->getDocumentoHuesped() == documento &&
            todas[i]->getFechaEntrada() >= hoy) {
            todas[i]->mostrarComprobante();
            cout << "-----------------------------\n";
            hayActivas = true;
        }
    }

    if (!hayActivas) {
        cout << "No tienes reservas activas.\n";
    }
}

//Ver las reservas de un alojamiento en un rango de fechas (Anfitrion)
void Portal::verReservasDeAlojamientos(const string& docAnfitrion) {
    int dia1, mes1, anio1;
    int dia2, mes2, anio2;

    cout << "\nIngrese la fecha inicial del rango (dd mm aaaa): ";
    cin >> dia1 >> mes1 >> anio1;
    cout << "Ingrese la fecha final del rango (dd mm aaaa): ";
    cin >> dia2 >> mes2 >> anio2;
    cin.ignore();
    gestorDatos.sumarInvocacionesExternas(1); // cin.ignore()

    Fecha inicio(dia1, mes1, anio1);
    Fecha fin(dia2, mes2, anio2);

    if (!inicio.esValida() || !fin.esValida() || fin < inicio) {
        cout << "Rango de fechas invalido.\n";
        return;
    }

    Alojamiento** todos = gestorDatos.getAlojamientos();
    int totalAlojamientos = gestorDatos.getNumAlojamientos();

    string* codigosAlojamientos = nullptr;
    int numAlojamientos = 0;

    for (int i = 0; i < totalAlojamientos; i++) {
        if (todos[i]->getDocumentoAnfitrion() == docAnfitrion) {
            string* nuevo = new string[numAlojamientos + 1];
            for (int j = 0; j < numAlojamientos; j++) {
                nuevo[j] = codigosAlojamientos[j];
            }
            nuevo[numAlojamientos] = todos[i]->getCodigo();
            delete[] codigosAlojamientos;
            codigosAlojamientos = nuevo;
            numAlojamientos++;
        }
    }

    if (numAlojamientos == 0) {
        cout << "No tienes alojamientos registrados.\n";
        return;
    }

    cout << "\nTus alojamientos registrados son: ";
    for (int i = 0; i < numAlojamientos; i++) {
        cout << codigosAlojamientos[i];
        if (i < numAlojamientos - 1) cout << ", ";
    }
    cout << "\n";

    Reservacion** todasReservas = gestorDatos.getReservaciones();
    int totalReservas = gestorDatos.getNumReservaciones();
    bool hay = false;

    cout << "\n--- RESERVAS ACTIVAS EN EL RANGO ---\n";
    for (int i = 0; i < totalReservas; i++) {
        string codAloj = todasReservas[i]->getCodigoAlojamiento();
        Fecha entrada = todasReservas[i]->getFechaEntrada();
        Fecha salida = todasReservas[i]->getFechaSalida();

        for (int j = 0; j < numAlojamientos; j++) {
            if (codAloj == codigosAlojamientos[j] &&
                !(salida < inicio || entrada > fin)) {

                todasReservas[i]->mostrarComprobante();
                cout << "-----------------------------------\n";
                hay = true;
                break;
            }
        }
    }

    delete[] codigosAlojamientos;

    if (!hay) {
        cout << "No hay reservas activas dentro del rango especificado.\n";
    }
}

//BUSQUEDAS

//Buscar alojamiento por filtro
void Portal::buscarAlojamientoConFiltros(const string& documento) {
    string municipio;
    int dia, mes, anio, duracion;

    cout << "\n=== Busqueda de Alojamiento ===\n";
    cout << "Municipio: ";
    getline(cin, municipio);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    for (int i = 0; i < municipio.length(); i++) {
        municipio[i] = tolower(municipio[i]);
        gestorDatos.sumarInvocacionesExternas(1); // tolower
    }

    cout << "Fecha de entrada (dd mm aaaa): ";
    cin >> dia >> mes >> anio;
    cout << "Duracion en noches: ";
    cin >> duracion;
    cin.ignore();
    gestorDatos.sumarInvocacionesExternas(1); // cin.ignore

    Fecha entrada(dia, mes, anio);

    Alojamiento** todos = gestorDatos.getAlojamientos();
    int n = gestorDatos.getNumAlojamientos();
    Alojamiento** disponibles = nullptr;
    int numDisponibles = 0;

    cout << "\nAlojamientos disponibles en " << municipio << " para esas fechas:\n";

    for (int i = 0; i < n; i++) {
        string muniAloj = todos[i]->getMunicipio();
        for (int j = 0; j < muniAloj.length(); j++) {
            muniAloj[j] = tolower(muniAloj[j]);
            gestorDatos.sumarInvocacionesExternas(1); // tolower
        }

        if (muniAloj == municipio && todos[i]->estaDisponible(entrada, duracion, fechaCorte)) {
            todos[i]->mostrarInfo();

            Alojamiento** nuevo = new Alojamiento*[numDisponibles + 1];
            for (int k = 0; k < numDisponibles; k++) {
                nuevo[k] = disponibles[k];
            }
            nuevo[numDisponibles] = todos[i];
            delete[] disponibles;
            disponibles = nuevo;
            numDisponibles++;
        }
    }

    if (numDisponibles == 0) {
        cout << "No hay alojamientos disponibles.\n";
        return;
    }

    char aplicarFiltros;
    cout << "\n¿Desea aplicar filtros por precio o puntuacion? (s/n): ";
    cin >> aplicarFiltros;
    cin.ignore();
    gestorDatos.sumarInvocacionesExternas(1); // cin.ignore

    if (tolower(aplicarFiltros) == 's') {
        gestorDatos.sumarInvocacionesExternas(1); // tolower
        double precioMax = -1;
        double puntMin = -1;
        char aplicarPrecio, aplicarPunt;

        cout << "¿Filtrar por precio maximo? (s/n): ";
        cin >> aplicarPrecio;
        if (tolower(aplicarPrecio) == 's') {
            gestorDatos.sumarInvocacionesExternas(1);
            cout << "Precio maximo por noche: ";
            cin >> precioMax;
        }
        cin.ignore();
        gestorDatos.sumarInvocacionesExternas(1);

        cout << "¿Filtrar por puntuacion minima del anfitrion? (s/n): ";
        cin >> aplicarPunt;
        if (tolower(aplicarPunt) == 's') {
            gestorDatos.sumarInvocacionesExternas(1);
            cout << "Puntuacion minima: ";
            cin >> puntMin;
            gestorDatos.sumarInvocacionesExternas(1);
        }
        cin.ignore();
        gestorDatos.sumarInvocacionesExternas(1);

        Alojamiento** filtrados = nullptr;
        int numFiltrados = 0;

        for (int i = 0; i < numDisponibles; i++) {
            Anfitrion* a = gestorDatos.buscarAnfitrion(disponibles[i]->getDocumentoAnfitrion());

            if ((precioMax < 0 || disponibles[i]->getPrecioPorNoche() <= precioMax) &&
                (puntMin < 0 || (a && a->getPuntuacion() >= puntMin))) {

                Alojamiento** nuevo = new Alojamiento*[numFiltrados + 1];
                for (int j = 0; j < numFiltrados; j++) {
                    nuevo[j] = filtrados[j];
                }
                nuevo[numFiltrados] = disponibles[i];
                delete[] filtrados;
                filtrados = nuevo;
                numFiltrados++;
            }
        }

        delete[] disponibles;
        disponibles = filtrados;
        numDisponibles = numFiltrados;

        if (numFiltrados == 0) {
            cout << "No hay alojamientos que cumplan con los filtros.\n";
            return;
        }

        cout << "\nResultados filtrados:\n";
        for (int i = 0; i < numDisponibles; i++) {
            disponibles[i]->mostrarInfo();
        }
    }

    string codigo;
    cout << "\nIngrese el codigo del alojamiento que desea reservar: ";
    getline(cin, codigo);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    crearReservacionConCodigo(documento, codigo, entrada, duracion);
    delete[] disponibles;
}

//Buscar alojamiento por codigo
void Portal::buscarAlojamientoPorCodigo(const string& documento) {
    string codigo;
    int dia, mes, anio, duracion;

    cout << "\n=== Busqueda por Codigo ===\n";
    cout << "Ingrese el codigo del alojamiento: ";
    getline(cin, codigo);
    gestorDatos.sumarInvocacionesExternas(1); // getline

    cout << "Fecha de entrada (dd mm aaaa): ";
    cin >> dia >> mes >> anio;
    cout << "Duracion en noches: ";
    cin >> duracion;
    cin.ignore();
    gestorDatos.sumarInvocacionesExternas(1); // cin.ignore

    Fecha entrada(dia, mes, anio);
    crearReservacionConCodigo(documento, codigo, entrada, duracion);
}

//Actualizar la fecha de corte
void Portal::actualizarFechaCorte() {
    int d, m, a;

    cout << "\n=== Actualizar Fecha de Corte ===\n";
    cout << "Ingrese la fecha de hoy (dd mm aaaa): ";
    cin >> d >> m >> a;
    cin.ignore();
    gestorDatos.sumarInvocacionesExternas(1); // cin.ignore

    Fecha nueva(d, m, a);
    if (!nueva.esValida()) {
        cout << "Fecha invalida.\n";
        return;
    }

    Reservacion** historicas = gestorDatos.getReservacionesHistoricas();
    int numHistoricas = gestorDatos.getNumReservacionesHistoricas();
    Fecha mayorFechaSalida(1, 1, 1900);

    for (int i = 0; i < numHistoricas; i++) {
        Fecha salida = historicas[i]->getFechaSalida();
        if (salida > mayorFechaSalida) {
            mayorFechaSalida = salida;
        }
    }

    if (nueva < mayorFechaSalida) {
        cout << "No se puede usar una fecha anterior a la ultima reserva historica.\n";
        cout << "Ultima fecha de salida historica registrada: " << mayorFechaSalida.toString() << "\n";
        return;
    }

    fechaCorte = nueva;
    cout << "\nMoviendo reservas al historico segun la nueva fecha...\n";
    gestorArchivos.moverReservasHistorico(fechaCorte, &gestorDatos);
    gestorArchivos.guardarFechaCorte(fechaCorte);

    cout << "Fecha de corte actualizada a: " << fechaCorte.toString() << "\n";
}

//Menu de eficiencia y medicion de consumo en memoria
void Portal::mostrarResumenEficiencia() {
    int iter = gestorDatos.getIteraciones();
    int invocaciones = gestorDatos.getInvocacionesExternas();

    // Tamaño de los arreglos de punteros
    int memoriaHuespedes = sizeof(Huesped*) * gestorDatos.getNumHuespedes();
    int memoriaAnfitriones = sizeof(Anfitrion*) * gestorDatos.getNumAnfitriones();
    int memoriaAlojamientos = sizeof(Alojamiento*) * gestorDatos.getNumAlojamientos();
    int memoriaReservas = sizeof(Reservacion*) * gestorDatos.getNumReservaciones();
    int memoriaHistoricas = sizeof(Reservacion*) * gestorDatos.getNumReservacionesHistoricas();

    // Memoria para fechas: 1 fechaCorte + 2 por cada reservación
    int numReservas = gestorDatos.getNumReservaciones();
    int numHistoricas = gestorDatos.getNumReservacionesHistoricas();
    int totalFechas = 1 + 2 * (numReservas + numHistoricas);
    int memoriaFechas = totalFechas * sizeof(Fecha);  // Cada Fecha pesa 12 bytes

    // Total
    int totalMemoria = memoriaHuespedes + memoriaAnfitriones + memoriaAlojamientos +
                       memoriaReservas + memoriaHistoricas + memoriaFechas;

    std::cout << "\n--- RESUMEN DE EFICIENCIA ---\n";
    std::cout << iter << " iteraciones + " << invocaciones << " invocaciones de metodos externos\n";

    // Memoria
    std::cout << "Memoria usada (en bytes): " << totalMemoria << "\n";

    // Costo computacional explicado
    //O(n) es el comportamiento teórico esperado. Se espera que las búsquedas y recorridos tarden proporcional a la cantidad de elementos.
    std::cout << endl;
    std::cout << "Costo computacional teorico: O(n)\n";
    std::cout << "Explicacion: Se recorren arreglos dinamicos de tamaño n (reservas, alojamientos, etc.)\n";
}
