\# Démo 1 — Le graphe au tableau



\## Commande utilisée



&#x20;   git --no-pager log --graph --oneline 7c3e84a0\~5..7c3e84a0



\## Sortie de git log --graph



&#x20;   \*   7c3e84a0 Merge remote-tracking branch 'origin/main'

&#x20;   |\\

&#x20;   | \* cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio synthetise (#84)

&#x20;   \* 4c7d66b5 Distribution : refuser de livrer un exe dont une DLL importee manque

&#x20;   \* ad0779cb NKCode : runtime MinGW en statique — l'exe ne depend plus du msys64 du testeur

&#x20;   \* 5fc605de Vulkan : la garde headless existait UNIQUEMENT sous Windows -- segfault sur les trois dorsales Linux

&#x20;   \* 56b0ed67 wiki : les mesures Vulkan sont CONFIRMEES par contre-verification -- et un 5e piege, celui qui a permis le desaccord



\## Dessin du graphe (tel qu'il serait tracé au tableau)



&#x20;   56b0ed67 ─── 5fc605de ─── ad0779cb ─── 4c7d66b5 ──┐

&#x20;                                                       │

&#x20;                                                       ▼

&#x20;                                                   7c3e84a0  (fusion, 2 parents)

&#x20;                                                       ▲

&#x20;                                                       │

&#x20;                                                   cc41ca45  (GemCrush, branche parallele)



Ou, dans le style ASCII habituel du tableau :



&#x20;   \*   7c3e84a0  <- fusion

&#x20;   |\\

&#x20;   | \* cc41ca45  <- branche GemCrush

&#x20;   \* | 4c7d66b5

&#x20;   |/

&#x20;   \* ad0779cb

&#x20;   \* 5fc605de

&#x20;   \* 56b0ed67



\## Faire correspondre les deux



\*\*Le point de divergence\*\* : entre 56b0ed67 et la suite, la ligne d'historique reste unique jusqu'à 4c7d66b5. Le vrai point de divergence n'est pas visible dans cette fenêtre de 5 commits (cc41ca45 a été développé ailleurs, sur une autre ligne, avant d'être rapatriée ici) — c'est une limite honnête de cette commande : --graph avec une plage aussi courte ne montre le début d'une branche que si son premier commit tombe dans la plage demandée. Ce qu'on voit à coup sûr, en revanche, c'est le résultat de la divergence : deux lignes parallèles juste avant la fusion (le | et le \* côte à côte sur la ligne de 4c7d66b5 / cc41ca45), signe que ces deux commits n'ont pas le même parent immédiat.



\*\*La fusion\*\* : 7c3e84a0 est le seul commit de cette plage dont le symbole \*   est suivi d'un |\\ — c'est la notation de git log --graph pour "ce commit a deux parents". Dans le dessin au tableau, ce sont les deux flèches qui convergent vers un même point : l'une venant de 4c7d66b5 (la ligne principale), l'autre venant de cc41ca45 (la branche GemCrush).



\*\*Les deux parents confirmés autrement\*\* : git show --stat 7c3e84a0 (utilisé à l'exercice 3) affichait explicitement Merge: 4c7d66b5 cc41ca45 sur sa première ligne — la preuve indépendante, hors du graphe ASCII, que ce commit a bien ces deux parents précis, ceux-là mêmes que le graphe dessine convergents.



\## Ce que ce graphe illustre du modèle du cours



Le cours dit : "les commits forment un graphe... chacun pointe vers son parent, les fusions en ont deux." Ce petit exemple réel le montre à l'échelle d'un seul commit de fusion : cc41ca45 a été développé indépendamment (sur une branche dont on ne voit ici que ce commit), pendant que 56b0ed67 → 5fc605de → ad0779cb → 4c7d66b5 avançait de son côté sur une autre ligne. 7c3e84a0 est le point où l'historique cesse d'être une simple liste et devient réellement un graphe : c'est le seul commit de toute cette fenêtre à avoir plus d'un parent.



\## Conclusion



Le graphe ASCII de git log --graph et le dessin au tableau se correspondent trait pour trait une fois qu'on sait lire les symboles : chaque \* est un commit, chaque colonne verticale une ligne de développement distincte, et un nœud où plusieurs colonnes convergent (|\\ suivi d'un point de jonction) est une fusion à deux parents. Sur ce dépôt réel, la fusion visible (7c3e84a0) correspond exactement à l'intégration du jeu GemCrush dans main, déjà analysée à l'exercice 3 pour la qualité de son message.

