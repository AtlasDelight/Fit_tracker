#include "../include/ExerciceCardio.h"

// Constructeur par défaut
ExerciceCardio::ExerciceCardio()
    : Exercice("Cardio", 20, 5), distanceKm(0.0), frequenceCardiaqueMoyenne(120) {}

// Constructeur paramétré
ExerciceCardio::ExerciceCardio(string nom, int dureeMinutes, int difficulte, double distanceKm, int fcMoyenne)
    : Exercice(nom, dureeMinutes, difficulte), distanceKm(distanceKm), frequenceCardiaqueMoyenne(fcMoyenne) {}

// Constructeur par copie
ExerciceCardio::ExerciceCardio(const ExerciceCardio& autre)
    : Exercice(autre), distanceKm(autre.distanceKm), frequenceCardiaqueMoyenne(autre.frequenceCardiaqueMoyenne) {}

// Destructeur
ExerciceCardio::~ExerciceCardio() {}

// Surcharge de l'opérateur =
ExerciceCardio& ExerciceCardio::operator=(const ExerciceCardio& autre) {
    if (this != &autre) {
        Exercice::operator=(autre);
        distanceKm = autre.distanceKm;
        frequenceCardiaqueMoyenne = autre.frequenceCardiaqueMoyenne;
    }
    return *this;
}

// Vitesse moyenne en km/h
double ExerciceCardio::calculerVitesseMoyenne() const {
    if (dureeMinutes <= 0) return 0.0;
    return distanceKm / (dureeMinutes / 60.0);
}

// Redéfinition : Calcul des calories brûlées
double ExerciceCardio::calculerCaloriesBrulees() const {
    double facteurFC = (frequenceCardiaqueMoyenne > 100) ? (frequenceCardiaqueMoyenne - 60) * 0.1 : 4.0;
    return (dureeMinutes * facteurFC) + (distanceKm * 35.0);
}

// Redéfinition : Affichage des détails
void ExerciceCardio::afficherDetails(ostream& os) const {
    os << "[Cardio]      " << nom << " (" << dureeMinutes << " min, diff: " << difficulte << "/10) - "
       << distanceKm << " km (" << calculerVitesseMoyenne() << " km/h) | FC moy: "
       << frequenceCardiaqueMoyenne << " bpm | Calories : " << calculerCaloriesBrulees() << " kcal";
}

// Redéfinition : Clonage polymorphe
Exercice* ExerciceCardio::cloner() const {
    return new ExerciceCardio(*this);
}