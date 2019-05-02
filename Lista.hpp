/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * TDA Lista
 * 
 * En este archivo se implementan las operaciones básicas de un TDA de una lista dinámica 
 * basada en listas enlazadas.
 * 
 * Fecha: 28/02/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */

#if !defined(_LISTA_HPP_)
#define _LISTA_HPP_

// Las clases para representar las excepciones.
struct error_lista_vacia
{
};

struct error_sin_sucesor
{
};

struct error_sin_antecesor
{
};

struct error_no_encontrado
{
};

// Componentes básicos de la lista dinámica.
template <typename T>
struct Nodo
{
  T dato;
  Nodo *siguiente;
};

template <typename T>
// Estructura para soportar la iteración de C++
// https://docs.microsoft.com/es-es/cpp/cpp/range-based-for-statement-cpp?view=vs-2017
struct IteradorLista
{
  Nodo<T> *nodo;

  T &operator*()
  {
    return nodo->dato;
  }

  IteradorLista<T> &operator++()
  {
    nodo = nodo->siguiente;
    return *this;
  }

  bool operator!=(IteradorLista<T> &otro)
  {
    return nodo != otro.nodo;
  }
};

template <typename T>
class Lista
{
public:
  /**
   * Construcción por default
   */
  Lista() {}

  /**
   * Construcción por copia
   */
  Lista(const Lista<T> &lista)
  {
    for (auto &x : lista)
      insertarFinal(x);
  }

  /**
   * Construcción por copia de asignación.
   */
  Lista<T> &operator=(const Lista<T> &lista)
  {
    for (auto &x : lista)
      insertarFinal(x);

    return *this;
  }

  /**
   * Construcción por movimiento.
   */
  Lista(Lista<T> &&otra) : frente{otra.frente}, atras{otra.atras}
  {
    otra.frente = nullptr;
    otra.atras = nullptr;
  }

  /**
   * Asignación por movimiento.
   */
  Lista &operator=(Lista<T> &&otra)
  {
    frente = otra.frente;
    atras = otra.atras;

    otra.frente = nullptr;
    otra.atras = nullptr;

    return *this;
  }

  /**
   * Regresa false si no hay elementos en la lista.
   */
  bool estaVacia() const
  {
    return frente == nullptr;
  }

  /**
   * Obtiene la longitud de la lista.
   */
  int obtenerLongitud() const
  {
    int contador = 0;
    Nodo<T> *ap = frente;

    while (ap != nullptr)
    {
      ap = ap->siguiente;
      contador++;
    }

    return contador;
  }

  /**
   * Inserta al inicio el valor proporcionado. 
   * 
   * @param valor el valor a insertar.
   */
  void insertarInicio(T valor)
  {
    Nodo<T> *ap = new Nodo<T>;
    ap->dato = valor;
    ap->siguiente = frente;
    frente = ap;

    // Si la lista estaba vacía.
    if (atras == nullptr)
    {
      atras = ap;
    }
  }

  /**
   * Inserta al final el valor proporcionado.
   * 
   * @param valor el valor a insertar.
   */
  void insertarFinal(T valor)
  {
    Nodo<T> *ap = new Nodo<T>;
    ap->dato = valor;
    ap->siguiente = nullptr;

    // Si la lista tiene más de un elemento
    if (atras != nullptr)
    {
      atras->siguiente = ap;
    }

    // Actualizar apuntador
    atras = ap;

    // Si la lista estaba vacía, actualizar frente.
    if (frente == nullptr)
    {
      frente = ap;
    }
  }

  /**
   * Elimina el elemento al inicio de la lista.
   * 
   * Cuando la lista está vacia manda una excepción.
   */
  void eliminarInicio()
  {
    if (estaVacia())
    {
      throw error_lista_vacia();
    }
    else
    {
      Nodo<T> *ap = frente;
      frente = frente->siguiente;

      // Si la lista tenía un elemento, se actualiza el apuntador de atras.
      if (frente == nullptr)
      {
        atras = nullptr;
      }

      delete ap;
    }
  }

  /**
   * Elimina el elemento al final de la lista.
   * 
   * Cuando la lista está vacia manda una excepción.
   */
  void eliminarFinal()
  {
    if (estaVacia())
    {
      throw error_lista_vacia();
    }
    else
    {
      // Si la lista tiene sólo un elemento, delegamos a eliminarInicio.
      if (frente->siguiente == nullptr)
      {
        eliminarInicio();
      }
      else
      {
        Nodo<T> *ap = frente;

        // Llegar al penúltimo nodo.
        while (ap->siguiente->siguiente != nullptr)
        {
          ap = ap->siguiente;
        }

        // Actualizar el nuevo último.
        atras = ap;
        atras->siguiente = nullptr;

        // Apuntar al último.
        ap = ap->siguiente;
        delete ap;
      }
    }
  }

  //OBTIENE EL PRIMER ELEMENTO
  void obtenerPrimero()
  {
    if (estaVacia()) //revisa si la lista está vacía
    {
      throw error_lista_vacia();
    }
    else //devuelve lo que tiene frente
    {
      return frente->dato;
    }
  }

  /**
   * Obtiene el sucesor del primer elemento con el valor dado.
   * Lanza una excepcion error_sin_sucesor si el elemento es el último
   * o si no se encontró en la lista. 
   * Lanza una expecion error_lista_vacia, en caso de que no tener elementos.
   * 
   * @param valor el valor a buscar en la lista.
   */
  T sucesor(T valor)
  {
    if (estaVacia())
    {
      throw error_lista_vacia();
    }
    else
    {
      Nodo<T> *ap = frente;

      while (ap != nullptr)
      {
        if (ap->dato == valor)
        {
          ap = ap->siguiente;
          if (ap == nullptr)
          {
            throw error_sin_sucesor();
          }
          else
          {
            return ap->dato;
          }
        }

        ap = ap->siguiente;
      }
      throw error_no_encontrado();
    }
  }

  /**
   * Obtiene el antecesor del primer elemento con el valor dado.
   * Lanza una excepcion error_sin_antecesor si el elemento es el primero
   * o si no se encontró en la lista. 
   * Lanza una excepcion error_lista_vacia en caso de que no tener elementos.
   * 
   * @param valor el valor a buscar en la lista.
   */
  T predecesor(int valor)
  {
    if (estaVacia())
    {
      throw error_lista_vacia();
    }
    else
    {
      Nodo<T> *anterior = frente;
      Nodo<T> *ap = frente->siguiente;

      // Si la lista tiene un solo elemento y el valor buscado está al inicio.
      if (ap == nullptr && anterior->dato == valor)
      {
        throw error_sin_antecesor();
      }

      // Recorrer hasta que sea el final de la lista.
      while (ap != nullptr)
      {
        if (ap->dato == valor)
        {
          return anterior->dato;
        }

        anterior = ap;
        ap = ap->siguiente;
      }

      throw error_no_encontrado();
    }
  }

  /**
   * Operador de indizado en una lista ligada.
   * La complejidad de este algoritmo es O(n) (lineal).
   */
  T &operator[](int indice)
  {
    auto ap = frente;
    while (indice != 0 && ap->siguiente != nullptr)
    {
      ap = ap->siguiente;
      indice--;
    }

    return ap->dato;
  }

  /**
   * Operador de indizado en una lista ligada.
   * La complejidad de este algoritmo es O(n) (lineal).
   */
  T obtenerIndice(int indice)
  {
    auto ap = frente;
    while (indice != 0 && ap->siguiente != nullptr)
    {
      ap = ap->siguiente;
      indice--;
    }

    return ap->dato;
  }

  /**
   * Operador de indizado en una lista ligada.
   * La complejidad de este algoritmo es O(n) (lineal).
   * Versión para constantes.
   */
  const T &operator[](int indice) const
  {
    auto ap = frente;
    while (indice != 0 && ap->siguiente != nullptr)
    {
      ap = ap->siguiente;
      indice--;
    }

    return ap->dato;
  }

  /**
   * Operador de indizado en una lista ligada.
   * La complejidad de este algoritmo es O(n) (lineal).
   * Versión para constantes.
   */
  const T obtenerIndice(int indice) const
  {
    auto ap = frente;
    while (indice != 0 && ap->siguiente != nullptr)
    {
      ap = ap->siguiente;
      indice--;
    }

    return ap->dato;
  }

  /**
   * Obtener el iterador que apunta al primer elemento de la lista.
   */
  IteradorLista<T> begin() const
  {
    return IteradorLista<T>{frente};
  }

  /**
   * Obtener el iterador que apunta al ultimo elemento de la lista.
   */
  IteradorLista<T> end() const
  {
    return IteradorLista<T>{nullptr};
  }

  Nodo<T> *frente = nullptr;
  Nodo<T> *atras = nullptr;

  /**
   * Obtiene la reversa de una lista
   */
  Lista<T> reversa() const {
    Lista<T> resultado;

    for (auto valor : *this)
      resultado.insertarInicio(valor);

    return resultado;
  }

  /**
   * Concatena una lista con otra
   */
  Lista<T> concatenar(const Lista<T> &otra) const {
    Lista<T> resultado{*this};

    for (auto valor : otra)
      resultado.insertarFinal(valor);

    return resultado;
  }
};

#endif // _LISTA_HPP_