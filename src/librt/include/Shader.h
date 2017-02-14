//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.h 
// Computes Shading
// RenderMode mode determines the type of shading algorithm used
// Given a normal, light direction, color and other shading input
//------------------------------------------------------------------------------------------------


#ifndef _SHADER_H
#define _SHADER_H

#include "STVector3.h"
#include "defs.h"
#include "Ray.h"


class Intersection;


class Shader {

public:

                                        Shader                          (void);
                                        ~Shader                         (void);

    void                                SetMode                         (RenderMode mode);

	RGBR_f                               Run                             (Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay);

	RGBR_f								 Run							 (Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay, RenderMode);

	


    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading functions for special effects.
    // 1. Declare functions for your special effects
    // 2. See the Run function to see when each shading function is called
    //---------------------------------------------------------
    //---------------------------------------------------------


private:

    RenderMode                          m_mode;

	float								m_fDLightIntensity;
	float								m_fALightIntensity;
	float								m_fSLightIntensity;

    RGBR_f                           Lambertian                      (Intersection *pIntersection, STVector3 *lightDirection);                                   
    RGBR_f                           Phong                           (Intersection *pIntersection, STVector3 *lightDirection, Ray* pRay);
	RGBR_f							 Mirror							 (Intersection* , STVector3*, Ray*);
	RGBR_f							 Ambient						 (Intersection *pIntersection);
};


#endif //_RAY_H