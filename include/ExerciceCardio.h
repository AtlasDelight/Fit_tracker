#ifndef EXERCICECARDIO_H
#define EXERCICECARDIO_H

#include "Exercice.h"

using namespace std;

class ExerciceCardio : public Exercice {
private:
    double distanceKm;
    int frequenceCardiaqueMoyenne;

public:
    // Constructeurs et Destructeur (Forme canonique)
    ExerciceCardio();
    ExerciceCardio(string nom, int dureeMinutes, int difficulte, double distanceKm, int fcMoyenne);
    ExerciceCardio(const ExerciceCardio& autre);
    virtual ~ExerciceCardio();

    // Surcharge de l'opérateur d'affectation
    ExerciceCardio& operator=(const ExerciceCardio& autre);

    // Méthodes spécifiques
    double calculerVitesseMoyenne() const; // en km/h

    // Redéfinition des méthodes virtuelles de Exercice (Polymorphisme)
    virtual double calculerCaloriesBrulees() const override;
    virtual void afficherDetails(ostream& os) const override;
    virtual Exercice* cloner() const override;
};

#endif