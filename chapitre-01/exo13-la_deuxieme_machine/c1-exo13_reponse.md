\# Exercice 13 — La deuxième machine



\## Limite honnête de cette réponse



Je n'ai pas accès à une deuxième machine physique, ni à Windows Sandbox, ni à un second compte utilisateur Windows pour cet exercice (contraintes matérielles/logicielles de mon environnement actuel). Je ne peux donc pas prétendre avoir reconstruit le dépôt sur un environnement réellement neuf de bout en bout. À la place, cette réponse s'appuie sur deux sources réelles :



1\. Le vrai journal de tout ce qui a manqué ou a bloqué depuis le tout début de ce projet sur ma machine actuelle, dans l'ordre chronologique où chaque incident est survenu.

2\. Une simulation partielle et honnête : la suppression temporaire, pour une seule session PowerShell (sans toucher au système de façon durable), de la variable d'environnement VULKAN\_SDK, pour reproduire un vrai message d'échec "outil absent" tel qu'une machine sans le SDK Vulkan l'obtiendrait.



\## Journal chronologique de ce qui a manqué



\### 1. Identité Git non configurée



Premier commit tenté sans succès : Git ne connaissait ni le nom ni l'email à associer aux commits.



Résolu par :



&#x20;   git config --global user.name "Pierre Jordan Bias"

&#x20;   git config --global user.email "pierrejordanbias@gmail.com"



\### 2. Absence d'authentification GitHub par mot de passe



Le push initial a demandé une authentification, refusée avec un mot de passe classique (GitHub ne l'accepte plus).



Résolu par la création d'un Personal Access Token (PAT) sur github.com/settings/tokens, utilisé comme mot de passe lors du push.



\### 3. Fautes d'indentation Python dans les fichiers .jenga



Plusieurs tentatives d'ajout de blocs with include(...) au fichier Nkentseu.jenga ont échoué avec :



&#x20;   Error loading workspace: unexpected indent (Nkentseu.jenga, line 764)



puis :



&#x20;   Error loading workspace: unindent does not match any outer indentation level (Nkentseu.jenga, line 769)



Cause : un .jenga est un vrai script Python (section 1.3 du chapitre), donc l'indentation n'est pas cosmétique. Le bloc copié-collé depuis une conversation avait perdu son indentation exacte.



Résolu en réalignant manuellement l'indentation (4 espaces pour with, 8 pour le pass suivant), en évitant tout mélange d'espaces et de tabulations.



\### 4. Encodage UTF-8 mal interprété dans les fichiers .jenga existants



En affichant NKContainers.jenga et NKCanvas.jenga avec Get-Content, les caractères accentués s'affichent comme des séquences illisibles (ex: "PÃ©rimÃ¨tre" au lieu de "Périmètre"). PowerShell interprète mal l'encodage UTF-8 du fichier source par défaut. Sans impact sur la compilation (les commentaires ne sont pas exécutés), mais gênant à la lecture.



\### 5. SDK Vulkan absent



Première tentative de construction de NkRef (WindowedApp dépendant de NKCanvas) :



&#x20;   C:/msys64/ucrt64/bin/ld: cannot find -lvulkan-1: No such file or directory

&#x20;   C:/msys64/ucrt64/bin/ld: have you installed the static version of the vulkan-1 library ?

&#x20;   clang++: error: linker command failed with exit code 1



Vérification :



&#x20;   $env:VULKAN\_SDK

&#x20;   (rien affiché — variable vide)



Résolu par l'installation du SDK Vulkan depuis vulkan.lunarg.com, qui a défini automatiquement VULKAN\_SDK = C:\\VulkanSDK\\1.4.357.0 et mis à jour le PATH. Un nouveau terminal PowerShell a été nécessaire pour que la variable soit prise en compte (les variables d'environnement ne se rechargent qu'à l'ouverture d'un nouveau terminal, pas dans une session déjà ouverte).



\### 6. Reproduction volontaire de l'absence de Vulkan (simulation d'une machine sans le SDK)



Pour ce dernier exercice, suppression temporaire de la variable pour la session en cours uniquement :



&#x20;   $env:VULKAN\_SDK = $null

&#x20;   jenga build --project NkRef --config Debug



Résultat : échec identique au point 5, reproduit à l'identique :



&#x20;   C:/msys64/ucrt64/bin/ld: cannot find -lvulkan-1: No such file or directory

&#x20;   Build Failed

&#x20;   Errors: 1 | Failed files: 1

&#x20;   Projects Built: 17/18



Confirmation que cette variable d'environnement est un vrai point de blocage reproductible, pas un incident isolé lié à l'ordre d'installation.



Variable rétablie immédiatement après :



&#x20;   $env:VULKAN\_SDK = "C:\\VulkanSDK\\1.4.357.0"

&#x20;   $env:VULKAN\_SDK

&#x20;   C:\\VulkanSDK\\1.4.357.0



\## Récapitulatif : outil absent / version / variable d'environnement / chemin



| Catégorie | Élément manquant | Symptôme observé |

|---|---|---|

| Configuration | Identité Git (user.name, user.email) | git commit ne crée aucun commit, sans message d'erreur explicite au premier abord |

| Authentification | Personal Access Token GitHub | Demande d'authentification lors du push, mot de passe classique refusé |

| Syntaxe | Indentation Python correcte dans .jenga | unexpected indent / unindent does not match any outer indentation level |

| Encodage | Terminal PowerShell en UTF-8 | Caractères accentués affichés comme séquences illisibles dans les commentaires .jenga |

| Outil externe | SDK Vulkan (vulkan-1.lib) | cannot find -lvulkan-1: No such file or directory au moment du link |

| Variable d'environnement | VULKAN\_SDK | Vide tant que le SDK n'est pas installé ou tant qu'un nouveau terminal n'a pas été ouvert après l'installation |



\## Conclusion



Même sans accès à une deuxième machine réelle, ce journal confirme l'idée centrale de l'exercice : la vraie documentation d'installation n'est pas écrite à l'avance, elle se découvre incident par incident, en notant précisément le message d'erreur, sa cause, et la commande qui l'a résolu. Sur ce projet, les manques n'étaient pas seulement des bibliothèques C++ (Vulkan) : identité Git, authentification, et même l'indentation syntaxique d'un langage de configuration ont chacun bloqué la progression à un moment donné, chacun avec un message différent qu'il a fallu interpréter avant de pouvoir avancer.

