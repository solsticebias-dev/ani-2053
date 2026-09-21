\# Exercice 12 — La règle du dépôt



Règles Git du projet — équipe de 4 personnes

Applicables dès demain.



\## 1. Nommage des branches



\- main : la branche principale. Toujours stable, toujours compilable. Personne n'y travaille directement.

\- Une branche par tâche, nommée <type>/<sujet-court> :

&#x20; - feature/inventaire-joueur

&#x20; - fix/crash-au-demarrage

&#x20; - wiki/notes-reunion

\- Pas de branche personnelle générique du type personne-a ou personne-b qui vit plusieurs semaines et accumule tout le travail d'une personne : ça produit exactement ce que le cours met en garde ("une branche vieille de trois semaines produit un conflit de trois semaines"). Une branche = une tâche, courte, puis supprimée après fusion dans main.



\## 2. Contenu d'un commit



\- Un commit, un sujet. Si le message contient "et aussi", c'est deux commits.

\- Message : une ligne de sujet courte à l'impératif ("Corriger le crash au chargement"), puis une ligne vide, puis un corps qui dit le pourquoi (jamais "fix", "update", "wip" seuls).

\- On ne commit jamais un fichier qui ne compile pas, sciemment.

\- On ne commit jamais : fichiers produits par la construction (Build/, \*.exe, \*.lib), réglages personnels d'éditeur, secrets (clés, mots de passe). Un secret commité reste dans l'historique même après suppression — le seul remède est de le changer, pas de le retirer.



\## 3. Qui relit quoi



\- Toute fusion vers main passe par une pull request, jamais par un push direct.

\- Une pull request est relue par au moins une personne qui n'a pas écrit le code.

\- Celui qui relit vérifie trois choses : ça compile, ça répond au message du commit (pas plus, pas moins), et ça n'introduit rien de la liste interdite (section 4).

\- La personne qui a écrit le code ne s'auto-approuve jamais.



\## 4. Ce qui est interdit



\- git push --force sur main, jamais, sous aucun prétexte. Un push refusé (non-fast-forward) se résout par fetch puis intégration, jamais en écrasant le travail du serveur.

\- git rebase sur des commits déjà partagés (déjà poussés et récupérés par quelqu'un d'autre). Le rebase ne s'utilise que sur son propre travail local, pas encore partagé.

\- Résoudre un conflit en "collant" les deux versions sans les lire, ou en gardant sa propre version par réflexe sans comprendre pourquoi l'autre a écrit ce qu'elle a écrit.

\- Valider un conflit résolu sans reconstruire le projet avant. Un conflit résolu qui ne compile pas est un conflit non résolu.



\## 5. Quand quelqu'un casse la branche principale



1\. On ne panique pas et on ne push pas par-dessus en urgence : ça empire souvent les choses.

2\. La personne qui a cassé main (ou la première qui le remarque) prévient immédiatement les trois autres dans le canal du groupe.

3\. On répare avec git revert du commit fautif (jamais un reset --hard sur main, qui est déjà partagée) : ça ajoute un commit correctif sans réécrire l'historique que les autres ont déjà récupéré.

4\. Une fois main réparée et repoussée, chacun fait git pull avant de continuer son propre travail.

5\. On regarde ensemble, sans chercher de coupable, pourquoi la relecture (section 3) n'a pas intercepté le problème, et on ajuste la checklist de relecture si besoin.



\## Résumé en une phrase par section



Des branches courtes et nommées par tâche ; des commits qui ne parlent que d'un seul sujet ; personne ne fusionne son propre travail sans un second regard ; on ne réécrit jamais l'histoire du serveur ; et quand main casse, on répare en ajoutant un commit, pas en effaçant les autres.

