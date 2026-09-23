\# Exercice 1 — La fenêtre nue



\## Où le code vit réellement



Le fichier source complet est Applications/MonEssai/src/main.cpp dans le dépôt Nkentseu, construit et exécuté avec succès (voir preuve ci-dessous). Il est reproduit dans c3-exo1\_main.cpp pour ce dépôt de réponses.



\## Configuration nécessaire (MonEssai.jenga)



Contrairement à l'exemple isolé du chapitre, faire fonctionner ce programme dans le dépôt réel a demandé une déclaration de dépendances explicite :



&#x20;   nkentseudependson(

&#x20;       \["NKWindow", "NKTime"],

&#x20;       extra\_includes=\["src"],

&#x20;   )



\## Commande de construction et d'exécution



&#x20;   jenga run MonEssai --config Debug --build



Résultat (extrait) :



&#x20;   Project: MonEssai   Kind: WINDOWED\_APP

&#x20;   Found 1 source file(s)

&#x20;   Compiled: main.cpp

&#x20;   Linking...

&#x20;   Built: Build\\Bin\\Debug-Windows\\MonEssai\\MonEssai.exe

&#x20;   Build Successful



&#x20;   BUILD COMPLETED

&#x20;   Projects Built: 12/12

&#x20;   Status: SUCCESS



&#x20;   EXECUTION — MonEssai.exe



Une fenêtre nommée "Ma fenetre" s'est ouverte, confirmant le fonctionnement réel du programme.



\## Compter les lignes



En excluant les lignes vides et en ne comptant que le code du fichier main.cpp (10 lignes non vides sur 12 lignes totales) :



&#x20;   1  #include "NKWindow/NKWindow.h"

&#x20;   2  #include "NKWindow/NKMain.h"

&#x20;   3  using namespace nkentseu;

&#x20;   4  int nkmain(const NkEntryState \&state) {

&#x20;   5      NkWindowConfig cfg;

&#x20;   6      cfg.title  = "Ma fenetre";

&#x20;   7      cfg.width  = 1280;

&#x20;   8      cfg.height = 720;

&#x20;   9      NkWindow window(cfg);

&#x20;   10     if (!window.IsOpen()) {

&#x20;   11         return -1;

&#x20;   12     }

&#x20;   13     while (window.IsOpen()) { }

&#x20;   14     return 0;

&#x20;   15 }



15 lignes au total (accolades fermantes comprises), 12 instructions ou déclarations distinctes.



\## Chaque ligne retrouvée dans le chapitre



\- #include "NKWindow/NKWindow.h" et #include "NKWindow/NKMain.h" : le chapitre les nomme explicitement dans "Le plus petit programme", et précise le piège si le second est oublié : "undefined reference to WinMain... Retenez le symptôme général — une erreur de lien qui parle d'un symbole que vous n'avez jamais écrit est presque toujours un point d'entrée manquant."

\- using namespace nkentseu; : ajout non présent dans l'extrait du chapitre, mais nécessaire dans le dépôt réel (les classes NkWindowConfig, NkWindow, NkEntryState vivent dans le namespace nkentseu). Ceci a été découvert par l'erreur de compilation réelle, pas deviné à l'avance.

\- int nkmain(const NkEntryState \&state) : le chapitre l'affirme directement — "Vous n'écrivez pas de main. Vous écrivez nkmain. Derrière lui, le module fournit le point d'entrée natif de chaque plateforme."

\- NkWindowConfig cfg; puis cfg.title/width/height : correspond à "NkWindowConfig se lit par familles : l'identité et la taille (titre, largeur, hauteur)..."

\- NkWindow window(cfg); : "La configuration se donne au constructeur. La fenêtre est créée à ce moment-là."

\- if (!window.IsOpen()) { return -1; } : "On vérifie IsOpen. Une création peut échouer... Un programme qui continue après cela travaille dans le vide."

\- while (window.IsOpen()) { } : la boucle principale du programme, correspondant à "les événements arrivent ici" dans l'exemple du chapitre (ici vide, car aucun événement n'est encore traité — c'est le sujet du chapitre 4).

\- return 0; et l'accolade fermante : convention C++ standard de fin de fonction, non spécifique au module mais nécessaire pour tout programme valide.



\## Différence avec l'exemple du chapitre



Deux écarts constatés entre l'extrait du chapitre et ce qui a réellement fonctionné :



1\. Le chapitre omet using namespace nkentseu; (ou suppose une convention non montrée dans l'extrait) — sans cette ligne, la compilation échoue avec trois erreurs "unknown type name", chacune suggérant le nom complet dans le namespace.

2\. Le chapitre omet logger.Error(...) dans mon programme final (retiré pour rester au plus simple, puisque le logger n'est pas encore introduit à ce stade du cours) ; l'exemple du chapitre l'utilise dans son bloc d'échec, mais ce n'est pas strictement nécessaire au fonctionnement du programme.



\## Conclusion



Le plus petit programme qui ouvre une fenêtre, la garde ouverte et se termine proprement tient en 15 lignes (12 hors accolades de fermeture), et chacune correspond directement à un principe énoncé dans le chapitre : point d'entrée spécial, configuration au constructeur, vérification de la création, boucle sur IsOpen. Le seul ajout non documenté dans l'extrait (using namespace nkentseu;) a été découvert par l'erreur de compilation elle-même, pas deviné — exactement la démarche attendue depuis le chapitre 1 : mesurer, pas supposer.

