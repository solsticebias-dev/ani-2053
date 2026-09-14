\# Exercice 11 — Casser exprès



\## Commandes lancées et sorties obtenues



\### Faute introduite



Fichier modifié : Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp

Ligne ajoutée tout en haut du fichier, avant tout le reste :



&#x20;   CECI\_EST\_UNE\_FAUTE\_DE\_SYNTAXE +++ ;;;



\### Construction complète après la faute



&#x20;   jenga build --config Debug



Sortie (extraits pertinents) :



&#x20;   Build Order (227 projects):

&#x20;     1. NKPlatform \[STATIC\_LIB]

&#x20;     2. NKGlad \[STATIC\_LIB]

&#x20;     3. NKGLSlang \[STATIC\_LIB]

&#x20;     4. NKSPIRVCross \[STATIC\_LIB]

&#x20;     5. NKMbedTLS \[STATIC\_LIB]

&#x20;     6. pybind11 \[STATIC\_LIB]

&#x20;     7. NKCore \[STATIC\_LIB] (depends: NKPlatform)

&#x20;     8. NKMemory \[STATIC\_LIB] (depends: NKCore, NKPlatform)

&#x20;     9. NKContainers \[STATIC\_LIB] (depends: NKCore, NKMemory, NKPlatform)

&#x20;     10. NKMath \[STATIC\_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;     11. NKThreading \[STATIC\_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;     ... (227 projets au total, jusqu'à NKCivilizationScaleTest)



&#x20;   Project: NKPlatform — Build Successful (0.05s)

&#x20;   Project: NKGlad — Build Successful (0.02s)

&#x20;   Project: NKGLSlang — Build Successful (0.89s)

&#x20;   Project: NKSPIRVCross — Build Successful (0.71s)

&#x20;   Project: NKMbedTLS — Build Successful (1.81s)

&#x20;   Project: pybind11 — No source files found for project pybind11

&#x20;   Project: NKCore — Build Successful (0.06s)

&#x20;   Project: NKMemory — Build Successful (0.13s)

&#x20;   Project: NKContainers — Build Successful (0.54s)



&#x20;   Project: NKMath

&#x20;   Found 12 source file(s)



&#x20;   Compilation Error: NkVec.cpp

&#x20;   Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp:1:1:

&#x20;   error: unknown type name 'CECI\_EST\_UNE\_FAUTE\_DE\_SYNTAXE'

&#x20;       1 | CECI\_EST\_UNE\_FAUTE\_DE\_SYNTAXE +++ ;;;

&#x20;         | ^

&#x20;   Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp:1:31:

&#x20;   error: expected unqualified-id

&#x20;       1 | CECI\_EST\_UNE\_FAUTE\_DE\_SYNTAXE +++ ;;;

&#x20;         |                               ^

&#x20;   2 errors generated.



&#x20;   Compilation failed: NkVec.cpp

&#x20;   Build Failed — Time: 0.87s — Errors: 2 — Failed files: 1



&#x20;   BUILD FAILED

&#x20;   Projects Built:  9/227

&#x20;   Failed:         1

&#x20;   Not reached:    217  (arret au premier echec — voir --keep-going)

&#x20;   Errors:         2

&#x20;   Time:           5.09s

&#x20;   Status:         FAILURE



&#x20;   Echecs (1) — a corriger :

&#x20;     NKMath



\### Restauration du fichier



&#x20;   Copy-Item "Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp.backup" "Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp" -Force

&#x20;   Remove-Item "Kernel\\Foundation\\NKMath\\src\\NKMath\\NkVec.cpp.backup"

&#x20;   jenga build --project NKMath --config Debug



Résultat : Build Order (5 projects), tous construits avec succès, y compris NKMath avec ses 12 fichiers source, dont NkVec.cpp. BUILD COMPLETED, Projects Built: 5/5, Status: SUCCESS.



\## Combien de temps la construction a-t-elle mis à s'arrêter ?



5,09 secondes au total pour atteindre l'échec (Time: 5.09s dans le résumé final), sur les 227 projets prévus.



\## Quels projets ont quand même été construits ?



9 projets sur 227 : NKPlatform, NKGlad, NKGLSlang, NKSPIRVCross, NKMbedTLS, pybind11 (sans source, donc rien à compiler), NKCore, NKMemory, NKContainers. Tous ces projets ne dépendent pas de NKMath — ce sont soit des bibliothèques indépendantes (NKGlad, NKGLSlang, NKSPIRVCross, NKMbedTLS, pybind11), soit des étages inférieurs de la pile de fondation (NKPlatform, NKCore, NKMemory, NKContainers) qui viennent avant NKMath dans le graphe de dépendances, mais dont aucun n'a besoin de NKMath pour être construit.



\## Ce que le message d'erreur apprend sur l'ordre de construction



Le résumé final indique explicitement "Not reached: 217 (arret au premier echec)". Cela confirme que Jenga construit dans l'ordre calculé du graphe de dépendances (section 1.2 et 1.8.5 du chapitre) et s'arrête dès qu'un projet échoue, sans tenter les projets suivants dans cet ordre — même ceux qui n'ont peut-être aucun rapport avec NKMath. Les 217 projets non atteints incluent aussi bien des modules qui dépendent réellement de NKMath (NKThreading, NKContainers l'utilise indirectement, etc.) que des modules placés après lui dans l'ordre linéaire calculé mais sans lien de dépendance direct avec lui — Jenga ne distingue pas les deux cas et arrête tout dès le premier échec, plutôt que de sauter uniquement les projets réellement affectés (ce que l'option --keep-going, mentionnée dans le message, permettrait de faire différemment).



\## Conclusion



Casser un seul fichier d'un module placé tôt dans l'ordre de construction (NKMath est le 10e sur 227) suffit à arrêter toute la chaîne : 218 projets restants (217 non atteints + celui en échec) ne sont jamais tentés, même ceux qui n'ont techniquement aucune dépendance envers NKMath. Cela illustre concrètement le rôle "il sait dans quel ordre" du chapitre (section 1.2) : l'ordre de construction est une séquence unique calculée à l'avance, et un échec en un point de cette séquence bloque tout ce qui vient après elle par défaut, pas seulement ce qui en dépend réellement.

