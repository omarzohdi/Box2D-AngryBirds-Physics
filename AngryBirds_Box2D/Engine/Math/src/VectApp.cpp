/*****************************************************************************/
/*                                                                           */
/* File: VectApp.cpp                                                         */
/*                                                                           */
/* Vector Application Class                                                  */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* system includes:                                                          */
/*****************************************************************************/
   
/*****************************************************************************/
/* user includes:                                                            */
/*****************************************************************************/

#include "MathEngine.h"
#include "MathApp.h"


/*****************************************************************************
* LERP - linear interpolation
*
* This function returns a point on a line segment given in parametric form. 
* Where the inputs are point a (starting point), point b (ending point) of  
* the line segment and the parametric variable t.  If t is in the range of  
* ranging from t=0.0 to 1.0, this function returns a point on the line      
* segment. If t=0.0 this function returns point a, if t=1.0 this returns    
* point b.  Values of t<0.0 return points on the infinite line defined      
* before point a. Values of t>1.0 returns points on the infinite line       
* defined after point b.                                                    
*
* inputs:
*		a - point A
*		b - point B
*		t - parametric t
*
* @return Vector (point) linearly interpolated based on parametric t
*
* Example:
*
*     Vect   v1(1.0f, 2.0f, 3.0f);   // create v1=[1,2,3,1]
*     Vect   v2(-5.0f, 2.0f, 7.0f);  // create v2=[-5,2,7,1]
*     Vect   out;                    // create out vector
*
*     out =	lineParametric (v1, v2, 0.4f );  // t = 0.4f

******************************************************************************/

void VectApp :: Lerp(Vect &out, const Vect &a, const Vect &b, const float t)
{
	// out = a + t * (b - a);   has 3 temporaries
	out.set(a[x] + t*(b[x]-a[x]),
			a[y] + t*(b[y]-a[y]),
			a[z] + t*(b[z]-a[z]) );
} 

void VectApp :: LerpArray(Vect *out, const Vect *a, const Vect *b, const float t, const int numVects)
{

	// out = a + t * (b - a);  // has 3 temporaries
	// Rewritten to remove all temporaries
	// Todo: compare preformance bewteen original versus non-temp version

	for( int i = 0; i < numVects; i++ )
		{
		Lerp( out[i], a[i],b[i],t);
		}
	
} 



/***** END of File VectApp.cpp ***********************************************/
