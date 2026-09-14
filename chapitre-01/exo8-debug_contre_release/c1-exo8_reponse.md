\# Exercice 8 — Debug contre Release



\## Commandes lancées et sorties obtenues



Projet testé : NKMath (déjà construit à l'exercice 3).



\### Construction et chronométrage en Debug



&#x20;   Measure-Command { jenga build --project NKMath --config Debug }



Résultat :



&#x20;   Seconds           : 11

&#x20;   Milliseconds      : 317

&#x20;   TotalSeconds      : 11.3171049



\### Taille du binaire Debug



&#x20;   Get-Item "Build\\Lib\\Debug-Windows\\NKMath.lib" | Select-Object Name, Length



Résultat :



&#x20;   Name       Length

&#x20;   ----       ------

&#x20;   NKMath.lib 905138



\### Construction et chronométrage en Release



&#x20;   Measure-Command { jenga build --project NKMath --config Release }



Résultat :



&#x20;   Seconds           : 12

&#x20;   Milliseconds      : 987

&#x20;   TotalSeconds      : 12.9872567



\### Taille du binaire Release



&#x20;   Get-Item "Build\\Lib\\Release-Windows\\NKMath.lib" | Select-Object Name, Length



Résultat :



&#x20;   Name       Length

&#x20;   ----       ------

&#x20;   NKMath.lib 178124



\## Tableau récapitulatif



| Configuration | Temps de construction | Taille du binaire |

|----------------|-----------------------|--------------------|

| Debug          | 11,32 s                | 905 138 octets (\~884 Ko) |

| Release        | 12,99 s                | 178 124 octets (\~174 Ko) |



\## Les quatre nombres, expliqués par le .jenga



Le fichier NKMath.jenga, montré intégralement dans le chapitre (section 1.6), contient ces deux filtres :



&#x20;   with filter("config:Debug"):

&#x20;       defines(\["\_DEBUG", "DEBUG"]); optimize("Off"); symbols(True)

&#x20;   with filter("config:Release"):

&#x20;       defines(\["NDEBUG"]); optimize("Speed"); symbols(False)



\*\*Taille Debug (905 138 octets, environ 5 fois plus grosse) :\*\* expliquée par symbols(True) et optimize("Off"). symbols(True) embarque les informations de débogage (noms de variables, correspondance ligne de code / instruction machine) directement dans le .lib. optimize("Off") ne supprime aucun code mort, ne fusionne aucune instruction : chaque ligne écrite est traduite presque telle quelle, sans compaction.



\*\*Taille Release (178 124 octets) :\*\* expliquée par symbols(False) et optimize("Speed"). Sans les informations de débogage, et avec un compilateur libre d'éliminer le code redondant, d'inliner les petites fonctions et de réordonner les instructions pour la vitesse, le résultat est mécaniquement plus compact.



\*\*Temps Debug (11,32 s) :\*\* optimize("Off") signifie que le compilateur ne cherche pas à transformer le code, il le traduit directement. C'est en théorie la voie la plus rapide à compiler, ce qui correspond au temps le plus court observé ici.



\*\*Temps Release (12,99 s), plus lent que Debug :\*\* optimize("Speed") demande au compilateur d'analyser le code pour l'optimiser (inlining, élimination de code mort, réordonnancement des instructions), un travail supplémentaire par rapport à une simple traduction. Ce coût d'analyse explique que Release ait pris plus de temps que Debug dans ce test, même si le résultat final est plus petit et plus rapide à l'exécution. La ligne optimize("Speed") a un coût à la compilation, pas seulement un bénéfice à l'exécution.



\## Conclusion



Les quatre nombres observés (deux temps, deux tailles) ne sont pas dus au hasard : ils sont la conséquence directe de six mots dans le fichier de projet, optimize("Off")/optimize("Speed") et symbols(True)/symbols(False). Ce sont ces options de projet (section 1.5.8 du chapitre) qui pilotent, via les flags passés au compilateur, à la fois la taille du binaire et le temps nécessaire pour le produire — et pas toujours dans le sens qu'on attend spontanément : optimiser pour la vitesse d'exécution prend plus de temps à compiler, pas moins.

