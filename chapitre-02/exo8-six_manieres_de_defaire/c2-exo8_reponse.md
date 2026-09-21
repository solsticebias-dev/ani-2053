\# Exercice 8 — Six manières de défaire



\## Configuration



Dépôt de travail (depot-exo8) relié à un vrai dépôt distant local simulé (remote-exo8.git, créé avec git init --bare), pour que la situation 4 (commit poussé à annuler) soit un vrai push/revert/push, pas une simulation.



&#x20;   git init --bare remote-exo8.git

&#x20;   cd depot-exo8

&#x20;   git init

&#x20;   (creation de notes.txt, commit initial)

&#x20;   git remote add origin ../remote-exo8.git

&#x20;   git push -u origin master



\## Situation 1 — Une modification non voulue



Modification :



&#x20;   Add-Content -Path notes.txt -Value "ligne indesirable"

&#x20;   git status



Résultat :



&#x20;   Changes not staged for commit:

&#x20;           modified:   notes.txt



Défaite avec :



&#x20;   git checkout -- notes.txt



Le fichier revient à son état du dernier commit, la ligne indésirable disparaît du répertoire de travail.



\## Situation 2 — Un add de trop



&#x20;   Add-Content -Path notes.txt -Value "ligne ajoutee par erreur"

&#x20;   git add notes.txt

&#x20;   git status



Résultat :



&#x20;   Changes to be committed:

&#x20;           modified:   notes.txt



Défaite avec :



&#x20;   git restore --staged notes.txt

&#x20;   git status



Résultat :



&#x20;   Changes not staged for commit:

&#x20;           modified:   notes.txt



La modification redescend de l'index vers le répertoire de travail seul (elle n'est pas effacée, juste désindexée) ; nettoyage complet ensuite avec git checkout -- notes.txt.



\## Situation 3 — Un commit de trop



&#x20;   Add-Content -Path notes.txt -Value "commit accidentel"

&#x20;   git add notes.txt

&#x20;   git commit -m "Commit accidentel a annuler"

&#x20;   git log --oneline -3



Résultat avant défaite :



&#x20;   027a70b (HEAD -> master) Commit accidentel a annuler

&#x20;   0171cf6 (origin/master) Commit initial



Défaite avec :



&#x20;   git reset --soft HEAD\~1

&#x20;   git log --oneline -3



Résultat :



&#x20;   0171cf6 (HEAD -> master, origin/master) Commit initial



Le commit disparaît de l'historique, mais --soft garde son contenu indexé (git status confirmait "Changes to be committed" juste après) : rien n'est perdu, seul le commit lui-même est défait.



\## Situation 4 — Un commit poussé qu'il faut annuler



&#x20;   Add-Content -Path notes.txt -Value "erreur poussee sur origin"

&#x20;   git add notes.txt

&#x20;   git commit -m "Erreur qui sera poussee"

&#x20;   git push origin master



Résultat du push :



&#x20;   To ../remote-exo8.git

&#x20;      0171cf6..ddffa3b  master -> master



Le commit ddffa3b est maintenant sur origin/master : un reset serait dangereux ici (règle du cours : jamais de force-push pour défaire du partagé). Défaite avec :



&#x20;   git revert HEAD --no-edit

&#x20;   git push origin master



Résultat :



&#x20;   \[master efaf757] Revert "Erreur qui sera poussee"

&#x20;    1 file changed, 1 deletion(-)

&#x20;   ...

&#x20;      ddffa3b..efaf757  master -> master



git revert crée un nouveau commit qui annule le précédent, sans réécrire l'historique déjà partagé — exactement la règle d'or du chapitre ("on ne rejoue jamais des commits que quelqu'un d'autre a déjà récupérés").



\## Situation 5 — Un travail en cours à mettre de côté



&#x20;   Add-Content -Path notes.txt -Value "travail en cours non termine"

&#x20;   git stash

&#x20;   git status



Résultat :



&#x20;   Saved working directory and index state WIP on master: efaf757 Revert "Erreur qui sera poussee"

&#x20;   ...

&#x20;   nothing to commit, working tree clean



Le répertoire de travail redevient propre (Get-Content notes.txt confirme : la ligne ajoutée a disparu, seul "Contenu initial" reste). Vérification que le travail est bien conservé ailleurs :



&#x20;   git stash list



Résultat :



&#x20;   stash@{0}: WIP on master: efaf757 Revert "Erreur qui sera poussee"



Récupération avec :



&#x20;   git stash pop



Résultat :



&#x20;   Changes not staged for commit:

&#x20;           modified:   notes.txt

&#x20;   Dropped refs/stash@{0} (19c78b9a...)



Le travail en cours revient exactement comme avant la mise de côté.



\## Situation 6 — Un commit "perdu" à retrouver par le reflog



&#x20;   Add-Content -Path notes.txt -Value "commit qui va etre perdu"

&#x20;   git add notes.txt

&#x20;   git commit -m "Commit qui sera perdu"

&#x20;   git log --oneline -3



Résultat avant la perte :



&#x20;   d532efd (HEAD -> master) Commit qui sera perdu

&#x20;   efaf757 (origin/master) Revert "Erreur qui sera poussee"

&#x20;   ddffa3b Erreur qui sera poussee



Perte volontaire :



&#x20;   git reset --hard HEAD\~1

&#x20;   git log --oneline -3



Résultat : d532efd a disparu de git log, comme s'il n'avait jamais existé :



&#x20;   efaf757 (HEAD -> master, origin/master) Revert "Erreur qui sera poussee"

&#x20;   ddffa3b Erreur qui sera poussee

&#x20;   0171cf6 Commit initial



Retrouvé avec :



&#x20;   git reflog



Résultat (extrait pertinent) :



&#x20;   efaf757 (HEAD -> master, origin/master) HEAD@{0}: reset: moving to HEAD\~1

&#x20;   d532efd HEAD@{1}: commit: Commit qui sera perdu

&#x20;   efaf757 (HEAD -> master, origin/master) HEAD@{2}: reset: moving to HEAD



Le reflog garde une trace de chaque déplacement de HEAD, y compris celui du commit "perdu" (d532efd) avant qu'il ne soit détaché de la branche. Récupération avec :



&#x20;   git reset --hard d532efd

&#x20;   git log --oneline -3



Résultat :



&#x20;   d532efd (HEAD -> master) Commit qui sera perdu

&#x20;   efaf757 (origin/master) Revert "Erreur qui sera poussee"

&#x20;   ddffa3b Erreur qui sera poussee



Le commit "perdu" redevient HEAD, entièrement récupéré.



\## Tableau récapitulatif



| Situation | Commande de défaite | Ce qu'elle touche |

|---|---|---|

| Modification non voulue | git checkout -- fichier | Répertoire de travail seul |

| Add de trop | git restore --staged fichier | Index seul (fait redescendre vers le répertoire de travail) |

| Commit de trop | git reset --soft HEAD\~1 | Dépôt (retire le commit), garde le contenu indexé |

| Commit poussé à annuler | git revert HEAD | Crée un nouveau commit, n'efface rien dans l'historique partagé |

| Travail en cours à mettre de côté | git stash / git stash pop | Range et restaure l'état complet (index + répertoire de travail) |

| Commit perdu à retrouver | git reflog puis git reset --hard <hash> | Retrouve un commit détaché grâce au journal des déplacements de HEAD |



\## Conclusion



Chacune des six situations correspond à un endroit précis où l'erreur peut se loger (répertoire de travail, index, dépôt local, dépôt distant, ou une pile de côté), et chacune a sa commande de défaite propre — aucune commande unique ne les couvre toutes. La différence la plus importante est entre reset (qui réécrit l'historique local, à n'utiliser que sur du non partagé) et revert (qui ajoute un commit correctif, seul outil sûr une fois qu'un commit a été poussé) : confondre les deux sur du code déjà partagé est exactement ce que le chapitre met en garde de ne jamais faire.

