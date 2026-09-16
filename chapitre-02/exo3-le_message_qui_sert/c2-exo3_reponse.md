\# Exercice 3 — Le message qui sert



\## Trois commits jugés (dépôt Nkentseu)



\### Commit 1 — b4cdf3cc



&#x20;   wiki pieges : l avertissement sur CreateWithFallback est MAINTENU -- mesure a l appui -- et gagne le corollaire sur les bancs



Dit-il ce qu'il fait ? Oui : il annonce clairement qu'un avertissement (CreateWithFallback) est maintenu, pas retiré.

Dit-il pourquoi ? Oui, en partie : "mesure a l appui" indique que la décision repose sur une vérification, pas une impression. Le "corollaire sur les bancs" laisse deviner qu'une conséquence a été tirée pour les bancs de tests, sans détailler laquelle en une ligne — acceptable pour un sujet court.

Un seul sujet ? Oui, un seul fil : le statut de cet avertissement précis et sa conséquence directe.

Jugement : message fort. Il informe (quoi), justifie (pourquoi : mesuré, pas supposé), et reste sur un seul sujet, conformément aux quatre règles du cours.



\### Commit 2 — 5fc605de



&#x20;   Vulkan : la garde headless existait UNIQUEMENT sous Windows -- segfault sur les trois dorsales Linux



Dit-il ce qu'il fait ? Oui : une garde (protection défensive) pour le mode headless de Vulkan.

Dit-il pourquoi ? Oui, explicitement : elle n'existait que sous Windows, ce qui causait un segfault (plantage) sur les trois backends Linux. C'est exactement la logique attendue par le cours ("le pourquoi n'est nulle part ailleurs" que dans le message).

Un seul sujet ? Oui : un seul bug, une seule cause, une seule plateforme concernée dans la correction.

Jugement : message fort, aussi bon que le premier. Le symptôme (segfault) et sa portée (trois dorsales Linux) sont assez précis pour qu'un lecteur, deux ans plus tard, comprenne l'urgence et la portée sans ouvrir le diff.



\### Commit 3 — 7c3e84a0



&#x20;   Merge remote-tracking branch 'origin/main'



Dit-il ce qu'il fait ? Non. C'est le message par défaut généré automatiquement par Git lors d'une fusion, jamais réécrit par l'auteur.

Dit-il pourquoi ? Non, aucune trace du pourquoi.

Un seul sujet ? Impossible à dire depuis le message seul — et c'est justement le problème. En vérifiant avec git show --stat 7c3e84a0, cette fusion a en réalité introduit l'intégralité du jeu GemCrush : 21 fichiers, 7397 lignes ajoutées (moteur du jeu, plateau, HUD, écrans, audio, art, niveaux, et l'entrée .jenga dans le workspace).

Jugement : message le plus faible des trois, de loin. C'est exactement le cas que le cours dénonce : "un dépôt dont les messages disent fix, update ou wip vous laisse seul devant le diff." Ici, ce n'est même pas "wip", c'est le message technique de Git lui-même, qui ne rapporte aucune information sur le contenu humain du changement — alors que ce changement est loin d'être anodin : c'est l'arrivée complète d'une application.



\## Réécriture du message le plus faible



Message original :



&#x20;   Merge remote-tracking branch 'origin/main'



Message réécrit, fidèle à ce que git show --stat a révélé :



&#x20;   Fusionner GemCrush dans main



&#x20;   Le jeu GemCrush (moteur de plateau, detection de correspondances,

&#x20;   HUD, ecrans, art et audio) rejoint le workspace principal :

&#x20;   21 fichiers, 7397 lignes. Ajoute aussi l'entree GemCrush au

&#x20;   Nkentseu.jenga racine et le workflow CI dedie

&#x20;   (.github/workflows/build-gemcrush.yml).



\## Conclusion



Les deux premiers messages jugés respectent les quatre règles du cours (sujet court à l'impératif, ligne vide, corps qui explique le pourquoi, un seul sujet) et permettraient à quelqu'un de comprendre l'intention du changement sans ouvrir le diff. Le troisième est l'exemple exact de ce que le cours met en garde : un message généré automatiquement par un outil, jamais retravaillé par l'auteur, qui ne porte aucune information utile — alors que le changement qu'il décrit (7397 lignes, un jeu entier) méritait justement d'être documenté.

