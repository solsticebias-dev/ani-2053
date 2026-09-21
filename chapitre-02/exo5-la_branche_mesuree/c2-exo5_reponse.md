\# Exercice 5 — La branche mesurée



\## Mesure avant les commits



Avant de créer la branche et les trois commits, la taille du répertoire `.git` était de \*\*31,76 Ko\*\*.



\## Création de la branche



J'ai créé la branche `ma-branche` puis je me suis placé dessus.



Une branche Git n'est pas une copie du dépôt. C'est simplement un nom qui pointe vers un commit.



\## Les trois commits



J'ai réalisé trois commits sur la branche `ma-branche` :



\* `4267eee` — `Ajouter setting\_eleven`

\* `1754304` — `Ajouter setting\_twelve`

\* `93ea191` — `Ajouter setting\_thirteen`



Chaque commit ajoute une nouvelle ligne dans le fichier `config.txt`.



\## Mesure après les commits



Après les trois commits, la taille du répertoire `.git` était de \*\*34,47 Ko\*\*.



L'augmentation est donc :



```text

34,47 Ko - 31,76 Ko = 2,71 Ko

```



Le dépôt a donc gagné environ \*\*2,71 Ko\*\* sur le disque.



\## Explication



La création de la branche n'a pas entraîné une copie complète du dépôt, car une branche Git est seulement un pointeur vers un commit.



L'augmentation de la taille provient des trois nouveaux commits et des objets Git nécessaires pour enregistrer les nouveaux états du projet.



Git réutilise les objets déjà présents lorsqu'ils sont identiques. Il ne recopie donc pas inutilement tout le projet à chaque commit.



Ainsi, les trois commits ont augmenté la taille du dépôt de \*\*2,71 Ko\*\*, tandis que la création de la branche elle-même n'a pratiquement pas ajouté de données.



