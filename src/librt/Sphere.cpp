//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

// constructor
Sphere::Sphere(void)
    : m_radius(0.5)
{
      m_center = STVector3(0,0,0);
	  m_enmSurfaceType = SURFACE_SPHERE;
}


// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
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

	double a = 0, b = 0, c = 0, discriminant = 0;
	double root1 = 0, root2 = 0, closerRoot = 0, fartherRoot = 0;

	STVector3 v3Diff;
	v3Diff.x = ray.Origin().x - m_center.x;
	v3Diff.y = ray.Origin().y - m_center.y;
	v3Diff.z = ray.Origin().z - m_center.z;

	//solving quadratic equation 
	a = ray.Direction().x * ray.Direction().x + ray.Direction().y * ray.Direction().y + ray.Direction().z * ray.Direction().z; 
	b = 2 * (ray.Direction().x * v3Diff.x + ray.Direction().y * v3Diff.y + ray.Direction().z * v3Diff.z);
	c = v3Diff.x * v3Diff.x + v3Diff.y * v3Diff.y + v3Diff.z * v3Diff.z - (m_radius * m_radius);

	discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		bFound = true;
		root1 = (-1*b - sqrt(discriminant) )/ (2 * a);
		root2 = (-1*b + sqrt(discriminant) )/ (2 * a);
	}
	else 
		return false;

	if(root1 < T_LOWER || root2 < T_LOWER )
		return false;

	//if(root1 == 0)
	//	closerRoot = root2;
	//else if (root2 == 0)
	//	closerRoot = root1;
	//else if (abs(root1) < abs(root2) /*&& root1 > 0*/) 
	//{
	//	closerRoot = root1;
	//	fartherRoot = root2;
	//}
	//else 
	//{
	//	closerRoot = root2;
	//	fartherRoot = root1;
	//}

	/*if(closerRoot >50)
		return false;*/

	STVector3 ptEntry, ptExit;

	ptEntry = STVector3(ray.Origin() + root1* ray.Direction());
	ptExit = STVector3(ray.Origin() + root2 * ray.Direction());;

	float mag1 = sqrt(ptEntry.x*ptEntry.x + ptEntry.y*ptEntry.y + ptEntry.z*ptEntry.z);
	float mag2 = sqrt(ptExit.x*ptExit.x + ptExit.y*ptExit.y + ptExit.z*ptExit.z);

	if(mag1 < mag2)
		closerRoot = root1;
	else
		closerRoot = root2;

	pIntersection->surface = this;
	pIntersection->point = STVector3(ray.Origin() + closerRoot * ray.Direction());
	pIntersection->normal = ((pIntersection->point - m_center) / m_radius);
	pIntersection->m_dTime = closerRoot;

	m_intersections.push_back(*pIntersection);

   //------------------------------------------------------

   return(bFound);
}

