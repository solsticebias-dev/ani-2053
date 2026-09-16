\# Exercice 2 — Les trois endroits



\## Commandes lancées et sorties obtenues



Dans le dépôt d'essai (C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai), sur fichier1.txt.



\### Étape 1 — Après modification, avant add



&#x20;   Set-Content -Path fichier1.txt -Value "Contenu modifie"

&#x20;   git status



Résultat :



&#x20;   On branch master

&#x20;   Changes not staged for commit:

&#x20;     (use "git add <file>..." to update what will be committed)

&#x20;     (use "git restore <file>..." to discard changes in working directory)

&#x20;           modified:   fichier1.txt



&#x20;   no changes added to commit (use "git add" and/or "git commit -a")



\### Incident réel : commit tenté sans add



Une première tentative a tapé "git add fichier1.txt git status" sur une seule ligne, ce qui a fait échouer la commande add (fatal: pathspec 'git' did not match any files, git interprétant "git" et "status" comme des noms de fichiers supplémentaires). git commit a donc été lancé alors que rien n'était réellement indexé :



&#x20;   git commit -m "Modification du contenu de fichier1"



Résultat (identique à l'étape 1, car rien n'avait été ajouté) :



&#x20;   On branch master

&#x20;   Changes not staged for commit:

&#x20;           modified:   fichier1.txt

&#x20;   no changes added to commit (use "git add" and/or "git commit -a")



Ce commit n'a rien créé : aucun message \[master ...] ne confirme de nouvelle validation, contrairement à un commit réussi. C'est une preuve concrète que commit ne peut valider que ce qui est déjà dans l'index — la modification restait uniquement dans le répertoire de travail.



\### Étape 2 — Après add (repris correctement, une commande par ligne)



&#x20;   git add fichier1.txt

&#x20;   git status



Résultat :



&#x20;   On branch master

&#x20;   Changes to be committed:

&#x20;     (use "git restore --staged <file>..." to unstage)

&#x20;           modified:   fichier1.txt



\### Étape 3 — Après commit



&#x20;   git commit -m "Modification du contenu de fichier1"

&#x20;   git status



Résultat du commit :



&#x20;   \[master cd4dd26] Modification du contenu de fichier1

&#x20;    1 file changed, 1 insertion(+), 1 deletion(-)



Résultat du git status suivant :



&#x20;   On branch master

&#x20;   nothing to commit, working tree clean



\## Ce qui change entre les trois sorties



\*\*Étape 1 (après modification seule)\*\* : Git signale "Changes not staged for commit" — la modification existe dans le répertoire de travail, mais Git précise explicitement "no changes added to commit". Le fichier est modifié, mais rien n'est encore prêt à être gravé.



\*\*Étape 2 (après add)\*\* : le message change de section : "Changes to be committed" au lieu de "Changes not staged for commit". Le contenu du fichier modifié n'a pas bougé sur le disque, mais son état dans l'index a changé — c'est exactement le rôle décrit par le cours : l'index contient "ce que contiendra le prochain commit", distinct du répertoire de travail.



\*\*Étape 3 (après commit)\*\* : le message devient "nothing to commit, working tree clean". L'index a été vidé de cette modification car elle a été gravée dans le dépôt (.git) sous forme d'un nouveau commit (cd4dd26). Les trois endroits (répertoire de travail, index, dépôt) sont maintenant synchronisés sur le même contenu.



\## L'incident comme preuve supplémentaire



L'erreur de frappe qui a fait échouer add a produit, sans le vouloir, une preuve directe qu'on ne peut pas sauter l'étape add : tenter un commit alors que rien n'est indexé ne produit aucun commit et laisse git status identique à l'état précédent. Ce n'est pas juste une règle du cours à croire sur parole, c'est ce que la commande a réellement fait ici.



\## Conclusion



Les trois git status donnent trois messages différents parce qu'ils décrivent trois endroits différents où une même modification peut se trouver : répertoire de travail (modifiée, non indexée), index (indexée, prête pour le prochain commit), dépôt (validée, tout est synchronisé). Le passage d'un état à l'autre suit exactement le chemin décrit par le cours : git add fait passer du répertoire de travail à l'index, git commit fait passer l'index au dépôt — et sauter l'un des deux (comme le montre l'incident) ne produit tout simplement rien.

