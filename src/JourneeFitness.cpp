#include "JourneeFitness.h"
#include "ExerciceMusculation.h"

// Constructeur par défaut
JourneeFitness::JourneeFitness()
    : date("01/01/2026"), nbExercices(0), capaciteExercices(5), nutritionDuJour() {
    seance = new Exercice*[capaciteExercices];
}

// Constructeur avec date
JourneeFitness::JourneeFitness(string date)
    : date(date), nbExercices(0), capaciteExercices(5), nutritionDuJour() {
    seance = new Exercice*[capaciteExercices];
}

// Constructeur par copie (Clonage polymorphe de chaque Exercice*)
JourneeFitness::JourneeFitness(const JourneeFitness& autre)
    : date(autre.date), nbExercices(autre.nbExercices),
      capaciteExercices(autre.capaciteExercices), nutritionDuJour(autre.nutritionDuJour) {
    seance = new Exercice*[capaciteExercices];
    for (int i = 0; i < nbExercices; ++i) {
        seance[i] = autre.seance[i]->cloner(); // Copie polymorphe !
    }
}

// Destructeur (Libération de chaque exercice pointé, puis du tableau de pointeurs)
JourneeFitness::~JourneeFitness() {
    for (int i = 0; i < nbExercices; ++i) {
        delete seance[i];
    }
    delete[] seance;
}

// Surcharge de l'opérateur =
JourneeFitness& JourneeFitness::operator=(const JourneeFitness& autre) {
    if (this != &autre) {
        // 1. Nettoyer la mémoire existante
        for (int i = 0; i < nbExercices; ++i) {
            delete seance[i];
        }
        delete[] seance;

        // 2. Copier les attributs
        date = autre.date;
        nbExercices = autre.nbExercices;
        capaciteExercices = autre.capaciteExercices;
        nutritionDuJour = autre.nutritionDuJour;

        // 3. Allouer et cloner de façon polymorphe
        seance = new Exercice*[capaciteExercices];
        for (int i = 0; i < nbExercices; ++i) {
            seance[i] = autre.seance[i]->cloner();
        }
    }
    return *this;
}

// Redimensionnement du tableau de pointeurs d'exercices
void JourneeFitness::redimensionnerSeance() {
    capaciteExercices *= 2;
    Exercice** nouvelleSeance = new Exercice*[capaciteExercices];
    for (int i = 0; i < nbExercices; ++i) {
        nouvelleSeance[i] = seance[i];
    }
    delete[] seance;
    seance = nouvelleSeance;
}

// Surcharge 1 : Ajouter n'importe quel Exercice (Musculation ou Cardio) par clonage
void JourneeFitness::ajouterExercice(const Exercice& ex) {
    if (nbExercices >= capaciteExercices) {
        redimensionnerSeance();
    }
    seance[nbExercices++] = ex.cloner();
}

// Surcharge 2 : Ajouter directement un exercice de musculation à charge fixe
void JourneeFitness::ajouterExercice(string nomMuscu, int duree, int difficulte, int series, int reps, double poidsFixe) {
    ExerciceMusculation ex(nomMuscu, duree, difficulte, series, reps, poidsFixe);
    ajouterExercice(ex);
}

// Ajout de repas
void JourneeFitness::ajouterRepas(const Aliment& a) {
    nutritionDuJour += a; // Utilise l'opérateur += surchargé de JournalAlimentaire
}

void JourneeFitness::ajouterRepas(string nom, int calories, double proteines, double glucides, double lipides) {
    nutritionDuJour.ajouterAliment(nom, calories, proteines, glucides, lipides);
}

// Accesseurs et Calculs (Polymorphisme en action)
string JourneeFitness::getDate() const { return date; }

double JourneeFitness::calculerTotalCaloriesBrulees() const {
    double total = 0.0;
    for (int i = 0; i < nbExercices; ++i) {
        total += seance[i]->calculerCaloriesBrulees(); // Appel polymorphe !
    }
    return total;
}

int JourneeFitness::calculerTotalCaloriesIngerees() const {
    return nutritionDuJour.calculerTotalCalories();
}

double JourneeFitness::calculerBilanCalorique() const {
    return calculerTotalCaloriesIngerees() - calculerTotalCaloriesBrulees();
}

// Surcharge de l'opérateur <<
ostream& operator<<(ostream& os, const JourneeFitness& jf) {
    os << "========================================================\n";
    os << " JOURNEE DU : " << jf.date << "\n";
    os << "========================================================\n";
    os << "  --- Seance d'entrainement (" << jf.nbExercices << " exercices) ---\n";
    for (int i = 0; i < jf.nbExercices; ++i) {
        os << "   " << (i + 1) << ". " << *(jf.seance[i]) << "\n";
    }
    os << "  => Total Calories Brulees (Sport) : " << jf.calculerTotalCaloriesBrulees() << " kcal\n\n";
    os << jf.nutritionDuJour << "\n\n";
    os << "  >>> BILAN ENERGETIQUE NET : " << jf.calculerBilanCalorique() << " kcal <<<\n";
    os << "========================================================";
    return os;
}