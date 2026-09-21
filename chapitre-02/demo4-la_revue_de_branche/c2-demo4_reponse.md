\# Démo 4 — La revue de branche



\## Contexte



Faute d'un deuxième groupe réel avec qui échanger une branche, cette revue porte sur une branche que j'ai construite moi-même pour cette démonstration (demo-revue), avec des défauts volontaires et réalistes plutôt qu'un exemple inventé abstraitement — dans le même esprit que la simulation de l'exercice 13.



\## Ce qui a été relu



&#x20;   git log --oneline main..demo-revue

&#x20;   ad3171c (HEAD -> demo-revue) ajout config

&#x20;   e949c0b Ajouter la reponse et corriger des trucs dans les notes

&#x20;   3e3b601 update



&#x20;   git diff main demo-revue --stat

&#x20;    chapitre-02/demo4-la\_revue\_de\_branche/c2-demo4\_reponse.md    | 1 +

&#x20;    chapitre-02/demo4-la\_revue\_de\_branche/config-personnelle.txt | 1 +

&#x20;    chapitre-02/demo4-la\_revue\_de\_branche/notes-brouillon.md     | 2 ++

&#x20;    3 files changed, 4 insertions(+)



\## Ce que la branche fait



Elle ajoute trois fichiers dans un nouveau dossier chapitre-02/demo4-la\_revue\_de\_branche/ : un brouillon de réponse (c2-demo4\_reponse.md), un fichier de notes de travail (notes-brouillon.md), et un fichier de configuration (config-personnelle.txt) contenant un chemin local propre à la machine de l'auteur.



\## Les commits sont-ils lisibles ?



Non, aucun des trois ne respecte les règles du chapitre :



\- 3e3b601 "update" — ne dit ni le quoi ni le pourquoi. Message générique interdit par le cours ("un dépôt dont les messages disent fix, update ou wip vous laisse seul devant le diff").

\- e949c0b "Ajouter la reponse et corriger des trucs dans les notes" — contient littéralement "et", signe de deux sujets mélangés dans un seul commit (règle du cours : "si votre message contient et aussi, faites deux commits"). Le diff confirme : ce commit touche à la fois c2-demo4\_reponse.md (nouveau fichier, sujet 1) et notes-brouillon.md (modification sans rapport, sujet 2).

\- ad3171c "ajout config" — dit le quoi de façon minimale, mais aucun pourquoi, et ne précise pas qu'il s'agit d'un fichier de réglages personnels.



\## Ce qui manque



\- Aucun message n'explique pourquoi ces fichiers sont ajoutés dans le contexte de l'exercice (quel exercice, quel objectif).

\- Le fichier c2-demo4\_reponse.md est un brouillon vide de contenu réel ("# Brouillon" seul) — la branche ne livre pas un travail terminé.

\- Aucune trace d'une relecture avant ces commits (pas de second regard visible dans l'historique).



\## Ce qui ne devrait pas y être



config-personnelle.txt est le défaut le plus sérieux de cette branche. Il contient un chemin local propre à une seule machine (C:\\Users\\anais\\reglages\_prives) — exactement le genre de fichier que le chapitre classe parmi ce qu'on ne commite jamais : "les fichiers produits par la construction, les binaires lourds, les réglages personnels de votre éditeur". Ce n'est pas un secret au sens strict (pas de mot de passe), mais c'est un réglage personnel qui n'a rien à faire dans l'historique partagé de l'équipe : il polluerait le dépôt de tous les autres membres s'il était fusionné.



notes-brouillon.md mélangé dans le même commit que la réponse officielle est aussi un problème : un fichier de travail temporaire ("a nettoyer plus tard") ne devrait pas être commité en même temps qu'une livraison, ni d'ailleurs être présent du tout dans l'historique partagé sans discussion préalable de l'équipe.



\## Verdict de la revue



Cette branche ne devrait pas être fusionnée en l'état. Trois actions demandées avant fusion :



1\. Retirer config-personnelle.txt de l'historique (pas seulement du répertoire de travail — il faudrait un nouveau commit qui le supprime, ou reconstruire la branche proprement si elle n'a pas encore été partagée).

2\. Réécrire les messages de commit pour qu'ils disent le quoi et le pourquoi, un seul sujet chacun.

3\. Séparer le commit e949c0b en deux : un pour la réponse, un pour les notes de travail (ou retirer les notes de travail du dépôt partagé).



\## À discuter à quatre



\- Faut-il un fichier .gitignore dans ani-2053 pour empêcher ce genre de fichier de réglages personnels d'être ajouté par accident (git status l'aurait quand même proposé, mais un motif reconnu comme config-personnelle\* dans .gitignore l'aurait explicitement écarté) ?

\- Qui, dans l'équipe, doit relire une branche avant fusion vers main quand il n'y a que deux personnes disponibles (cf. règle du dépôt rédigée à l'exercice 12) ?

\- Est-ce que "update" et "ajout config" auraient dû être bloqués avant même d'arriver en revue, par exemple par une relecture personnelle rapide juste avant de pousser ?

