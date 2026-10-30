#include "../include/ExerciceMusculation.h"

// Constructeur par défaut
ExerciceMusculation::ExerciceMusculation()
    : Exercice("Musculation", 15, 5), nbSeries(0), nbRepetitions(0), chargesParSerie(nullptr) {}

// Constructeur avec tableau de charges
ExerciceMusculation::ExerciceMusculation(string nom, int dureeMinutes, int difficulte, int nbSeries, int nbRepetitions, const double* charges)
    : Exercice(nom, dureeMinutes, difficulte), nbSeries(nbSeries), nbRepetitions(nbRepetitions), chargesParSerie(nullptr) {
    if (this->nbSeries > 0) {
        chargesParSerie = new double[this->nbSeries];
        for (int i = 0; i < this->nbSeries; ++i) {
            chargesParSerie[i] = (charges != nullptr) ? charges[i] : 0.0;
        }
    }
}

// Surcharge du constructeur avec une charge fixe pour toutes les séries
ExerciceMusculation::ExerciceMusculation(string nom, int dureeMinutes, int difficulte, int nbSeries, int nbRepetitions, double chargeFixe)
    : Exercice(nom, dureeMinutes, difficulte), nbSeries(nbSeries), nbRepetitions(nbRepetitions), chargesParSerie(nullptr) {
    if (this->nbSeries > 0) {
        chargesParSerie = new double[this->nbSeries];
        for (int i = 0; i < this->nbSeries; ++i) {
            chargesParSerie[i] = chargeFixe;
        }
    }
}

// Constructeur par copie (Copie profonde du pointeur chargesParSerie)
ExerciceMusculation::ExerciceMusculation(const ExerciceMusculation& autre)
    : Exercice(autre), nbSeries(autre.nbSeries), nbRepetitions(autre.nbRepetitions), chargesParSerie(nullptr) {
    if (nbSeries > 0 && autre.chargesParSerie != nullptr) {
        chargesParSerie = new double[nbSeries];
        for (int i = 0; i < nbSeries; ++i) {
            chargesParSerie[i] = autre.chargesParSerie[i];
        }
    }
}

// Destructeur (Libération de la mémoire dynamique)
ExerciceMusculation::~ExerciceMusculation() {
    delete[] chargesParSerie;
}

// Surcharge de l'opérateur = (Copie profonde)
ExerciceMusculation& ExerciceMusculation::operator=(const ExerciceMusculation& autre) {
    if (this != &autre) {
        Exercice::operator=(autre); // Appel à l'opérateur = de la classe mère

        delete[] chargesParSerie; // Libération de l'ancienne mémoire

        nbSeries = autre.nbSeries;
        nbRepetitions = autre.nbRepetitions;
        if (nbSeries > 0 && autre.chargesParSerie != nullptr) {
            chargesParSerie = new double[nbSeries];
            for (int i = 0; i < nbSeries; ++i) {
                chargesParSerie[i] = autre.chargesParSerie[i];
            }
        } else {
            chargesParSerie = nullptr;
        }
    }
    return *this;
}

// Modifier la charge d'une série spécifique
void ExerciceMusculation::modifierChargeSerie(int indexSerie, double nouvelleCharge) {
    if (indexSerie >= 0 && indexSerie < nbSeries && chargesParSerie != nullptr) {
        chargesParSerie[indexSerie] = nouvelleCharge;
    }
}

// Calcul du tonnage total soulevé (en kg)
double ExerciceMusculation::calculerTonnageTotal() const {
    double tonnage = 0.0;
    for (int i = 0; i < nbSeries; ++i) {
        tonnage += chargesParSerie[i] * nbRepetitions;
    }
    return tonnage;
}

// Redéfinition : Calcul des calories brûlées
double ExerciceMusculation::calculerCaloriesBrulees() const {
    // Formule combinant la durée, la difficulté et le tonnage soulevé
    return (dureeMinutes * 4.5) + (calculerTonnageTotal() * 0.05) + (difficulte * 3.0);
}

// Redéfinition : Affichage des détails
void ExerciceMusculation::afficherDetails(ostream& os) const {
    os << "[Musculation] " << nom << " (" << dureeMinutes << " min, diff: " << difficulte << "/10) - "
       << nbSeries << "x" << nbRepetitions << " reps | Charges : [";
    for (int i = 0; i < nbSeries; ++i) {
        os << chargesParSerie[i] << "kg" << (i < nbSeries - 1 ? ", " : "");
    }
    os << "] | Tonnage : " << calculerTonnageTotal() << " kg | Calories : " << calculerCaloriesBrulees() << " kcal";
}

// Redéfinition : Clonage polymorphe
Exercice* ExerciceMusculation::cloner() const {
    return new ExerciceMusculation(*this);
}

// Surcharge des opérateurs de comparaison (basés sur le tonnage)
bool ExerciceMusculation::operator>(const ExerciceMusculation& autre) const {
    return this->calculerTonnageTotal() > autre.calculerTonnageTotal();
}

bool ExerciceMusculation::operator<(const ExerciceMusculation& autre) const {
    return this->calculerTonnageTotal() < autre.calculerTonnageTotal();
}