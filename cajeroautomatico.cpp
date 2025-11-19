#include <iostream>
using namespace std;

int main() {
    // Saldos iniciales de las cuentas
    double cuenta1 = 5000.0;
    double cuenta2 = 3000.0;
    int opcion;
    double monto;

    do {
        cout << "\n===== CAJERO AUTOMATICO =====\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Deposito\n";
        cout << "3. Retiro\n";
        cout << "4. Transferencia entre cuentas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n--- CONSULTA DE SALDO ---\n";
                cout << "Saldo de Cuenta 1: $" << cuenta1 << endl;
                cout << "Saldo de Cuenta 2: $" << cuenta2 << endl;
                break;

            case 2:
                cout << "\n--- DEPOSITO ---\n";
                cout << "Ingrese monto a depositar: ";
                cin >> monto;
                if (monto > 0) {
                    cuenta1 += monto;
                    cout << "Deposito realizado. Nuevo saldo Cuenta 1: $" << cuenta1 << endl;
                } else {
                    cout << "Monto invalido.\n";
                }
                break;

            case 3:
                cout << "\n--- RETIRO ---\n";
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                if (monto > 0 && monto <= cuenta1) {
                    cuenta1 -= monto;
                    cout << "Retiro realizado. Nuevo saldo Cuenta 1: $" << cuenta1 << endl;
                } else {
                    cout << "Monto invalido o saldo insuficiente.\n";
                }
                break;

            case 4:
                cout << "\n--- TRANSFERENCIA ENTRE CUENTAS ---\n";
                cout << "Ingrese monto a transferir de Cuenta 1 a Cuenta 2: ";
                cin >> monto;
                if (monto > 0 && monto <= cuenta1) {
                    cuenta1 -= monto;
                    cuenta2 += monto;
                    cout << "Transferencia realizada.\n";
                    cout << "Saldo Cuenta 1: $" << cuenta1 << endl;
                    cout << "Saldo Cuenta 2: $" << cuenta2 << endl;
                } else {
                    cout << "Monto invalido o saldo insuficiente.\n";
                }
                break;

            case 5:
                cout << "\nGracias por usar el cajero. ¡Hasta luego!\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 5);

    return 0;
}
