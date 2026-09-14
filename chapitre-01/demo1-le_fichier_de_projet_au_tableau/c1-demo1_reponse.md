\# Démo 1 — Le fichier de projet au tableau



\## Module présenté



NKCanvas (Kernel/Runtime/NKCanvas/NKCanvas.jenga), déjà annoté en détail à l'exercice 4. Cette démo reprend ce fichier sous l'angle demandé : ce qu'il déclare, ce qu'il filtre, ce qu'il délègue, avec la preuve précise de la question posée.



\## Ce qu'il déclare



\- Un projet nommé NKCanvas (with project("NKCanvas")), en C++17, dont les sources sont sous src/NKCanvas/\*\*.cpp et \*\*.h.

\- Ses 16 dépendances directes (NKWindow, NKFont, NKImage, NKGui, NKEvent, NKGlad, NKStream, NKTime, NKThreading, NKFileSystem, NKLogger, NKMath, NKContainers, NKMemory, NKCore, NKPlatform), listées explicitement dans une variable \_canvasDeps, avec un commentaire qui précise que chaque dépendance est nommée même quand elle arriverait par transitivité.

\- Un choix conditionnel : NKUI est ajouté seulement si le flag USE\_CANVAS\_NKUI est actif.



\## Ce qu'il filtre



Des blocs with filter(...) distincts pour : Windows desktop, UWP, Linux (XLib, XCB, Wayland, headless), macOS, Android, HarmonyOS, iOS, Web, Xbox. Chaque filtre choisit une chaîne de compilation différente (usetoolchain) et des liens système différents. Par exemple, sur Windows, links(\_WIN\_LINKS) ajoute gdi32, user32, d3d11, d3d12, dxgi, dxguid, et vulkan-1 seulement si WANT\_VULKAN est vrai — exactement le lien qui manquait sur ma machine avant l'installation du SDK Vulkan (documenté à l'exercice 13).



Un filtre config:Debug / config:Release classique définit aussi les macros et le niveau d'optimisation.



\## Ce qu'il délègue



Le fichier ne fait presque aucun choix seul : il appelle nkentseudependson(\_canvasDeps, selfexport="NKCanvas", ...), le raccourci maison qui va chercher dans un registre central (config/modules.jenga) ce que chaque dépendance nommée doit fournir (includes, liens, defines transitifs). Le .jenga du module se contente de nommer ses dépendances ; c'est le registre qui sait comment les traiter.



\## Où est décidé que NKCanvas est une bibliothèque statique ?



Réponse précise, avec la chaîne de preuve trouvée dans config/modules.jenga :



1\. NKCanvas.jenga appelle nkentseudependson(\_canvasDeps, selfexport="NKCanvas", ...). Le paramètre selfexport n'est pas vide, donc ce module est en mode LIB (commentaire du registre, ligne \~381 : "Mode LIB : selfexport = nom de CE module -> declare son kind/export").



2\. En mode LIB, le registre exécute :



&#x20;      kindexport(\_GLOBAL\_KIND, \_REGISTRY\[selfkey]\["export"])



&#x20;  (config/modules.jenga, ligne 386)



3\. \_GLOBAL\_KIND est défini une seule fois, tout en haut du fichier :



&#x20;      \_GLOBAL\_KIND = ProjectKind.STATIC\_LIB



&#x20;  (config/modules.jenga, ligne 42), avec en commentaire juste au-dessus : "\_GLOBAL\_KIND : interrupteur unique static <-> shared pour toute la solution."



Donc NKCanvas n'est pas déclaré staticlib() dans son propre fichier .jenga (comme le fait l'exemple simple du chapitre avec MathLib). Le type "bibliothèque statique" vient d'un unique interrupteur central dans config/modules.jenga, appliqué à tous les modules du dépôt qui passent par nkentseudependson en mode LIB. Changer une seule ligne (\_GLOBAL\_KIND = ProjectKind.SHARED\_LIB) transformerait toute la solution en bibliothèques dynamiques d'un coup, sans toucher à aucun fichier de module individuel.



\## Remarque trouvée dans le registre en cherchant la réponse



Le fichier config/modules.jenga contient un avertissement explicite qui concerne directement NKCanvas (lignes \~173-177) : "CETTE TABLE FAIT FOI, PAS LE nkentseudependson DU PROJET." L'auteur y raconte que la table et un .jenga individuel se sont déjà contredits (la table disait NKUI, le projet disait NKGui), et que corriger le .jenga seul n'a aucun effet tant que la table du registre n'est pas mise à jour — un exemple concret de ce que "déléguer" signifie vraiment ici : le fichier de projet n'a pas le dernier mot.



\## Conclusion pour la présentation



La question "où est décidé que ce module est une bibliothèque statique ?" a une réponse à trois niveaux : le .jenga du module (appelle nkentseudependson avec selfexport), le registre (traduit ça en kindexport avec \_GLOBAL\_KIND), et une seule variable globale en haut du registre qui fixe le choix pour tout le dépôt. C'est l'exemple concret de ce que le chapitre appelle "déléguer" (section 1.7) : un fichier de projet bien tenu ne prend pas lui-même les décisions transverses, il les demande à un point central.

