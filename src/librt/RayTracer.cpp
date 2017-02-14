//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#pragma once
#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"
#include "Surface.h"


RayTracer::RayTracer(void)
    : m_maxLevel            (20),
     m_intensityThreshold   (0.001)
{
    pShader = new Shader();
}


RayTracer::~RayTracer()
{
	delete pShader;
}


//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------
void RayTracer::Run(Scene *pScene, std::string fName, RenderMode mode)
{
    // begin 
    std::cout << "Running... " << std::endl;

    // the color redult from shading
    RGBR_f color;

    // set the shader's render mode
    pShader->SetMode(mode);

	float fWidth = 1280/2;
	float fHeight = 720/2;
	float fAspectRatio = fHeight/fWidth;


    // TO DO: Proj2 raytracer
    // CAP5705 - Implement the ray tracing algorithm.
    // 1. Cast a ray from the camera into the scene
    // 2. For every object in the scene compute intersections
    // 3. Compute shading for the closest intersections
    //       - no interection means shade to the background color
    //       - one intersection - great compute shading
    //       - otherwise implement any special handling resolve
    //         ambiguities (determine the best choice or throw an exception)
    // 4. Save the output image
    // NOTE: STImage stores colors in pixels in the range 0-255
    // If you compute color channels in a range 0-1 you must convert
    //------------------------------------------------

	/*float xIncVector = (U*2*halfWidth)/xResolution;
    float yIncVector = (V*2*halfHeight)/yResolution;*/

	
	//Defining the projection plane
	//---------------------------------------------------------------------------------------------//
	float fFOV = 90;
	fFOV =  DegreesToRadians(fFOV);

	float fVPHalfWidth= tan(fFOV/2);
	float fVPHalfHeight = fAspectRatio*fVPHalfWidth;

	STVector3 v3VPBottomLeft = pScene->GetCamera()->LookAt()- pScene->GetCamera()->Up()*fVPHalfHeight - pScene->GetCamera()->Right()*fVPHalfWidth;
	STVector3 fXIncrement = (pScene->GetCamera()->Right()*2*fVPHalfWidth)/fWidth;
	STVector3 fYIncrement = (pScene->GetCamera()->Up()*2*fVPHalfHeight)/fHeight;	
	//---------------------------------------------------------------------------------------------//

    RGBR_f bkground = pScene->GetBackgroundColor();
    STImage *pImg = new STImage(fWidth, fHeight, STImage::Pixel(bkground.r*255, bkground.g*255, bkground.b*255, bkground.a*255));

	Intersection viewRayIntersection;
	Ray ray;
	ray.SetOrigin(pScene->GetCamera()->Position());

	for(int i = 0; i < fWidth; i++)
	{	
		for(int j = 0; j < fHeight; j++)
		{
			STVector3 viewPlanePoint = v3VPBottomLeft + i*fXIncrement + j*fYIncrement;
			STVector3 castRay = viewPlanePoint - pScene->GetCamera()->Position();
			castRay.Normalize();
			ray.SetDirection(castRay);

			int bRetVal = 0;
			bRetVal = pScene->FindIntersection(ray, &viewRayIntersection, false);
			
			if(bRetVal)
			{
				RGBR_f finalColor(0.0f, 0.0f, 0.0f, 1.0f);
				int nNumberOfLights = pScene->GetLightsList()->size();
				for(int nLight = 0; nLight<nNumberOfLights; nLight++)
				{
					STVector3 v3LightDirection = pScene->GetLightDirection(nLight, viewRayIntersection.point);
					RGBR_f shadedColor;
					shadedColor= pShader->Run(&viewRayIntersection, &v3LightDirection , &ray, PHONG);
					
					//------------------------Shadowing start-------------------------------------------------------------//
					Ray shadowRay;		

					STVector3 v3ShadowRayDirection = v3LightDirection;
					shadowRay.SetDirection(v3ShadowRayDirection);

					STVector3 v3ShadowRayOrigin = viewRayIntersection.point + .001*v3ShadowRayDirection;
					shadowRay.SetOrigin(v3ShadowRayOrigin);
				
					Intersection shadowRayIntersection;
					bRetVal = pScene->FindIntersection(shadowRay, &shadowRayIntersection, false);
					if(bRetVal) //point lies under a shadow
					{
						
						if(shadowRayIntersection.surface != viewRayIntersection.surface)
						{
							viewRayIntersection.m_bLiesUnderShadow = true;
							//shadedColor = pShader->Run(&viewRayIntersection, &v3LightDirection, &ray, AMBIENT);
							shadedColor.r = 10.0f/255.0f;
							shadedColor.g = 10.0f/255.0f;
							shadedColor.b = 10.0f/255.0f;
						}
					}
					//------------------------Shadowing end---------------------------------------------------------------//

					//-------------- Reflection start---------------------------------------------------------------------------------//
					if(viewRayIntersection.surface->GetSurfaceType() == SURFACE_TRIANGLE)
					{
						Ray reflectedRay;	
						STVector3 v3Temp = 2*(STVector3::Dot(-1*ray.Direction(), viewRayIntersection.normal)*viewRayIntersection.normal);
						STVector3 v3ReflectedRayDirection = ray.Direction() + v3Temp;
						reflectedRay.SetDirection(v3ReflectedRayDirection);
					
						STVector3 v3reflectedRayOrigin = viewRayIntersection.point + .001*v3ReflectedRayDirection;
						reflectedRay.SetOrigin(v3reflectedRayOrigin);

						Intersection reflectedRayIntersection;
						bRetVal = pScene->FindIntersection(reflectedRay, &reflectedRayIntersection, false);

						if(bRetVal)  //reflected ray intersects a surface
						{
							RGBR_f reflectedColor = pShader->Run(&reflectedRayIntersection, &v3LightDirection , &reflectedRay, PHONG);
							{
								shadedColor.r = 0.5*shadedColor.r + 0.5*reflectedColor.r;
								shadedColor.g = 0.5*shadedColor.g + 0.5*reflectedColor.g;
								shadedColor.b = 0.5*shadedColor.b + 0.5*reflectedColor.b;
							}

							Ray shadowRay2;	//do a shadow ray tracing to find if the intersected point lies under a shadow	

							shadowRay2.SetDirection(v3ShadowRayDirection);

							STVector3 v3ShadowRayOrigin2 = reflectedRayIntersection.point + .001*v3ShadowRayDirection;
							shadowRay2.SetOrigin(v3ShadowRayOrigin2);
				
							Intersection shadowRayIntersection2;
							bRetVal = pScene->FindIntersection(shadowRay2, &shadowRayIntersection2, false);
							if(bRetVal) //point lies under a shadow
							{
								if(shadowRayIntersection2.surface != reflectedRayIntersection.surface)
								{
									//RGBR_f tempColor = pShader->Run(&reflectedRayIntersection, &v3LightDirection, &reflectedRay, AMBIENT);
									shadedColor.r = 0.5*10.0f/255.0f;
									shadedColor.g = 0.5*10.0f/255.0f;
									shadedColor.b = 0.5*10.0f/255.0f;
								}
									
							}
						}
					}

					//--------------Reflection end---------------------------------------------------------------------------------//

					finalColor.r += shadedColor.r;
					finalColor.g += shadedColor.g;
					finalColor.b += shadedColor.b;
				}

				if(finalColor.r > 1)
					finalColor.r = 1;

				if(finalColor.g > 1)
					finalColor.g = 1;
				
				if(finalColor.b > 1)
					finalColor.b = 1;

				if(finalColor.a > 1)
					finalColor.a = 1;

				//Uncomment to view the basic ray tracing results(no shading, shadows, etc.)
				/*finalColor.r = viewRayIntersection.surface->GetDiffuseColor().r * 1.5f;
				finalColor.g = viewRayIntersection.surface->GetDiffuseColor().g * 1.5f;
				finalColor.b = viewRayIntersection.surface->GetDiffuseColor().b * 1.5f;*/

				pImg->SetPixel(i, j, STColor4ub(finalColor.r * 255, finalColor.g * 255, finalColor.b* 255, finalColor.a * 255));
				
			}

			else
				pImg->SetPixel(i, j, STColor4ub(0, 0, 0, 255));
		}
	}

    ///-----------------------------------------------

    // end
    std::cout << "DONE... " << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}


// This function computes all of the shading
// Recursively bounce the ray from object to object
// Use the Shader class to compute the final shading
RGBR_f RayTracer::Shade(Scene *pScene, Intersection *pIntersection)
{
    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Calculate the shading.
    // 1. Bounce the ray from object to object
    // 2. Compute the shading using the functions in the
    //    Shader class, attributes in pIntersection, and information
    //    about your scene
    // 3. Remember to stop the recursion
    //------------------------------------------------

    //-----------------------------------------------

    return(color);
}


//------------------------------------------------------
// Always render with a minimum color so that the scene
// is not black
//------------------------------------------------------
bool RayTracer::MinimumColor(RGBR_f color)
{
    if((color.r  >= m_intensityThreshold) ||
       (color.g >= m_intensityThreshold) ||
       (color.b >= m_intensityThreshold)) {
        return(true);
    }

   
    return(false);
}

