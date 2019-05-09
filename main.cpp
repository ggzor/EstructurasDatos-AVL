/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Implementación de la interfaz para mostrar recorridos
 *  en un arbol binario.
 * 
 * Fecha: 24/04/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */
#include "Arbol.hpp"
#include "Color.hpp"
#include "Utilerias.hpp"

#include <iostream>

int main()
{
  Arbol<int> arbol;

  int op;
  do
  {
    limpiarTerminal();
    std::cout << arbol << std::endl;
    std::cout << "Menú:\n" 
              << "  1. Recorrido en PreOrden. \n "
              << "  2. Recorrido En Orden. \n "
              << "  3. Recorrido en Post Orden.  \n"
              << "  4. Insertar un elemento. \n"
              << "  5. Eliminar un valor dado.\n "
              << "  6. Salir. \n"
              << std::endl;
    std::cout << "Opción: ";
    std::cin >> op;
    std::cout << std::endl;

    switch (op)
    {
    case 1:
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        // Realizar recorrido en PreOrden y mostrar los resultados.
        auto recorrido = arbol.recorrerPreOrden();

        std::cout << "El recorrido en PreOrden es: "
                  << colorNodo << enNegritas;
        for (auto nodo : recorrido)
        {
          std::cout << nodo->valor << ' ';
        }

        std::cout << terminarColor << std::endl;
      }

      esperarEnter();
      break;

    case 2:
    {
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        // Realizar recorrido en EnOrden y mostrar los resultados.
        auto recorrido = arbol.recorrerEnOrden();

        std::cout << "El recorrido en EnOrden es: "
                  << colorNodo << enNegritas;
        for (auto nodo : recorrido)
        {
          std::cout << nodo->valor << ' ';
        }

        std::cout << terminarColor << std::endl;
      }

      esperarEnter();
      break;
    }
    case 3:
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        // Realizar recorrido en PostOrden y mostrar los resultados.
        auto recorrido = arbol.recorrerPostOrden();
        std::cout << "El recorrido en PostOrden es: "
                  << colorNodo << enNegritas;
        for (auto nodo : recorrido)
        {
          std::cout << nodo->valor << ' ';
        }

        std::cout << terminarColor << std::endl;
      }
      esperarEnter();
      break;

    case 4:
      // Insertar valores al arbol
      int valor;
      std::cout << "Valor a insertar: " << colorNodo;
      std::cin >> valor;

      arbol.insertar(valor);

      esperarEnter();
      break;
    case 5:
      // Elimina un valor dado  al árbol 
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor;
        std::cout << "Valor a eliminar: " << colorNodo;
        std::cin >> valor;

        if (arbol.buscarNodo(valor) == nullptr) 
        {
          std::cout << colorError << "El valor especificado no está en el árbol." << terminarColor << std::endl;
        }
        else
        {
          arbol.eliminar(valor);
        }

        esperarEnter();
      }
      esperarEnter();
      break;
    case 6:
      // Para evitar el siguiente mensaje
      break;

    default:
      std::cout << colorError << "Opcion inválida." << terminarColor << std::endl;
      esperarEnter();
      break;
    }
  } while(op != 6);

  return 0;
}