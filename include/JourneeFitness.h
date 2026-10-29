#ifndef JOURNEEFITNESS_H
#define JOURNEEFITNESS_H

#include "JournalAlimentaire.h"
#include "Exercice.h"

using namespace std;

class JourneeFitness {
private:
    string date;
    Exercice** seance; // POINTEUR DOUBLE : Tableau dynamique de pointeurs d'Exercice (Polymorphisme)
    int nbExercices;
    int capaciteExercices;
    JournalAlimentaire nutritionDuJour;

    void redimensionnerSeance();

public:
    // Constructeurs et Destructeur (Forme canonique avec clonage polymorphe)
    JourneeFitness();
    JourneeFitness(string date);
    JourneeFitness(const JourneeFitness& autre);
    ~JourneeFitness();

    // Surcharge de l'opérateur d'affectation
    JourneeFitness& operator=(const JourneeFitness& autre);

    // Surcharge de méthodes pour ajouter un exercice
    void ajouterExercice(const Exercice& ex); // Clone l'exercice passé en référence
    void ajouterExercice(string nomMuscu, int duree, int difficulte, int series, int reps, double poidsFixe); // Crée directement un ExerciceMusculation

    // Gestion de la nutrition du jour
    void ajouterRepas(const Aliment& a);
    void ajouterRepas(string nom, int calories, double proteines, double glucides, double lipides);

    // Calculs et Bilans
    string getDate() const;
    double calculerTotalCaloriesBrulees() const; // Appel polymorphe sur chaque Exercice*
    int calculerTotalCaloriesIngerees() const;
    double calculerBilanCalorique() const; // Calories ingérées - Calories brûlées

    // Surcharge de l'opérateur d'affichage
    friend ostream& operator<<(ostream& os, const JourneeFitness& jf);
};

#endif