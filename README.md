# 🏋️‍♂️ Fit_tracker — Application de Suivi Sportif et Nutritionnel en C++

## 👥 Auteurs
* **Membre 1 :** [Mugisha Axcel]
* **Membre 2 :** [Chouman Ahmad]

---

## 📖 Description du Projet
**Fit_tracker** est un prototype d'application en ligne de commande (console) développé en C++ orienté objet. Il permet à un particulier de suivre au quotidien ses séances d'entraînement (musculation avec suivi des charges par série, et cardio) ainsi que son alimentation (calories et macronutriments), afin de calculer automatiquement son bilan énergétique journalier.

---

## 🎯 Mise en œuvre des concepts de POO (Cahier des charges)

Conformément aux consignes d'évaluation, tous les concepts orientés objet exigés ont été intégrés de manière naturelle et pertinente dans l'architecture du projet :

| Concept exigé | Implémentation concrète dans Fit_tracker |
| :--- | :--- |
| **Héritage & Redéfinition** | La classe de base abstraite `Exercice` est dérivée en deux classes filles : `ExerciceMusculation` et `ExerciceCardio`[cite: 1]. Elles redéfinissent les méthodes de calcul calorique et d'affichage[cite: 1]. |
| **Polymorphisme**[cite: 1] | `JourneeFitness` stocke un tableau polymorphe `Exercice**`[cite: 1]. L'appel à `calculerCaloriesBrulees()`, `afficherDetails()` et `cloner()` s'effectue dynamiquement selon le type réel de l'exercice[cite: 1]. |
| **Gestion dynamique de la mémoire (Pointeurs)**[cite: 1] | 1. `double* chargesParSerie` dans `ExerciceMusculation` (stocke le poids soulevé pour chaque série)[cite: 1].<br>2. `Exercice** seance` dans `JourneeFitness`[cite: 1].<br>3. `Aliment* listeAliments` dans `JournalAlimentaire`[cite: 1].<br>4. `JourneeFitness* historique` dans `Sportif`[cite: 1]. |
| **Forme Canonique de Coplien**[cite: 1] | **Chacune des 7 classes** du projet implémente un constructeur par défaut/paramétré, un **constructeur par copie** (copie profonde), un **destructeur** (`virtual` pour la classe mère), et la **surcharge de l'opérateur `=`**[cite: 1]. |
| **Surcharge de méthodes**[cite: 1] | Dans `JourneeFitness`, la méthode `ajouterExercice()` est surchargée pour accepter soit un pointeur `Exercice*` déjà instancié, soit directement les paramètres d'un exercice de musculation à charge constante[cite: 1]. |
| **Surcharge d'opérateurs**[cite: 1] | - `operator=` : sur **toutes** les classes (copie profonde des pointeurs)[cite: 1].<br>- `operator+=` et `operator+` : sur `JournalAlimentaire` pour ajouter un aliment ou fusionner deux repas[cite: 1].<br>- `operator>` et `operator<` : sur `ExerciceMusculation` pour comparer le tonnage total soulevé entre deux exercices[cite: 1].<br>- `operator<<` : sur toutes les classes pour l'affichage direct en flux (`std::cout`)[cite: 1]. |

---

## 📂 Architecture du Dépôt

```text
fit_tracker/
├── include/       # Fichiers d'en-tête (.h) contenant les déclarations des classes
├── src/           # Fichiers sources (.cpp) contenant les implémentations et le main.cpp
├── docs/          # Documentation technique et diagramme de classes UML
├── Makefile       # Script de compilation automatisée
└── README.md      # Présentation du projet