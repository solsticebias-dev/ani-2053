\# Démo 3 — Ce que le reflog sauve



\## Créer un travail réel à perdre



&#x20;   New-Item -ItemType Directory -Path "travail-important" -Force

&#x20;   Set-Content -Path "travail-important\\rapport.txt" -Value "Analyse complete : 3 semaines de travail"

&#x20;   git add travail-important

&#x20;   git commit -m "Ajouter le rapport d'analyse (3 semaines de travail)"

&#x20;   git log --oneline -3



Résultat :



&#x20;   \[master b0a304f] Ajouter le rapport d'analyse (3 semaines de travail)

&#x20;    1 file changed, 1 insertion(+)

&#x20;    create mode 100644 travail-important/rapport.txt



&#x20;   b0a304f (HEAD -> master) Ajouter le rapport d'analyse (3 semaines de travail)

&#x20;   0d5bfc1 Retirer le gros fichier aleatoire

&#x20;   e1cf680 Ajouter un gros fichier aleatoire par erreur



\## Constater ce qui existe, avant la destruction



&#x20;   Get-ChildItem travail-important

&#x20;   -a----  rapport.txt (42 octets)



&#x20;   Get-Content "travail-important\\rapport.txt"

&#x20;   Analyse complete : 3 semaines de travail



Le commit et le fichier existent tous les deux, confirmés indépendamment.



\## Destruction volontaire



&#x20;   git reset --hard HEAD\~1

&#x20;   git log --oneline -3



Résultat :



&#x20;   HEAD is now at 0d5bfc1 Retirer le gros fichier aleatoire



&#x20;   0d5bfc1 (HEAD -> master) Retirer le gros fichier aleatoire

&#x20;   e1cf680 Ajouter un gros fichier aleatoire par erreur

&#x20;   517277f Retirer le gros fichier



Le commit b0a304f a complètement disparu de git log, comme s'il n'avait jamais existé.



\## Constater la perte



&#x20;   Test-Path travail-important

&#x20;   False



&#x20;   Get-ChildItem travail-important -ErrorAction SilentlyContinue

&#x20;   (aucun resultat)



Le dossier travail-important et son fichier rapport.txt ont disparu du disque, pas seulement de l'historique : reset --hard réécrit aussi le répertoire de travail pour qu'il corresponde au commit ciblé. Perte constatée à deux niveaux (historique et fichiers réels).



\## Retrouver par le reflog



&#x20;   git reflog



Résultat (extrait pertinent) :



&#x20;   0d5bfc1 (HEAD -> master) HEAD@{0}: reset: moving to HEAD\~1

&#x20;   b0a304f HEAD@{1}: commit: Ajouter le rapport d'analyse (3 semaines de travail)

&#x20;   0d5bfc1 (HEAD -> master) HEAD@{2}: checkout: moving from conflit-a to master

&#x20;   ...



Le reflog garde une trace de chaque déplacement de HEAD, y compris le commit b0a304f juste avant qu'il ne soit détaché par le reset. Contrairement à git log, le reflog n'affiche pas l'historique des ancêtres d'un commit : il affiche l'historique des positions successives de HEAD sur cette machine, ce qui inclut donc des commits qu'aucune branche ne pointe plus.



Note pratique : le reflog s'affiche par défaut dans le pager (less), qui bloque le terminal en attente d'une touche (le : en bas de l'écran). Appuyer sur q permet de revenir à l'invite normale sans interrompre quoi que ce soit.



\## Récupération



&#x20;   git reset --hard b0a304f

&#x20;   git log --oneline -3

&#x20;   Get-Content "travail-important\\rapport.txt"



Résultat :



&#x20;   HEAD is now at b0a304f Ajouter le rapport d'analyse (3 semaines de travail)



&#x20;   b0a304f (HEAD -> master) Ajouter le rapport d'analyse (3 semaines de travail)

&#x20;   0d5bfc1 Retirer le gros fichier aleatoire

&#x20;   e1cf680 Ajouter un gros fichier aleatoire par erreur



&#x20;   Analyse complete : 3 semaines de travail



Le commit est de retour à sa place exacte, et le fichier rapport.txt a réapparu sur le disque avec son contenu original intact.



\## Pourquoi ça marche



Le cours l'explique en un principe simple : "un commit ne change jamais." Le reset --hard n'a pas détruit le commit b0a304f, il a seulement déplacé le pointeur de la branche master ailleurs (vers 0d5bfc1) et réécrit le répertoire de travail en conséquence. Le commit lui-même, avec tout son contenu, restait entier dans .git/objects — simplement plus référencé par aucune branche, donc invisible pour git log et pour un git status ordinaire. Le reflog est la liste des repères que Git garde en plus des branches, précisément pour ce genre de situation : il permet de retrouver un commit qu'on a perdu de vue, tant que le ramasse-miettes de Git ne l'a pas encore supprimé pour de bon (ce qui n'arrive qu'après un certain délai, jamais immédiatement).



\## Conclusion



Cette démonstration illustre concrètement la différence entre "supprimer une référence" et "supprimer des données" : reset --hard a fait disparaître toute trace visible du travail (aucun commit dans le log, aucun fichier sur le disque), et pourtant rien n'était réellement perdu. Le reflog est le filet de sécurité qui rend cette distinction utile en pratique plutôt que seulement théorique — trois semaines de travail (simulées ici en 30 secondes) récupérées entièrement, sans sauvegarde externe, juste en sachant que Git garde une trace de tout ce que HEAD a pointé, même après.

