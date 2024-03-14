#include "Combat.h" // Incluye el archivo de encabezado de la clase Combat
#include <iostream> // Incluye la librería estándar de entrada y salida
#include <algorithm> // Incluye la librería estándar de algoritmos

using namespace std; // Permite el uso de los elementos de la librería estándar dentro del ámbito actual

// Función que compara la velocidad de dos personajes para ordenarlos en orden descendente
bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed(); // Compara la velocidad de los personajes y devuelve verdadero si la velocidad de 'a' es mayor que la de 'b'
}

// Constructor de la clase Combat que recibe una lista de participantes
Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants); // Asigna la lista de participantes al atributo 'participants'
    // Separa los participantes en dos grupos: equipo de jugadores y enemigos
    for (auto participant : participants) {
        if (participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant); // Agrega al equipo de jugadores
        } else {
            enemies.push_back((Enemy*)participant); // Agrega a los enemigos
        }
    }
}

// Constructor de la clase Combat que recibe listas separadas de jugadores y enemigos
Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers); // Asigna la lista de jugadores al atributo 'teamMembers'
    enemies = std::move(_enemies); // Asigna la lista de enemigos al atributo 'enemies'
}

// Constructor por defecto de la clase Combat
Combat::Combat() {
    participants = vector<Character*>(); // Inicializa el atributo 'participants' como un vector vacío
}

// Método para agregar un participante al combate
void Combat::addParticipant(Character *participant) {
    participants.push_back(participant); // Agrega un participante al vector 'participants'
    if (participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant); // Agrega un jugador al equipo de jugadores
    } else {
        enemies.push_back((Enemy*)participant); // Agrega un enemigo a la lista de enemigos
    }
}

// Método para preparar el combate, ordenando a los participantes por velocidad
void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed); // Ordena a los participantes por velocidad utilizando la función compareSpeed
}

// Método para ejecutar el combate
void Combat::doCombat() {
    prepareCombat(); // Prepara el combate ordenando a los participantes por velocidad

    // Bucle que representa una ronda de combate
    while (enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions(); // Registra las acciones de cada participante
        executeActions(); // Ejecuta las acciones registradas
    }

    // Imprime el resultado del combate
    if (enemies.size() == 0) {
        cout << "---You won the battle---" << endl; // El jugador ganó el combate
    } else {
        cout << "---You died---Game over..." << endl; // El jugador perdió el combate
    }
}

// Método para registrar las acciones de los participantes en el combate
void Combat::registerActions() {
    // Itera sobre los participantes para registrar sus acciones
    for (auto participant : participants) {
        Character* target = nullptr; // Inicializa el objetivo de la acción como nulo
        Action currentAction; // Crea una acción actual vacía
        // Si el participante es un jugador, registra su acción
        if (participant->getIsPlayer()) {
            currentAction = ((Player*)participant)->takeAction(enemies); // Obtiene la acción del jugador
        } else {
            currentAction = ((Enemy*)participant)->takeAction(teamMembers); // Obtiene la acción del enemigo
        }
        actions.push(currentAction); // Agrega la acción actual a la cola de acciones
    }
}

// Método para ejecutar las acciones registradas en el combate
void Combat::executeActions() {
    // Itera sobre las acciones en la cola y las ejecuta
    while (!actions.empty()) {
        Action currentAction = actions.top(); // Obtiene la acción actual de la parte superior de la cola
        currentAction.action(); // Ejecuta la acción actual
        checkForFlee(currentAction.subscriber); // Verifica si el participante ha huido
        if (currentAction.target != nullptr) { // Si hay un objetivo para la acción
            checkParticipantStatus(currentAction.subscriber); // Verifica el estado del participante que ejecutó la acción
            checkParticipantStatus(currentAction.target); // Verifica el estado del objetivo de la acción
            actions.pop(); // Elimina la acción ejecutada de la cola
        } else { // Si no hay objetivo para la acción
            while (!actions.empty()) { // Vacía la cola de acciones
                actions.pop();
            }
        }
    }
}

// Método para verificar el estado de un participante en el combate
void Combat::checkParticipantStatus(Character* participant) {
    if (participant->getHealth() <= 0) { // Si la salud del participante es igual o menor que cero
        if (participant->getIsPlayer()) { // Si el participante es un jugador
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end()); // Elimina al jugador del equipo de jugadores
        } else { // Si el participante es un enemigo
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end()); // Elimina al enemigo de la lista de enemigos
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end()); // Elimina al participante de la lista de participantes
    }
}

// Método para verificar si un participante ha huido del combate
void Combat::checkForFlee(Character *character) {
    bool fleed = character->hasFleed(); // Verifica si el personaje ha huido
    if (character->getHealth() != 0 && character->getHealth() > 0) { // Si el personaje está vivo
        if (fleed) { // Si el personaje ha huido
            if (character->getIsPlayer()) { // Si el personaje es un jugador
                cout << "---You have fled like a sewer rat---" << endl; // Imprime un mensaje de que el jugador ha huido
                teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end()); // Elimina al jugador del 
                } else { // Si el personaje es un enemigo
                cout << character->getName() << "---He has fled with his tail between his legs---" << endl; // Imprime un mensaje de que el enemigo ha huido
                enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end()); // Elimina al enemigo de la lista de enemigos
            }
            participants.erase(remove(participants.begin(), participants.end(), character), participants.end()); // Elimina al participante de la lista de participantes
        }
    }
}

// Método para convertir la información de los participantes en una cadena de texto
string Combat::participantsToString() {
    string result = ""; // Inicializa la cadena de texto resultante
    for (int i = 0; i < participants.size(); i++) { // Itera sobre los participantes
        result += participants[i]->toString() + "\n"; // Agrega la información de cada participante a la cadena resultante
    }
    return result; // Devuelve la cadena de texto resultante
}