#include "Player.h" // Incluye el archivo de encabezado Player.h que define la clase Player
#include <iostream> // Incluye la biblioteca de entrada y salida estándar
#include "../Utils.h" // Incluye el archivo de utilidades Utils.h

using namespace std; // Usa el espacio de nombres estándar

using namespace combat_utils; // Usa el espacio de nombres combat_utils definido en Utils.h

// Función que compara la velocidad de dos enemigos
bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed(); // Devuelve verdadero si la velocidad de a es mayor que la velocidad de b
}

// Constructor de la clase Player que inicializa los miembros de la clase
Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    experience = 0; // Inicializa la experiencia del jugador en cero
    level = 1; // Inicializa el nivel del jugador en uno
}

// Método para que el jugador realice un ataque
void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack()); // Obtiene el valor del ataque después de aplicar un rollo aleatorio
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense(); // Calcula el daño real
    target->takeDamage(trueDamage); // Hace que el objetivo reciba el daño calculado
}

// Método para que el jugador reciba daño
void Player::takeDamage(int damage) {
    setHealth(health - damage); // Reduce la salud del jugador por la cantidad de daño recibido
    cout << "---You have taken " << damage << " damage---" << endl; // Imprime un mensaje indicando la cantidad de daño recibido
    if (health <= 0) { // Si la salud del jugador es igual o menor a cero
        cout << "---You died---" << endl; // Imprime un mensaje indicando que el jugador ha muerto
    }
}

// Método para que el jugador huya de los enemigos
void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed); // Ordena los enemigos por velocidad
    Enemy *fastestEnemy = enemies[0]; // Obtiene el enemigo más rápido
    bool fleed = false; // Variable para almacenar si el jugador huyó o no
    if (this->getSpeed() > fastestEnemy->getSpeed()) { // Si la velocidad del jugador es mayor que la del enemigo más rápido
        fleed = true; // El jugador huye
    } else { // Si no
        srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios
        int chance = rand() % 100; // Genera un número aleatorio entre 0 y 99
        cout << "Chance: " << chance << endl; // Imprime la probabilidad de huida
        fleed = chance > 99; // El jugador huye si la probabilidad es mayor que 99
    }

    this->fleed = fleed; // Actualiza el estado de huida del jugador
}

// Método para que el jugador realice una acción emotiva
void Player::emote() {
    cout << "---He's doing Mewign---" << endl; // Imprime un mensaje indicando que el jugador está realizando una acción emotiva
}

// Método para que el jugador suba de nivel
void Player::levelUp() {
    level++; // Incrementa el nivel del jugador en uno
    setHealth(getHealth() + 10); // Aumenta la salud del jugador en 10 puntos
    setAttack(getAttack() + 5); // Aumenta el ataque del jugador en 5 puntos
    setDefense(getDefense() + 5); // Aumenta la defensa del jugador en 5 puntos
    setSpeed(getSpeed() + 5); // Aumenta la velocidad del jugador en 5 puntos
}

// Método para que el jugador gane experiencia
void Player::gainExperience(int exp) {
    experience += exp; // Incrementa la experiencia del jugador
    if (experience >= 100) { // Si la experiencia alcanza o supera 100 puntos
        levelUp(); // El jugador sube de nivel
        experience = 0; // La experiencia se reinicia a cero
    }
}

// Método para que el jugador seleccione un objetivo de entre los enemigos
Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose who to attack " << endl; // Imprime un mensaje solicitando al jugador que elija un objetivo
    int targetIndex = 0; // Índice del objetivo seleccionado
    for (int i = 0; i < enemies.size(); i++) { // Itera sobre los enemigos
        cout << i << ". " << enemies[i]->getName() << endl; // Imprime el nombre y el índice de cada enemigo
    }
    cin >> targetIndex; // Lee el índice del objetivo seleccionado por el jugador
    //TODO: Add input validation

    return enemies[targetIndex]; // Devuelve el objetivo seleccionado por el jugador
}

// Método para que el jugador tome una acción durante el combate
Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0; // Opción seleccionada por el jugador
    cout << "Choose an action" << endl; // Imprime un mensaje solicitando al jugador que elija una acción
    cout << "1. Attack" << endl; // Opción para atacar
    cout << "2. Escape rope" << endl; // Opción para huir
    cin >> option; // Lee la opción seleccionada por el jugador
    Character *target = nullptr; // Objetivo de la acción

    // Variable que almacena la acción a realizar por el jugador
    Action myAction;
    myAction.speed = this->getSpeed(); // Velocidad del jugador
    myAction.subscriber = this; // Jugador que realiza la acción

    switch (option) { // Evalúa la opción seleccionada por el jugador
        case 1: // Si la opción es atacar
            target = getTarget(enemies); // Obtiene el objetivo del ataque
            myAction.target = target; // Establece el objetivo de la acción
            // Define la acción como un ataque al objetivo seleccionado
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2: // Si la opción es huir
            // Define la acción como una huida de los enemigos
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            break;
        default: // Si la opción no es válida
            cout << "Invalid option (read numb)" << endl; // Imprime un mensaje indicando que la opción no es válida
            break;
    }

    return myAction; // Devuelve la acción seleccionada por el jugador
}