//--------------------------------------------------------
// CAP5705 Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#define GLEW_STATIC
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"


// globals
//---------------------------------
// scene
Scene       *pScene = NULL;     // scene geometry and lights
RayTracer   *pRayTracer = NULL; // runs ray tracing algorithm
RenderMode   mode = LAMBERTIAN;

// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;


// Function Prototypes
// TO DO: Proj2 raytracer
// Nothing to do here but note:
// These are not actually used in this
// app unless you were to create a glut
// window loop in the main and add a display callback
// You do not need this but it is available
//--------------------------------------
void MouseMotionCallback(int x, int y);
void MouseCallback(int button, int state, int x, int y);
void KeyCallback(unsigned char key, int x, int y);
void SpecialKeyCallback(int key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void EnvironmentMapping(void);

//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//
void Setup(void)
{

    // init the scene
    pScene = new Scene();

    // TO DO: Proj2 raytracer
    // CAP5705 - Set up your scene.
    // Use the variable pScene to set parameters
    // 1. change background color
    // 2. add lights
    // 3. add objects
    // 4. add translation and rotation operations to place objects
    //------------------------------------------------
	//Background
	RGBR_f bgColor(0, 0, 0, 1);
	pScene->SetBackgroundColor(bgColor);

	//Surfaces

	//Traingles 1 & 2 form the plane upon which spheres will be placed
	Surface *pTriangle1 = new Triangle(STVector3(-30,-5, 10), STVector3(30, -5, 10), STVector3(30, -5, -80));
	Surface *pTriangle2 = new Triangle(STVector3(30, -5, -80), STVector3(-30, -5, -80), STVector3(-30, -5, 10));

	//blue color for the plane
	pTriangle1->SetDiffuseColor(STColor4f(0.0f, 0.0f, 80.0f/255.0f, 1.0f));
	pTriangle1->SetSpecularColor(STColor4f(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f, 1.0f));
	pTriangle1->SetAmbientColor(STColor4f(0.0f, 0.0f, 15.0f/255.0f, 1.0f));

	//blue color for the plane
	pTriangle2->SetDiffuseColor(STColor4f(0.0f, 0.0f, 80.0f/255.0f, 1.0f));
	pTriangle2->SetSpecularColor(STColor4f(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f, 1.0f));
	pTriangle2->SetAmbientColor(STColor4f(0.0f, 0.0f, 15.0f/255.0f, 1.0f));

	pScene->AddSurface(pTriangle1);
	pScene->AddSurface(pTriangle2);

	//Sphere1, red color
	Surface *pSphere1 = new Sphere(STVector3(-4.00f, -2.0f, -7.0f), 3);

	pSphere1->SetDiffuseColor(STColor4f(65.0f/255.0f, 0.0f/255.0f, 0.0f, 1.0f));
	pSphere1->SetSpecularColor(STColor4f(120.0f/255.0f, 110.0f/255.0f, 110.0f/255.0f, 1.0f));
	pSphere1->SetAmbientColor(STColor4f(20.0f/255.0f, 0.0f, 0.0f, 1.0f));
	
	//Sphere2, green color
	Surface *pSphere2 = new Sphere(STVector3(+4.0f, -2.0f, -3.0f), 3);

	pSphere2->SetDiffuseColor(STColor4f(0.0f, 65.0f/255.0f, 0.0f, 1.0f));
	pSphere2->SetSpecularColor(STColor4f(110.0f/255.0f, 120.0f/255.0f, 110.0f/255.0f, 1.0f));
	pSphere2->SetAmbientColor(STColor4f(0.0f, 20.0f/255.0f, 0.0f, 1.0f));
	
	pScene->AddSurface(pSphere2);	
	pScene->AddSurface(pSphere1);

	//Lights
	RGBR_f clrLight1 (1, 1, 1, 1);
	STVector3 v3light1Pos (-25,3, 5);
	Light light1 (v3light1Pos, clrLight1, "1");
	pScene->AddLight(light1);

	RGBR_f clrLight2 (1, 1, 1, 1);
	STVector3 v3light2Pos (35,2, 10);
	Light light2 (v3light2Pos, clrLight2, "2");
	pScene->AddLight(light2);

	//------------------------------------------------
    // init a ray tracer object
    pRayTracer = new RayTracer();

}

//
// Reshape the window and record the size so
// that we can use it for screenshots.
//
void ReshapeCallback(int w, int h)
{
	gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	// Set up a perspective projection
    float aspectRatio = (float) gWindowSizeX / (float) gWindowSizeY;
	gluPerspective(30.0f, aspectRatio, .1f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            pScene->GetCamera()->Strafe(10,0);
            break;
        case GLUT_KEY_RIGHT:
            pScene->GetCamera()->Strafe(-10,0);
            break;
        case GLUT_KEY_DOWN:
            pScene->GetCamera()->Strafe(0,-10);
            break;
        case GLUT_KEY_UP:
            pScene->GetCamera()->Strafe(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
    case 's': {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
        }
        break;
    case 'r':
        pScene->GetCamera()->Reset();
        break;
    case 'u':
        pScene->GetCamera()->ResetUp();
        break;
	case 'q':
		exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}


/**
 * Mouse event handler
 */
void MouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON
        || button == GLUT_RIGHT_BUTTON
        || button == GLUT_MIDDLE_BUTTON)
    {
        gMouseButton = button;
    } else
    {
        gMouseButton = -1;
    }
    
    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}


/**
 * Mouse active motion callback (when button is pressed)
 */
void MouseMotionCallback(int x, int y)
{
    if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
    {
        //compute delta
        float deltaX = x-gPreviousMouseX;
        float deltaY = y-gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;
        
        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON)
        {
            pScene->GetCamera()->Rotate(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_MIDDLE_BUTTON)
        {
            pScene->GetCamera()->Strafe(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_RIGHT_BUTTON)
        {
            pScene->GetCamera()->Zoom(deltaY);
        }
        
    } else
    {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }
    
}




//-----------------------------------------------
// Proj2 Ray Tracer
// This function follows the main
// logic of your rendering program.
// No command line inputs are necessary.
//-----------------------------------------------
int main(int argc, char** argv)
{

    // TO DO: Proj2 raytracer
    // CAP5705 - Set the render mode.
    // 1. Add a commandline parameter for the render mode
    // 2. Remove the global variable
    //------------------------------------------------
	mode = PHONG;
    //------------------------------------------------

    // Initializes the scene
    Setup();

    // run the ray tracer
    pRayTracer->Run(pScene, "output.png", mode);

    return 0;
}


#pragma endregion
