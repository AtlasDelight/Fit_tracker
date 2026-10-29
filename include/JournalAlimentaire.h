#ifndef JOURNALALIMENTAIRE_H
#define JOURNALALIMENTAIRE_H

#include "Aliment.h"

using namespace std;

class JournalAlimentaire {
private:
    Aliment* listeAliments; // POINTEUR : Tableau dynamique d'aliments consommés
    int nbAliments;
    int capaciteMax;

    void redimensionner(); // Double la capacité du tableau dynamique si plein

public:
    // Constructeurs et Destructeur (Forme canonique avec copie profonde)
    JournalAlimentaire();
    JournalAlimentaire(int capaciteInitiale);
    JournalAlimentaire(const JournalAlimentaire& autre);
    ~JournalAlimentaire();

    // Surcharge de l'opérateur d'affectation
    JournalAlimentaire& operator=(const JournalAlimentaire& autre);

    // Surcharge de méthodes pour ajouter un aliment
    void ajouterAliment(const Aliment& a);
    void ajouterAliment(string nom, int calories, double proteines, double glucides, double lipides);

    // Surcharge d'opérateurs (+= pour ajouter un aliment, << pour afficher)
    JournalAlimentaire& operator+=(const Aliment& a);
    friend ostream& operator<<(ostream& os, const JournalAlimentaire& ja);

    // Bilans nutritionnels
    int calculerTotalCalories() const;
    double calculerTotalProteines() const;
    double calculerTotalGlucides() const;
    double calculerTotalLipides() const;
    int getNbAliments() const;
};

#endif