\# EXERCICE 4 - Le commit partiel





\# fichier et contenue introduit dans le fichier



Dans le depot essai nous avons cree un fichier de nom fichier.txt

le contenue introduit est le suivant :



\# Configuration

setting\_one = 10

setting\_two = 20

setting\_three = 30

setting\_four = 40

setting\_five = 50

setting\_six = 60

setting\_seven = 70

setting\_eight = 80

setting\_nine = 90

setting\_ten = 100



Nous avons fais un  git add config.txt et fais aussi un git commit



\# Modification fais dans le fichier



A l'aide des commandes suivantes :
(Get-Content config.txt) -replace 'setting\_one = 10', 'setting\_one = 99' | Set-Content config.txt
et

&#x20;(Get-Content config.txt) -replace 'setting\_ten = 100', 'setting\_ten = 999' | Set-Content config.txt



Nous avons fait des modification sur la premiere ligne et la dernière ligne comme sur les commandes

"setting\_one = 10" en "setting\_one = 99"

"setting\_ten = 100" en "setting\_ten = 999"





\# Commandes et résultat



* En faisant un "git diff" on obtient le résultat suivant :



diff --git a/config.txt b/config.txt

index 91d5ab6..62b78e1 100644

\--- a/config.txt

+++ b/config.txt

@@ -1,5 +1,5 @@

&#x20;# Configuration

\-setting\_one = 10

+setting\_one = 99

&#x20;setting\_two = 20

&#x20;setting\_three = 30

&#x20;setting\_four = 40

@@ -8,4 +8,4 @@ setting\_six = 60

&#x20;setting\_seven = 70

&#x20;setting\_eight = 80

&#x20;setting\_nine = 90

\-setting\_ten = 100

+setting\_ten = 999



* Lorsque l'on fait alors un "git add -p config.txt" Git va afficher le premier hunk (celui de setting\_one) et attendre une réponse. y pour dire "oui, ajoute ce hunk". Il va ensuite afficher le second hunk (setting\_ten) — cette fois n pour dire "non, pas celui-ci pour l'instant".



## voici le résultat de l'échange







diff --git a/config.txt b/config.txt

index 91d5ab6..62b78e1 100644

\--- a/config.txt

+++ b/config.txt

@@ -1,5 +1,5 @@

&#x20;# Configuration

\-setting\_one = 10

+setting\_one = 99

&#x20;setting\_two = 20

&#x20;setting\_three = 30

&#x20;setting\_four = 40

(1/2) Stage this hunk \[y,n,q,a,d,k,K,j,J,g,/,e,p,P,?]? y

@@ -8,4 +8,4 @@ setting\_six = 60

&#x20;setting\_seven = 70

&#x20;setting\_eight = 80

&#x20;setting\_nine = 90

\-setting\_ten = 100

+setting\_ten = 999

(2/2) Stage this hunk \[y,n,q,a,d,K,J,g,/,e,p,P,?]? n





voici la suite des commandes effectue :



PS C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai> git add -p config.txt

diff --git a/config.txt b/config.txt

index 0f6b22d..62b78e1 100644

\--- a/config.txt

+++ b/config.txt

@@ -8,4 +8,4 @@ setting\_six = 60

&#x20;setting\_seven = 70

&#x20;setting\_eight = 80

&#x20;setting\_nine = 90

\-setting\_ten = 100

+setting\_ten = 999

(1/1) Stage this hunk \[y,n,q,a,d,e,p,P,?]? y







PS C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai> git commit -m "Modification de setting\_ten"

\[master b830a2b] Modification de setting\_ten

&#x20;1 file changed, 1 insertion(+), 1 deletion(-)

PS C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai> git log --oneline -2

b830a2b (HEAD -> master) Modification de setting\_ten

9b457fa Modification de setting\_one

PS C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai> git show --stat

commit b830a2b7cb5f66127554fb329bc007441715a591 (HEAD -> master)

Author: Bias Pierre Jordan [pierrejordanbias@gmail.com](mailto:pierrejordanbias@gmail.com)

Date:   Wed Sep 16 08:55:22 2026 +0100



&#x20;   Modification de setting\_ten



&#x20;config.txt | 2 +-

&#x20;1 file changed, 1 insertion(+), 1 deletion(-)

PS C:\\Users\\anais\\OneDrive\\Desktop\\depot-essai> git show HEAD

commit b830a2b7cb5f66127554fb329bc007441715a591 (HEAD -> master)

Author: Bias Pierre Jordan [pierrejordanbias@gmail.com](mailto:pierrejordanbias@gmail.com)

Date:   Wed Sep 16 08:55:22 2026 +0100



&#x20;   Modification de setting\_ten



diff --git a/config.txt b/config.txt

index 0f6b22d..62b78e1 100644

\--- a/config.txt

+++ b/config.txt

@@ -8,4 +8,4 @@ setting\_six = 60

&#x20;setting\_seven = 70

&#x20;setting\_eight = 80

&#x20;setting\_nine = 90

\-setting\_ten = 100

+setting\_ten = 999







\# Conclusion



Cet exercice montre l'utilisation de git add -p pour effectuer un commit partiel. Deux modifications indépendantes ont été réalisées dans le même fichier config.txt : la modification de setting\_one et celle de setting\_ten.



Grâce à git add -p, j'ai pu sélectionner uniquement la première modification pour le premier commit, puis sélectionner la seconde modification pour le deuxième commit.



Ainsi, les deux modifications, bien qu'étant dans le même fichier, sont enregistrées dans deux commits distincts. La vérification de l'historique permet de confirmer que chaque commit contient uniquement la modification correspondant à son sujet.



