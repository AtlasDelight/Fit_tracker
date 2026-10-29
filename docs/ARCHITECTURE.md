# 📐 Architecture Détaillée et Graphe de Dépendances

Ce document détaille la conception orientée objet de **Fit_tracker** et justifie les choix techniques liés à la gestion de la mémoire et au polymorphisme.

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
```

## 2. Gestion de la Copie Profonde (Deep Copy) et Polymorphisme

Étant donné que chaque classe doit posséder un constructeur par copie et surcharger l'opérateur d'affectation `=` :
* **Tableaux dynamiques simples (`double*`, `Aliment*`, `JourneeFitness*`)** : Lors de la copie ou de l'affectation, l'ancienne mémoire est désallouée (`delete[]`), un nouveau bloc mémoire est alloué (`new[]`), et chaque élément est copié individuellement.
* **Tableau dynamique polymorphe (`Exercice** seance`)** : Pour copier une `JourneeFitness` sans connaître à l'avance le type exact de chaque `Exercice` pointé (`ExerciceMusculation` ou `ExerciceCardio`), la classe abstraite `Exercice` définit la méthode virtuelle pure `virtual Exercice* cloner() const = 0;` (Patron de conception *Prototype*).

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

### Équivalent visuel (Graphe de compilation)

```mermaid
graph TD
    Main["main.cpp"] --> Sportif["Sportif.h"]
    Main -.->|Instancie| ExMuscu["ExerciceMusculation.h"]
    Main -.->|Instancie| ExCardio["ExerciceCardio.h"]
    
    Sportif --> Journee["JourneeFitness.h"]
    
    Journee --> Journal["JournalAlimentaire.h"]
    Journee --> Exercice["Exercice.h (Abstraite)"]
    
    Journal --> Aliment["Aliment.h"]
    
    ExMuscu -->|#include & Hérite| Exercice
    ExCardio -->|#include & Hérite| Exercice
```

### Ordre logique de développement et de compilation :
1. **Niveau 0 (Classes feuilles sans dépendances internes)** : `Aliment.h` et `Exercice.h`.
2. **Niveau 1 (Classes spécialisées et conteneurs premiers)** : `JournalAlimentaire.h` (dépend de `Aliment.h`), ainsi que `ExerciceMusculation.h` et `ExerciceCardio.h` (héritent de `Exercice.h`).
3. **Niveau 2 (Agrégation journalière)** : `JourneeFitness.h` (combine `JournalAlimentaire.h` et le tableau polymorphe `Exercice**`).
4. **Niveau 3 (Contrôleur global)** : `Sportif.h` (gère l'historique dynamique des `JourneeFitness`).
5. **Niveau 4 (Point d'entrée)** : `main.cpp` (orchestre le menu console et les tests unitaires).