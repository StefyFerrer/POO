#ifndef RPG_ENEMY_H // Directiva del preprocesador para evitar la inclusión múltiple del archivo Enemy.h
#define RPG_ENEMY_H // Define el identificador RPG_ENEMY_H si aún no está definido

#include "../Character/Character.h" // Incluye el archivo de encabezado Character.h que define la clase base Character
#include "../Player/Player.h" // Incluye el archivo de encabezado Player.h que define la clase Player
#include "../Combat/Action.h" // Incluye el archivo de encabezado Action.h que define la estructura Action

struct Action; // Declaración adelantada de la estructura Action para que el compilador conozca su existencia

class Player; // Declaración adelantada de la clase Player para que el compilador conozca su existencia

class Enemy: public Character { // Declaración de la clase Enemy que hereda de la clase Character
public:
    int MaxHealth = 0; // Variable pública que representa la salud máxima del enemigo, inicializada en cero
    Enemy(string, int, int, int, int); // Declaración del constructor de la clase Enemy
    void doAttack(Character *target) override; // Declaración del método para que el enemigo realice un ataque
    void takeDamage(int damage) override; // Declaración del método para que el enemigo reciba daño
    Character* getTarget(vector<Player*> teamMembers); // Declaración del método para obtener el objetivo del enemigo
    Action takeAction(vector<Player*> player); // Declaración del método para que el enemigo tome una acción durante el combate
};

#endif // RPG_ENEMY_H // Fin de la directiva del preprocesador