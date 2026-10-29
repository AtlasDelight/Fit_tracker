#ifndef EXERCICEMUSCULATION_H
#define EXERCICEMUSCULATION_H

#include "Exercice.h"

using namespace std;

class ExerciceMusculation : public Exercice {
private:
    int nbSeries;
    int nbRepetitions;
    double* chargesParSerie; // POINTEUR : Gestion dynamique des poids soulevés à chaque série

public:
    // Constructeurs et Destructeur (Forme canonique avec copie profonde)
    ExerciceMusculation();
    ExerciceMusculation(string nom, int dureeMinutes, int difficulte, int nbSeries, int nbRepetitions, const double* charges);
    ExerciceMusculation(string nom, int dureeMinutes, int difficulte, int nbSeries, int nbRepetitions, double chargeFixe); // Surcharge de constructeur
    ExerciceMusculation(const ExerciceMusculation& autre);
    virtual ~ExerciceMusculation();

    // Surcharge de l'opérateur d'affectation
    ExerciceMusculation& operator=(const ExerciceMusculation& autre);

    // Méthodes spécifiques
    void modifierChargeSerie(int indexSerie, double nouvelleCharge);
    double calculerTonnageTotal() const; // Somme des (répétitions * charge de chaque série)

    // Redéfinition des méthodes virtuelles de Exercice (Polymorphisme)
    virtual double calculerCaloriesBrulees() const override;
    virtual void afficherDetails(ostream& os) const override;
    virtual Exercice* cloner() const override;

    // Surcharge d'opérateurs de comparaison (compare le tonnage total soulevé)
    bool operator>(const ExerciceMusculation& autre) const;
    bool operator<(const ExerciceMusculation& autre) const;
};

#endif