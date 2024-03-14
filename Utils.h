#ifndef RPG_UTILS_H // Directiva de preprocesador para evitar la inclusión múltiple del archivo
#define RPG_UTILS_H

#include <cstdlib> // Incluye la biblioteca estándar de C++ para utilizar la función srand y rand

namespace combat_utils { // Espacio de nombres para las utilidades relacionadas con el combate

    int getRolledAttack(int attack) { // Definición de la función getRolledAttack que recibe un valor de ataque y devuelve un valor de ataque aleatorio entre 80% y 100% del valor original
        srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios con el tiempo actual
        int lowerLimit = attack * .80; // Calcula el límite inferior del rango de ataque aleatorio
        return (rand() % (attack - lowerLimit)) + lowerLimit; // Devuelve un valor de ataque aleatorio dentro del rango establecido
    }

}

#endif // Fin de la directiva de preprocesador