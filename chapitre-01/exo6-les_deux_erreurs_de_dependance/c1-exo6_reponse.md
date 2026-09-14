\# Exercice 6 — Les deux erreurs de dépendance



\## Configuration de test



MonEssai appelle nkentseu::math::NkSqrt(4.0f), une fonction réellement compilée (non-template) dans NKMath.lib, pour que l'édition de liens intervienne vraiment.



\## Test 1 — Sans dependson (avec links)



MonEssai.jenga contenait :



&#x20;   includedirs(\[...])

&#x20;   links(\["NKMath"])



(pas de dependson)



Commande : jenga build --project MonEssai --config Debug



Résultat :



&#x20;   Build Order (1 projects):

&#x20;     1. MonEssai \[CONSOLE\_APP]



&#x20;   ld: cannot find -lNKMath: No such file or directory

&#x20;   ld: have you installed the static version of the NKMath library ?

&#x20;   clang++: error: linker command failed with exit code 1



Analyse : sans dependson, Jenga ne construit que MonEssai seul — NKMath disparaît complètement de l'ordre de construction (Build Order (1 projects) au lieu de 6). Le linker cherche donc une bibliothèque NKMath.lib qui n'a jamais été (re)construite à cet endroit. C'est exactement le rôle "il sait dans quel ordre" (section 1.2 du chapitre) qui manque ici.



\## Test 2 — Avec dependson (sans links)



MonEssai.jenga contenait :



&#x20;   includedirs(\[...])

&#x20;   dependson(\["NKMath"])



(pas de links)



Commande : jenga build --project MonEssai --config Debug



Résultat :



&#x20;   Build Order (6 projects):

&#x20;     1. NKPlatform \[STATIC\_LIB]

&#x20;     2. NKCore \[STATIC\_LIB]

&#x20;     3. NKMemory \[STATIC\_LIB]

&#x20;     4. NKContainers \[STATIC\_LIB]

&#x20;     5. NKMath \[STATIC\_LIB]

&#x20;     6. MonEssai \[CONSOLE\_APP] (depends: NKMath)



&#x20;   Compiled: main.cpp

&#x20;   Linking...

&#x20;   Built: Build\\Bin\\Debug-Windows\\MonEssai\\MonEssai.exe

&#x20;   Build Successful



Résultat inattendu : la construction a réussi, sans erreur de liaison, alors que le chapitre (tableau section 1.5.5) prédit un "undefined reference" quand links manque.



\## Ce qui distingue les deux messages



Le premier message (cannot find -lNKMath) est une erreur d'ordre : le linker ne trouve même pas le fichier .lib, car il n'a jamais été produit dans ce build — c'est le rôle "il sait dans quel ordre" qui a manqué.



Le second cas devrait, en théorie, produire une erreur de liaison ("undefined reference" aux symboles de NkSqrt), car le fichier .lib existe mais n'est pas explicitement passé à l'éditeur de liens. Mais dans les faits, la construction a réussi.



\## Pourquoi ce résultat diffère de la théorie du chapitre



Deux hypothèses, la plus probable étant la première :



1\. Cette implémentation de Jenga lie automatiquement les dépendances statiques du même workspace déclarées via dependson. Contrairement au modèle théorique présenté section 1.5.5 (où dependson ne serait qu'une contrainte d'ordre), ce moteur semble collecter automatiquement les .lib des projets StaticLib listés en dependson et les ajouter à l'édition de liens — un comportement pratique qui évite la duplication, mais qui contredit la distinction pédagogique stricte du livre.

2\. Le .lib de NKMath était peut-être encore réutilisé depuis une configuration antérieure du linker (moins probable, car le dossier Build/Bin/MonEssai a bien été régénéré).



\## Conclusion



L'exercice révèle un écart entre le modèle conceptuel du chapitre (dependson = ordre uniquement, links = édition de liens uniquement) et le comportement réel observé sur ce dépôt : au moins pour les bibliothèques statiques internes au workspace, dependson seul semble suffire à la fois pour l'ordre ET la liaison. La distinction théorique reste vraie pour les bibliothèques système (ex: opengl32), qui elles ne sont jamais construites par Jenga et ne peuvent donc être liées que via links.

