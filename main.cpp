#include <iostream> // Incluye la biblioteca estándar de entrada y salida.
#include "Enemy/Enemy.h" // Incluye el archivo de encabezado para la clase Enemy.
#include "Player/Player.h" // Incluye el archivo de encabezado para la clase Player.
#include "Combat/Combat.h" // Incluye el archivo de encabezado para la clase Combat.
#include <queue> 

using namespace std; // Usa el espacio de nombres estándar de C++.

int main() { // La función principal del programa.
    // Crea un objeto de la clase Player con valores específicos.
    Player *player = new Player("--Player without light--", 100, 125, 100, 150); // Nombre, vida, ataque, defensa, velocidad.
    // Crea un objeto de la clase Enemy con valores específicos.
    Enemy *enemy = new Enemy("--Malenia--", 140, 150, 100, 130);
    // Crea otro objeto de la clase Enemy con valores específicos.
    Enemy *enemy2 = new Enemy("--Radahn--", 160, 70, 100, 80);

    // Crea un vector de punteros a Character y agrega los objetos player, enemy y enemy2.
    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    // Crea un objeto de la clase Combat, pasando el vector de participantes como argumento.
    Combat* combat = new Combat(participants);
    // Inicia el combate llamando al método doCombat().
    combat->doCombat();

    // Libera la memoria de los objetos creados con new.
    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0; // Retorna 0, indicando que el programa terminó correctamente.
}