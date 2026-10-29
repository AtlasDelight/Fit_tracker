# 📐 Architecture Détaillée et Graphe de Dépendances

Ce document détaille la conception orientée objet de **Fit_tracker** et justifie les choix techniques liés à la gestion de la mémoire et au polymorphisme[cite: 1].

## 1. Diagramme de Classes UML

```mermaid
classDiagram
    direction TB

    class Sportif {
        -string nom
        -double poidsCorps
        -int objectifCalorique
        -JourneeFitness* historique
        -int nbJours
        +Sportif()
        +Sportif(const Sportif&)
        +~Sportif()
        +operator=(const Sportif&) Sportif&
        +ajouterJournee(const JourneeFitness&) void
    }

    class JourneeFitness {
        -string date
        -Exercice** seance
        -int nbExercices
        -JournalAlimentaire nutritionDuJour
        +JourneeFitness()
        +JourneeFitness(const JourneeFitness&)
        +~JourneeFitness()
        +operator=(const JourneeFitness&) JourneeFitness&
        +ajouterExercice(Exercice*) void
        +ajouterExercice(string, int, int, double) void
        +calculerTotalCaloriesBrulees() double
        +calculerBilanCalorique() double
    }

    class JournalAlimentaire {
        -Aliment* listeAliments
        -int nbAliments
        +JournalAlimentaire()
        +JournalAlimentaire(const JournalAlimentaire&)
        +~JournalAlimentaire()
        +operator=(const JournalAlimentaire&) JournalAlimentaire&
        +operator+=(const Aliment&) JournalAlimentaire&
        +calculerTotalCalories() int
        +calculerTotalProteines() double
    }

    class Aliment {
        -string nom
        -int calories
        -double proteines
        -double glucides
        -double lipides
        +Aliment()
        +Aliment(const Aliment&)
        +~Aliment()
        +operator=(const Aliment&) Aliment&
    }

    class Exercice {
        <<Abstract>>
        #string nom
        #int dureeMinutes
        +Exercice()
        +Exercice(const Exercice&)
        +virtual ~Exercice()
        +operator=(const Exercice&) Exercice&
        +calculerCaloriesBrulees()* double
        +afficherDetails(ostream&)* void
        +cloner()* Exercice*
    }

    class ExerciceMusculation {
        -int nbSeries
        -int nbRepetitions
        -double* chargesParSerie
        +ExerciceMusculation()
        +ExerciceMusculation(const ExerciceMusculation&)
        +virtual ~ExerciceMusculation()
        +operator=(const ExerciceMusculation&) ExerciceMusculation&
        +calculerTonnage() double
        +calculerCaloriesBrulees() double
        +afficherDetails(ostream&) void
        +cloner() Exercice*
    }

    class ExerciceCardio {
        -double distanceKm
        -int frequenceCardiaque
        +ExerciceCardio()
        +ExerciceCardio(const ExerciceCardio&)
        +virtual ~ExerciceCardio()
        +operator=(const ExerciceCardio&) ExerciceCardio&
        +calculerCaloriesBrulees() double
        +afficherDetails(ostream&) void
        +cloner() Exercice*
    }

    Sportif *-- "0..*" JourneeFitness : Gère (Pointeur dynamique)
    JourneeFitness *-- "1" JournalAlimentaire : Contient
    JourneeFitness o-- "0..*" Exercice : Stocke (Exercice**)
    JournalAlimentaire *-- "0..*" Aliment : Contient (Pointeur dynamique)
    Exercice <|-- ExerciceMusculation : Hérite
    Exercice <|-- ExerciceCardio : Hérite



    ## 3. Arbre d'inclusion des fichiers d'en-tête (`#include`)

Pour éviter toute inclusion circulaire lors de la compilation séparée, le projet suit une hiérarchie stricte du bas vers le haut (des classes de base indépendantes vers le contrôleur principal) :

```text
                       [ main.cpp ]
                            │
                            ▼
                      [ Sportif.h ]
                            │
                            ▼
                   [ JourneeFitness.h ]
                     /              \
                    /                \
                   ▼                  ▼
     [ JournalAlimentaire.h ]    [ Exercice.h ] (Classe abstraite)
               │                       ▲
               ▼                      / \
         [ Aliment.h ]               /   \
                                    /     \
        [ ExerciceMusculation.h ] ─┘       └─ [ ExerciceCardio.h ]

```