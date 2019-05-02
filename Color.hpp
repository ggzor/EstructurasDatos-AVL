/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Métodos para agregar color a la salida usando colores ASCII.
 * 
 * Fecha: 07/02/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */
#ifndef _COLORES_H_
#define _COLORES_H_

#include <ostream>

static std::ostream &colorNodo(std::ostream &flujo)
{
  flujo << "\033[34m";
  return flujo;
}

static std::ostream &colorError(std::ostream &flujo)
{
  flujo << "\033[31m";
  return flujo;
}

static std::ostream &enNegritas(std::ostream &flujo)
{
  flujo << "\033[1m";
  return flujo;
}

static std::ostream &terminarColor(std::ostream &flujo)
{
  flujo << "\033[0m";
  return flujo;
}

#endif