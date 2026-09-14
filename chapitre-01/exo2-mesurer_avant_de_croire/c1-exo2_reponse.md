\# Exercice 2 — Mesurer avant de croire



\## Mes chiffres vs ceux du livre



| Mesure | Ma valeur | Valeur du livre |

|---|---|---|

| Fichiers .cpp et .h (hors Build) | 4428 | 2641 |

| Fichiers .cpp et .h (avec Build) | 4428 | — |

| Lignes de code | 2 004 178 | 1 193 385 |

| Fichiers .jenga | 220 | 221 |

| Taille du dépôt sur le disque | 1,40 Go | 17 Go |



\## Méthode



Comptage effectué en PowerShell depuis la racine du dépôt Nkentseu, avec `Get-ChildItem -Recurse`, en excluant (puis sans exclure) le dossier `Build` via un filtre sur le chemin.



\## Explication des écarts



\*\*Le dossier Build n'explique pas l'écart chez moi\*\* : le nombre de fichiers .cpp/.h est strictement identique avec et sans exclusion de `Build`. Cela signifie que mon `Build` ne contient aucune copie de sources — probablement parce que je n'ai pas encore lancé une construction complète (`jenga build`) qui y déposerait des fichiers intermédiaires.



\*\*Les fichiers et lignes sont nettement plus nombreux chez moi\*\* (4428 contre 2641, presque le double en lignes). Deux causes probables : mon comptage inclut les fichiers de test (`tests/\*\*.cpp`), que le chiffre du livre n'a peut-être pas inclus de la même façon ; et surtout, le dépôt Nkentseu est un projet réel et vivant — l'auteur précise lui-même que ses chiffres ont été "mesurés le jour où il écrit cette page". Le dépôt continue d'évoluer, donc mes chiffres, mesurés plus tard, reflètent un état plus avancé du projet.



\*\*Le nombre de fichiers .jenga est quasiment identique\*\* (220 contre 221), un écart d'un seul fichier cohérent avec un module ajouté ou retiré entre-temps.



\*\*La taille sur disque est très différente\*\* (1,40 Go contre 17 Go). Un clone Git frais ne contient que le code source, sans les objets compilés ni les binaires produits par une construction complète. Le chiffre du livre inclut vraisemblablement le dossier `Build` rempli (objets, exécutables) et peut-être de gros fichiers d'assets (textures, audio) que mon dépôt cloné ne contient pas encore.



\## Conclusion



Cet exercice montre qu'un même dépôt, mesuré à des instants différents ou avant/après une construction, donne des chiffres différents. Le seul chiffre fiable est celui qu'on mesure soi-même, sur son propre dépôt, à l'instant présent.

