//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Plane.h
// Plane surface object
//------------------------------------------------------------------------------


#ifndef __PLANE_H__
#define __PLANE_H__



#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"


class Plane  : public Surface 
{



public:


	Plane                              (void);
	~Plane                             (void);

	Plane(STVector3 center, double distance, STVector3 normal)
	{
		m_center = center;
		m_dDistance = distance;
		m_v3Normal = normal;
		
	}


    bool                FindIntersection                    (Ray ray, Intersection *pIntersection);

	STVector3 ComputeNormalVector(void);

private:

	STVector3			m_v3Normal;
	double				m_dDistance;

	STVector3			m_a, m_b, m_c, m_d;

};


#endif //__Plane_H__

