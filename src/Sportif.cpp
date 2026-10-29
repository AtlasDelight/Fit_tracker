#include "Sportif.h"

// Constructeur par défaut
Sportif::Sportif()
    : nom("Anonyme"), poidsCorps(70.0), objectifCalorique(2000), nbJours(0), capaciteJours(7) {
    historique = new JourneeFitness[capaciteJours];
}

// Constructeur paramétré
Sportif::Sportif(string nom, double poidsCorps, int objectifCalorique)
    : nom(nom), poidsCorps(poidsCorps), objectifCalorique(objectifCalorique), nbJours(0), capaciteJours(7) {
    historique = new JourneeFitness[capaciteJours];
}

// Constructeur par copie (Copie profonde de l'historique)
Sportif::Sportif(const Sportif& autre)
    : nom(autre.nom), poidsCorps(autre.poidsCorps), objectifCalorique(autre.objectifCalorique),
      nbJours(autre.nbJours), capaciteJours(autre.capaciteJours) {
    historique = new JourneeFitness[capaciteJours];
    for (int i = 0; i < nbJours; ++i) {
        historique[i] = autre.historique[i]; // Appelle l'opérateur = de JourneeFitness
    }
}

// Destructeur
Sportif::~Sportif() {
    delete[] historique;
}

// Surcharge de l'opérateur =
Sportif& Sportif::operator=(const Sportif& autre) {
    if (this != &autre) {
        delete[] historique;

        nom = autre.nom;
        poidsCorps = autre.poidsCorps;
        objectifCalorique = autre.objectifCalorique;
        nbJours = autre.nbJours;
        capaciteJours = autre.capaciteJours;

        historique = new JourneeFitness[capaciteJours];
        for (int i = 0; i < nbJours; ++i) {
            historique[i] = autre.historique[i];
        }
    }
    return *this;
}

// Redimensionnement de l'historique
void Sportif::redimensionnerHistorique() {
    capaciteJours *= 2;
    JourneeFitness* nouvelHistorique = new JourneeFitness[capaciteJours];
    for (int i = 0; i < nbJours; ++i) {
        nouvelHistorique[i] = historique[i];
    }
    delete[] historique;
    historique = nouvelHistorique;
}

// Ajouter une journée
void Sportif::ajouterJournee(const JourneeFitness& journee) {
    if (nbJours >= capaciteJours) {
        redimensionnerHistorique();
    }
    historique[nbJours++] = journee;
}

JourneeFitness* Sportif::getJournee(int index) {
    if (index >= 0 && index < nbJours) {
        return &historique[index];
    }
    return nullptr;
}

int Sportif::getNbJours() const { return nbJours; }
string Sportif::getNom() const { return nom; }
void Sportif::setPoidsCorps(double nouveauPoids) { poidsCorps = nouveauPoids; }

// Surcharge de l'opérateur +=
Sportif& Sportif::operator+=(const JourneeFitness& journee) {
    ajouterJournee(journee);
    return *this;
}

// Surcharge de l'opérateur <<
ostream& operator<<(ostream& os, const Sportif& s) {
    os << "########################################################\n";
    os << " PROFIL SPORTIF : " << s.nom << "\n";
    os << " Poids actuel   : " << s.poidsCorps << " kg\n";
    os << " Objectif       : " << s.objectifCalorique << " kcal / jour\n";
    os << " Jours suivis   : " << s.nbJours << "\n";
    os << "########################################################\n\n";
    for (int i = 0; i < s.nbJours; ++i) {
        os << s.historique[i] << "\n";
        // CODE CORRIGÉ
        int caloriesIngerees = s.historique[i].calculerTotalCaloriesIngerees();
        double ecart = caloriesIngerees - s.objectifCalorique;
        if (ecart > 0) {
            os << " -> Surplus calorique de +" << ecart << " kcal par rapport a l'objectif (Prise de masse).\n\n";
        } else {
            os << " -> Deficit calorique de " << ecart << " kcal par rapport a l'objectif (Seche / Perte de poids).\n\n";
        }
    }
    return os;
}