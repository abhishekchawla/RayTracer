//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>



Surface::Surface(void)
{
	m_clr4Diffuse	= STColor4f(65.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 255.0f/255.0f);
	m_clr4Specular	= STColor4f(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f, 255.0f/255.0f);
	m_clr4Ambient	= STColor4f(40.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 255.0f/255.0f);
	m_fPhongExponent = 1.0f;
}


Surface::~Surface()
{

}

void Surface::SetPhongExponent(float fVal)
{
	m_fPhongExponent = fVal;
}

float Surface::GetPhoneExponent()
{
	return m_fPhongExponent;
}

STColor4f Surface::GetSpecularColor()
{
	return m_clr4Specular;
}


STColor4f Surface::GetDiffuseColor()
{
	return m_clr4Diffuse;
}


STColor4f Surface::GetAmbientColor()
{
	return m_clr4Ambient;
}

void Surface::SetSpecularColor(STColor4f color)
{
	m_clr4Specular = color;
}


void Surface::SetDiffuseColor(STColor4f color)
{
	m_clr4Diffuse = color;
}


void Surface::SetAmbientColor(STColor4f color)
{
	m_clr4Ambient = color;
}

int Surface::FindClosestIntersection(Intersection *pIntersection)
{
    // TO DO: Proj2 raytracer
    // CAP5705 - Find the closest intersection.
    // 1. Return the closest intersection in m_intersections
    //    0 returned for no intersection; otherwise the number
    //    of close intersections within a small threshold
    //    and the pIntersection is updated with the closest intersection
    //------------------------------------------------
    //------------------------------------------------

    return(0);
}
 
SURFACETYPE Surface::GetSurfaceType()
{
	return m_enmSurfaceType;
}


