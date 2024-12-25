11/11/2024: Ajout du modèle v1 de modélisation, la trajectoire semble bonne mais la planète accélère au cours du temps
(peut être à cause du deltaTime?). Certaines des variables ne sont pas liées entre les fichiers (position du Soleil par ex.)

20/11/2024: TODO
- Une manière de rajouter des planètes facilement (Structures Liste de Planetes) FAIT ('fin essayé)
- Faire marcher un modele physique mieux au niveau des distances (Log ? Passer en UA ? Juste faire des calculs mieux ?)
- Zoom - Dezoom de la caméra FAIT
- Mode centré de la caméra FAIT
- Bosser sur le concept de Lune (Apres le modele physique) -> Detection de proximité

20/12/2024
- Liste chainée OK pour calcul vitesse,position; affichage de tout OK mais soleil séparé.
- liste chainée OK est sur une branche séparée → à merge (je galère)
- Soleil pas inclus dans la liste chainée → il est dessiné séparément.
- Les Traces sont cassées (à adapter à la liste chainée)
- intégrer le fichier CSV
- faire du nettoyage (on a toujours les commentaires de la V1 avec le cos(omega*t) mdr)
- refaire du test lune; anti catapultage ?

24/12/2024 : L'odyssée du merge
Je galere a merge nos branches depuis tout a l'heure, je comprends pas ce qui marche pas :'(
Je vais tenter de tout reprendre fichier par fichier et faire un gros push sur main mais bon on va bien voir si ça marche

En fait non ça marche pas non plus
Je vais recopier toutes les fonctions une par une du coup :)
Finalement tout marche j'ai pas compris exactement comment mais c'est pas grave

25/12/2024 : 
Faut encore que je fasse le parsing du csv, je pense que le csv renverra un tableau de planetes qu'ensuite on ajoute dans la liste chainee pour pouvoir la gérer dynamiquement
Ca permettra de gérer facilement la caméra sur les planetes + d'avoir la dynamique de la liste chainee
Des que j'ai fini le parsing je me met au générateur d'astéroïdes et après ce sera que du détail
