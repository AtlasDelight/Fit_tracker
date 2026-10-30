#include "../include/Aliment.h"

// Constructeur par défaut
Aliment::Aliment() : nom("Inconnu"), calories(0), proteines(0.0), glucides(0.0), lipides(0.0) {}

// Constructeur paramétré
Aliment::Aliment(string nom, int calories, double proteines, double glucides, double lipides)
    : nom(nom), calories(calories), proteines(proteines), glucides(glucides), lipides(lipides) {}

// Constructeur par copie
Aliment::Aliment(const Aliment& autre)
    : nom(autre.nom), calories(autre.calories), proteines(autre.proteines),
      glucides(autre.glucides), lipides(autre.lipides) {}

// Destructeur
Aliment::~Aliment() {}

// Surcharge de l'opérateur =
Aliment& Aliment::operator=(const Aliment& autre) {
    if (this != &autre) {
        nom = autre.nom;
        calories = autre.calories;
        proteines = autre.proteines;
        glucides = autre.glucides;
        lipides = autre.lipides;
    }
    return *this;
}

// Accesseurs
string Aliment::getNom() const { return nom; }
int Aliment::getCalories() const { return calories; }
double Aliment::getProteines() const { return proteines; }
double Aliment::getGlucides() const { return glucides; }
double Aliment::getLipides() const { return lipides; }

// Surcharge de l'opérateur + (Fusionner deux aliments/portions)
Aliment Aliment::operator+(const Aliment& autre) const {
    return Aliment(
        nom + " + " + autre.nom,
        calories + autre.calories,
        proteines + autre.proteines,
        glucides + autre.glucides,
        lipides + autre.lipides
    );
}

// Surcharge de l'opérateur <<
ostream& operator<<(ostream& os, const Aliment& a) {
    os << a.nom << " (" << a.calories << " kcal | P: " << a.proteines
       << "g, G: " << a.glucides << "g, L: " << a.lipides << "g)";
    return os;
}