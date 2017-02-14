//----------------------------------------------------------------
// Plane.cpp
//----------------------------------------------------------------

#include "Plane.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

// constructor
Plane::Plane(void)
{
      m_center = STVector3(0,0,0);
	  m_v3Normal = STVector3(0,1,0);
	  m_dDistance = 0.0f;
}


// clean up here
Plane::~Plane()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Plane::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;
	
    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    // 2. Store the results of the intersection 
    // 3. if found and return true, otherwise, return false
    // NOTE: The IntersectionPoint pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

	double dotProduct = STVector3::Dot(ray.Direction(), m_v3Normal);
	if(dotProduct == 0)
	{
		//ray is parellal
		return false;
	}
	else
	{

		double val;
		
		pIntersection->surface = this;
		pIntersection->point = STVector3(ray.Origin() + val * ray.Direction());

	}


   //------------------------------------------------------

   return(bFound);
}

STVector3 Plane::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------
	//m_v3Normal = STVector3::Cross(m_v3AB, m_v3AC);
	//m_v3Normal.Normalize();

    //---------------------------------------------------

    return(normal);
}

