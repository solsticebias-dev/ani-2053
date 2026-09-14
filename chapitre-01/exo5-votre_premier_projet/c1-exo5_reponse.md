\# Exercice 5 — Votre premier projet



\## Structure créée



Applications/MonEssai/

├── MonEssai.jenga

└── src/

&#x20;   └── main.cpp



\## main.cpp (n'affiche rien)



int main()

{

&#x20;   return 0;

}



\## MonEssai.jenga



from Jenga import \*

from jengaconfig import \*



with project("MonEssai"):

&#x20;   consoleapp()

&#x20;   language("C++")

&#x20;   cppdialect("C++17")

&#x20;   location(".")



&#x20;   files(\["src/\*\*.cpp"])



&#x20;   objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

&#x20;   targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")



&#x20;   with filter("system:Windows"):

&#x20;       usetoolchain(TC\_WINDOWS)



&#x20;   with filter("config:Debug"):

&#x20;       defines(\["\_DEBUG"]); optimize("Off"); symbols(True)

&#x20;   with filter("config:Release"):

&#x20;       defines(\["NDEBUG"]); optimize("Speed"); symbols(False)



\## Déclaration au workspace (Nkentseu.jenga)



&#x20;   with include("Applications/MonEssai/MonEssai.jenga"):

&#x20;       pass



\## Vérification avec jenga info



Le projet apparaît bien dans la liste :



MonEssai    ConsoleApp    C++    No    Yes



\## Construction



jenga build --project MonEssai --config Debug



Build Order (1 projects):

&#x20; 1. MonEssai \[CONSOLE\_APP]



Found 1 source file(s)

Compiled: main.cpp

Linking...

Built: Build\\Bin\\Debug-Windows\\MonEssai\\MonEssai.exe



Build Successful — Time: 1.37s



\## Incident rencontré



La première tentative de déclaration au workspace a échoué avec "Error loading workspace: unexpected indent", puis "unindent does not match any outer indentation level". La cause : le bloc with include("Applications/MonEssai/MonEssai.jenga"): pass avait été collé à la colonne 0 au lieu d'être indenté à 4 espaces, comme les autres blocs with include(...) du fichier. Comme le chapitre le rappelle (section 1.5.1), un fichier .jenga est un vrai programme Python : l'indentation n'est pas cosmétique, elle définit la structure du code. La correction a consisté à aligner exactement l'indentation sur les blocs voisins (4 espaces pour with, 8 pour pass).

