\# Exercice 9 — L'histoire d'un fichier



\## Fichier choisi



Kernel/Foundation/NKMath/src/NKMath/NkVec.cpp



\## Commande utilisée



&#x20;   git log --follow --oneline -- Kernel/Foundation/NKMath/src/NKMath/NkVec.cpp

&#x20;   git log --follow --stat -- Kernel/Foundation/NKMath/src/NKMath/NkVec.cpp



\--follow est nécessaire car le fichier a changé de chemin en cours de route (voir ci-dessous) ; sans cette option, git log arrête de suivre l'historique au moment du déplacement.



\## Historique complet (du plus ancien au plus récent)



&#x20;   9c49f79f  21 mars 2026   bug fix vulkan opengl dx11 current bug software and dx12

&#x20;   f1e536a5  29 avril 2026  refactor 001

&#x20;   d557314e   5 mai 2026    update

&#x20;   bdda350a   9 juillet 2026  style: reformatage clang-format repo-wide (Kernel/Engine/Applications)



\## Sa création



Le fichier est né dans le commit 9c49f79f (21 mars 2026), avec 6 lignes seulement (Modules/Foundation/NKMath/src/NKMath/NkVec.cpp | 6 +). Ce commit est massif dans l'ensemble (994 fichiers changés, 280342 insertions au total : c'est un commit fondateur qui a posé une grande partie du dépôt d'un coup, incluant des bibliothèques externes entières comme FreeType et stb). NkVec.cpp lui-même n'était qu'une infime partie de ce commit géant — sa naissance est presque invisible dans un commit dont le message ("bug fix vulkan opengl dx11 current bug software and dx12") ne dit rien sur la création de fichiers, seulement sur des corrections de bugs graphiques.



\## Les trois moments où il a le plus changé



\### 1. f1e536a5 — "refactor 001" (29 avril 2026)



&#x20;   Modules/Foundation/NKMath/src/NKMath/NkVec.cpp | 56 ++++++++++++++++++++++++--

&#x20;   1 file changed, 52 insertions(+), 4 deletions(-)



C'est la plus grosse croissance réelle du fichier : 52 lignes ajoutées pour seulement 4 retirées, presque un décuplement de sa taille d'origine (6 lignes). Le message "refactor 001" est cependant très faible : il ne dit ni ce qui a été refactorisé, ni pourquoi, ni ce que "001" signifie dans une éventuelle série. C'est le type de message que le cours dénonce explicitement.



\### 2. bdda350a — "style: reformatage clang-format repo-wide" (9 juillet 2026)



&#x20;   Kernel/Foundation/NKMath/src/NKMath/NkVec.cpp | 62 +++++++++++++--------------

&#x20;   1 file changed, 31 insertions(+), 31 deletions(-)



62 lignes touchées, mais à parité exacte (31+/31-) : ce n'est pas une croissance, c'est une réécriture ligne par ligne sans changement de contenu logique. Le message est excellent : il explique précisément quoi (application d'un .clang-format), le périmètre (1748 fichiers), et même la vérification faite après coup ("NKGptTrain 25/25 et renderdemo 28/28 buildent OK"). Ce contraste avec "refactor 001" illustre bien la différence entre un message qui informe et un message qui ne fait qu'exister.



\### 3. 9c49f79f — la création elle-même (21 mars 2026)



Même si ce n'est que 6 lignes pour NkVec.cpp, ce commit compte parmi les trois moments les plus significatifs car c'est celui qui fait exister le fichier — sans lui, aucune des deux autres évolutions n'aurait de sujet.



\## Un déplacement sans changement de contenu



d557314e ("update", 5 mai 2026) mérite d'être noté séparément : le fichier passe de Modules/Foundation/NKMath/... à Kernel/Foundation/NKMath/..., mais avec 0 insertion et 0 suppression (Git le détecte comme un renommage pur, d'où l'indication {Modules => Kernel} dans la sortie de --stat). Le message "update" ne dit rien de ce déplacement de dossier racine, qui est pourtant l'information la plus notable de ce commit.



\## Ce que les messages disent des raisons



Sur les quatre commits, seul bdda350a explique clairement le pourquoi (uniformiser le style de tout le dépôt, avec preuve de non-régression). Les trois autres échouent chacun à sa manière :



\- 9c49f79f mélange la création de dizaines de fichiers dans un message qui ne parle que de correctifs Vulkan/OpenGL/DX11/DX12 — le pourquoi de la création de NkVec.cpp spécifiquement est invisible.

\- f1e536a5 ("refactor 001") ne dit ni le quoi ni le pourquoi, malgré un changement de contenu substantiel (52 lignes).

\- d557314e ("update") ne signale même pas qu'il s'agit d'un déplacement de dossier, l'information la plus factuelle et la plus simple à écrire de tout son propre commit.



\## Conclusion



L'histoire de ce fichier illustre concrètement une asymétrie que le cours ne montre qu'en théorie : le volume d'un changement (52 lignes pour "refactor 001", 280342 pour la création) n'a aucun rapport avec la qualité de son message. Le seul commit qui explique vraiment son pourquoi (bdda350a) est aussi, par coïncidence, celui où le contenu logique n'a pas changé d'une ligne — alors que les changements les plus substantiels de ce fichier (sa naissance, son refactor) restent aujourd'hui difficiles à justifier sans ouvrir le diff soi-même.

