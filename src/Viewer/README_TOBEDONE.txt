/******************************************/
/**************** VIEWER *****************/
/******************************************/

Le visualisateur permet de représenter la scène de lancer de balle en temps réel.
Il représente : un sol quadrillé, un mur plein, une balle, une ou plusieurs trajectoires
différenciées par un identifiant 0, 1, 2 ...

Pour compiler :
1) Installer la suite Qt, QtOpengGL et Glut

Pour compiler à la main :
2) dans src/Viewer/ générer le Makefile : ~$ qmake
3 Puis ~$ make
4) Puis ~$ ./Viewer

(ou sinon Ctrl+R dans Qt Creator après avoir ouvert Viewer.pro)

* Pour info les noms des bibliothèques sont -lopenGL et -lglut mais vous ne devriez
  pas en avoir besoin, tout est dans Viewer.pro et sera généré par qmake
* NE PAS MODIFIER LE MAKEFILE DIRECTEMENT, UTILISER QMAKE.




/**********************************************/
/************** LE CODE ACTUEL ****************/
/**********************************************/

* Lire le rapport en premier !

La base du code est une démo de Qt faisant tourner un logo Qt avec OpenGL.

* main et window proviennent uniquement de la démo et gèrent la fenêtre et le
composant OpenGL, ils ne devraient pas être modifiés

* glWigdet est le composant OpenGL. Tous les élements de la scène sont déclarés
dans son header (Trajectory *t, Ball *b, Plane *mur, ...), construits soit dans
le son constructeur. Pour la balle et les trajectoires elles pourront être
construites à la volée, il faudra remplacer les attributs

* plane représente un plan, soit quadrillé soit plein (sol et mur)

* coordinate system représente le "grand repère", c'est à dire le repère de la
scène. Le but est qu'il corresponde exactement à celui d'Optitrack (celui
définit par le calibration square). On doit donc pouvoir aisément le changer de
sens et de place pour le faire correspond à celui de la scène, ce qui n'est
pas encore au point et reste à faire.

* trajectory représente une trajectoire de la balle. Un identifiant permet de
la distinguer des autres si on veut en dessiner plusieurs. Elle comporte une
liste de points _points qui, reliés ensemble dessinent la trajectoire.

* ball représente la balle. Eventuellement on peut lui ajouter un identifiant
comme pour trajectory si on veut en dessiner plusieurs.

* arm représente le bras. La classe n'est pas codée. On doit pouvoir mettre à
jour en temps réel la position du bras en appelant directement les setAngle()
pour chacun des servomoteurs. setAngle fait appel au modèle géométrique du
robot pour mettre à jour la représentation.

* tools est une classe utilitaire, où on met toutes les mini-classes et les
fonctions utilitaires qui méritent pas forcément un fichier à elles seules.




/******************************************/
/************** NOTES ET TODO *************/
/******************************************/

* svp conservez le visualisateur indépendant du client Optitrack et du
"calculateur". Les trois parties doivent communiquer sur leurs E/S standards
avec de simples printf() et scanf() par exemple. (cf rapport)

* Corriger coordinate system et les fonctions de rotation de GLWidget pour pouvoir
déplacer le repère scène sans déplacer le sol et les murs grâce à la méthode
CoordinateSystem::moveCoordinateSystem(). Attention la méthode
CoordinateSystem::rotateCoordinateSystem() ne doit faire tourner que le repère
scène et la scène elle-même, pas le mur et le sol. Plus de détails :

** Le mur et le sol sont pour l'instant dessinés par quatre points DANS LE REPERE
DE LA SCENE. Il serait peut-être plus judicieux de les dessiner dans le REPERE
OPENGL afin qu'ils ne bougent jamais et qu'on puisse déplacer le repère scène
sans bouger le sol et les murs.

** Le "petit" repère est le repère OpenGL et le "grand" repère est le repère
Scène. Actuellement le repère OpenGL ne bouge pas mais c'est lui qui devra tourner
lorsqu'on clique avec la souris car une fois que le mur et le sol seront exprimés
dans le repère openGL on veut continuer à tourner autour. Dès lors ce ne sera plus
vraiment le repère OpenGL mais plutôt le repère "Salle" lié au sol et au mur.


* Pour Trajectoire, il faudra différencier deux vecteurs de points par la suite :
** le vecteur des points acquis par Optitrack (de 2 à N points) qu'on peut
   dessiner avec une petite boule pour montrer les points acquis.
** le vecteur des points interpolé, faisant appel au calcul de trajectoire et
   qu'on obtient donc à partir d'une équation. Il pourra posséder un nombre de
   points fixes (par 30) reliés par des petites droites GL_LINES pour obtenir
   une trajectoire bien lisse. C'est plus ou moins le rôle de l'actuel _points
   car ce sont ces points qui sont directement dessinés.

* L'étape suivante est de lire sur l'entrée standard les informations de la
scène et de construire ou mettre à jour la scène (= balle + trajectoire + bras)
en temps réel.

* Les identifiants _ID pourront avoir un intérêt lorsque la partie "calculatoire"
transmettra les informations de la scène, pour qu'on sache quel est la balle/le
bras/la trajectoire a mettre à jour.
