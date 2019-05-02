/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * En este archivo se implementan funciones de conveniencia para interactuar con 
 * el usuario desde consola.
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
#if !defined(_UTILERIAS_HPP_)
#define _UTILERIAS_HPP_

#include <iostream>
#include <cstdlib>

/**
 * Limpia la terminal con el comando apropiado según la plataforma.
 */
void limpiarTerminal()
{
  // Limpiar terminal
#ifdef __unix__
  system("tput reset");
#elif defined(_WIN32)
  system("cls")
#endif
}

/**
 * Solicita presionar enter al usuario para continuar.
 */
void esperarEnter()
{
  std::cout << "Presione enter para continuar...";

  std::cin.get();
  std::cin.get();
}

#endif // _UTILERIAS_HPP_
