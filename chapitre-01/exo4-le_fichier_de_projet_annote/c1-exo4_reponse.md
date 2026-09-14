\# Exercice 4 — Le fichier de projet annoté



\## Fichier choisi



`Kernel/Foundation/NKContainers/NKContainers.jenga` — un module que le chapitre n'a pas montré directement (le chapitre montre NKMath.jenga comme exemple réel).



\## Annotation ligne par ligne



```python

\#!/usr/bin/env python3

\# -\*- coding: utf-8 -\*-

```

? Shebang et déclaration d'encodage UTF-8. Le chapitre ne parle pas de ces lignes, mais comme un .jenga est un vrai script Python (section 1.3), ce sont des conventions Python standards, pas quelque chose de spécifique à Jenga.



```python

"""

NKContainers - Conteneurs fondamentaux (C++17)

...

"""

```

Docstring Python de module : documentation en commentaire, ignorée à l'exécution. Confirme que le fichier est bien un programme Python (section 1.3), pas un format de configuration figé.



```python

from Jenga import \*

from jengaconfig import \*

```

Import obligatoire de Jenga (section 1.3) : donne accès aux fonctions project, files, filter, etc. Le second import donne accès à `nkentseudependson`, le raccourci maison du dépôt (section 1.7).



```python

with project("NKContainers"):

```

Déclare un projet nommé NKContainers (section 1.5.3). Pas de staticlib()/consoleapp() explicite ici : le type vient du registre partagé via nkentseudependson (section 1.6, remarque n°1).



```python

&#x20;   language("C++")

&#x20;   cppdialect("C++17")

&#x20;   location(".")

```

Langage et dialecte C++ du projet ; location(".") = le dossier courant du fichier .jenga sert de racine pour les chemins relatifs (section 1.5.4).



```python

&#x20;   nkentseudependson(

&#x20;       \["NKCore", "NKPlatform", "NKMemory"],

&#x20;       selfexport="NKContainers",

&#x20;       extra\_includes=\["src", "pch"],

&#x20;       extra\_defines=\["NK\_USE\_STD\_INITIALIZER\_LIST"],

&#x20;   )

```

Le raccourci maison (section 1.7) : émet en un seul appel les includedirs + links + dependson + defines pour les trois dépendances, y compris transitives. `extra\_defines` ? — le chapitre montre `extra\_includes` dans son exemple mais pas `extra\_defines` ; je suppose que c'est un define supplémentaire ajouté en plus de ceux générés automatiquement, mais je ne suis pas sûr de son mécanisme exact.



```python

&#x20;   pchheader("pch/pch.h")

&#x20;   pchsource("pch/pch.cpp")

```

En-tête précompilé (section 1.5.8, tableau des options de projet) : accélère la compilation en pré-compilant les includes communs.



```python

&#x20;   files(\[

&#x20;       "src/NKContainers/\*\*.cpp",

&#x20;   ])

```

Motif de fichiers sources (section 1.5.4) : `\*\*` descend dans tous les sous-dossiers. Correspond exactement à ce que compte l'exercice 2.



```python

&#x20;   objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

&#x20;   targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

```

Variables de chemin (section 1.5.6) : dossier des fichiers intermédiaires et dossier du résultat final, paramétrés par workspace/config/système/projet pour ne jamais écraser un autre build.



```python

&#x20;   with filter("system:Windows \&\& options:windows-runtime=uwp"):

&#x20;       objdir(...)

&#x20;       targetdir(...)

```

Filtre combiné avec `\&\&` (section 1.5.7, exemple donné dans le livre) : redéfinit les chemins uniquement pour la cible UWP (Universal Windows Platform). ? — UWP lui-même n'est pas expliqué dans le chapitre, mais apparaît dans la liste Target OSes de jenga info.



```python

&#x20;   with filter("system:Windows \&\& !options:windows-runtime=uwp \&\& !system:XboxSeries \&\& !system:XboxOne"):

&#x20;       usetoolchain(TC\_WINDOWS)

&#x20;   with filter("system:UWP || system:Windows \&\& options:windows-runtime=uwp"):

&#x20;       usetoolchain("xbox-clang")

&#x20;   with filter("system:Linux"):

&#x20;       links(\["pthread"])

&#x20;   with filter("system:macOS"):

&#x20;       usetoolchain("clang-native")

```

Une chaîne de compilation différente par plateforme (section 1.5.7 : rôle "il sait comment appeler le compilateur", section 1.2). `TC\_WINDOWS` a déjà été vu dans l'exemple réel du chapitre (NKMath.jenga). `links(\["pthread"])` = bibliothèque système, donc seulement links, pas dependson (tableau section 1.5.5). ? — "xbox-clang" pour UWP est surprenant, je ne comprends pas encore pourquoi UWP partage la même chaîne que Xbox.



```python

&#x20;   with filter("system:Android"):

&#x20;       pchheader("")

&#x20;       pchsource("")

&#x20;       usetoolchain("android-ndk")

&#x20;       links(\["log"])

&#x20;   with filter("system:HarmonyOS"):

&#x20;       pchheader("")

&#x20;       pchsource("")

&#x20;       usetoolchain("ohos-ndk")

&#x20;       links(\["hilog\_ndk.z"])

```

Désactivation du PCH sur Android/HarmonyOS : même contrainte documentée dans l'exemple NKMath.jenga du chapitre ("PCH désactivé sur Android, NDK r27+ clang18"). ? — HarmonyOS et son toolchain "ohos-ndk" ne sont pas expliqués dans le chapitre, seulement cités dans la liste des Target OSes.



```python

&#x20;   with filter("system:Web"):

&#x20;       usetoolchain("emscripten")

&#x20;   with filter("system:XboxSeries || system:XboxOne"):

&#x20;       usetoolchain("xbox-clang")

```

? Toolchains "emscripten" (Web) et "xbox-clang" (consoles Xbox) : noms non expliqués dans le chapitre, mais cohérents avec le principe "une chaîne de compilation par plateforme" (section 1.2).



```python

&#x20;   with filter("config:Debug"):

&#x20;       defines(\["\_DEBUG", "DEBUG", "NKENTSEU\_DEBUG"])

&#x20;       optimize("Off")

&#x20;       symbols(True)

&#x20;   with filter("config:Release"):

&#x20;       defines(\["NDEBUG"])

&#x20;       optimize("Speed")

&#x20;       symbols(False)

```

Filtres de configuration (section 1.5.7), identiques dans la forme à l'exemple du chapitre. Seule différence : une macro supplémentaire `NKENTSEU\_DEBUG` propre à ce module.



```python

&#x20;   with filter("(system:Linux || system:macOS || (system:Windows \&\& !options:windows-runtime=uwp \&\& !system:XboxSeries \&\& !system:XboxOne)) \&\& !system:Android \&\& !system:iOS || system:Web"):

&#x20;       with test():

&#x20;           testfiles(\["tests/\*\*.cpp"])

```

Bloc test() (section 1.5.9) : déclare une suite de tests, activée seulement sur certaines plateformes (desktop + Web, pas mobile/console). ? — la logique booléenne ici est complexe (parenthèses, priorité de `||` sur `\&\&`) ; je ne suis pas certain à 100% de comprendre l'ordre d'évaluation exact de cette expression.



\## Ce que je ne comprends pas encore



\- Le paramètre `extra\_defines` de `nkentseudependson`

\- Pourquoi UWP utilise le toolchain "xbox-clang"

\- La priorité exacte des opérateurs `||`/`\&\&`/parenthèses dans le dernier filtre

\- Les toolchains "ohos-ndk" et "emscripten" en détail (probablement expliqués dans un chapitre suivant sur le multi-plateforme)

