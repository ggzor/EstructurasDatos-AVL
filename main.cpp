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

// Lectura del grafo
Arbol<int> leerArbol()
{
  Arbol<int> arbol;

  int cantidadNodos;
  std::cout << "¿Cuántos nodos va a tener el árbol? " << enNegritas << colorNodo;
  std::cin >> cantidadNodos;
  std::cout << terminarColor;

  int valor;
  std::cout << "Valores del árbol: " << colorNodo << enNegritas;
  for (int i = 0; i < cantidadNodos; i++)
  {
    std::cin >> valor;
    arbol.insertar(valor);
  }
  std::cout << terminarColor;

  return arbol;
}

int main()
{
  Arbol<int> arbol = leerArbol();

  int op;
  do
  {
    limpiarTerminal();
    std::cout << arbol << std::endl;
    std::cout << "Menú:\n"
              << "  1. Mostrar PreOrden.\n"
              << "  2. Mostrar InOrden.\n"
              << "  3. Mostrar PostOrden.\n"
              << "  4. Mostrar hijos de un nodo.\n"
              << "  5. Lista nodos hoja.\n"
              << "  6. Hallar hermano de un nodo.\n"
              << "  7. Hallar el padre de un nodo.\n"
              << "  8. Lista descendientes de un nodo.\n"
              << "  9. Camino de un nodo N a un nodo M.\n"
              << " 10. Altura de un nodo.\n"
              << " 11. Peso del árbol.\n"
              << " 12. ¿Es un árbol lleno?\n"
              << " 13. Salir.\n"
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
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        // Recibir el valor del nodo a buscar.
        int valor;
        std::cout << "Valor del nodo: " << colorNodo;
        std::cin >> valor;
        std::cout << terminarColor;

        auto resultado = arbol.buscarNodo(valor);

        if (resultado == nullptr)
        {
          std::cout << colorError << "No se encontró el valor en el árbol." << terminarColor << std::endl;
        }
        else
        {
          std::cout << "Los hijos del nodo son: " << std::endl;

          // Imprime el hijo de la izquierda si no es nulo, o una cadena que representa el valor nulo
          std::cout << "  Izquierda: " << terminarColor;
          if (resultado->izquierda == nullptr)
          {
            std::cout << colorError << enNegritas << "nulo";
          }
          else
          {
            std::cout << colorNodo << enNegritas << resultado->izquierda->valor;
          }
          std::cout << terminarColor << std::endl;

          // Imprime el hijo de la derecha si no es nulo, o una cadena que representa el valor nulo
          std::cout << "  Derecha:   " << terminarColor;
          if (resultado->derecha == nullptr)
          {
            std::cout << colorError << enNegritas << "nulo";
          }
          else
          {
            std::cout << colorNodo << enNegritas << resultado->derecha->valor;
          }
          std::cout << terminarColor << std::endl;
        }
      }

      esperarEnter();
      break;
    case 5:
      //Imprime los nodos hoja del arbol
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        // Obtener nodos hoja de un árbol
        auto hojas = arbol.obtenerHojas();
        std::cout << "Las hojas del árbol son: "
                  << colorNodo << enNegritas;
        for (auto nodo : hojas)
        {
          std::cout << nodo->valor << ' ';
        }

        std::cout << terminarColor << std::endl;
      }
      esperarEnter();
      break;
    case 6:
      //Halla el hermano de un nodo N
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor;
        std::cout << "Valor: " << colorNodo;
        std::cin >> valor;
        std::cout << terminarColor;

        auto nodo = arbol.buscarNodo(valor);
        if (nodo == nullptr)
        {
          std::cout << colorError << "El valor proporcionado no está en el arbol." << std::endl;
        }
        else
        {
          if (nodo == arbol.obtenerRaiz())
          {
            std::cout << "El nodo raíz no tiene hermanos." << std::endl;
          }
          else
          {
            auto hermano = arbol.obtenerHermano(valor);

            if (hermano == nullptr)
            {
              std::cout << "El hermano del nodo es nulo." << std::endl;
            }
            else
            {
              std::cout << "El valor del hermano es: " << hermano->valor << std::endl;
            }
          }
        }
      }
      esperarEnter();
      break;

    case 7:
      //Halla el padre de un nodo N
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor;
        std::cout << "Valor: " << colorNodo;
        std::cin >> valor;
        std::cout << terminarColor;

        auto nodo = arbol.buscarNodo(valor);
        if (nodo == nullptr)
        {
          std::cout << colorError << "El valor proporcionado no está en el arbol." << std::endl;
        }
        else
        {
          if (nodo == arbol.obtenerRaiz())
          {
            std::cout << "El nodo raíz no tiene padre." << std::endl;
          }
          else
          {
            auto padre = arbol.obtenerPadre(valor);

            if (padre == nullptr)
            {
              std::cout << "El padre del nodo es nulo." << std::endl;
            }
            else
            {
              std::cout << "El valor del padre es: " << padre->valor << std::endl;
            }
          }
        }
      }
      esperarEnter();
      break;

    case 8:
      //Lista descendientes de un nodo
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor;
        std::cout << "Valor: " << colorNodo;
        std::cin >> valor;
        std::cout << terminarColor;

        if (arbol.buscarNodo(valor) == nullptr)
        {
          std::cout << colorError << "El nodo no existe." << terminarColor << std::endl;
        }
        else
        {
          // Encontrar los descendientes del nodo
          auto recorrido = arbol.obtenerDescendientes(valor);

          if (recorrido.estaVacia())
          {
            std::cout << "El nodo no tiene descendientes." << std::endl;
          }
          else
          {
            std::cout << "Los descendientes del nodo son: "
                      << colorNodo << enNegritas;
            for (auto nodo : recorrido)
            {
              std::cout << nodo->valor << ' ';
            }

            std::cout << terminarColor << std::endl;
          }
        }
      }
      esperarEnter();
      break;

    case 9:
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor1, valor2;
        std::cout << "Valor 1: " << colorNodo;
        std::cin >> valor1;
        std::cout << terminarColor;

        if (arbol.buscarNodo(valor1) == nullptr) 
        {
          std::cout << colorError << "El nodo no existe." << terminarColor << std::endl;
        }
        else
        {
          std::cout << "Valor 2: " << colorNodo;
          std::cin >> valor2;
          std::cout << terminarColor;

          if (arbol.buscarNodo(valor2) == nullptr)
          {
            std::cout << colorError << "El nodo no existe." << terminarColor << std::endl;
          }
          else if (valor1 == valor2)
          {
            std::cout << "Se introdujo el mismo nodo de origen que de destino." << std::endl;
          }
          else
          {
            // Encontrar los descendientes del nodo
            auto recorrido = arbol.obtenerCamino(valor1, valor2);

            if (recorrido.estaVacia())
            {
              std::cout << "No existe camino entre los valores especificados. (Lo cual es raro :( ))" << std::endl;
            }
            else
            {
              std::cout << "El camino entre los nodos es: ";
              for (auto nodo : recorrido)
              {
                std::cout << colorNodo << enNegritas << nodo->valor << terminarColor;
                if (nodo->valor != valor2)
                  std::cout << enNegritas << " -> ";
              }

              std::cout << terminarColor << std::endl;
            }
          }
        }
      }
      esperarEnter();
      break;

    case 10:
      //Calcula la altura del arbol
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int valor;
        std::cout << "Valor: " << colorNodo;
        std::cin >> valor;
        std::cout << terminarColor;

        if (arbol.buscarNodo(valor) == nullptr)
        {
          std::cout << colorError << "El nodo no existe." << std::endl;
        }
        else
        {
          int altura = arbol.obtenerAltura(valor);
          std::cout << "La altura del nodo es: " << colorNodo << altura << terminarColor << std::endl;
        }
      }
      esperarEnter();
      break;

    case 11:
      //Calcula el peso del arbol
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        int peso = arbol.obtenerPeso();
        std::cout << "El peso del árbol es: " << enNegritas << colorNodo << peso << terminarColor << std::endl;
      }
      esperarEnter();
      break;

    case 12:
      //Determina si el arbol es lleno
      if (arbol.estaVacio())
      {
        std::cout << colorError << "El árbol está vacío." << terminarColor << std::endl;
      }
      else
      {
        if (arbol.esLleno() == true)
        {
          std::cout << enNegritas << colorNodo << "El arbol es lleno." << terminarColor << std::endl;
        }
        else
        {
          std::cout << enNegritas << colorError << "El arbol no es lleno." << terminarColor << std::endl;
        }
      }
      esperarEnter();
      break;
    case 13:
      // Para evitar el siguiente mensaje
      break;

    default:
      std::cout << colorError << "Opcion inválida." << terminarColor << std::endl;
      esperarEnter();
      break;
    }
  } while (op != 13);

  return 0;
}