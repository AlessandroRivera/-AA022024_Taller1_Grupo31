#include <iostream>
#include <string>

using namespace std;

// Declaracion de la estructura Nodo para almacenar cada producto en el inventario
struct Nodo
{
    string nombre;   // Nombre del producto
    int cantidad;    // Cantidad de productos en stock
    Nodo *siguiente; // Puntero al siguiente nodo de la lista enlazada
};

// Prototipos de las funciones para manejar el inventario
void agregar_producto(Nodo *&head, const string &nombre, int cantidad);
void actualizar_producto(Nodo *head);
void eliminar_producto(Nodo *&head);
void mostrar_productos(Nodo *head);
void reabastecer_productos(Nodo *head);
void liberar_memoria(Nodo *&head);

int main(int argc, char *argv[])
{
    // Variables para almacenar la opcion del menu y los datos del producto
    int opcion, cantidad;
    string nombre;

    // Puntero inicial del inventario (lista enlazada vacia al principio)
    Nodo *inventario = nullptr;

    // Bucle principal del menu
    while (true)
    {
        // Mostramos las opciones disponibles para gestionar el inventario
        cout << "\n========== Menu ==========\n\n";
        cout << "1. Agregar producto\n";
        cout << "2. Modificar producto\n";
        cout << "3. Productos a rebastecer\n";
        cout << "4. Mostrar inventario\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Salir\n";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Ignoramos el salto de linea restante en el buffer

        switch (opcion)
        {
        case 1:
            // Pedimos al usuario que ingrese los detalles del nuevo producto
            cout << "\nIngrese el nombre del producto: ";
            getline(cin, nombre);
            cout << "\nIngrese la cantidad en stock: ";
            cin >> cantidad;
            agregar_producto(inventario, nombre, cantidad); // Llamamos a la funcion para agregar el producto
            break;
        case 2:
            actualizar_producto(inventario); // Llamamos a la funcion para modificar un producto existente
            break;
        case 3:
            reabastecer_productos(inventario); // Mostramos los productos que necesitan reabastecimiento
            break;
        case 4:
            mostrar_productos(inventario); // Mostramos el inventario completo
            break;
        case 5:
            eliminar_producto(inventario); // Permitimos al usuario eliminar un producto
            break;
        case 6:
            liberar_memoria(inventario); // Liberamos la memoria de todos los productos antes de salir
            cout << "\nSaliendo del sistema...\n\n";
            return 0;
        default:
            // Si el usuario ingresa una opcion invalida, mostramos un mensaje
            cout << "\nOpcion no valida, intente de nuevo.\n\n";
        }
    }
    return 0;
}

// Funcion para agregar un producto al inventario
void agregar_producto(Nodo *&head, const string &nombre, int cantidad)
{
    // Creamos un nuevo nodo con los datos del producto
    Nodo *nuevo_nodo = new Nodo{nombre, cantidad, nullptr};

    // Si la lista esta vacia, el nuevo nodo sera el primero
    if (!head)
    {
        head = nuevo_nodo;
    }
    else
    {
        // Si ya hay productos, recorremos la lista hasta el final
        Nodo *actual = head;
        while (actual->siguiente)
        {
            actual = actual->siguiente;
        }
        // Insertamos el nuevo nodo al final de la lista
        actual->siguiente = nuevo_nodo;
    }
    // Informamos que el producto fue agregado
    cout << "\nProducto '" << nombre << "' agregado con " << cantidad << " unidades.\n\n";
}

// Funcion para modificar el nombre o la cantidad de un producto en el inventario
void actualizar_producto(Nodo *head)
{
    // Verificamos si la lista esta vacia
    if (!head)
    {
        cout << "\nEl inventario esta vacio.\n\n";
        return;
    }

    // Mostramos los productos con su numero para que el usuario elija cual modificar
    cout << "\nSeleccione el producto que desea modificar:\n";
    Nodo *actual = head;
    int index = 1;

    // Recorremos la lista y mostramos los productos con su cantidad
    while (actual)
    {
        cout << index << ". " << actual->nombre << " (Cantidad: " << actual->cantidad << ")\n";
        actual = actual->siguiente;
        index++;
    }

    // Le pedimos al usuario que ingrese el numero del producto a modificar
    int opcion;
    cout << "\nIngrese el numero del producto: ";
    cin >> opcion;

    // Verificamos si la opcion es valida
    if (opcion < 1 || opcion >= index)
    {
        cout << "\nOpcion no valida.\n\n";
        return;
    }

    // Recorremos la lista hasta encontrar el producto seleccionado
    actual = head;
    for (int i = 1; i < opcion; ++i)
    {
        actual = actual->siguiente;
    }

    // Preguntamos si desea modificar el nombre o la cantidad
    cout << "\nQue desea modificar?\n";
    cout << "1. Nombre del producto\n";
    cout << "2. Cantidad en stock\n";
    cout << "\nSeleccione una opcion: ";
    cin >> opcion;
    cin.ignore();

    // Segun la eleccion del usuario, actualizamos el nombre o la cantidad
    switch (opcion)
    {
    case 1:
        cout << "\nIngrese el nuevo nombre: ";
        getline(cin, actual->nombre);
        cout << "\nNombre actualizado.\n\n";
        break;
    case 2:
        cout << "\nIngrese la nueva cantidad: ";
        cin >> actual->cantidad;
        cout << "\nCantidad actualizada.\n\n";
        break;
    default:
        cout << "\nOpcion no valida.\n\n";
    }
}

// Funcion para eliminar un producto del inventario
void eliminar_producto(Nodo *&head)
{
    // Verificamos si la lista esta vacia
    if (!head)
    {
        cout << "\n\nEl inventario esta vacio.\n\n";
        return;
    }

    // Mostramos los productos con su numero para que el usuario elija cual eliminar
    cout << "\n\nSeleccione el producto que desea eliminar:\n\n";
    Nodo *actual = head;
    int index = 1;

    // Recorremos la lista y mostramos los productos
    while (actual)
    {
        cout << index << ". " << actual->nombre << " (Cantidad: " << actual->cantidad << ")\n";
        actual = actual->siguiente;
        index++;
    }

    // Le pedimos al usuario que ingrese el numero del producto a eliminar
    int opcion;
    cout << "\nIngrese el numero del producto: ";
    cin >> opcion;

    // Verificamos si la opcion es valida
    if (opcion < 1 || opcion >= index)
    {
        cout << "\nOpcion no valida.\n\n";
        return;
    }

    // Si es el primer producto, actualizamos el puntero de la cabeza
    if (opcion == 1)
    {
        Nodo *temp = head;
        head = head->siguiente;
        delete temp;
        cout << "\nProducto eliminado.\n\n";
        return;
    }

    // Recorremos la lista hasta el producto anterior al seleccionado
    actual = head;
    for (int i = 1; i < opcion - 1; ++i)
    {
        actual = actual->siguiente;
    }

    // Eliminamos el nodo seleccionado
    Nodo *temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;

    cout << "\nProducto eliminado.\n\n";
}

// Funcion para mostrar los productos que necesitan reabastecimiento (menos de 10 unidades)
void reabastecer_productos(Nodo *head)
{
    cout << "\nProductos que necesitan reabastecimiento:\n";
    Nodo *actual = head;

    // Recorremos la lista y mostramos los productos con stock menor a 10
    while (actual)
    {
        if (actual->cantidad < 10)
        {
            cout << actual->nombre << ": " << actual->cantidad << " unidades\n";
        }
        actual = actual->siguiente;
    }
    cout << "\n";
}

// Funcion para mostrar todo el inventario
void mostrar_productos(Nodo *head)
{
    cout << "\nInventario actual:\n";
    Nodo *actual = head;

    // Recorremos la lista y mostramos cada producto con su cantidad
    while (actual)
    {
        cout << actual->nombre << " (Cantidad: " << actual->cantidad << ")\n";
        actual = actual->siguiente;
    }
    cout << "\n";
}

// Funcion para liberar la memoria de todos los nodos al final del programa
void liberar_memoria(Nodo *&head)
{
    while (head)
    {
        Nodo *temp = head;      // Guardamos el nodo actual
        head = head->siguiente; // Movemos la cabeza al siguiente nodo
        delete temp;            // Liberamos la memoria del nodo anterior
    }
}
