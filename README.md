# ENSEA in the Shell (enseash)

## Introduction

**enseash** est un micro-shell développé dans le cadre du TP de synthèse en deuxième année de la majeure informatique. Ce projet a pour objectif de mettre en œuvre un interpréteur de commandes simple capable d'exécuter des programmes, d'afficher leurs codes de sortie, leurs temps d'exécution, et de gérer des fonctionnalités supplémentaires comme les redirections, les pipes et les processus en arrière-plan.

## Fonctionnalités

Les principales fonctionnalités implémentées sont les suivantes :

1. **Message d'accueil et prompt personnalisé** :
   - Affiche un message de bienvenue suivi d'un prompt simple : `enseash %`.

2. **Boucle REPL (Read-Eval-Print Loop)** :
   - Lecture et exécution des commandes saisies par l'utilisateur.
   - Retour au prompt après chaque commande.

3. **Sortie du shell** :
   - Gestion des commandes `exit` et `<Ctrl>+D` pour quitter le shell avec un message d'au revoir.

4. **Affichage des codes de retour et signaux** :
   - Après l'exécution d'une commande, le prompt affiche le code de sortie ou le signal ayant causé son arrêt.

5. **Mesure des temps d'exécution** :
   - Affichage du temps d'exécution de chaque commande en millisecondes (ms).

6. **Exécution de commandes avec arguments** :
   - Support des commandes complexes avec leurs arguments.

7. **Gestion des redirections** :
   - Redirections des entrées et sorties standard avec les opérateurs `<` et `>`.

8. **Gestion des pipes** :
   - Support des redirections avec `|` pour connecter plusieurs commandes.

9. **Exécution en arrière-plan** :
   - Support des commandes exécutées avec `&`.
   - Gestion des processus en arrière-plan avec un affichage des informations pertinentes (numéro du processus, temps d'exécution, etc.).

## Structure du projet

L'architecture du projet suit une organisation claire pour séparer les fichiers d'en-tête et les implémentations :

```
├── include/
│   ├── detect_exit.h
│   ├── display_exit_status.h
│   ├── repl.h
│   ├── utils.h
├── src/
│   ├── detect_exit.c
│   ├── display_exit_status.c
│   ├── enseash.c
│   ├── repl.c
│   ├── utils.c
```

### Description des fichiers

- **`include/`** : Contient tous les fichiers d'en-tête déclarant les fonctions utilisées dans les fichiers sources.
- **`src/`** : Contient les fichiers d'implémentation des fonctionnalités décrites ci-dessus.

## Compilation et exécution

Pour compiler le projet, utilisez le fichier Makefile fourni (à créer si nécessaire) :

```bash
make
```

L'exécutable généré sera nommé `enseash`. Pour lancer le shell :

```bash
./enseash
```

## Instructions d'utilisation

- Tapez une commande simple pour l'exécuter (exemple : `ls`).
- Utilisez `exit` ou `<Ctrl>+D` pour quitter le shell.
- Essayez des commandes complexes avec arguments, redirections (`<`, `>`), pipes (`|`), ou en arrière-plan (`&`).

## Bonnes pratiques suivies

- Code entièrement en anglais (variables, fonctions, commentaires).
- Utilisation de `read` et `write` au lieu de `printf` pour une meilleure compatibilité avec les redirections.
- Gestion des chaînes de caractères avec des fonctions sécurisées (`strncpy`, etc.).
- Respect des bonnes pratiques de développement, avec un découpage clair en fonctions et des noms explicites.

## Auteurs

Ce projet a été réalisé en binôme par deux élèves en classe **2G2TD1TP1**:
- **Baguelin Benoit**
- **Dugard Kevin**

## Remerciements

Merci à **C. Barès**, **N. Papazoglou** et **G. Renton** pour l'encadrement pédagogique et les ressources fournies.

