\# Exercice 3 — Le module seul



\## Commande lancée



jenga build --project NKMath --config Debug



\## Ordre de construction affiché par Jenga



Build Order (5 projects):

&#x20; 1. NKPlatform \[STATIC\_LIB]

&#x20; 2. NKCore \[STATIC\_LIB] (depends: NKPlatform)

&#x20; 3. NKMemory \[STATIC\_LIB] (depends: NKCore, NKPlatform)

&#x20; 4. NKContainers \[STATIC\_LIB] (depends: NKCore, NKMemory, NKPlatform)

&#x20; 5. NKMath \[STATIC\_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)



\## Arbre (le premier construit en bas, NKMath en haut)



&#x20;       NKMath

&#x20;          |

&#x20;    NKContainers

&#x20;          |

&#x20;      NKMemory

&#x20;          |

&#x20;       NKCore

&#x20;          |

&#x20;     NKPlatform



\## Explication



Chaque module ne dépend que des modules construits avant lui, jamais de ceux construits après. NKPlatform est construit en premier car il ne dépend de rien : c'est le socle. Chaque étage suivant (NKCore, puis NKMemory, puis NKContainers) ajoute une dépendance de plus vers le bas, jusqu'à NKMath qui dépend des quatre modules précédents. Cet ordre n'est pas écrit à la main : il est calculé automatiquement par Jenga à partir des dependson déclarés dans chaque fichier .jenga. Le temps total de construction (15,84 s pour 5 projets, dont 6,32 s rien que pour NKContainers avec ses 43 fichiers) montre aussi que le coût n'est pas réparti également entre les couches.

