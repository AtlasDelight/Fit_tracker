#ifndef EXERCICE_H
#define EXERCICE_H

#include <iostream>
#include <string>

using namespace std;

class Exercice {
protected:
    string nom;
    int dureeMinutes;
    int difficulte; // Échelle de 1 à 10

public:
    // Constructeurs et Destructeur virtuel (Forme canonique)
    Exercice();
    Exercice(string nom, int dureeMinutes, int difficulte);
    Exercice(const Exercice& autre);
    virtual ~Exercice();

    // Surcharge de l'opérateur d'affectation
    Exercice& operator=(const Exercice& autre);

    // Accesseurs
    string getNom() const;
    int getDureeMinutes() const;
    int getDifficulte() const;

    // Méthodes virtuelles pures (Polymorphisme et Redéfinition)
    virtual double calculerCaloriesBrulees() const = 0;
    virtual void afficherDetails(ostream& os) const = 0;
    virtual Exercice* cloner() const = 0; // Pour la copie profonde polymorphe

    // Surcharge de l'opérateur d'affichage (appelle afficherDetails de façon polymorphe)
    friend ostream& operator<<(ostream& os, const Exercice& ex);
};

#endif