\# Exercice 9 — L'utilisateur avant le lecteur



Date de la session : 14 septembre 2026

Durée : un peu plus de 10 minutes

Application testée : NkRef (jenga run NkRef --config Debug)



\## Ce que NkRef fait (observations, sans avoir lu une ligne de code)



\- Un menu propose un thème sombre, désactivable pour repasser en thème clair.

\- Une option permet d'afficher ou de masquer une grille sur la zone de dessin.

\- Une option "toujours devant" existe dans le menu, mais je n'ai observé aucun effet visible en l'activant ou la désactivant.

\- Un curseur contrôle l'opacité de la fenêtre, entre un maximum (fenêtre pleinement visible) et un minimum proche de zéro. En diminuant l'opacité, on voit à travers la fenêtre ce qui se trouve derrière sur l'écran, un peu comme un calque : on peut dessiner par-dessus ce qu'on voit en transparence.

\- Une case "glisser le fond = fenêtre" existe, effet non identifié.

\- Un item de menu "Origine début" (raccourci Ctrl+P) existe, sans effet visible observé au clic.

\- Un outil crayon peut être activé ou désactivé, avec un choix de couleurs et un réglage d'épaisseur de trait de 1 à 24.

\- Le trait du crayon est lisse en ligne droite, mais devient irrégulier (crénelé) quand on dessine des courbes ou des cercles.

\- On peut annuler le dernier trait, ou effacer tous les traits d'un coup.

\- Un item "aucune image activée" existe dans le menu, mais je n'ai pas réussi à activer d'image.

\- Une section "gestes" liste : molette = zoom au curseur, espace + glisser = déplacer la vue (pan), Ctrl + glisser = dessiner un rectangle.

\- Un clic droit sur la zone de dessin ouvre un menu contextuel avec : Enregistrer (Ctrl+S), glisser le fond, déplacer la fenêtre, réduire les grandes images à l'import, afficher la grille, toujours devant, mode crayon.

\- Une petite fenêtre de "capacité" (opacité) apparaît avec des paliers en pourcentage (100 %, 70 %, 40 %) qui semblent piloter le même réglage que le curseur d'opacité.

\- J'ai écrit mon nom à la main avec le crayon directement sur la fenêtre, puis je l'ai effacé.

\- J'ai testé Enregistrer (Ctrl+S) : un fichier semble être créé, mais après avoir fermé NkRef, je n'ai pas réussi à le retrouver facilement via la recherche Windows, ni à l'ouvrir avec l'application : le système me propose d'autres logiciels (comme Photoshop) pour l'ouvrir, jamais NkRef lui-même.



\## Ce que j'aurais voulu qu'il fasse



\- Que "toujours devant" ait un effet clairement observable quand on l'active ou le désactive.

\- Voir exactement où se situe le minimum réel du curseur d'opacité : je ne suis pas sûr qu'il atteigne zéro, et quand le fond derrière la fenêtre est très clair (blanc), la transparence devient difficile à distinguer de l'opacité normale, ce qui rend le réglage peu lisible dans ce cas précis.

\- Comprendre à quoi sert la case "glisser le fond = fenêtre" — aucun changement visible constaté en la cochant ou la décochant.

\- Que "Origine début" fasse quelque chose de visible ou affiche un message expliquant son rôle.

\- Réussir à dessiner un rectangle avec Ctrl + glisser comme l'indique la liste des gestes — je n'ai obtenu aucune forme à l'écran en essayant.

\- Réussir à activer une image via l'item "aucune image activée" — je n'ai pas compris comment déclencher cette fonctionnalité.

\- Pouvoir retrouver et rouvrir facilement, depuis NkRef lui-même, un fichier enregistré avec Ctrl+S — actuellement, le fichier semble exister quelque part mais le système ne sait pas quel programme devrait l'ouvrir.

\- Une explication même minimale de ce à quoi sert l'application dans son ensemble : après dix minutes, je pense que c'est un outil de dessin en transparence par-dessus l'écran (une sorte de calque pour annoter ou dessiner sur ce qui est affiché ailleurs), mais je n'en suis pas certain — l'usage global reste flou sans documentation.



\## Conclusion de la session



L'idée la plus intéressante et la plus claire pour moi a été l'opacité de fenêtre combinée au crayon : dessiner tout en voyant ce qu'il y a derrière donne l'impression d'un calque posé sur l'écran. Plusieurs fonctions (toujours devant, glisser le fond, origine début, activer une image, dessiner des formes) existent dans les menus mais n'ont produit aucun effet observable pour moi en dix minutes d'utilisation sans lecture de code — ce qui suggère soit des fonctionnalités pas encore terminées, soit des interactions que je n'ai pas trouvées par moi-même. Cette liste sera relue au chapitre 16.

