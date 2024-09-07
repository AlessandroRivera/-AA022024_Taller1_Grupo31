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

// Declaracin de constantes globales

const int kStockMinimo = 10; // Cantidad mínima de stock para reabastecimiento

// Prototipos de las funciones para manejar el inventario
void agregar_producto(Nodo *&head, const string &nombre, int cantidad);
void actualizar_producto(Nodo *head);
void eliminar_producto(Nodo *&head);
void mostrar_productos(Nodo *head);
void reabastecer_productos(Nodo *head);
void menos_stock(Nodo *head, int n);
void liberar_memoria(Nodo *&head);

int main(int argc, char *argv[])
{
  // Variables para almacenar la opcion del menu y los datos del producto
  int opcion, cantidad, numProductos;
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
    cout << "6. Productos con menor stock\n";
    cout << "7. Salir";
    cout << "\n\nSeleccione una opcion: ";
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
    case 6:;
      cout << "\nIngrese el numero de productos a mostrar: ";
      cin >> numProductos;
      menos_stock(inventario, numProductos); // Llamamos a la funcion para mostrar n productos con menor stock
      break;

    case 7:

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
  cout << "\n\nIngrese el numero del producto: ";
  cin >> opcion;

  // Verificamos si la opcion es valida
  if (opcion < 1 || opcion >= index)
  {

    cout << "\n\nOpcion no valida.\n\n";
    return;
  }

  // Si es el primer producto, actualizamos el puntero de la cabeza
  if (opcion == 1)
  {

    Nodo *temp = head;
    head = head->siguiente;
    delete temp;
    cout << "\n\nProducto eliminado.\n\n";
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

  cout << "\n\nProducto eliminado.\n\n";
}

// Funcion para mostrar los productos que necesitan reabastecimiento (menos de kStockMinimo unidades)
void reabastecer_productos(Nodo *head)
{

  cout << "\n\nProductos que necesitan reabastecimiento:\n";
  Nodo *actual = head;

  // Recorremos la lista y mostramos los productos con stock menor a kStockMinimo
  while (actual)
  {
    if (actual->cantidad < kStockMinimo)
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

  cout << "\nInventario actual:\n\n";
  Nodo *actual = head;

  // Recorremos la lista y mostramos todos los productos
  while (actual)
  {
    cout << "Producto: " << actual->nombre << ", Cantidad: " << actual->cantidad << "\n";
    actual = actual->siguiente;
  }
  cout << "\n";
}

// Funcion para mostrar los n productos con menor stock
void menos_stock(Nodo *head, int n)
{
  if (!head)
  {
    cout << "\n\nEl inventario está vacío.\n\n";
    return;
  }

  // Contar el numero total de productos en la lista enlazada
  int total_productos = 0;
  Nodo *temp = head;
  while (temp)
  {
    total_productos++;
    temp = temp->siguiente;
  }

  // Si n es mayor que el numero total de productos, ajustar n al total
  if (n > total_productos)
  {
    n = total_productos;
  }

  // Ordena los productos por cantidad de stock usando una el algoritmo de burbuja
  for (int i = 0; i < total_productos - 1; i++)
  {
    Nodo *actual = head;
    Nodo *siguiente = actual->siguiente;
    for (int j = 0; j < total_productos - i - 1; j++)
    {
      if (actual->cantidad > siguiente->cantidad)
      {
        // Intercambiaa los valores de nombre y cantidad entre actual y siguiente
        swap(actual->nombre, siguiente->nombre);
        swap(actual->cantidad, siguiente->cantidad);
      }
      actual = siguiente;
      siguiente = siguiente->siguiente;
    }
  }

  // Mostrar los primeros n productos con menor stock
  cout << "\n\nLos " << n << " productos con menor stock son:\n";
  temp = head;
  for (int i = 0; i < n && temp; i++)
  {
    cout << temp->nombre << " (Cantidad: " << temp->cantidad << ")\n";
    temp = temp->siguiente;
  }
  cout << "\n";
}

// Funcion para liberar la memoria de toda la lista enlazada
void liberar_memoria(Nodo *&head)
{
  while (head)
  {
    Nodo *temp = head;
    head = head->siguiente;
    delete temp;
  }
}
