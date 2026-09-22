\# Exercice 10 — Fusionner ou rejouer



\## Préparation : la même intégration en deux exemplaires



Une branche demo-base (avec un commit propre à elle, base-file.txt) et une branche demo-feature créée à partir d'elle (avec deux commits propres à elle, feature-file.txt) ont divergé, dans un fichier différent chacune pour isoler la comparaison de toute question de conflit de contenu. Chaque paire a été dupliquée pour tester séparément les deux méthodes d'intégration à partir du même point de départ exact.



\## Méthode 1 — La fusion (merge)



&#x20;   git checkout demo-base-merge

&#x20;   git merge demo-feature-merge --no-edit



Résultat :



&#x20;   Merge made by the 'ort' strategy.

&#x20;    feature-file.txt | 2 ++

&#x20;    1 file changed, 2 insertions(+)

&#x20;    create mode 100644 feature-file.txt



Graphe obtenu :



&#x20;   \*   3277941 (HEAD -> demo-base-merge) Merge branch 'demo-feature-merge' into demo-base-merge

&#x20;   |\\

&#x20;   | \* 6aa0a8f (demo-feature-merge, demo-feature) Completer feature-file

&#x20;   | \* cd54567 Ajouter feature-file

&#x20;   \* | 158e7f6 (demo-base) Ajouter base-file sur demo-base

&#x20;   |/

&#x20;   \* 400c5cd (master) Ajouter setting\_seize sur master

&#x20;   ...



\## Méthode 2 — Le rejeu (rebase)



&#x20;   git checkout demo-feature-rebase

&#x20;   git rebase demo-base-rebase

&#x20;   git checkout demo-base-rebase

&#x20;   git merge demo-feature-rebase --ff-only



Résultat :



&#x20;   Successfully rebased and updated refs/heads/demo-feature-rebase.

&#x20;   ...

&#x20;   Updating 158e7f6..a23f01d

&#x20;   Fast-forward

&#x20;    feature-file.txt | 2 ++

&#x20;    1 file changed, 2 insertions(+)

&#x20;    create mode 100644 feature-file.txt



Graphe obtenu :



&#x20;   \* a23f01d (HEAD -> demo-base-rebase, demo-feature-rebase) Completer feature-file

&#x20;   \* 8f1d596 Ajouter feature-file

&#x20;   \* 158e7f6 (demo-base) Ajouter base-file sur demo-base

&#x20;   \* 400c5cd (master) Ajouter setting\_seize sur master

&#x20;   ...



\## Comparaison des deux graphes



\*\*Fusion\*\* : trois commits visibles pour "Ajouter/Completer feature-file" plus un commit de fusion (3277941) qui a deux parents (158e7f6 et 6aa0a8f). L'historique garde la trace exacte de la divergence : on voit clairement que demo-base et demo-feature ont avancé en parallèle avant de se rejoindre. Les empreintes des deux commits d'origine (cd54567, 6aa0a8f) restent inchangées.



\*\*Rejeu\*\* : une ligne strictement droite. Les commits "Ajouter feature-file" et "Completer feature-file" existent toujours, mais avec de nouvelles empreintes (8f1d596 et a23f01d, différentes de cd54567 et 6aa0a8f) : ce sont des copies rejouées par-dessus demo-base, pas les commits originaux. Aucune trace de la branche parallèle ne subsiste dans le graphe ; on dirait que le travail a été fait directement après base-file.txt, dans l'ordre.



\## Ce que le cours dit de cette différence



Le tableau du chapitre résume exactement ce qui vient d'être observé :



| | merge | rebase |

|---|---|---|

| Ce qu'il fait | un commit à deux parents | rejoue vos commits par-dessus |

| L'histoire | fidèle, avec ses branches | linéaire, plus lisible |

| Les empreintes | inchangées | toutes recalculées |



Les empreintes recalculées sont visibles ici concrètement : 8f1d596 ≠ cd54567 alors que le contenu du commit ("Ajouter feature-file") est identique — c'est la preuve directe que rebase ne déplace pas un commit, il en crée un nouveau avec le même contenu mais un parent différent.



\## Lequel je préfère lire, et pourquoi



Je préfère lire le graphe du \*\*rejeu\*\*, pour cet exemple précis. La ligne droite dit immédiatement "d'abord base-file, puis feature-file, dans cet ordre" sans qu'il faille interpréter un point de fusion. Sur une intégration aussi simple (deux branches courtes, aucun conflit), la fidélité historique du merge (montrer que le travail s'est fait en parallèle) n'apporte pas d'information utile à un lecteur futur — ça reste un détail d'exécution, pas une décision de conception.



Mais je nuance : le cours est clair sur la limite de cette préférence — "on ne rejoue jamais des commits que quelqu'un d'autre a déjà récupérés." Cette préférence pour la lisibilité du rebase ne vaut que pour du travail encore local et non partagé (exactement le cas ici, une branche que personne d'autre n'a récupérée). Sur du travail déjà poussé et visible par d'autres, comme démontré à l'exercice 8, le choix n'est même plus une question de goût : c'est merge (ou revert) obligatoirement, jamais rebase.



\## Conclusion



Sur une branche locale, courte et non partagée, le rejeu produit un historique plus simple à lire d'un coup d'œil, au prix de perdre la trace exacte de la parallélisation du travail — un compromis que je trouve favorable dans ce cas précis. Le facteur qui devrait vraiment décider entre les deux n'est cependant pas une préférence de lecture, mais une question factuelle : ce travail a-t-il déjà été partagé avec quelqu'un d'autre ? Si oui, rebase est exclu, quelle que soit la lisibilité qu'il offrirait.

