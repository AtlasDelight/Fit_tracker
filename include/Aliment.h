#ifndef ALIMENT_H
#define ALIMENT_H

#include <iostream>
#include <string>

using namespace std;

class Aliment {
private:
    string nom;
    int calories;       // Pour la portion consommée
    double proteines;   // en grammes
    double glucides;    // en grammes
    double lipides;     // en grammes

public:
    // Constructeurs et Destructeur (Forme canonique)
    Aliment();
    Aliment(string nom, int calories, double proteines, double glucides, double lipides);
    Aliment(const Aliment& autre);
    ~Aliment();

    // Surcharge de l'opérateur d'affectation (obligatoire)
    Aliment& operator=(const Aliment& autre);

    // Accesseurs (Getters)
    string getNom() const;
    int getCalories() const;
    double getProteines() const;
    double getGlucides() const;
    double getLipides() const;

    // Surcharge d'opérateurs arithmétiques et d'affichage
    Aliment operator+(const Aliment& autre) const; // Fusionner deux portions
    friend ostream& operator<<(ostream& os, const Aliment& a);
};

#endif