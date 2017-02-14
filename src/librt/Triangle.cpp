//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"


// contructor
Triangle::Triangle(void)
        : Surface()
{
	m_enmSurfaceType = SURFACE_TRIANGLE;

}

// clean up
Triangle::~Triangle()
{

}

Triangle::Triangle(STVector3 ptA, STVector3 ptB, STVector3 ptC)
{

	m_a = ptA;
	m_b = ptB;
	m_c = ptC;

	ComputeNormalVector();
	m_enmSurfaceType = SURFACE_TRIANGLE;
}

//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double &u, double&v, double&w)
{
    LinearSolver L;
    bool bFoundSolution = false;
    
    // TO DO: Proj2 raytracer
    // CAP5705 - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

	//		 Du + Ev + Fw + G = 0
	//       Hu + Iv + Jw + K = 0
	//       Lu + Mv + Nw + P = 0

    //------------------------------------------------------

	float fD = A.x - B.x;
	float fE = A.x - C.x;
	float fF = ray.Direction().x;
	float fG = ray.Origin().x - A.x;
	
	float fH = A.y - B.y;
	float fI = A.y - C.y;
	float fJ = ray.Direction().y;
	float fK = ray.Origin().y - A.y ;
	
	float fL = A.z - B.z;
	float fM = A.z - C.z;
	float fN = ray.Direction().z;
	float fP = ray.Origin().z- A.z;

	bFoundSolution = L.Run(fD, fE, fF, fG, fH, fI, fJ, fK, fL, fM, fN, fP, u, v, w);

    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection 
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

	double dBeta = 0.0f, dGamma = 0.0f, dT = 0.0f;
	bFound = IntersectionSolver(ray, m_a, m_b, m_c,dBeta, dGamma, dT); 

	if(dGamma < 0 || dGamma > 1) 
		return false;
	if(dBeta < 0 || dBeta > 1- dGamma)
		return false;
	if(dT<0)
		return false;

	//storing the surface, point, and the normal
	pIntersection->surface = this;
	pIntersection->point = STVector3(ray.Origin() + dT * ray.Direction()); //m_a + dBeta*m_v3AB + dGamma*m_v3AC;
	pIntersection->normal = m_v3normal;
	pIntersection->m_dTime = dT;

	m_intersections.push_back(*pIntersection);

	return bFound;

    //------------------------------------------------------//
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------

	//the direction vectors
	m_v3AB = m_b-m_a;
	m_v3AC = m_c-m_a;

	m_v3normal = STVector3::Cross(m_v3AB, m_v3AC);
	m_v3normal.Normalize();

    //---------------------------------------------------

    return(normal);
}

// TO DO: Proj2 raytracer
// CAP5705 - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
// 
//---------------------------------------------------------
//---------------------------------------------------------