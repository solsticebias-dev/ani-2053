\# Exercice 6 — Le conflit provoqué



\## Objectif



L'objectif était de provoquer volontairement un conflit Git à partir de deux répertoires de travail différents, après avoir modifié la même ligne du même fichier.



J'ai utilisé deux clones du dépôt :



\* `conflit-A`

\* `conflit-B`



Les deux clones étaient initialement basés sur le commit :



```text

3524b81 — Ajout de la reponse de l'exercice 5 du chapitre 2

```



\---



\## 1. Création du fichier dans le répertoire A



Dans `conflit-A`, j'ai créé le fichier `conflit.txt` contenant :



```text

message = Bonjour

```



J'ai ensuite ajouté et validé le fichier :



```text

\[main 7f89ad0] Ajouter le fichier de conflit

&#x20;1 file changed, 1 insertion(+)

&#x20;create mode 100644 conflit.txt

```



J'ai poussé ce commit vers GitHub avec :



```text

To https://github.com/solsticebias-dev/ani-2053.git

&#x20;  3524b81..7f89ad0  main -> main

```



Le premier envoi a donc réussi.



\---



\## 2. Modification différente dans le répertoire B



Au moment où le clone B a été créé, il ne possédait pas encore le commit `7f89ad0` envoyé par A.



Dans `conflit-B`, j'ai créé le même fichier `conflit.txt`, mais avec une modification différente :



```text

message = Au revoir

```



J'ai créé le commit :



```text

\[main 0f3d34b] Modifier le message dans B

&#x20;1 file changed, 1 insertion(+)

&#x20;create mode 100644 conflit.txt

```



\---



\## 3. Refus du push



J'ai ensuite essayé de pousser le commit de B :



```text

git push

```



Git a refusé l'envoi :



```text

To https://github.com/solsticebias-dev/ani-2053.git

&#x20;! \[rejected]        main -> main (fetch first)

error: failed to push some refs to 'https://github.com/solsticebias-dev/ani-2053.git'

hint: Updates were rejected because the remote contains work that you do

hint: not have locally.

hint: This is usually caused by another repository pushing to

hint: the same ref.

hint: If you want to integrate the remote changes, use

hint: 'git pull' before pushing again.

```



Ce refus s'explique par le fait que GitHub contenait déjà le commit `7f89ad0` provenant du répertoire A, tandis que le répertoire B possédait son propre commit `0f3d34`.



Git a donc empêché B d'écraser le travail déjà présent sur le dépôt distant.



\---



\## 4. Récupération et apparition du conflit



J'ai utilisé :



```text

git pull

```



Git a récupéré le commit de A puis a essayé de fusionner les deux versions.



Le message obtenu a été :



```text

From https://github.com/solsticebias-dev/ani-2053

&#x20;  3524b81..7f89ad0  main       -> origin/main

Auto-merging conflit.txt

CONFLICT (add/add): Merge conflict in conflit.txt

Automatic merge failed; fix conflicts and then commit the result.

```



Git a donc détecté un conflit `add/add` dans `conflit.txt`.



Le `git status` a confirmé le conflit :



```text

On branch main

Your branch and 'origin/main' have diverged,

and have 1 and 1 different commits each, respectively.



You have unmerged paths.

&#x20; (fix conflicts and run "git commit")



Unmerged paths:

&#x20;       both added:      conflit.txt

``

```



