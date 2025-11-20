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

// Prototipos
void registrarProductos(Producto arr[], int n);
void mostrarProductos(Producto arr[], int n);
int buscarPorID(Producto arr[], int n, int id);
int buscarPorNombre(Producto arr[], int n, string nombre);
void ordenarPorPrecio(Producto arr[], int n);
void ordenarPorCantidad(Producto arr[], int n);
void modificarCantidad(Producto *p, int nuevaCant);

int main() {
    const int N = 10;
    Producto inventario[N];

    registrarProductos(inventario, N);

    int opcion;

    do {
        cout << "\n===== MENU DE INVENTARIO =====\n";
        cout << "1. Mostrar productos\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por nombre\n";
        cout << "4. Ordenar por precio (Burbuja)\n";
        cout << "5. Ordenar por cantidad (Seleccion)\n";
        cout << "6. Modificar cantidad (punteros)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        try {
            if (opcion == 1) {
                mostrarProductos(inventario, N);
            }
            else if (opcion == 2) {
                int id;
                cout << "Ingrese ID: ";
                cin >> id;

                int index = buscarPorID(inventario, N, id);
                cout << "Producto encontrado: " << inventario[index].nombre << endl;
            }
            else if (opcion == 3) {
                string nombre;
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);

                int index = buscarPorNombre(inventario, N, nombre);
                cout << "Producto encontrado: ID " << inventario[index].id << endl;
            }
            else if (opcion == 4) {
                ordenarPorPrecio(inventario, N);
                cout << "Productos ordenados por precio.\n";
            }
            else if (opcion == 5) {
                ordenarPorCantidad(inventario, N);
                cout << "Productos ordenados por cantidad.\n";
            }
            else if (opcion == 6) {
                int id, nuevaCant;
                cout << "ID del producto: ";
                cin >> id;

                int index = buscarPorID(inventario, N, id);
                cout << "Nueva cantidad: ";
                cin >> nuevaCant;

                modificarCantidad(&inventario[index], nuevaCant);
                cout << "Cantidad modificada con éxito.\n";
            }
        }
        catch (exception &e) {
            cout << "\n[EXCEPCION] " << e.what() << endl;
        }

    } while (opcion != 0);

    return 0;
}

// Registrar los productos
void registrarProductos(Producto arr[], int n) {
    cout << "\n=== REGISTRO DE 10 PRODUCTOS ===\n";
    for (int i = 0; i < n; i++) {
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

// Mostrar productos
void mostrarProductos(Producto arr[], int n) {
    cout << "\n=== LISTA DE PRODUCTOS ===\n";
    for (int i = 0; i < n; i++) {
        cout << "ID: " << arr[i].id
             << " | Nombre: " << arr[i].nombre
             << " | Precio: $" << arr[i].precio
             << " | Cantidad: " << arr[i].cantidad << endl;
    }
}

// Buscar por ID
int buscarPorID(Producto arr[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id)
            return i;
    }
    throw runtime_error("No se encontro el producto con ese ID.");
}

// Buscar por nombre
int buscarPorNombre(Producto arr[], int n, string nombre) {
    for (int i = 0; i < n; i++) {
        if (arr[i].nombre == nombre)
            return i;
    }
    throw runtime_error("No se encontro el producto con ese nombre.");
}

// Ordenamiento burbuja por precio
void ordenarPorPrecio(Producto arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].precio > arr[j + 1].precio)
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Ordenamiento selección por cantidad
void ordenarPorCantidad(Producto arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].cantidad < arr[minIndex].cantidad)
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Modificar cantidad usando punteros
void modificarCantidad(Producto *p, int nuevaCant) {
    p->cantidad = nuevaCant;
}
