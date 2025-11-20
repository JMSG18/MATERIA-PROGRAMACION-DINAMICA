#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

struct Producto {
    int id;
    string nombre;
    float precio;
    int cantidad;
};

// ------ PROTOTIPOS ------
void registrarProductos(Producto arr[], int tam);
void mostrarProductos(Producto arr[], int tam);
int buscarPorID(Producto arr[], int tam, int id);
int buscarPorNombre(Producto arr[], int tam, string nombre);
void ordenarPorPrecio(Producto arr[], int tam);
void ordenarPorCantidad(Producto arr[], int tam);
void modificarCantidad(Producto *p, int nuevaCantidad);

// ------ FUNCIONES ------
void registrarProductos(Producto arr[], int tam) {
    for (int i = 0; i < tam; i++) {
        cout << "\nProducto " << i + 1 << ":\n";
        cout << "ID: ";
        cin >> arr[i].id;
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, arr[i].nombre);
        cout << "Precio: ";
        cin >> arr[i].precio;
        cout << "Cantidad: ";
        cin >> arr[i].cantidad;
    }
}

void mostrarProductos(Producto arr[], int tam) {
    cout << "\n--- LISTA DE PRODUCTOS ---\n";
    for (int i = 0; i < tam; i++) {
        cout << "ID: " << arr[i].id
             << " | Nombre: " << arr[i].nombre
             << " | Precio: $" << arr[i].precio
             << " | Cantidad: " << arr[i].cantidad << endl;
    }
}

int buscarPorID(Producto arr[], int tam, int id) {
    for (int i = 0; i < tam; i++) {
        if (arr[i].id == id) {
            return i;
        }
    }
    throw runtime_error("ERROR: No se encontró el producto con ese ID.");
}

int buscarPorNombre(Producto arr[], int tam, string nombre) {
    for (int i = 0; i < tam; i++) {
        if (arr[i].nombre == nombre) {
            return i;
        }
    }
    throw runtime_error("ERROR: No se encontró el producto con ese nombre.");
}

void ordenarPorPrecio(Producto arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (arr[j].precio > arr[j + 1].precio) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void ordenarPorCantidad(Producto arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < tam; j++) {
            if (arr[j].cantidad < arr[minIndex].cantidad) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void modificarCantidad(Producto *p, int nuevaCantidad) {
    p->cantidad = nuevaCantidad;
}

// ------ MENÚ ------
int main() {
    const int TAM = 10;
    Producto inventario[TAM];

    registrarProductos(inventario, TAM);

    int opcion;
    do {
        cout << "\n===== MENU INVENTARIO =====\n";
        cout << "1. Mostrar productos\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por nombre\n";
        cout << "4. Ordenar por precio (burbuja)\n";
        cout << "5. Ordenar por cantidad (selección)\n";
        cout << "6. Modificar inventario usando punteros\n";
        cout << "0. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        try {
            if (opcion == 1) {
                mostrarProductos(inventario, TAM);
            }
            else if (opcion == 2) {
                int id;
                cout << "ID a buscar: ";
                cin >> id;
                int index = buscarPorID(inventario, TAM, id);
                cout << "Producto encontrado: " << inventario[index].nombre << endl;
            }
            else if (opcion == 3) {
                string nombre;
                cout << "Nombre a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                int index = buscarPorNombre(inventario, TAM, nombre);
                cout << "Producto encontrado: " << inventario[index].id << endl;
            }
            else if (opcion == 4) {
                ordenarPorPrecio(inventario, TAM);
                cout << "Ordenado por precio.\n";
            }
            else if (opcion == 5) {
                ordenarPorCantidad(inventario, TAM);
                cout << "Ordenado por cantidad.\n";
            }
            else if (opcion == 6) {
                int id, nuevaCant;
                cout << "ID del producto: ";
                cin >> id;
                int index = buscarPorID(inventario, TAM, id);
                cout << "Nueva cantidad: ";
                cin >> nuevaCant;
                modificarCantidad(&inventario[index], nuevaCant);
                cout << "Cantidad actualizada.\n";
            }
        }
        catch (exception &e) {
            cout << e.what() << endl;
        }

    } while (opcion != 0);

    return 0;
}
