\# Exercice 7 — Le temps que ça prend



\## Commandes lancées et sorties obtenues



Depuis la racine du dépôt Nkentseu.



\### Construction complète à froid



&#x20;   Measure-Command { jenga build --config Debug }



Résultat :



&#x20;   Minutes           : 2

&#x20;   Seconds           : 37

&#x20;   Milliseconds      : 120

&#x20;   TotalSeconds      : 157.1208435



\### Deuxième construction, lancée immédiatement après, sans rien modifier



&#x20;   Measure-Command { jenga build --config Debug }



Résultat :



&#x20;   Minutes           : 0

&#x20;   Seconds           : 22

&#x20;   Milliseconds      : 104

&#x20;   TotalSeconds      : 22.1048635



\## Remarque sur la mesure



Measure-Command capture la sortie du bloc de script et ne l'affiche pas à l'écran par défaut. Je n'ai donc pas le résumé BUILD COMPLETED de Jenga pour ces deux runs, seulement les temps précis mesurés par PowerShell. C'est la limite honnête de cette méthode de chronométrage.



\## Tableau récapitulatif



| Run                          | Temps total |

|-------------------------------|------------|

| Construction complète (froid) | 157,12 s   |

| Deuxième construction (chaud) | 22,10 s    |

| Écart                         | 135,02 s (environ 7 fois plus lent à froid) |



\## Explication de l'écart



Le chapitre l'explique en section 1.8.3 : Jenga compare les dates des fichiers source à celles des fichiers objets déjà produits. À la première construction, aucun fichier objet n'existe encore, donc les 296 projets du dépôt (4428 fichiers .cpp/.h au total, mesurés à l'exercice 2) sont intégralement compilés puis liés, d'où les 157 secondes.



À la deuxième construction, aucun fichier source n'a changé depuis la première. Pour chacun des 296 projets, Jenga compare les dates et constate qu'aucun objet n'a besoin d'être régénéré : rien n'est recompilé, rien n'est relié.



Le temps n'est cependant pas nul (22 secondes, pas 0). Cela s'explique par le fait que Jenga doit tout de même parcourir l'arbre du workspace, lire les 220 fichiers .jenga, résoudre le graphe de dépendances entre les 296 projets, et vérifier la date de chacun des 4428 fichiers sources un par un pour confirmer qu'aucun n'a changé. Ce travail de vérification a un coût, même quand la conclusion est de ne rien reconstruire. Sur un dépôt de cette taille, ce coût de vérification reste largement inférieur au coût de compilation réelle, mais il n'est pas gratuit.



\## Conclusion



La construction n'est pas une fonction du nombre de lignes du dépôt, mais du nombre de fichiers dont les sources ont changé depuis la dernière construction. C'est ce qui rend supportable un dépôt d'un million de lignes (ou ici, deux millions) : sans cette vérification incrémentale, chaque construction reconstruirait tout, et personne ne pourrait itérer rapidement sur un module précis.

