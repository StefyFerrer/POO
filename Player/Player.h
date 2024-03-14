#ifndef RPG_PLAYER_H // Directiva de preprocesador para evitar la inclusión múltiple del archivo
#define RPG_PLAYER_H

#include "../Character/Character.h" // Incluye el archivo de encabezado Character.h para utilizar la clase base Character
#include "../Enemy/Enemy.h" // Incluye el archivo de encabezado Enemy.h para utilizar la clase Enemy
#include "../Combat/Action.h" // Incluye el archivo de encabezado Action.h para utilizar la estructura Action

struct Action; // Declaración adelantada de la estructura Action

class Enemy; // Declaración adelantada de la clase Enemy

class Player: public Character { // Definición de la clase Player que hereda de Character
protected: // Modificador de acceso protegido para los miembros de la clase Player
    int experience; // Variable para almacenar la experiencia del jugador
    int level; // Variable para almacenar el nivel del jugador
public: // Modificador de acceso público para los miembros de la clase Player
    Player(string _name, int _health, int _attack, int _defense, int _speed); // Declaración del constructor de la clase Player
    void doAttack(Character *target) override; // Declaración de la función doAttack para que el jugador realice un ataque
    void takeDamage(int damage) override; // Declaración de la función takeDamage para que el jugador reciba daño

    Character* getTarget(vector<Enemy*> enemies); // Declaración de la función getTarget para seleccionar un objetivo para atacar

    void flee(vector<Enemy*> enemies); // Declaración de la función flee para que el jugador huya del combate
    void emote(); // Declaración de la función emote para que el jugador realice una acción emotiva
    void levelUp(); // Declaración de la función levelUp para aumentar el nivel del jugador
    void gainExperience(int); // Declaración de la función gainExperience para que el jugador obtenga experiencia

    Action takeAction(vector<Enemy*> enemies); // Declaración de la función takeAction para que el jugador seleccione una acción durante el combate
};

#endif // RPG_PLAYER_H