/*****************************************************************************/
/*                                                                           */
/* File: QuatApp.cpp                                                         */
/*                                                                           */
/* Quaternioin Application Class                                             */
/*                                                                           */
/*****************************************************************************/

#include "MathEngine.h"
#include "MathApp.h"
#include <math.h>



/** 
 * Mutates result to be a slerp between the source and target by the
 * specified factor.
 * For a factor of 0.0, result == source.
 * For a factor of 1.0, result == target.
 */
void QuatApp::Slerp( Quat &result, const Quat &src, const Quat &tar, const float slerpFactor )
{
	Quat	target;

	// Constants.
	const float QUAT_EPSILON = 0.001f;
	
	float cosom = src.dot(tar);
	if( cosom >= 1.0f)
	{
		// do nothing
		result = src;
	}
	else
	{
	// adjust signs if necessary
	if ( cosom < 0.0f )
		{
		cosom = -cosom;
		target = -tar;
		}
	else
		{
		target = tar;
		}

	// If the the source and target are close, we can do a lerp.
	float tarFactor = slerpFactor;
	float srcFactor = 1.0f - slerpFactor;

	// calculate coefficients
	if ( cosom < (1.0f - QUAT_EPSILON) )
		{
		// Quats are not close enough for a lerp.
		// Calculating coefficients for a slerp.
		const float omega = acosf( cosom );
		const float sinom = 1.0f / sinf( omega );
	  
		srcFactor = sinf( srcFactor * omega ) * sinom;
		tarFactor = sinf( tarFactor * omega ) * sinom;
		}


		result.set(src[x] * srcFactor + target[x] * tarFactor,
			       src[y] * srcFactor + target[y] * tarFactor,
			       src[z] * srcFactor + target[z] * tarFactor,
			       src[w] * srcFactor + target[w] * tarFactor);
	}

};

void QuatApp::SlerpArray( Quat *out, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats )
{


	for( int i = 0; i < numQuats; i++ )
		{
		Slerp( out[i], source[i], target[i],slerpFactor);
		}
	
} ;


/***** END of File QuatApp.cpp ***********************************************/
