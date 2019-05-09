/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Clase que representa un árbol binario de búsqueda balanceado (AVL).
 * 
 * Fecha: 09/05/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */

#if !defined(_ARBOL_HPP_)
#define _ARBOL_HPP_

#include <cmath>
#include <ostream>
#include "Lista.hpp"

/**
 * Estructura para representar los nodos de un árbol.
 */
template <typename T>
struct NodoArbol {
  T valor;
  NodoArbol<T> *izquierda = nullptr;
  NodoArbol<T> *derecha = nullptr;
};

template <typename T>
class Arbol
{
  private:
    NodoArbol<T> *raiz = nullptr;

  public:
    /**
     * Inserta un valor en el árbol de forma ordenada, delegando su funcionamiento al método privado.
     */
    void insertar(T valor)
    {
      // Bandera para indicar si ya se realizó un balanceo
      bool balanceado = false;
      raiz = insertar(raiz, valor, balanceado);
    }

    /**
     * Elimina el nodo del árbol que contiene el valor especificado, llamando al método recursivo
     */
    void eliminar(T valor) 
    {
      raiz = eliminar(raiz, valor);
    }

    /**
     * Busca un nodo con el valor especificado, delega su funcionamiento a la función recursiva 
     * del mismo nombre
     */
    NodoArbol<T> *buscarNodo(T valor)
    {
      return buscarNodo(raiz, valor);
    }

    /**
     * Recorre el árbol en pre-orden, delegando su funcionamiento al método recursivo
     * del mismo nombre pero con visibilidad privada.
     */
    Lista<NodoArbol<T> *> recorrerPreOrden()
    {
      Lista<NodoArbol<T> *> resultado;
      recorrerPreOrden(raiz, resultado);
      return resultado;
    }

    /**
     * Recorre el árbol en in-orden, delegando su funcionamiento al método recursivo
     * del mismo nombre pero con visibilidad privada.
     */
    Lista<NodoArbol<T> *> recorrerEnOrden() {
      Lista<NodoArbol<T> *> resultado;
      recorrerEnOrden(raiz, resultado);
      return resultado;
    }

    /**
     * Recorre el árbol en post-orden, delegando su funcionamiento al método recursivo
     * del mismo nombre pero con visibilidad privada.
     */
    Lista<NodoArbol<T> *> recorrerPostOrden() {
      Lista<NodoArbol<T> *> resultado;
      recorrerPostOrden(raiz, resultado);
      return resultado;
    }

    /**
     * Este método regresa verdadero si el árbol está vacío.
     */
    bool estaVacio() {
      return raiz == nullptr;
    }

    /**
     * Expone la raíz del árbol.
     */
    NodoArbol<T> *obtenerRaiz() {
      return raiz;
    }

    /**
     * Obtiene el padre de un nodo con el valor especificado
     */
    NodoArbol<T> *obtenerPadre(T valor)
    {
      if (raiz != nullptr)
      {
        if (raiz->valor == valor)
        {
          // La raíz no tiene padre
          return nullptr;
        }
        else
        {
          // Delegar a método recursivo
          return obtenerPadre(raiz, valor);
        }
      }
      else
      {
        return nullptr;
      }
    }

    /**
     * Obtiene el camino entre dos nodos, si estos existen
     */
    Lista<NodoArbol<T> *> obtenerCamino(T valor1, T valor2)
    {
      auto nodo1 = buscarNodo(valor1);
      auto nodo2 = buscarNodo(valor2);

      if (nodo1 != nullptr && nodo2 != nullptr && esAncestroDe(nodo1, nodo2))
      {
        return obtenerCaminoAncestroDescendiente(nodo1, nodo2);
      }
      else
      {
        return {};
      }
    }

    /**
     * Obtiene la altura desde un nodo
     */
    int obtenerAltura(T valor)
    {
      auto nodo = buscarNodo(valor);

      if (nodo != nullptr)
      {
        return obtenerAltura(nodo);
      }
      else
      {
        return -1;
      }
    }

    /**
     * Obtener la altura total
     */
    int obtenerAlturaTotal()
    {
      return obtenerAltura(raiz);
    }

    /**
     * Obtiene el peso total del árbol
     */
    int obtenerPeso() {
      auto recorrido = recorrerPostOrden();
      return recorrido.obtenerLongitud();
    }

    /**
     * Verifica si el arbol es lleno
     */
    bool esLleno() {
      return std::pow(2, obtenerAlturaTotal() + 1) - 1 == obtenerPeso();
    }

  private:
    /**
     * Inserta un elemento en el árbol dependiendo de su orden con respecto a los otros nodos,
     * regresando el nodo donde se inició la inserción. Este nodo puede cambiar si se realiza una
     * rotación.
     */
    NodoArbol<T> *insertar(NodoArbol<T> *nodo, T valor, bool &balanceado)
    {
      // Si es nulo regresar un nuevo nodo
      if (nodo == nullptr) 
      {
        return new NodoArbol<T>{valor};
      }
      // Posiblemente reasignar alguno de los nodos, si son nulos.
      else if (valor <= nodo->valor)
      {
        nodo->izquierda = insertar(nodo->izquierda, valor, balanceado);
      }
      else
      {
        nodo->derecha = insertar(nodo->derecha, valor, balanceado);
      }

      // Verificar que no se ha balanceado anteriormente
      if (!balanceado) 
      {
        int factorEquilibrio = obtenerFactorEquilibrio(nodo);

        // Verificar si el árbol está desequilibrado en la izquierda
        if (factorEquilibrio <= -2)
        {
          // Marcar que ya se realizó un rebalanceo, por lo que no se necesitan más
          balanceado = true;

          if (valor <= nodo->izquierda->valor)
          {
            // El nuevo nodo se agregó a la izquierda. (Caso II)
            return rotarDerecha(nodo);
          }
          else
          {
            // El nuevo nodo se agregó a la derecha. (Caso ID)
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
          }
        } 
        // Verificar si está desequilibrado a la derecha.
        else if (factorEquilibrio >= 2) 
        {
          // Marcar que ya se realizó un rebalanceo, por lo que no se necesitan más
          balanceado = true;

          if (valor <= nodo->derecha->valor)
          {
            // El nuevo nodo se agregó a la izquierda. (Caso DI)
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
          }
          else
          {
            // El nuevo nodo se agregó a la derecha. (Caso DD)
            return rotarIzquierda(nodo);
          }
        }
      }

      // En este caso, no se realizó un rebalanceo, por lo que el nodo sigue igual
      return nodo;
    }

    /** 
     * Realiza una rotación de un nodo en la dirección especificada. Regresa la nueva ráiz.
     */
    NodoArbol<T> *rotarDerecha(NodoArbol<T> *raiz) 
    {
      NodoArbol<T> *nuevaRaiz = raiz->izquierda;
      NodoArbol<T> *temp = nuevaRaiz->derecha;

      nuevaRaiz->derecha = raiz;
      raiz->izquierda = temp;

      return nuevaRaiz;
    }

    /** 
     * Realiza una rotación de un nodo en la dirección especificada. Regresa la nueva ráiz.
     */
    NodoArbol<T> *rotarIzquierda(NodoArbol<T> *raiz) 
    {
      NodoArbol<T> *nuevaRaiz = raiz->derecha;
      NodoArbol<T> *temp = nuevaRaiz->izquierda;

      nuevaRaiz->izquierda = raiz;
      raiz->derecha = temp;

      return nuevaRaiz;
    }

    /**
     * Obtiene el factor de equilibrio de un nodo.
     */
    int obtenerFactorEquilibrio(NodoArbol<T> *nodo) {
      if (nodo == nullptr) 
      {
        return 0;
      }
      else 
      {
        int alturaIzquierda = obtenerAltura(nodo->izquierda);
        int alturaDerecha = obtenerAltura(nodo->derecha);

        if (nodo->izquierda != nullptr)
          alturaIzquierda += 1;

        if (nodo->derecha != nullptr)
          alturaDerecha += 1;

        return alturaDerecha - alturaIzquierda;
      }
    }

    /**
     * Elimina el nodo con el valor especificado, regresando el nuevo nodo.
     */
    NodoArbol<T> *eliminar(NodoArbol<T> *nodo, T valor)
    {
      // No se encontró el valor
      if (nodo == nullptr)
      {
        return nullptr;
      }
      else if (valor < nodo->valor)
      {
        // Seguir la búsqueda a la izquierda
        nodo->izquierda = eliminar(nodo->izquierda, valor);
      }
      else if (valor > nodo->valor)
      {
        // Seguir la búsqueda a la derecha 
        nodo->derecha = eliminar(nodo->derecha, valor);
      }
      // Este es el nodo buscado
      else
      {
        // Es un nodo hoja
        if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
        {
          delete nodo;
          nodo = nullptr;
        }
        // Sólo tiene hijo izquierdo
        else if(nodo->derecha == nullptr)
        {
          // Su hijo izquierdo será la nueva raíz del subárbol
          NodoArbol<T> *temp = nodo->izquierda;
          delete nodo;
          nodo = temp;
        }
        // Sólo tiene hijo derecho
        else if (nodo->izquierda == nullptr)
        {
          // Su hijo derecho será la nueva raíz del subárbol
          NodoArbol<T> *temp = nodo->derecha;
          delete nodo;
          nodo = temp;
        }
        // Tiene ambos hijos
        else
        {
          // Buscar el máximo nodo de la izquierda
          NodoArbol<T> *maximo = nodo->izquierda;
          while (maximo->derecha != nullptr)
            maximo = maximo->derecha;

          // Copiar valor al nodo actual
          nodo->valor = maximo->valor;

          // Eliminar recursivamente el nodo máximo de la izquierda
          nodo->izquierda = eliminar(nodo->izquierda, maximo->valor);
        }        
      }

      // El árbol fue eliminado completamente
      if (nodo == nullptr)
        return nullptr;

      int factorEquilibrio = obtenerFactorEquilibrio(nodo);

      // Verificar si está desbalanceado a la izquierda
      if (factorEquilibrio <= -2) 
      {
        if (obtenerFactorEquilibrio(nodo->izquierda) <= 0)
        {
          // El subárbol de la izquierda es más grande (alto) o igual al subárbol de la derecha (Caso II)
          return rotarDerecha(nodo);
        }
        else
        {
          // El subárbol de la izquierda es menor que el de la derecha (Caso ID)
          nodo->izquierda = rotarIzquierda(nodo->izquierda);
          return rotarDerecha(nodo);
        }        
      }
      // Verificar si está desbalanceado a la derecha
      else if (factorEquilibrio >= 2)
      {
        if (obtenerFactorEquilibrio(nodo->derecha) >= 0)
        {
          // El subárbol de la derecha es más pequeño (alto) o igual al subárbol de la izquierda (Caso DD)
          return rotarIzquierda(nodo);
        }
        else
        {
          // El subárbol de la izquierda es menor que el de la derecha (Caso DI)
          nodo->derecha = rotarDerecha(nodo->derecha);
          return rotarIzquierda(nodo);
        }
      }

      // No había desequilibrio, regresar nodo sin modificaciones
      return nodo;
    }

    /**
     * Busca un nodo con el valor especificado, recursivamente.
     */
    NodoArbol<T> *buscarNodo(NodoArbol<T> *nodo, T valor)
    {
      // Caso base
      if (nodo == nullptr)
      {
        return nullptr;
      }
      else
      {
        // Buscar en el nodo especificado según sea el caso
        if (valor == nodo->valor)
        {
          return nodo;
        }
        else if (valor < nodo->valor)
        {
          return buscarNodo(nodo->izquierda, valor);
        }
        else
        {
          return buscarNodo(nodo->derecha, valor);
        }
      }
    }

    /**
     * Método interno para llenar la lista de resultados con el recorrido en pre-orden.
     */
    void recorrerPreOrden(NodoArbol<T> *nodo, Lista<NodoArbol<T> *> &resultado)
    {
      // Raíz - Izquierda - Derecha
      if (nodo != nullptr)
      {
        resultado.insertarFinal(nodo);
        recorrerPreOrden(nodo->izquierda, resultado);
        recorrerPreOrden(nodo->derecha, resultado);
      }
    }

    /**
     * Método interno para llenar la lista de resultados con el recorrido en in-orden.
     */
    void recorrerEnOrden(NodoArbol<T> *nodo, Lista<NodoArbol<T> *> &resultado)
    {
      // Izquierda - Raíz - Derecha
      if (nodo != nullptr)
      {
        recorrerEnOrden(nodo->izquierda, resultado);
        resultado.insertarFinal(nodo);
        recorrerEnOrden(nodo->derecha, resultado);
      }
    }

    /**
     * Método interno para llenar la lista de resultados con el recorrido en post-orden.
     */
    void recorrerPostOrden(NodoArbol<T> *nodo, Lista<NodoArbol<T> *> &resultado)
    {
      // Izquierda - Derecha - Raíz
      if (nodo != nullptr)
      {
        recorrerPostOrden(nodo->izquierda, resultado);
        recorrerPostOrden(nodo->derecha, resultado);
        resultado.insertarFinal(nodo);
      }
    }

    /**
     * Obtiene el padre de un nodo con el valor especificado
     */
    NodoArbol<T> *obtenerPadre(NodoArbol<T> *nodo, T valor)
    {
      if (nodo != nullptr)
      {
        if (nodo->izquierda != nullptr && nodo->izquierda->valor == valor)
        {
          return nodo;
        }
        else if (nodo->derecha != nullptr && nodo->derecha->valor == valor)
        {
          return nodo;
        }
        else
        {
          auto resultadoIzquierda = obtenerPadre(nodo->izquierda, valor);

          if (resultadoIzquierda != nullptr)
          {
            return resultadoIzquierda;
          }
          else
          {
            return obtenerPadre(nodo->derecha, valor);
          }
        }
      }
      else
      {
        return nullptr;
      }
    }

    /**
     * Método recursivo para obtener la altura de un árbol
     */
    int obtenerAltura(NodoArbol<T> *nodo) {
      if (nodo == nullptr) 
      {
        return 0;
      } else if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
        return 0;
      } else {
        return std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha)) + 1;
      }
    }

    /**
     * Devuelve verdadero si el nodo es un ancestro del nodo especificado
     */
    bool esAncestroDe(NodoArbol<T> *ancestro, NodoArbol<T> *nodo) 
    {
      return ancestro != nullptr && (
              ancestro == nodo || ancestro->izquierda == nodo || ancestro->derecha == nodo ||
              esAncestroDe(ancestro->izquierda, nodo) || esAncestroDe(ancestro->derecha, nodo)
            );
    }

    /**
     * Encuentra un camino entre ancestro y descendiente
     */
    Lista<NodoArbol<T> *> obtenerCaminoAncestroDescendiente(NodoArbol<T> *ancestro, NodoArbol<T> *descendiente)
    {
      if (ancestro == descendiente)
        return {};

      Lista<NodoArbol<T> *> resultado;
      resultado.insertarInicio(ancestro);
      obtenerCaminoAncestroDescendiente(ancestro, descendiente, resultado);
      return resultado.reversa();
    }

    /**
     * Encuentra un camino entre ancestro y descendiente
     */
    bool obtenerCaminoAncestroDescendiente(NodoArbol<T> *actual, NodoArbol<T> *descendiente,
                                           Lista<NodoArbol<T> *> &resultado)
    {
      if (actual == descendiente)
      {
        return true;
      }
      else if (actual == nullptr)
      {
        return false;
      }
      else
      {
        resultado.insertarInicio(actual->izquierda);

        if (obtenerCaminoAncestroDescendiente(actual->izquierda, descendiente, resultado))
        {
          return true;
        }
        else
        {
          resultado.eliminarInicio();
          resultado.insertarInicio(actual->derecha);

          if (obtenerCaminoAncestroDescendiente(actual->derecha, descendiente, resultado))
          {
            return true;
          }
          else
          {
            resultado.eliminarInicio();
            return false;
          }
        }
      }
    }
};
/**
 * El toString de la clase.
*/
template <typename T>
std::ostream &operator<<(std::ostream &flujo, const Arbol<T> &arbol)
{
  return flujo;
}

#endif // _ARBOL_HPP_