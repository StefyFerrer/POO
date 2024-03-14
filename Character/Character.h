#ifndef RPG_CHARACTER_H // Directiva del preprocesador que verifica si el archivo de encabezado aún no ha sido incluido
#define RPG_CHARACTER_H // Directiva del preprocesador que define un identificador único para evitar la inclusión múltiple

#include<string> // Incluye la librería estándar de cadenas de C++

using namespace std; // Permite el uso de los elementos de la librería estándar dentro del ámbito actual

// Declaración de la clase Character
class Character {
protected:
    // Atributos protegidos de la clase Character
    string name;
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool fleed;

public:
    // Declaración del constructor de la clase Character
    Character(string, int, int, int, int, bool);

    // Declaración de los métodos de la clase Character
    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    void setName(string); // Método para establecer el nombre del personaje
    string getName(); // Método para obtener el nombre del personaje
    void setHealth(int); // Método para establecer la salud del personaje
    int getHealth(); // Método para obtener la salud del personaje
    void setAttack(int); // Método para establecer el ataque del personaje
    int getAttack(); // Método para obtener el ataque del personaje
    void setDefense(int); // Método para establecer la defensa del personaje
    int getDefense(); // Método para obtener la defensa del personaje
    void setSpeed(int); // Método para establecer la velocidad del personaje
    int getSpeed(); // Método para obtener la velocidad del personaje
    string toString(); // Método para obtener una representación en cadena del personaje
    bool getIsPlayer(); // Método para verificar si el personaje es un jugador
    bool hasFleed(); // Método para verificar si el personaje ha huido
};

#endif // RPG_CHARACTER_H