\# Exercice 11 — Le fichier qu'on n'aurait pas dû



\## Tentative 1 — données à zéro (résultat trompeur, à noter honnêtement)



Premier essai avec New-Object byte\[] (10MB), qui crée un tableau rempli de zéros par défaut :



&#x20;   "{0:N2} Mo (avant)" -f (...)

&#x20;   0.05 Mo (avant)



&#x20;   git add gros-fichier.bin

&#x20;   git commit -m "Ajouter un gros fichier par erreur"



&#x20;   "{0:N2} Mo (apres ajout)" -f (...)

&#x20;   0.10 Mo (apres ajout)



La taille de .git n'a presque pas augmenté (0,05 à 0,10 Mo) alors que le fichier fait 10 Mo. Ce n'est pas que git ait ignoré le fichier : git compresse chaque objet avec zlib avant de l'écrire dans .git/objects, et un fichier de 10 Mo entièrement composé de zéros se compresse en quelques centaines d'octets seulement. Cette première tentative n'était donc pas une mesure représentative d'un vrai fichier de 10 Mo, et a été refaite avec des données aléatoires (non compressibles) pour donner une mesure honnête.



\## Tentative 2 — données aléatoires (mesure représentative)



&#x20;   $rng = New-Object System.Random

&#x20;   $data = New-Object byte\[] (10MB)

&#x20;   $rng.NextBytes($data)

&#x20;   \[System.IO.File]::WriteAllBytes("$PWD\\gros-fichier2.bin", $data)

&#x20;   git add gros-fichier2.bin

&#x20;   git commit -m "Ajouter un gros fichier aleatoire par erreur"



&#x20;   "{0:N2} Mo (apres ajout, donnees aleatoires)" -f (...)

&#x20;   10.10 Mo (apres ajout, donnees aleatoires)



Cette fois la taille de .git reflète fidèlement les 10 Mo ajoutés (aucune compression possible sur des données aléatoires).



&#x20;   git rm gros-fichier2.bin

&#x20;   git commit -m "Retirer le gros fichier aleatoire"



&#x20;   "{0:N2} Mo (apres retrait, donnees aleatoires)" -f (...)

&#x20;   10.10 Mo (apres retrait, donnees aleatoires)



\## Le résultat central de l'exercice



Après avoir retiré le fichier au commit suivant, la taille de .git reste à 10,10 Mo, strictement identique à la mesure d'avant le retrait. Retirer un fichier d'un commit ne le retire pas du dépôt.



\## Pourquoi ce résultat, techniquement



git rm supprime le fichier du répertoire de travail et de l'index, et le nouveau commit (0d5bfc1) enregistre un instantané où ce fichier n'existe plus. Mais le cours le rappelle : git enregistre des instantanés complets, et chaque commit ne change jamais. Le commit précédent (e1cf680), qui contient le fichier de 10 Mo, reste entièrement dans l'historique : son empreinte, son contenu, tout est conservé tel quel. Le blob de 10 Mo associé à ce commit reste physiquement dans .git/objects, atteignable par quiconque remonte l'historique jusqu'à e1cf680, même si HEAD ne le montre plus aujourd'hui.



\## Rapport avec la règle du cours sur les secrets



C'est très exactement le mécanisme que le cours décrit à propos des secrets : "un mot de passe ou une clé publiés restent dans l'historique même après suppression, et c'est la seule chose de ce chapitre qu'on ne peut pas rattraper." Le principe est identique pour n'importe quel contenu volumineux ou indésirable, pas seulement les secrets : un commit suivant qui "retire" un fichier ne fait que dire "ne le montre plus à partir d'ici", sans jamais effacer sa présence dans les commits antérieurs.



\## Ce qu'il aurait fallu faire à la place



\- Avant de committer : ne jamais ajouter ce type de fichier (d'où l'intérêt d'un .gitignore et d'une relecture avant add, comme discuté à l'exercice 12).

\- Si l'erreur est locale et pas encore partagée : git reset --soft (voire --hard) sur le commit fautif, comme fait à l'exercice 8, plutôt qu'un nouveau commit de retrait.

\- Si l'erreur a déjà été poussée et doit être purgée définitivement de l'historique (cas hors du périmètre simple de ce cours) : des outils comme git filter-repo, qui réécrivent l'historique et recalculent toutes les empreintes en aval — une opération lourde, dangereuse sur du partagé, et qu'il vaut mieux éviter en amont plutôt que corriger après coup.



\## Conclusion



Mesurer avant de croire, une fois de plus : la première tentative avec des zéros aurait pu laisser croire, à tort, que retirer un fichier libère l'espace qu'il occupait. La seconde tentative, avec des données réellement volumineuses, montre l'inverse : la taille de .git ne redescend pas après un git rm suivi d'un commit, parce qu'un commit ne change jamais et que l'historique garde tout. Committer, même par erreur, engage bien plus que l'instant présent.

