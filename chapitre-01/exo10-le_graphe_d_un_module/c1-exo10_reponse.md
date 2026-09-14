\# Exercice 10 — Le graphe d'un module



\## Source des données



Niveau 1 : lu directement dans Kernel/Runtime/NKCanvas/NKCanvas.jenga (commande Get-Content, exercice 10).

Niveau 2 : lu dans la sortie réelle de jenga build --project NkRef --config Debug --build (exercice 9), qui affiche, pour chaque projet du Build Order, la liste "(depends: ...)" de ses propres dépendances.



\## Niveau 1 — Dépendances directes de NKCanvas



Trouvées dans le fichier, via la variable \_canvasDeps passée à nkentseudependson :



&#x20;   \_canvasDeps = \["NKWindow", "NKFont", "NKImage", "NKGui", "NKEvent", "NKGlad",

&#x20;                  "NKStream", "NKTime", "NKThreading",

&#x20;                  "NKFileSystem", "NKLogger", "NKMath", "NKContainers", "NKMemory",

&#x20;                  "NKCore", "NKPlatform"]



Soit 16 dépendances directes : NKWindow, NKFont, NKImage, NKGui, NKEvent, NKGlad, NKStream, NKTime, NKThreading, NKFileSystem, NKLogger, NKMath, NKContainers, NKMemory, NKCore, NKPlatform.



Une 17e dépendance conditionnelle existe (NKUI), ajoutée seulement si le flag USE\_CANVAS\_NKUI est actif (non vérifié sur ma configuration, donc non comptée ici).



\## Niveau 2 — Dépendances de chaque dépendance directe



Extrait de la sortie réelle de jenga build --project NkRef --config Debug (Build Order, 18 projects) :



&#x20;   1. NKPlatform (aucune dépendance)

&#x20;   2. NKGlad (aucune dépendance)

&#x20;   3. NKCore (depends: NKPlatform)

&#x20;   4. NKMemory (depends: NKCore, NKPlatform)

&#x20;   5. NKContainers (depends: NKCore, NKMemory, NKPlatform)

&#x20;   6. NKThreading (depends: NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;   7. NKMath (depends: NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;   8. NKLogger (depends: NKContainers, NKCore, NKMemory, NKPlatform, NKThreading)

&#x20;   9. NKTime (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   10. NKFont (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading)

&#x20;   11. NKFileSystem (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   12. NKEvent (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime)

&#x20;   13. NKStream (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   14. NKWindow (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime)

&#x20;   15. NKImage (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading)

&#x20;   16. NKGui (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading)



\## Observation : le niveau 2 n'ajoute aucun nouveau module



En listant tous les noms qui apparaissent au niveau 2 (les dépendances des dépendances), aucun nom nouveau n'apparaît par rapport au niveau 1 : tous les modules cités (NKPlatform, NKCore, NKMemory, NKContainers, NKThreading, NKMath, NKLogger, NKTime, NKFont, NKFileSystem, NKEvent, NKStream, NKWindow) sont déjà présents dans la liste \_canvasDeps du niveau 1.



Le fichier NKCanvas.jenga l'explique lui-même en commentaire : les modules de fondation (NKPlatform, NKCore, NKMemory, NKContainers, NKThreading, NKMath, NKLogger) arriveraient de toute façon par transitivité via NKWindow ou NKGui, mais ils sont déclarés explicitement dans dependson plutôt que laissés implicites. Le commentaire du fichier dit littéralement qu'une dépendance transitive n'est pas considérée comme une dépendance déclarée dans ce dépôt — donc chaque module réellement utilisé est nommé, même s'il serait de toute façon tiré par un autre.



\## Graphe à deux niveaux



&#x20;   NKCanvas

&#x20;   ├── NKWindow ── (NKContainers, NKCore, NKEvent, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime)

&#x20;   ├── NKFont ───── (NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKImage ──── (NKContainers, NKCore, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading)

&#x20;   ├── NKGui ────── (NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKEvent ──── (NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime)

&#x20;   ├── NKGlad ───── (aucune)

&#x20;   ├── NKStream ─── (NKContainers, NKCore, NKFileSystem, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKTime ───── (NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKThreading ─ (NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;   ├── NKFileSystem ─ (NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKLogger ──── (NKContainers, NKCore, NKMemory, NKPlatform, NKThreading)

&#x20;   ├── NKMath ────── (NKContainers, NKCore, NKMemory, NKPlatform)

&#x20;   ├── NKContainers ─ (NKCore, NKMemory, NKPlatform)

&#x20;   ├── NKMemory ──── (NKCore, NKPlatform)

&#x20;   ├── NKCore ────── (NKPlatform)

&#x20;   └── NKPlatform ── (aucune)



\## Combien de projets faut-il construire avant NKCanvas ?



16 projets, exactement les 16 dépendances directes listées ci-dessus, dans l'ordre donné par le Build Order réel : NKPlatform, NKGlad, NKCore, NKMemory, NKContainers, NKThreading, NKMath, NKLogger, NKTime, NKFont, NKFileSystem, NKEvent, NKStream, NKWindow, NKImage, NKGui.



Aucun projet supplémentaire n'est nécessaire au-delà de ces 16, puisqu'aucun nom nouveau n'apparaît au niveau 2 (voir observation ci-dessus).



\## Conclusion



Le graphe de dépendances de NKCanvas est large en largeur (16 modules directs) mais peu profond au-delà : le niveau 2 ne fait que révéler les arêtes internes entre les 16 modules déjà connus, sans ajouter de nouveaux sommets. Cela tient à un choix de conception documenté dans le fichier lui-même : chaque dépendance réellement utilisée est déclarée explicitement dans dependson, même quand elle arriverait de toute façon par transitivité via un autre module — ce qui rend le graphe plat plutôt que profondément imbriqué.

