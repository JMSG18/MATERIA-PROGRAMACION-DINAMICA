#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

// ---------------- FUNCIONES BÁSICAS ----------------

// Sobrecarga: suma de dos números
double suma(double a, double b) {
    return a + b;
}

// Sobrecarga: suma con tercer parámetro opcional
double suma(double a, double b, double c) {
    return a + b + c;
}

// Resta
double resta(double a, double b) {
    return a - b;
}

// Multiplicación
double multiplicacion(double a, double b) {
    return a * b;
}

// División con excepción
double division(double a, double b) {
    if (b == 0)
        throw runtime_error("Error: Division entre cero.");
    return a / b;
}

// ---------------- FUNCIONES AVANZADAS ----------------

// Factorial recursivo
long long factorial(int n) {
    if (n < 0)
        throw runtime_error("Error: Factorial de numero negativo.");
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

// Potencia con parámetro por omisión (exponente = 2)
double potencia(double base, int exponente = 2) {
    return pow(base, exponente);
}

// Raíz cuadrada con excepción
double raiz(double n) {
    if (n < 0)
        throw runtime_error("Error: No existe raiz cuadrada real de numero negativo.");
    return sqrt(n);
}

// ---------------- MENÚ PRINCIPAL ----------------

int main() {
    int opcion;
    double a, b;

    do {
        cout << "\n===== CALCULADORA =====\n";
        cout << "1. Suma\n";
        cout << "2. Resta\n";
        cout << "3. Multiplicacion\n";
        cout << "4. Division\n";
        cout << "5. Factorial\n";
        cout << "6. Potencia\n";
        cout << "7. Raiz Cuadrada\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        try {
            switch (opcion) {
                case 1:
                    cout << "Ingrese dos numeros: ";
                    cin >> a >> b;
                    cout << "Resultado: " << suma(a, b) << endl;
                    break;
                case 2:
                    cout << "Ingrese dos numeros: ";
                    cin >> a >> b;
                    cout << "Resultado: " << resta(a, b) << endl;
                    break;
                case 3:
                    cout << "Ingrese dos numeros: ";
                    cin >> a >> b;
                    cout << "Resultado: " << multiplicacion(a, b) << endl;
                    break;
                case 4:
                    cout << "Ingrese dos numeros: ";
                    cin >> a >> b;
                    cout << "Resultado: " << division(a, b) << endl;
                    break;
                case 5: {
                    int n;
                    cout << "Ingrese un numero entero: ";
                    cin >> n;
                    cout << "Factorial: " << factorial(n) << endl;
                    break;
                }
                case 6:
                    cout << "Ingrese base: ";
                    cin >> a;
                    cout << "Ingrese exponente (opcional, default=2): ";
                    cin >> b;
                    cout << "Resultado: " << potencia(a, b) << endl;
                    break;
                case 7:
                    cout << "Ingrese un numero: ";
                    cin >> a;
                    cout << "Raiz: " << raiz(a) << endl;
                    break;
                case 0:
                    cout << "Saliendo..." << endl;
                    break;
                default:
                    cout << "Opcion invalida\n";
            }
        }
        catch (exception &e) {
            cout << e.what() << endl;
        }

    } while (opcion != 0);

    return 0;
}
