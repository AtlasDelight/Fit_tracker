#include "../include/Exercice.h"

// Constructeur par défaut
Exercice::Exercice() : nom("Exercice sans nom"), dureeMinutes(0), difficulte(1) {}

// Constructeur paramétré
Exercice::Exercice(string nom, int dureeMinutes, int difficulte)
    : nom(nom), dureeMinutes(dureeMinutes), difficulte(difficulte) {
    if (this->difficulte < 1) this->difficulte = 1;
    if (this->difficulte > 10) this->difficulte = 10;
}

// Constructeur par copie
Exercice::Exercice(const Exercice& autre)
    : nom(autre.nom), dureeMinutes(autre.dureeMinutes), difficulte(autre.difficulte) {}

// Destructeur virtuel
Exercice::~Exercice() {}

// Surcharge de l'opérateur =
Exercice& Exercice::operator=(const Exercice& autre) {
    if (this != &autre) {
        nom = autre.nom;
        dureeMinutes = autre.dureeMinutes;
        difficulte = autre.difficulte;
    }
    return *this;
}

// Accesseurs
string Exercice::getNom() const { return nom; }
int Exercice::getDureeMinutes() const { return dureeMinutes; }
int Exercice::getDifficulte() const { return difficulte; }

// Surcharge de l'opérateur << (utilise le polymorphisme via afficherDetails)
ostream& operator<<(ostream& os, const Exercice& ex) {
    ex.afficherDetails(os);
    return os;
}