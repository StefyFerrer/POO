#ifndef RPG_ACTION_H
#define RPG_ACTION_H

#include <functional> // Incluye la biblioteca estándar de funciones
#include "../Character/Character.h" // Incluye el archivo de encabezado Character.h

class Character; // Declaración adelantada de la clase Character

struct Action {
    int speed = 0; // Velocidad de la acción (utilizada para determinar el orden de las acciones en el combate)
    Character* subscriber = nullptr; // Puntero al participante que realiza la acción
    Character* target = nullptr; // Puntero al objetivo de la acción
    std::function<void(void)> action = nullptr; // Función que representa la acción a realizar

    Action(std::function<void(void)> _action, int _speed, Character* _subscriber, Character* _target) { // Constructor que inicializa los miembros de la estructura
        action = _action; // Inicializa la acción
        speed = _speed; // Inicializa la velocidad
        subscriber = _subscriber; // Inicializa el participante que realiza la acción
        target = _target; // Inicializa el objetivo de la acción
    }
    Action(){}; // Constructor por defecto
    bool operator<(const Action& p) const // Sobrecarga del operador < para ordenar las acciones por velocidad
    {
        return this->speed < p.speed; // Devuelve verdadero si la velocidad de esta acción es menor que la velocidad de la acción p
    }
};

#endif // RPG_ACTION_H