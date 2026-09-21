\# Exercice 7 — Le conflit qui n'en est pas un



\## Objectif



L'objectif de cet exercice est de montrer que Git peut fusionner automatiquement les modifications de deux personnes lorsqu'elles travaillent sur le même fichier mais sur des zones différentes.



Deux branches ont été utilisées pour simuler le travail de deux personnes :



\* `personne-a` a modifié la vitesse du moteur ;

\* `personne-b` a modifié le volume audio.



Les deux modifications concernent donc des lignes différentes du même fichier `exemple.txt`.



\---



\## 1. Création du fichier commun



Un fichier `exemple.txt` a d'abord été créé avec plusieurs sections afin de disposer de zones suffisamment éloignées pour les deux modifications.



La version initiale contenait notamment :



```text

\## Moteur

Vitesse = 100

Gravite = 9.81



\## Affichage

Largeur = 800

Hauteur = 600



\## Audio

Volume = 80

Musique = active

```



Cette version initiale a été enregistrée dans un premier commit :



```text

Ajouter le fichier de démonstration

```



\---



\## 2. Modification effectuée par la personne A



La branche `personne-a` a été créée à partir de l'état initial.



La personne A a uniquement modifié la section `Moteur` :



```diff

\- Vitesse = 100

\+ Vitesse = 200

```



La modification a ensuite été enregistrée dans le commit :



```text

Modifier la vitesse du moteur

```



La commande `git diff` a permis de vérifier que seule cette partie du fichier avait été modifiée.



\---



\## 3. Modification effectuée par la personne B



À partir de l'état initial, une seconde branche appelée `personne-b` a été créée.



La personne B a modifié une autre partie du même fichier, dans la section `Audio` :



```diff

\- Volume = 80

\+ Volume = 100

```



Cette modification a été enregistrée dans le commit :



```text

Augmenter le volume audio

```



Ainsi, les deux personnes ont bien travaillé sur le même fichier, mais elles n'ont pas modifié les mêmes lignes.



\---



\## 4. Fusion des deux modifications



La branche `personne-a` a ensuite été fusionnée dans `personne-b` avec :



```bash

git merge personne-a

```



La fusion s'est effectuée automatiquement.



Le terminal a notamment indiqué :



```text

Auto-merging exemple.txt

Merge made by the 'ort' strategy.

```



Aucun message `CONFLICT` n'est apparu.



Cela montre que Git a pu déterminer automatiquement que les deux modifications pouvaient être conservées.



\---



\## 5. Résultat obtenu après la fusion



Après la fusion, le contenu de `exemple.txt` était :



```text

\# Projet de démonstration



\## Configuration

Nom = ProjetGit

Version = 1.0



\## Moteur

Vitesse = 200

Gravite = 9.81



\## Affichage

Largeur = 800

Hauteur = 600



\## Audio

Volume = 100

Musique = active

```



On constate que les deux modifications sont présentes simultanément :



\* `Vitesse` est passée de `100` à `200` ;

\* `Volume` est passé de `80` à `100`.



Git n'a donc pas demandé de choisir entre les deux versions.



\---



\## 6. Vérification de l'absence de conflit



La commande :



```bash

git status

```



a indiqué que l'arbre de travail était propre :



```text

On branch personne-b

nothing to commit, working tree clean

```



Une recherche des marqueurs de conflit dans le fichier n'a également rien retourné :



```text

<<<<<<<

=======

>>>>>>>

```



Aucun de ces marqueurs n'est présent dans le fichier final.



\---



\## 7. Historique obtenu



La commande :



```bash

git log --oneline --graph --decorate --all

```



a permis de visualiser les deux branches et leur fusion.



L'historique montre que les deux personnes sont parties du même état initial, ont réalisé leurs modifications séparément, puis que Git les a réunies lors de la fusion.



\---



\## Conclusion



Cette expérience montre qu'un conflit Git ne se produit pas simplement parce que deux personnes modifient le même fichier.



Le conflit apparaît lorsque Git ne peut pas déterminer automatiquement comment combiner les modifications, notamment lorsque les mêmes lignes ou des zones qui se chevauchent sont modifiées.



Dans cet exercice, les deux personnes ont modifié des zones éloignées du même fichier. Git a donc pu conserver les deux changements et effectuer la fusion automatiquement.



Le résultat final contient bien les modifications de la personne A et celles de la personne B, sans intervention manuelle pour résoudre un conflit.



