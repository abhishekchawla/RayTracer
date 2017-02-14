//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _SURFACE_H
#define _SURFACE_H


#define T_UPPER 100
#define T_LOWER 0

#include "STVector3.h"
#include "STColor4f.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"


typedef enum
{
	SURFACE_NONE=0,
	SURFACE_TRIANGLE,
	SURFACE_SPHERE

}SURFACETYPE; 

class Surface
{

    public:
                                    Surface                             (void);
                                    ~Surface                            (void);

    virtual bool                    FindIntersection                     (Ray ray, Intersection *pIntersection){ return(false);} 
    int                             FindClosestIntersection             (Intersection *pIntersection);

	STColor4f						GetDiffuseColor();
	STColor4f						GetAmbientColor();
	STColor4f						GetSpecularColor();
	float							GetPhoneExponent();

	void							SetDiffuseColor(STColor4f);
	void							SetAmbientColor(STColor4f);
	void							SetSpecularColor(STColor4f);
	void							SetPhongExponent(float);
	SURFACETYPE						GetSurfaceType();
	

protected:
    

    // TO DO: Proj2 raytracer
    // CAP5705 - Note: You have to manage your intersection list
    // 1. Know when to clear and add items to your list
    //------------------------------------------------
    //------------------------------------------------
    IntersectionList                m_intersections;

    STVector3                       m_center;

private:

	RGBR_f							m_color;

	STColor4f						m_clr4Diffuse;
	STColor4f						m_clr4Ambient;
	STColor4f						m_clr4Specular;

	float							m_fPhongExponent;

protected:

	SURFACETYPE						m_enmSurfaceType;






};


#endif //_SURFACE_H



