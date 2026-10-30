#include "../include/JournalAlimentaire.h"

// Constructeur par défaut
JournalAlimentaire::JournalAlimentaire() : nbAliments(0), capaciteMax(5) {
    listeAliments = new Aliment[capaciteMax];
}

// Constructeur avec capacité initiale
JournalAlimentaire::JournalAlimentaire(int capaciteInitiale)
    : nbAliments(0), capaciteMax(capaciteInitiale > 0 ? capaciteInitiale : 5) {
    listeAliments = new Aliment[capaciteMax];
}

// Constructeur par copie (Copie profonde du tableau dynamique d'aliments)
JournalAlimentaire::JournalAlimentaire(const JournalAlimentaire& autre)
    : nbAliments(autre.nbAliments), capaciteMax(autre.capaciteMax) {
    listeAliments = new Aliment[capaciteMax];
    for (int i = 0; i < nbAliments; ++i) {
        listeAliments[i] = autre.listeAliments[i];
    }
}

// Destructeur
JournalAlimentaire::~JournalAlimentaire() {
    delete[] listeAliments;
}

// Surcharge de l'opérateur =
JournalAlimentaire& JournalAlimentaire::operator=(const JournalAlimentaire& autre) {
    if (this != &autre) {
        delete[] listeAliments;

        nbAliments = autre.nbAliments;
        capaciteMax = autre.capaciteMax;
        listeAliments = new Aliment[capaciteMax];
        for (int i = 0; i < nbAliments; ++i) {
            listeAliments[i] = autre.listeAliments[i];
        }
    }
    return *this;
}

// Redimensionnement dynamique du tableau
void JournalAlimentaire::redimensionner() {
    capaciteMax *= 2;
    Aliment* nouveauTableau = new Aliment[capaciteMax];
    for (int i = 0; i < nbAliments; ++i) {
        nouveauTableau[i] = listeAliments[i];
    }
    delete[] listeAliments;
    listeAliments = nouveauTableau;
}

// Surcharge 1 : Ajouter un objet Aliment
void JournalAlimentaire::ajouterAliment(const Aliment& a) {
    if (nbAliments >= capaciteMax) {
        redimensionner();
    }
    listeAliments[nbAliments++] = a;
}

// Surcharge 2 : Ajouter directement via les attributs
void JournalAlimentaire::ajouterAliment(string nom, int calories, double proteines, double glucides, double lipides) {
    ajouterAliment(Aliment(nom, calories, proteines, glucides, lipides));
}

// Surcharge de l'opérateur +=
JournalAlimentaire& JournalAlimentaire::operator+=(const Aliment& a) {
    ajouterAliment(a);
    return *this;
}

// Calculs nutritionnels
int JournalAlimentaire::calculerTotalCalories() const {
    int total = 0;
    for (int i = 0; i < nbAliments; ++i) total += listeAliments[i].getCalories();
    return total;
}

double JournalAlimentaire::calculerTotalProteines() const {
    double total = 0.0;
    for (int i = 0; i < nbAliments; ++i) total += listeAliments[i].getProteines();
    return total;
}

double JournalAlimentaire::calculerTotalGlucides() const {
    double total = 0.0;
    for (int i = 0; i < nbAliments; ++i) total += listeAliments[i].getGlucides();
    return total;
}

double JournalAlimentaire::calculerTotalLipides() const {
    double total = 0.0;
    for (int i = 0; i < nbAliments; ++i) total += listeAliments[i].getLipides();
    return total;
}

int JournalAlimentaire::getNbAliments() const {
    return nbAliments;
}

// Surcharge de l'opérateur <<
ostream& operator<<(ostream& os, const JournalAlimentaire& ja) {
    os << "  --- Journal Alimentaire (" << ja.nbAliments << " aliments) ---\n";
    for (int i = 0; i < ja.nbAliments; ++i) {
        os << "   * " << ja.listeAliments[i] << "\n";
    }
    os << "  => Total Nutrition : " << ja.calculerTotalCalories() << " kcal "
       << "(P: " << ja.calculerTotalProteines() << "g, "
       << "G: " << ja.calculerTotalGlucides() << "g, "
       << "L: " << ja.calculerTotalLipides() << "g)";
    return os;
}