																		// *** Rendu Cosmos (En Profondeur) *** //
																		//	    En C++ Natif (FREEGLUT x64)     //
																		//           Ecrit le 20/07/2025		//
																		//////////////////////////////////////////


#include <cstdio>                                                       // Bib. Standard E/S C++ //
#include <cstdlib>                                                      // Bib. Standard C++ //
#include <ctime>                                                        // Pour Variables Al�atoires //
#include <Windows.h>                                                    // Pour Masquage Fen�tre Console //

#include "GL/freeglut.h"                                                //
#include "GL/freeglut_ext.h"                                            //
#include "GL/freeglut_std.h"                                            //
#include "GL/glut.h"                                                    // Bib. FREEGLUT (x64) //

using namespace std;                                                    // Utilisation Espace de Noms Standard //

const GLint Tick = 40;                                                  // Valeur Tick Timer D�placement Etoiles //
const int NB_ETOILES = 10000;                                           // Valeur Nombre d'etoiles //

struct Etoile                                                           // D�claration Structure Etoile //
{                                                         
    int x, y, z;                                                        // Coordonn�es 3D des Etoiles //
};

Etoile etoiles[NB_ETOILES];                                             // Tableau de 10000 Etoiles dans la Structure Etoile //

static void initEtoiles()                                               
{
    for (int i = 0; i < NB_ETOILES; i++)                                // Pour 10000 Etoiles //
    {
        etoiles[i].x = rand() % 741 + 30;                               // Coordonn�es en X entre 30 et 770 //
        etoiles[i].y = rand() % 441 + 30;                               // Coordonn�es en Y entre 30 et 470 //
        etoiles[i].z = rand() % 101 + 1;                                // Coordonn�es en Z entre 1 et 101 //
    }
}

static void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);                                   // Effacement Ecran avec Couleur Noire //
    glShadeModel(GL_FLAT);                                              // Colorisation Unie (Mod�le de D�grad�) //
    glEnable(GL_DEPTH_TEST);                                            // Activation Du Tampon de Profondeur (Z-Buffer) //
    glPointSize(1.0);                                                   // Etoiles de 1 Pixel de Taille //
}

static void reshape(int w, int h) 
{
    glViewport(0, 0, w, h);                                             // Transformation de Cadrage //
    glMatrixMode(GL_PROJECTION);                                        // Matrice Active -> Projection //
    glLoadIdentity();                                                   // On vide cette Matrice //
    gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 0.1, 300.0);          // Perspective Sym�trique //
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // On vide le Tampon Chromatique et de Profondeur //
    glMatrixMode(GL_MODELVIEW);                                         // Matrice Active -> Mod�lisation-Visualisation //
    glLoadIdentity();                                                   // On vide cette Matrice //
    gluLookAt(400.0, 250.0, -10.0, 400.0, 250.0, 0.0, 0.0, 1.0, 0.0);   // Cam�ra //


    glColor3f(1.0, 1.0, 1.0);                                           // De Couleur Blanche //
    glBegin(GL_POINTS);                                                 // D�but Dessins Etoiles //
    for (int i = 0; i < NB_ETOILES; i++)                                // Pour 10000 Etoiles //
    {
        glVertex3i(etoiles[i].x, etoiles[i].y, etoiles[i].z);           // Coordonn�es 3D des Etoiles //
    }
    glEnd();                                                            // Fin des Dessins //

    glFlush();                                                          // Ach�vement Toutes Commandes Pr�c�dentes //

    glutSwapBuffers();
}

static void Timer(int value) 
{

    for (int i = 0; i < NB_ETOILES; i++)                                // Pour 10000 Etoiles //
    {
        etoiles[i].z -= 1;                                              // Avanc�e en profondeur (Axe Z) //
        

        if (etoiles[i].z < 1)                                           // Si les Etoiles arrivent Devant //
        {
            etoiles[i].z = rand() % 101;                                // R�attribution Coordonn�es en Axe Z //
        }
    }


    glutPostRedisplay();                                                // Raffraichissement Affichage //

    glutTimerFunc(Tick, Timer, 0);                                      // R�armement Timer //
}

static void keyboard(int key, int x, int y) 
{
    switch (key)                                                        // Commutation Touche Appuy�e //
    {
    case GLUT_KEY_F1:                                                   // Appui sur 'F1' //
        glutFullScreen();                                               // Passage en Plein Ecran //
        break;

    case GLUT_KEY_F4:                                                   // Appui sur 'F4' //
        glutReshapeWindow(800, 500);                                    // Remise en Taille & Position D'Origine //
        glutPositionWindow(560, 350);
        break;

    case GLUT_KEY_F10:                                                  // Appui sur 'F10' //
        exit(0);                                                        // On quitte le Logiciel //
        break;

    }
}

int main(int argc, char** argv) 
{
    srand((unsigned int)time(NULL));                                    // Amor�age du Pseudo-Al�atoire //
    FreeConsole();                                                      // Masquage Fen�tre Console //
    glutInit(&argc, argv);                                              // Initialisation de GLUT //
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);           // Modes Affichage //
    glutInitWindowSize(800, 500);                                       // Taille Initiale Fen�tre OPENGL //
    glutInitWindowPosition(560, 350);                                   // Position Initiale Fen�tre OPENGL //        
    glutCreateWindow("Cosmos");                                         // Cr�ation Fen�tre OPENGL //
    initEtoiles();                                                      // Initialisation des Etoiles //
    init();                                                             // Initialisation de l'affichage //
    glutDisplayFunc(display);                                           // Fonction GLUT Affichage //
    glutReshapeFunc(reshape);                                           // Fonction GLUT Redimensionnement Fen�tre //
    glutTimerFunc(Tick, Timer, 0);                                      // Fonction GLUT Gestion Timer //
    glutSpecialFunc(keyboard);                                          // Fonction GLUT Gestion Clavier //
    glutMainLoop();                                                     // Fonction GLUT Gestion Boucle Fonction Affichage //

    return 0;                                                           // Renvoie '0' a WINDOWS //
}




