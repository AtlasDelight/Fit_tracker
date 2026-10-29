#ifndef SPORTIF_H
#define SPORTIF_H

#include "JourneeFitness.h"

using namespace std;

class Sportif {
private:
    string nom;
    double poidsCorps;      // en kg
    int objectifCalorique;  // ex: 2500 kcal/jour
    JourneeFitness* historique; // POINTEUR : Tableau dynamique des journées enregistrées
    int nbJours;
    int capaciteJours;

    void redimensionnerHistorique();

public:
    // Constructeurs et Destructeur (Forme canonique)
    Sportif();
    Sportif(string nom, double poidsCorps, int objectifCalorique);
    Sportif(const Sportif& autre);
    ~Sportif();

    // Surcharge de l'opérateur d'affectation
    Sportif& operator=(const Sportif& autre);

    // Gestion des journées et du profil
    void ajouterJournee(const JourneeFitness& journee);
    JourneeFitness* getJournee(int index);
    int getNbJours() const;
    string getNom() const;
    void setPoidsCorps(double nouveauPoids);

    // Surcharge d'opérateur += pour ajouter une journée directement (sportif += journee;)
    Sportif& operator+=(const JourneeFitness& journee);

    // Affichage complet du profil et de l'historique
    friend ostream& operator<<(ostream& os, const Sportif& s);
};

#endif