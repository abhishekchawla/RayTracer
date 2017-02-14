//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"
#include "Surface.h"



Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
	m_fDLightIntensity = 2.0f;
	m_fALightIntensity = 1.0f;
	m_fSLightIntensity = 1.0f;
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}

// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
			color = Phong(pIntersection, lightDirection, pRay);
            break;

		case MIRROR:
			color =  Mirror(pIntersection, lightDirection, pRay);
			break;

        default:
            color = Lambertian(pIntersection, lightDirection);
            break;
        }

    // TO DO: Proj2 raytracer
    // CAP5705 - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay, RenderMode mode)
{
    RGBR_f color;

    switch (mode) {\
	case AMBIENT:
		color = Ambient(pIntersection);
		break;
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
			color = Phong(pIntersection, lightDirection, pRay);
            break;
       
		case MIRROR:
			color =  Mirror(pIntersection, lightDirection, pRay);
			break;

        default:
            color = Lambertian(pIntersection, lightDirection);
            break;
        }

    // TO DO: Proj2 raytracer
    // CAP5705 - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}

RGBR_f Shader::Ambient(Intersection *pIntersection)
{
	RGBR_f color;

	Surface* pSurface = pIntersection->surface;

	color.r = pSurface->GetAmbientColor().r * m_fALightIntensity;
	color.b = pSurface->GetAmbientColor().g * m_fALightIntensity;
	color.g = pSurface->GetAmbientColor().b * m_fALightIntensity;
	color.a = 1.0f;

	return color;

}

// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection)
{
    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
    //    normal and light direction
    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

	Surface *pSurface = pIntersection->surface;
	
	float dotProduct = STVector3::Dot(pIntersection->normal, (*lightDirection));

	if (dotProduct < 0)
		dotProduct = 0;

	color.r = pSurface->GetDiffuseColor().r * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().r * m_fALightIntensity;
	color.g = pSurface->GetDiffuseColor().g * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().g * m_fALightIntensity;
	color.b = pSurface->GetDiffuseColor().b * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().b * m_fALightIntensity;
	color.a = 1.0f;

    //---------------------------------------------------------

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay)
{
    assert(pIntersection);
    assert(lightDirection);
	assert(pRay);

    RGBR_f color;

	Surface *pSurface = pIntersection->surface;

	float dotProduct = STVector3::Dot(pIntersection->normal, (*lightDirection));
	if (dotProduct < 0)
		dotProduct = 0;

	color.r = pSurface->GetDiffuseColor().r * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().r * m_fALightIntensity;
	color.g = pSurface->GetDiffuseColor().g * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().g * m_fALightIntensity;
	color.b = pSurface->GetDiffuseColor().b * dotProduct * m_fDLightIntensity + pSurface->GetAmbientColor().b * m_fALightIntensity;
	color.a = 1.0f;

	STVector3 v3HalfVector = -1*(pRay->Direction()) + *lightDirection;
	v3HalfVector.Normalize();

	dotProduct = STVector3::Dot(pIntersection->normal, v3HalfVector);
	if(dotProduct < 0)
		dotProduct = 0;

	color.r += pSurface->GetSpecularColor().r * m_fSLightIntensity * pow(dotProduct, 50);
	color.g += pSurface->GetSpecularColor().g * m_fSLightIntensity * pow(dotProduct, 50);
	color.b += pSurface->GetSpecularColor().b * m_fSLightIntensity * pow(dotProduct, 50);

	if(color.r > 1)
		color.r = 1;

	if(color.g > 1)
		color.g = 1;

	if(color.b > 1)
		color.b = 1;

	//Shadows

    // TO DO: Proj2 raytracer
    // CAP5705 - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to 
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


RGBR_f Shader::Mirror(Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay)
{
	RGBR_f color;


	Phong(pIntersection, lightDirection, pRay);

	return color;
}

Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
// CAP5705 - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

