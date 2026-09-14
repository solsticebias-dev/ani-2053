# Exercice 2 — Mesurer avant de croire

## Commandes lancées et sorties obtenues

Toutes les commandes suivantes ont été tapées en PowerShell depuis la racine du dépôt Nkentseu (C:\Users\anais\OneDrive\Desktop\Nkentseu).

### Fichiers .cpp et .h ensemble, hors dossier Build

    (Get-ChildItem -Recurse -Include *.cpp,*.h | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

Résultat : 4428

### Fichiers .cpp et .h ensemble, Build inclus (sans filtre)

    (Get-ChildItem -Recurse -Include *.cpp,*.h).Count

Résultat : 4428

### Fichiers .cpp seuls, hors Build

    (Get-ChildItem -Recurse -Include *.cpp | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

Résultat : 1637

### Fichiers .h seuls, hors Build

    (Get-ChildItem -Recurse -Include *.h | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

Résultat : 2792

### Lignes de code (.cpp + .h), hors Build

    (Get-ChildItem -Recurse -Include *.cpp,*.h | Where-Object { $_.FullName -notmatch '\\Build\\' } | Get-Content | Measure-Object -Line).Lines

Résultat : 2004178

### Fichiers .jenga

    (Get-ChildItem -Recurse -Include *.jenga).Count

Résultat : 220

### Taille du dépôt sur le disque

    "{0:N2} Go" -f ((Get-ChildItem -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1GB)

Résultat : 1,40 Go

## Tableau récapitulatif

| Mesure                              | Ma valeur  | Valeur du livre |
|--------------------------------------|-----------|------------------|
| Fichiers .cpp + .h (hors Build)      | 4428      | 2641             |
| Fichiers .cpp seuls                  | 1637      | non détaillé     |
| Fichiers .h seuls                    | 2792      | non détaillé     |
| Fichiers .cpp + .h (avec Build)      | 4428      | —                |
| Lignes de code                       | 2 004 178 | 1 193 385        |
| Fichiers .jenga                      | 220       | 221              |
| Taille du dépôt sur le disque        | 1,40 Go   | 17 Go            |

## Explication des écarts

**Le dossier Build n'explique pas l'écart chez moi.** Le nombre de fichiers .cpp/.h est strictement identique (4428) avec et sans exclusion de Build. Mon dossier Build ne contient donc aucune copie de sources — je n'ai pas encore lancé de construction complète qui y déposerait des fichiers intermédiaires ou des en-têtes copiés.

**J'ai séparé .cpp et .h, comme le suggère l'énoncé.** Sur mes 4428 fichiers, 1637 sont des .cpp et 2792 sont des .h — presque deux fois plus d'en-têtes que de fichiers source. Le livre ne donne qu'un chiffre combiné (2641), donc je ne peux pas comparer directement chaque type séparément à une référence du livre, mais cette séparation confirme que les en-têtes pèsent plus lourd en nombre de fichiers que les .cpp dans ce dépôt, ce qui est cohérent avec un moteur qui expose beaucoup d'API publiques (types, macros, templates) par rapport au code d'implémentation.

**Petite incohérence observée : 1637 + 2792 = 4429, alors que le comptage combiné direct donne 4428.** Écart de 1 fichier, probablement un fichier avec une extension ambiguë ou un doublon de chemin compté différemment selon que le filtre porte sur un motif combiné ou sur deux motifs séparés. Je note cet écart plutôt que de l'ignorer, car mesurer honnêtement inclut signaler quand deux mesures censées coïncider ne coïncident pas exactement.

**Les fichiers et lignes sont nettement plus nombreux chez moi que dans le livre** (4428 contre 2641 fichiers, 2 004 178 contre 1 193 385 lignes, presque le double dans les deux cas). Le dépôt Nkentseu est un projet réel et vivant : l'auteur précise lui-même que ses chiffres ont été mesurés le jour où il a écrit cette page. Mon clone, obtenu plus tard, reflète un état plus avancé du dépôt, avec davantage de modules.

**Le nombre de fichiers .jenga est quasiment identique** (220 contre 221 dans le livre), un écart d'un seul fichier cohérent avec un module ajouté ou retiré entre-temps.

**La taille sur disque est très différente** (1,40 Go contre 17 Go dans le livre). Un clone Git frais ne contient que le code source, sans les objets compilés ni les binaires produits par une construction complète. Le chiffre du livre inclut vraisemblablement un dossier Build rempli (objets, exécutables) et peut-être de gros fichiers d'assets (textures, audio) que mon dépôt cloné ne contient pas encore.

## Conclusion

Cet exercice montre qu'un même dépôt, mesuré à des instants différents ou avant/après une construction, donne des chiffres différents. Séparer .cpp et .h révèle une information que le comptage combiné cache : la proportion entre code d'en-tête et code d'implémentation. Le seul chiffre fiable est celui qu'on mesure soi-même, sur son propre dépôt, à l'instant présent, avec la commande et la sortie qui permettent à quelqu'un d'autre de le refaire.