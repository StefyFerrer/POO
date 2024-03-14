#include "Enemy.h" // Incluye el archivo de encabezado Enemy.h
#include <iostream> // Incluye la biblioteca estándar de entrada y salida

using namespace std; // Usa el espacio de nombres estándar

// Función local para calcular el ataque con un valor aleatorio dentro de un rango
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80; // Calcula el límite inferior del rango de ataque
    return (rand() % (attack - lowerLimit)) + lowerLimit; // Devuelve un valor de ataque aleatorio dentro del rango
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) { // Constructor de la clase Enemy que inicializa los miembros con los valores proporcionados
    MaxHealth = health; // Inicializa la máxima salud del enemigo
}

void Enemy::doAttack(Character *target) { // Método para que el enemigo realice un ataque contra un objetivo
    int rolledAttack = getRolledAttack(getAttack()); // Calcula el ataque del enemigo con un valor aleatorio
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense(); // Calcula el daño real teniendo en cuenta la defensa del objetivo
    target->takeDamage(trueDamage); // Realiza el daño al objetivo
}

void Enemy::takeDamage(int damage) { // Método para que el enemigo reciba daño
    setHealth(getHealth() - damage); // Reduce la salud del enemigo según el daño recibido
    if(getHealth() <= 0) { // Si la salud del enemigo llega a cero o menos
        cout<<getName()<<"---The enemy died---"<<endl; // Imprime un mensaje indicando que el enemigo ha muerto
    }
    else { // Si el enemigo sigue vivo
        cout<<getName()<<" ---Has taken " << damage << " damage---" << endl; // Imprime un mensaje indicando el daño recibido
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) { // Método para obtener el objetivo del enemigo (jugador con menos salud)
    int targetIndex = 0; // Índice del objetivo inicializado en cero
    int lowestHealth = INT_MAX; // Salud más baja inicializada en el máximo valor posible
    for(int i=0; i < teamMembers.size(); i++) { // Itera sobre los miembros del equipo
        if(teamMembers[i]->getHealth() < lowestHealth) { // Si la salud del jugador actual es menor que la salud más baja encontrada hasta el momento
            lowestHealth = teamMembers[i]->getHealth(); // Actualiza la salud más baja
            targetIndex = i; // Actualiza el índice del objetivo
        }
    }
    return teamMembers[targetIndex]; // Devuelve el jugador con menos salud como objetivo
}

Action Enemy::takeAction(vector<Player *> player) { // Método para que el enemigo tome una acción durante el combate
    Action myAction; // Crea una instancia de la acción a realizar
    myAction.speed = getSpeed(); // Asigna la velocidad del enemigo a la acción
    myAction.subscriber = this; // Asigna al enemigo como el que realiza la acción
    Character* target = getTarget(player); // Obtiene el objetivo del enemigo
    myAction.target = target; // Asigna el objetivo a la acción
    if ((this->MaxHealth * 0.50 >= this->getHealth()) && rand() % 100 < 50) { // Si la salud del enemigo es igual o menor al 50% y se cumple una probabilidad del 50%
        myAction.action = [this, target]() { // Asigna una función de acción para huir
            this->fleed = true; // Establece que el enemigo ha huido
            };
    }
    else { // Si no se cumple la condición anterior
        myAction.target = target; // Asigna el objetivo a la acción
        myAction.action = [this, target]() { // Asigna una función de acción para atacar al objetivo
            doAttack(target); // Realiza un ataque contra el objetivo
        };
    }

    return myAction; // Devuelve la acción a realizar
}