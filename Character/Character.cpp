#include "Character.h" // Incluye el archivo de encabezado para la clase Character.

//El operador :: sirve para acceder a los miembros declarados en una clase (pueden ser funciones,variables, contantes, etc)
Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) { // Definición del constructor de la clase Character.
    // Inicializa los atributos de la clase con los valores proporcionados.
    name = _name;
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fleed = false; // Inicializa fleed como falso.
}

void Character::setName(string _name) { // Definición del método setName.
    name = _name; // Establece el nombre del personaje.
}

string Character::getName() { // Definición del método getName.
    return name; // Devuelve el nombre del personaje.
}

void Character::setHealth(int _health) { // Definición del método setHealth.
    health = _health; // Establece la salud del personaje.
}

int Character::getHealth() { // Definición del método getHealth.
    return health; // Devuelve la salud del personaje.
}

void Character::setAttack(int _attack) { // Definición del método setAttack.
    attack = _attack; // Establece el ataque del personaje.
}

int Character::getAttack() { // Definición del método getAttack.
    return attack; // Devuelve el ataque del personaje.
}

void Character::setDefense(int _defense) { // Definición del método setDefense.
    defense = _defense; // Establece la defensa del personaje.
}

int Character::getDefense() { // Definición del método getDefense.
    return defense; // Devuelve la defensa del personaje.
}

void Character::setSpeed(int _speed) { // Definición del método setSpeed.
    speed = _speed; // Establece la velocidad del personaje.
}

int Character::getSpeed() { // Definición del método getSpeed.
    return speed; // Devuelve la velocidad del personaje.
}

string Character::toString() { // Definición del método toString.
    // Devuelve una representación en cadena de texto de los atributos del personaje.
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() { // Definición del método getIsPlayer.
    return isPlayer; // Devuelve true si el personaje es un jugador, false si es un enemigo.
}

bool Character::hasFleed() { // Definición del método hasFleed.
    return fleed; // Devuelve true si el personaje ha huido del combate, false si no lo ha hecho.
}