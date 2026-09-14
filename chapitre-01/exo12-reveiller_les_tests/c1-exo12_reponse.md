\# Exercice 12 — Réveiller les tests



\## Objectif



Le workspace désactive la compilation des tests.  

L'objectif est de :



\- trouver la ligne qui contrôle cette désactivation ;

\- déterminer combien de suites de tests existent ;

\- lancer malgré tout une suite de tests d'un module ;

\- déterminer combien de suites s'exécutent et combien passent.



\---



\## 1. Ligne contrôlant la compilation des tests



La recherche de `dutc` dans `Nkentseu.jenga` donne :



```text

Nkentseu.jenga:452:

dutc(enable=True, allow=\["NKCore\_Tests", "NKMath\_Tests", "NKContainers\_Tests",

"NKMemory\_Tests", "NKPhysics\_Tests", "NKFileSystem\_Tests", "NKStream\_Tests",

"NKReflection\_Tests", "NKWindow\_Tests", "NKCamera\_Tests", "NKCollision\_Tests",

"NKImage\_Tests", "NKPlatform\_Tests", "NKLogger\_Tests", "NKTime\_Tests",

"Noge\_Tests", "NKThreading\_Tests", "NKAnima\_Tests", "NKSerialization\_Smoke\_Tests",

"NKECS\_EntitySerialization\_Tests", "NKXR\_Xr\_Tests", "NKAudio\_Audio\_Tests",

"NKSerialization\_ReflectSerializer\_Tests", "NKSerialization\_ReflectPhase3\_Tests",

"NKSerialization\_ReflectObjContainer\_Tests", "NKSerialization\_Bench\_Tests",

"NKECS\_ReflectBridge\_Tests", "NKXR\_Ar\_Tests",

"NKSerialization\_ReflectPhase5\_Tests", "NKRenderer\_Tests"])



La ligne concernée est donc la ligne 452 de Nkentseu.jenga.



La directive utilisée est :



dutc(...)



Elle définit la politique de compilation des tests du workspace, avec une liste de suites explicitement autorisées par allow.





\##2. Nombre de suites de tests existantes



La commande utilisée pour compter les projets de type TestSuite dans la sortie de jenga info est :



(Select-String -Path ".\\info.txt" -Pattern "TestSuite").Count



Résultat :



68



Il existe donc 68 suites de tests dans le workspace.



\##3. Exécution d'une suite malgré la politique du workspace



La suite choisie est :



NKLogger\_Tests



Pour l'exécuter malgré la politique qui désactive la compilation/exécution normale des tests, la commande utilisée est :



jenga test --project NKLogger\_Tests --force



L'option --force permet de forcer l'exécution de la suite malgré la politique du workspace.



La sortie indique notamment :



Workspace policy disableunittestcompilation lifted for this invocation (--force).



La politique de désactivation de la compilation des tests a donc bien été levée uniquement pour cette exécution.



\##4. Résultat des tests



La suite NKLogger\_Tests contient :



Number of tests: 2



Les deux tests sont passés :



\[OK]

\[OK]



Le bilan obtenu est :



Tests:       2 passed / 2 total

Assertions:  5 / 5

Success:     100%



La sortie confirme également :



All tests succeeded

All tests passed for NKLogger\_Tests.

5\. Réponse finale

Élément	Résultat

Suites de tests existantes	68

Suite lancée	NKLogger\_Tests

Suites exécutées dans cette commande	1

Tests exécutés	2

Tests réussis	2

Assertions réussies	5 / 5

Taux de réussite	100 %

Ligne de politique dutc	Nkentseu.jenga:452







\##Conclusion



Le workspace contient 68 suites de tests.



La compilation des tests est contrôlée par la directive dutc(...) à la ligne 452 de Nkentseu.jenga, avec une liste de suites autorisées.



En utilisant :



jenga test --project NKLogger\_Tests --force



j'ai pu exécuter malgré la politique du workspace 1 suite de tests.



Cette suite contient 2 tests, et les 2 ont réussi, soit 100 % de réussite, avec 5 assertions réussies sur 5.





Cette version répond directement aux \*\*trois nombres demandés par l'exercice\*\* : \*\*68 suites existent, 1 suite est exécutée dans la démonstration, et 1 suite passe\*\* (avec 2/2 tests réussis).

