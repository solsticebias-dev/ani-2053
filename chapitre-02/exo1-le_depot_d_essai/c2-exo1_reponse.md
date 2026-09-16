\# Exercice 1 — Le dépôt d'essai



\## Commandes lancées et sorties obtenues



Dépôt créé dans un dossier séparé, dédié à l'expérimentation (C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai), distinct des dépôts Nkentseu et ani-2053.



\### Initialisation



&#x20;   git init



Résultat :



&#x20;   Initialized empty Git repository in C:/Users/anais/OneDrive/Desktop/depot-essai/.git/



\### Premier commit



&#x20;   git add fichier1.txt

&#x20;   git commit -m "Ajout du premier fichier"



Résultat :



&#x20;   \[master (root-commit) 3e73a54] Ajout du premier fichier

&#x20;    1 file changed, 1 insertion(+)

&#x20;    create mode 100644 fichier1.txt



\### Deuxième commit



&#x20;   git add fichier2.txt

&#x20;   git commit -m "Ajout du deuxième fichier"



Résultat :



&#x20;   \[master c12f9dc] Ajout du deuxième fichier

&#x20;    1 file changed, 1 insertion(+)

&#x20;    create mode 100644 fichier2.txt



\### Troisième commit



&#x20;   git add fichier3.txt

&#x20;   git commit -m "Ajout du troisième fichier"



Résultat :



&#x20;   \[master 1080c36] Ajout du troisième fichier

&#x20;    1 file changed, 1 insertion(+)

&#x20;    create mode 100644 fichier3.txt



\### Historique en une ligne par commit



&#x20;   git log --oneline



Résultat :



&#x20;   1080c36 (HEAD -> master) Ajout du troisième fichier

&#x20;   c12f9dc Ajout du deuxième fichier

&#x20;   3e73a54 Ajout du premier fichier



\### Graphe



&#x20;   git log --oneline --graph --all



Résultat :



&#x20;   \* 1080c36 (HEAD -> master) Ajout du troisième fichier

&#x20;   \* c12f9dc Ajout du deuxième fichier

&#x20;   \* 3e73a54 Ajout du premier fichier



\## Remarque honnête



Les fichiers ont été créés vides : la commande prévue ("texte" | Out-File -FilePath fichierX.txt) a été coupée en deux lors de la frappe, si bien que seule la partie Out-File -FilePath fichierX.txt s'est exécutée, sans contenu à écrire. Cela n'affecte pas l'objectif de l'exercice, qui porte sur la structure des commits et de l'historique, pas sur le contenu des fichiers — mais je le signale plutôt que de le passer sous silence.



\## Lecture du graphe



Les trois commits (3e73a54, c12f9dc, 1080c36) sont alignés verticalement avec un seul astérisque par ligne, sans branchement ni fusion : c'est un graphe strictement linéaire, cohérent avec le modèle du cours ("chacun pointe vers son parent"). HEAD -> master indique que la branche master pointe actuellement sur le commit le plus récent (1080c36), qui est celui affiché en haut de git log car l'historique se lit du plus récent au plus ancien.



\## Conclusion



Trois commits successifs sur une branche unique produisent un historique et un graphe identiques en forme : une simple chaîne, chaque commit ayant exactement un parent (sauf le premier, 3e73a54, qui n'en a aucun — c'est un root-commit, comme l'indique Git lui-même dans le message du premier commit). Le graphe ne devient intéressant visuellement qu'en présence de branches ou de fusions, ce que cet exercice, volontairement simple, ne produit pas encore.

