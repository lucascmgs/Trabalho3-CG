#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Point.h"
#include "Segment.h"
#include "Polygonal.h"

using namespace std;


const float GREEN[3] = {0.0, 1.0, 0.0};
const float RED[3] = {1.0, 0.0, 0.0};


const int WINDOWSIZE = 500;

Polygonal IsolatedPoints;
Polygonal ConvexResult;

void mouse (int button, int state, int givenX, int givenY)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point result = Point((2.*givenX)/WINDOWSIZE - 1., -(2.*givenY)/WINDOWSIZE + 1.);

        
        IsolatedPoints.Add(result);
        glutPostRedisplay();
    }
}

void keyboard_cb(unsigned char key, int X, int Y)
{
    switch (key)
    {
        case 27:             
            exit (0);
            break;

        //Tecla para chamar a suaviação das retas
        case 'c':
            if(!ConvexResult.IsPolygon() && IsolatedPoints.GetSize() > 3){
                ConvexResult = IsolatedPoints.GetConvexHull();
            }
            glutPostRedisplay();
            break;
        //Tecla para limpar os points
        case 'r':
            cout << "Pontos resetados" << endl;
            IsolatedPoints.Reset();
            ConvexResult.Reset();
            glutPostRedisplay();
            break;
    }
}


void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPointSize(8.0);
    
    glLineWidth(3);
    
    IsolatedPoints.PlotPoints();

    if(ConvexResult.IsPolygon()){
        ConvexResult.PlotLines();
    }
    

    glEnd();
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    IsolatedPoints = Polygonal();
    ConvexResult = Polygonal();
    glutInit(&argc,argv);
    glutInitWindowSize (WINDOWSIZE, WINDOWSIZE);
    glutCreateWindow("points");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return EXIT_SUCCESS ;

}
