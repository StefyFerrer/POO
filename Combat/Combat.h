#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#pragma once

#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "Action.h"
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Combat {
private:
    vector<Character*> participants; // Vector que almacena a todos los participantes del combate (jugadores y enemigos)
    vector<Player*> teamMembers; // Vector que almacena a los miembros del equipo (jugadores)
    vector<Enemy*> enemies; // Vector que almacena a los enemigos
    priority_queue<Action> actions; // Cola de prioridad que almacena las acciones de los participantes

    void prepareCombat(); // Método para preparar el combate, ordenando a los participantes por velocidad
    Character* getTarget(Character* target); // Método para obtener un objetivo para un participante
    void registerActions(); // Método para registrar las acciones de los participantes en la cola de acciones
    void executeActions(); // Método para ejecutar las acciones registradas en la cola de acciones

    void checkParticipantStatus(Character* participant); // Método para verificar el estado de un participante (si está vivo o muerto)
    void checkForFlee(Character* character); // Método para verificar si un participante ha huido del combate

public:
    Combat(vector<Character*> _participants); // Constructor que recibe un vector de participantes
    Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies); // Constructor que recibe un vector de jugadores y un vector de enemigos
    Combat(); // Constructor por defecto
    void addParticipant(Character* participant); // Método para añadir un participante al combate
    void doCombat(); // Método para realizar el combate
    string participantsToString(); // Método para obtener una representación en forma de cadena de texto de los participantes
};

#endif //RPG_COMBAT_H