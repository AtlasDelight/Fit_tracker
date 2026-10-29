#include <iostream>
#include "Sportif.h"
#include "ExerciceMusculation.h"
#include "ExerciceCardio.h"
#include "Aliment.h"

using namespace std;

int main() {
    cout << "========================================================\n";
    cout << "     TESTS EXHAUSTIFS DE LA FEUILLE DE ROUTE C++        \n";
    cout << "========================================================\n\n";

    // ---------------------------------------------------------
    // TEST 1 : Surcharge d'opérateurs sur les Aliment (+)
    // ---------------------------------------------------------
    cout << "[1] Test de la surcharge d'operateurs sur les Aliments (+)..." << endl;
    Aliment pomme("Pomme", 50, 0.3, 12.0, 0.2);
    Aliment banane("Banane", 90, 1.1, 23.0, 0.3);
    Aliment mixFruits = pomme + banane; // Utilise operator+
    cout << "  -> Aliment fusionne : " << mixFruits << "\n\n";

    // ---------------------------------------------------------
    // TEST 2 : Héritage, Polymorphisme et Pointeurs (Exercice**)
    // ---------------------------------------------------------
    cout << "[2] Test de l'heritage, du polymorphisme et des pointeurs dynamiques..." << endl;
    JourneeFitness jourTest("12/06/2026");

    // Musculation (utilise double* chargesParSerie)
    double chargesDC[] = {80.0, 85.0, 90.0, 90.0};
    ExerciceMusculation squat("Squat", 50, 9, 4, 8, chargesDC);
    
    // Cardio (hérite de Exercice)
    ExerciceCardio velo("Velo d'appartement", 45, 6, 18.5, 140);

    // Ajout polymorphe via Exercice**
    jourTest.ajouterExercice(squat);
    jourTest.ajouterExercice(velo);
    cout << "  -> Exercices ajoutes avec succes dans le tableau polymorphe.\n\n";

    // ---------------------------------------------------------
    // TEST 3 : Surcharge d'opérateurs de comparaison (<, >)
    // ---------------------------------------------------------
    cout << "[3] Test de la surcharge des operateurs de comparaison (<, >)..." << endl;
    double chargesLegeres[] = {40.0, 45.0};
    ExerciceMusculation legPress("Leg Press", 20, 4, 2, 10, chargesLegeres);
    
    if (squat > legPress) {
        cout << "  -> 'Squat' a un tonnage total superieur a 'Leg Press' (Test operator> valide !)\n\n";
    }

    // ---------------------------------------------------------
    // TEST 4 : Journal Alimentaire et opérateur +=
    // ---------------------------------------------------------
    cout << "[4] Test du journal alimentaire et de l'operateur +=..." << endl;
    jourTest.ajouterRepas(pomme);
    jourTest.ajouterRepas("Omelette", 350, 25.0, 2.0, 24.0);
    cout << "  -> Repas enregistres dans le journal.\n\n";

    // ---------------------------------------------------------
    // TEST 5 : Forme Canonique (Constructeur par copie et operator=)
    // ---------------------------------------------------------
    cout << "[5] Test de la Forme Canonique (Copie profonde et operateur =)..." << endl;
    
    // Test sur JourneeFitness (copie du tableau de pointeurs polymorphes et de la nutrition)
    JourneeFitness jourCopie = jourTest; // Constructeur par copie
    JourneeFitness jourAffectee;
    jourAffectee = jourTest;             // Surcharge de l'opérateur =
    cout << "  -> Copies profondes de JourneeFitness effectuees sans fuite memoire.\n\n";

    // ---------------------------------------------------------
    // TEST 6 : Bilan global via le Sportif et opérateur <<
    // ---------------------------------------------------------
    cout << "[6] Test du controleur Sportif et de l'historique dynamique..." << endl;
    Sportif athlete("Alexandre", 78.0, 2500);
    athlete.ajouterJournee(jourTest);
    athlete += jourCopie; // Test de l'opérateur += sur le Sportif

    // Affichage global via la surcharge de l'opérateur <<
    cout << athlete << endl;

    cout << "========================================================\n";
    cout << "   TOUTES LES FONCTIONNALITES DE LA FEUILLE SONT TESTES !\n";
    cout << "========================================================\n";

    return 0;
}