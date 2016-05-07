/*****************************************************************************/
/*                                                                           */
/* File: Quat.cpp                                                            */
/*                                                                           */
/* Quaterion Class                                                           */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* system includes:                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* user includes:                                                            */
/*****************************************************************************/


#include "MathEngine.h"
#include <math.h>
#include <assert.h>







Quat :: Quat ( void )
:qx(0.0f), qy(0.0f),qz(0.0f),qw(1.0f)
{



} /* QUAT() */



float & Quat::operator[] (const enum x_enum)	{	return this->qx;	};
float & Quat::operator[] (const enum y_enum)	{	return this->qy;	};
float & Quat::operator[] (const enum z_enum)	{	return this->qz;	};
float & Quat::operator[] (const enum w_enum)	{	return this->qw; };


const float Quat::operator[] (const enum x_enum) const { return this->qx; };
const float Quat::operator[] (const enum y_enum) const { return this->qy; };
const float Quat::operator[] (const enum z_enum) const { return this->qz; };
const float Quat::operator[] (const enum w_enum) const { return this->qw; };



void Quat :: set( const float vx, const float vy, const float vz, const float qReal )
{
	this->qx = vx;
	this->qy = vy;
	this->qz = vz;
	this->qw = qReal;

}

void Quat :: set( const Vect &vIn, const float qReal )
{
   this->qx = vIn[x];
   this->qy = vIn[y];
   this->qz = vIn[z];
   this->qw = qReal;
}

Quat :: Quat( const float vx, const float vy, const float vz, const float qReal )
:qx(vx),qy(vy),qz(vz),qw(qReal)
{

}


Quat :: Quat ( const Quat &q )
:qx(q.qx),qy(q.qy),qz(q.qz),qw(q.qw)
{

}

Quat :: Quat( const Vect &vect, const float qReal )
:qx(vect[x]),qy(vect[y]),qz(vect[z]),qw(qReal)
{

}



Quat :: ~Quat ( void )
{

} /* ~Quat() */


void Quat :: set( const Matrix &M )
{


float tr = M[m0] + M[m5] + M[m10];

if (tr > 0.0f) 
{ 
  float S = sqrtf(tr+1.0f) * 2.0f; // S=4*qw 
  this->qw = 0.25f * S;
  this->qx = -(M[m9] - M[m6]) / S;
  this->qy = -(M[m2] - M[m8]) / S; 
  this->qz = -(M[m4] - M[m1]) / S; 
} 
else if ((M[m0] > M[m5]) && (M[m0] > M[m10])) 
{ 
  float S = sqrtf(1.0f + M[m0] - M[m5] - M[m10]) * 2.0f; // S=4*qx 
  this->qw = -(M[m9] - M[m6]) / S;
  this->qx = 0.25f * S;
  this->qy = (M[m1] + M[m4]) / S; 
  this->qz = (M[m2] + M[m8]) / S; 
} 
else if (M[m5] > M[m10]) 
{ 
  float S = sqrtf(1.0f + M[m5] - M[m0] - M[m10]) * 2.0f; // S=4*qy
  this->qw = -(M[m2] - M[m8]) / S;
  this->qx = (M[m1] + M[m4]) / S; 
  this->qy = 0.25f * S;
  this->qz = (M[m6] + M[m9]) / S; 
} 
else 
{ 
  float S = sqrtf(1.0f + M[m10] - M[m0] - M[m5]) * 2.0f; // S=4*qz
  this->qw = -(M[m4] - M[m1]) / S;
  this->qx = (M[m2] + M[m8]) / S;
  this->qy = (M[m6] + M[m9]) / S;
  this->qz = 0.25f * S;
}


}





// by matrix ( essentially Quat to Matrix conversion, flag if Matrix is not pure rotation )
Quat :: Quat ( const Matrix &m )
{
	this->set( m );
}


Quat::Quat( const MatrixSpecialType  value )
{
	switch (value)
	{
		case IDENTITY:
			this->set(0.0f,0.0f,0.0f,1.0f);
			break;
		case ZERO:
			this->set(0.0f,0.0f,0.0f,0.0f);
			break;
	}
}

void Quat::set( const MatrixSpecialType  value )
{
	switch (value)
	{
		case IDENTITY:
			this->set(0.0f,0.0f,0.0f,1.0f);
			break;
		case ZERO:
			this->set(0.0f,0.0f,0.0f,0.0f);
			break;
	}
}

Quat :: Quat( const RotType mode, const float angle )
{
	switch(mode)
		{
		case ROT_X:
			this->setRotX( angle );
			break;
		case ROT_Y:
			this->setRotY( angle );
			break;
		case ROT_Z:
			this->setRotZ( angle );
			break;
		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}

Quat :: Quat( Rot3AxisType mode, const float angle_0, const float angle_1, const float angle_2 )
{
	switch(mode)
		{
		case ROT_XYZ:
			this->setRotXYZ( angle_0, angle_1, angle_2 );
			break;

		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}

void Quat :: set( Rot3AxisType mode, const float angle_0, const float angle_1, const float angle_2 )
{
	switch(mode)
		{
		case ROT_XYZ:
			this->setRotXYZ( angle_0, angle_1, angle_2 );
			break;

		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}

void Quat :: set( const RotType mode, const float angle )
{
	switch(mode)
		{
		case ROT_X:
			this->setRotX( angle );
			break;
		case ROT_Y:
			this->setRotY( angle );
			break;
		case ROT_Z:
			this->setRotZ( angle );
			break;
		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}


void Quat :: setRotXYZ( const float a, const float b, const float c )
{
   Quat qx(ROT_X, a);
   Quat qy(ROT_Y, b);
   Quat qz(ROT_Z, c);

   *this = qx * qy * qz;


}	/* RotXIdent */

void Quat :: setRotX( const float a )
{
	const float angle = a * 0.5f;

	this->qx = sinf(angle);
	this->qy = 0.0f;
	this->qz = 0.0f;
	this->qw = cosf(angle);

}	/* RotXIdent */


void Quat :: setRotY( const float a)
{
	const float angle = a * 0.5f;

	this->qx = 0.0f;
	this->qy = sinf(angle);
	this->qz = 0.0f;
	this->qw = cosf(angle);

}	/* RotYIdent */


void Quat :: setRotZ( const float a )
{
	const float angle = a * 0.5f;

	this->qx = 0.0f;
	this->qy = 0.0f;
	this->qz = sinf(angle);
	this->qw = cosf(angle);

}	/* RotZIdent */




// Quat * Quat
Quat Quat :: operator*(const Quat &B) const 
{
	const Vect &qV = (const Vect &)(*this);
	const Vect &BqV = (const Vect &)(B);

	Vect vtmp = this->qw * BqV;
	vtmp += (B.qw * qV);
	vtmp += (BqV.cross(qV));
	
	// Scalar component
	const float tmp = (this->qw * B.qw) - qV.dot(BqV);


	return( Quat( vtmp, tmp) );			

} /* Quat * Quat */

// Overload the = operator
const Quat & Quat :: operator=(const Matrix &m)
{

	this->set( m );
	
	return (*this);
}

void Quat :: Lqvqc(const Vect &vIn, Vect &vOut) const
{
    const Vect &qV = (const Vect &)(*this);

    vOut = (2.0f * qV[w]) * vIn.cross(qV);
    vOut += ( qV[w] * qV[w] - qV.dot(qV) ) * vIn;
	vOut += qV *( 2.0f * qV.dot(vIn) );
}

void Quat :: Lqcvq(const Vect &vIn, Vect &vOut) const
{
	const Vect &qV = (const Vect &)(*this);

	vOut = (2.0f * qV[w]) * qV.cross(vIn);
	vOut +=  vIn *( qV[w] * qV[w] - qV.dot(qV));
	vOut +=  qV*( 2.0f * qV.dot(vIn) );
}




// Quat * Matrix 
Matrix Quat :: operator*(const Matrix &m) const
{
	// TODO: do this mess by hand!
	Matrix mtmp(*this);

    return( Matrix( mtmp * m ) );
}



// Quat *= Matrix 
const Quat & Quat :: operator*=(const Matrix &m)
{
	// Make sure that matrix is a rotation matrix
	assert( m.isRotation(MATH_TOLERANCE) );

	// Make Quaternion a Matrix
	Matrix mtmp(*this);

	//Multiply matrix by matrix, replace the original quaternion
	*this = Quat( mtmp * m );

	return ( *this );
}

void Quat :: setRotAxisAngle(const Vect &axis, const float angle)
{
	const float angle_a = 0.5f * angle;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_a);
	sin_a = sinf(angle_a);

	Vect qV = axis.getNorm();

	qV *= sin_a;
	this->qx = qV[x];
	this->qy = qV[y];
	this->qz = qV[z];
	this->qw = cos_a;
}

Quat::Quat( const RotAxisAngleType , const Vect &vAxis, const float angle )
{
	this->setRotAxisAngle(vAxis, angle);
}


void Quat :: set( const RotAxisAngleType , const Vect &axis, const float angle )
{
	this->setRotAxisAngle(axis, angle);
}


const float Quat :: getAngle(void) const
{

	float angle;
	angle = 2.0f * acosf( this->qw );
	return(angle);
}




void Quat :: getVect( Vect &vIn ) const
{
	vIn[x] = this->qx;
	vIn[y] = this->qy;
	vIn[z] = this->qz;
	vIn[w] = 1.0f;

}	



void Quat :: getAxis( Vect &vIn ) const
{
	vIn[x] = this->qx;
	vIn[y] = this->qy;
	vIn[z] = this->qz;
	vIn[w] = 1.0f;

}



Quat :: Quat( const RotOrientType mode, const Vect &dof, const Vect &vup)
{
	
	Matrix mtmp;
	switch(mode)
		{
		case ROT_ORIENT:
			mtmp.set(ROT_ORIENT, dof, vup );
			this->set(mtmp);
			break;
		case ROT_INVERSE_ORIENT:
			mtmp.set(ROT_INVERSE_ORIENT, dof, vup );
			this->set(mtmp);
			break;
		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}

void Quat :: set( const RotOrientType mode, const Vect &dof, const Vect &vup)
{
	
	Matrix mtmp;
	switch(mode)
		{
		case ROT_ORIENT:
			mtmp.set(ROT_ORIENT, dof, vup );
			this->set(mtmp);
			break;
		case ROT_INVERSE_ORIENT:
			mtmp.set(ROT_INVERSE_ORIENT, dof, vup );
			this->set(mtmp);
			break;
		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}


void Quat :: setVect( const Vect &vIn )
{

	

	this->qx = vIn[x];
	this->qy = vIn[y];
	this->qz = vIn[z];
	
}



#if 0










/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_X_PI2_ENUM )
//:VectBase(MATH_INV_SQRT_2,0.0f,0.0f,MATH_INV_SQRT_2)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_Y_PI2_ENUM )
//:VectBase(0.0f,MATH_INV_SQRT_2,0.0f,MATH_INV_SQRT_2)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_Z_PI2_ENUM )
//:VectBase(0.0f,0.0f,MATH_INV_SQRT_2,MATH_INV_SQRT_2)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_X_PI_ENUM )
//:VectBase(1.0f,0.0f,0.0f,0.0f)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_Y_PI_ENUM )
//:VectBase(0.0f,1.0f,0.0f,0.0f)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
//Quat :: Quat ( const ROT_Z_PI_ENUM )
//:VectBase(0.0f,0.0f,1.0f,0.0f)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//}










/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/







/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
// by matrix ( essentially Quat to Matrix conversion, flag if Matrix is not pure rotation )
void Quat :: set ( const Matrix &m )
{
	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
	UNINITIALIZED_MATRIX_ELEMENT_CHECK(m);

	this->setMatrixToQuat( m );
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: set( const IDENTITY_ENUM mode)
{
	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
	this->setIdentity();
	MATH_UNUSED(mode);

}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: set( const ZERO_ENUM mode)
{
	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
	this->setZero();
	MATH_UNUSED(mode);

}









	 	 

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: set( const ROT_AXIS_ANGLE_ENUM mode, const VectBase &axis, const float angle )
{
	NO_UNINITIALIZED_MATRIX_CHECK_NEEDED;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(axis);
	
	switch(mode)
		{
		case ROT_AXIS_ANGLE:
			this->setRotAxisAngle(axis.getVect(),angle);
			break;
		case ROT_AXIS_ANGLE_UNIT_VECTORS:
			this->setRotAxisAngleNormalized(axis.getVect(),angle);
			break;
		default:
			MATHASSERT( MATH_ALWAYS_FAIL );
			break;
	}	
}


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: set( const ROT_ORIENTATION_ENUM mode, const VectBase &dof, const VectBase &vup)
{
	NO_UNINITIALIZED_MATRIX_CHECK_NEEDED;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(dof);
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(vup);

	switch(mode)
		{
		case ROT_ORIENT:
			this->setRotOrient( dof.getVect(), vup.getVect() );
			break;
		case ROT_INVERSE_ORIENT:
			this->setRotInvOrient( dof.getVect(), vup.getVect() );
			break;
		case ROT_ORIENT_UNIT_VECTORS:
			this->setRotOrientNormalized( dof.getVect(), vup.getVect() );
			break;
		case ROT_INVERSE_ORIENT_UNIT_VECTORS:
			this->setRotInvOrientNormalized( dof.getVect(), vup.getVect() );
			break;
		default:
			MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}





/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: getVect( Vect4D &vIn ) const
{
	UNINITIALIZED_QUAT_CHECK;

	vIn.v.x = this->v.x;
	vIn.v.y = this->v.y;
	vIn.v.z = this->v.z;
	vIn.v.w = 0.0f;
// BANG
//	v.set(this->qV[px],this->qV[py],this->qV[pz],0.0f);
}	



/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: getAxis( Vect4D &vIn ) const
{
	UNINITIALIZED_QUAT_CHECK;
	vIn.v.x = this->v.x;
	vIn.v.y = this->v.y;
	vIn.v.z = this->v.z;
	vIn.v.w = 0.0f;

// BANG
//v.set(this->qV[px],this->qV[py],this->qV[pz],0.0f);
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: getUnitAxis( Vect &vIn ) const
{
	UNINITIALIZED_QUAT_CHECK;

	vIn.v.x = this->v.x;
	vIn.v.y = this->v.y;
	vIn.v.z = this->v.z;
	vIn.v.w = 1.0f;

	vIn.norm();
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: getUnitAxis( Vect4D &vIn ) const
{
	UNINITIALIZED_QUAT_CHECK;

	vIn.v.x = this->v.x;
	vIn.v.y = this->v.y;
	vIn.v.z = this->v.z;
	vIn.v.w = 0.0f;

	vIn.norm();

	// BANG 
	//v.set(this->qV[px],this->qV[py],this->qV[pz],0.0f);
	//v.norm(v);
}

#endif


const bool Quat :: isNormalized(const float epsilon) const
{
	float	dot_sq;

	dot_sq = this->dot(*this);

	return( Util::isEqual(1.0f,dot_sq,epsilon) );
}


const bool Quat :: isEqual(const Quat &qIn, const float epsilon) const
{
	return (   Util::isEqual(this->qx,qIn.qx,epsilon) 
			&& Util::isEqual(this->qy,qIn.qy,epsilon) 
			&& Util::isEqual(this->qz,qIn.qz,epsilon) 
			&& Util::isEqual(this->qw,qIn.qw,epsilon) );
}

const bool Quat :: isNegEqual(const Quat &qIn, const float epsilon) const
{
	return (   Util::isEqual(-this->qx,qIn.qx,epsilon) 
			&& Util::isEqual(-this->qy,qIn.qy,epsilon) 
			&& Util::isEqual(-this->qz,qIn.qz,epsilon) 
			&& Util::isEqual(-this->qw,qIn.qw,epsilon) );
}


const bool Quat :: isEquivalent(const Quat &q, const float epsilon) const
{
	// To be equivalent, the quaternions have to be equal to each other,
	// or equal to the negative of one quaternion
	if ( this->isEqual(q,epsilon) )
		{
		return( true );
		}
	else
		{
		return (this->isNegEqual(q,epsilon));
		}
}

const bool Quat :: isConjugateEqual(const Quat &qIn, const float epsilon) const
{
	return (   Util::isEqual(-this->qx,qIn.qx,epsilon) 
			&& Util::isEqual(-this->qy,qIn.qy,epsilon) 
			&& Util::isEqual(-this->qz,qIn.qz,epsilon) 
			&& Util::isEqual( this->qw,qIn.qw,epsilon) );
}

const bool Quat :: isIdentity(const float epsilon) const
{
	return (   Util::isEqual( this->qx,0.0f,epsilon) 
			&& Util::isEqual( this->qy,0.0f,epsilon) 
			&& Util::isEqual( this->qz,0.0f,epsilon) 
			&& Util::isEqual( this->qw,1.0f,epsilon) );
}


const bool Quat :: isZero(const float epsilon) const
{
	return (   Util::isZero( this->qx, epsilon ) 
			&& Util::isZero( this->qy, epsilon ) 
			&& Util::isZero( this->qz, epsilon ) 
			&& Util::isZero( this->qw, epsilon ) );
}




/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
// Overload the = operator
//const Quat & Quat :: operator=(const Quat &qIn)
//{
//	NO_UNINITIALIZED_QUAT_CHECK_NEEDED;
//	UNINITIALIZED_QUAT_ELEMENT_CHECK(qIn);

//	this->qV[px] = qIn.qV[px];
//	this->qV[py] = qIn.qV[py];
//	this->qV[pz] = qIn.qV[pz];
//	this->qV[pw] = qIn.qV[pw];


//	return (*this);
//}


// Overload the = operator
//const Quat & Quat :: operator=(const Matrix &m)
////{
//	this->setMatrixToQuat( m );
///	
//	return (*this);
//}

// Overload the = operator
const Quat & Quat :: operator=(const Quat &qIn)
{
	
	this->set(qIn.qx,qIn.qy,qIn.qz,qIn.qw);

	return (*this);
}

// +Quat
const Quat Quat :: operator + (void) const
{

	return( Quat(this->qx, this->qy, this->qz, this->qw) );
}


// Quat + Quat
const Quat Quat :: operator+(const Quat &qIn) const 
{

	return ( Quat( this->qx + qIn.qx, this->qy + qIn.qy, this->qz + qIn.qz, this->qw + qIn.qw ) );

} /* Quat + Quat */


// Quat += Quat
const Quat & Quat :: operator+=(const Quat &qIn)
{
	this->qx += qIn.qx;
	this->qy += qIn.qy;
	this->qz += qIn.qz;
	this->qw += qIn.qw;
	return (*this);
}

// Quat + const
Quat Quat :: operator+(const float a) const
{
	return ( Quat( this->qx + a, this->qy + a, this->qz + a, this->qw + a ) );
}
	
// Quat += Constant
const Quat & Quat :: operator+=(const float a)
{
	this->qx += a;
	this->qy += a;
	this->qz += a;
	this->qw += a;
	return (*this);
}


//friend
// Constant + Quat
Quat operator+( const float a, const Quat &qIn )
{
	return ( Quat(a + qIn[x], a + qIn[y], a + qIn[z], a + qIn[w]) );
	
}


// Quat - Quat
Quat Quat :: operator-(const Quat &qIn) const 
{

	return ( Quat(this->qx - qIn.qx, this->qy - qIn.qy, this->qz - qIn.qz, this->qw - qIn.qw));

} /* Quat - Quat */



// Quat -= Quat
const Quat & Quat :: operator-=(const Quat &qIn)
{
	this->qx -= qIn.qx;
	this->qy -= qIn.qy;
	this->qz -= qIn.qz;
	this->qw -= qIn.qw;

	return (*this);

}


// Quat - const
Quat Quat :: operator-(const float a) const
{
	return ( Quat( this->qx - a, this->qy - a, this->qz - a, this->qw - a) );
}
	

// Quat -= Constant
const Quat & Quat :: operator-=(const float a)
{
	this->qx -= a;
	this->qy -= a;
	this->qz -= a;
	this->qw -= a;

	return (*this);
}


// friend
// Constant - Quat
Quat operator-(const float a,const Quat &qIn)
{
	return ( Quat( a - qIn[x],a - qIn[y],a - qIn[z], a - qIn[w]));
}


const Quat Quat :: operator-(void) const
{

return ( Quat(-this->qx, -this->qy, -this->qz, -this->qw) );

}


// Quat * Quat element by element
const Quat Quat :: multByElement(const Quat &B) const 
{
	
	return( Quat( this->qx * B.qx, this->qy * B.qy, this->qz * B.qz, this->qw * B.qw )  );			
	
} // Quat * Quat 


// Quat *= Quat
const Quat & Quat :: operator*=(const Quat &q)
{
	/* Copy the pig over */
	*this = (*this) * q;
		
	return (*this);

}


// Quat * const
Quat Quat :: operator*(const float a) const
{
	return ( Quat( this->qx * a, this->qy * a, this->qz * a, this->qw * a ) );

}
	

// Quat *= Constant
const Quat & Quat :: operator*=(const float a)
{
	this->qx *= a;
	this->qy *= a;
	this->qz *= a;
	this->qw *= a;

	return (*this);
	
}

// friend
// Constant * Quat
Quat operator*(const float a,const Quat &qIn)
{
	return ( Quat( a * qIn[x], a * qIn[y], a * qIn[z], a * qIn[w] ));

}


#if 0

// Quat * Matrix 
Matrix Quat :: operator*(const Matrix &m) const
{
	// TODO: do this mess by hand!
	Matrix mtmp(*this);

    return( Matrix(mtmp*m) );
}



// Quat *= Matrix 
const Quat & Quat :: operator*=(const Matrix &m)
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_MATRIX_ELEMENT_CHECK(m);

	// Make sure that matrix is a rotation matrix
	MATHASSERT( m.isRotation(MATH_TOLERANCE) );

	// Make Quaternion a Matrix
	Matrix mtmp(*this);

	//Multiply matrix by matrix, replace the original quaternion
	*this = Quat( mtmp * m );

	return ( *this );
}

// Quat * Vector
const Vect Quat :: operator*(const Vect &v) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_CHECK(v);

	Vect vtmp;
	this->Lqvqc(v,vtmp);

	return( Vect(vtmp) );
}


// Quat * Vector
const Vect4D Quat :: operator*(const Vect4D &v) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_CHECK(v);

	Vect4D vtmp;
	this->Lqvqc(v,vtmp);

	return( Vect4D(vtmp) );
}

#endif



// Quat / Quat
Quat Quat :: operator/(const Quat &qIn) const 
{	
	return ( Quat( this->qx/qIn.qx, this->qy/qIn.qy, this->qz/qIn.qz, this->qw/qIn.qw ));

} /* Quat / Quat */


// Quat /= Quat
const Quat & Quat :: operator/=(const Quat &qIn)
{
	this->qx /= qIn.qx;
	this->qy /= qIn.qy;
	this->qz /= qIn.qz;
	this->qw /= qIn.qw;

	return (*this);
}

// Quat / const
Quat Quat :: operator/(const float a) const
{	
	// Create inverse of constant
	const float inv_a = 1.0f/a;

	return ( Quat( this->qx * inv_a, this->qy * inv_a, this->qz * inv_a, this->qw * inv_a ) );
	
}

// Quat /= Constant
const Quat & Quat :: operator/=(const float a)
{	
	// Create inverse of constant
	const float inv_a = 1.0f/a;

	this->qx *= inv_a;
	this->qy *= inv_a;
	this->qz *= inv_a;
	this->qw *= inv_a;

	return (*this);
}


//friend
// Constant / Quat
Quat operator/(const float a,const Quat &qIn)
{
	return ( Quat( a/qIn[x], a/qIn[y], a/qIn[z], a/qIn[w] ) );

}

#if 0

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
// Print to debug screen
void Quat :: print(const char * const name) const
{
	UNINITIALIZED_QUAT_CHECK;

	// Safety net for non terminated character string
	MATHASSERT(Misc::strlen(name) < 64);

	// print to screen
	/*lint -save -e911 */
	Io::Printf("%s: %f %f %f %f \n", name, this->v.x, this->v.y, this->v.z, this->v.w );
	/*lint -restore */
}




/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXYIdent( const float a, const float b )
{
	float sx,cx;
	float sy,cy;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_a, cx, sx);
	Trig::CosSin(angle_b, cy, sy);

	this->v.x =  sx * cy;
	this->v.y =  cx * sy;
	this->v.z = -sx * sy;
	this->v.w =  cx * cy;

}	/* RotXYIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXZIdent(const float a, const float b )
{
	float sx,cx;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_a, cx, sx);
	Trig::CosSin(angle_b, cz, sz);

	this->v.x =  sx * cz;
	this->v.y =  sx * sz;
	this->v.z =  cx * sz;
	this->v.w =  cx * cz;

}	/* RotXZIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYXIdent( const float a, const float b )
{
	float sx,cx;
	float sy,cy;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_a, cy, sy);
	Trig::CosSin(angle_b, cx, sx);

	this->v.x = sx * cy;
	this->v.y = cx * sy;
	this->v.z = sx * sy;
	this->v.w = cx * cy;


}	/* RotYXIdent */


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYZIdent(const float a, const float b )
{
	float sz,cz;
	float sy,cy;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_a, cy, sy);
	Trig::CosSin(angle_b, cz, sz);

	this->v.x = -sy * sz;
	this->v.y =  sy * cz;
	this->v.z =  cy * sz;
	this->v.w =  cy * cz;


}	/* RotYZIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZXIdent(const float a, const float b )
{
	float sz,cz;
	float sx,cx;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_b, cx, sx);
	Trig::CosSin(angle_a, cz, sz);

	this->v.x =  sx * cz;
	this->v.y = -sx * sz;
	this->v.z =  cx * sz;
	this->v.w =  cx * cz;

}	/* RotZXIdent */


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZYIdent( const float a, const float b )
{
	float sz,cz;
	float sy,cy;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;

	Trig::CosSin(angle_b, cy, sy);
	Trig::CosSin(angle_a, cz, sz);

	this->v.x =  sy * sz;
	this->v.y =  sy * cz;
	this->v.z =  cy * sz;
	this->v.w =  cy * cz;

}	/* RotZYIdent */


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXYZIdent( const float a, const float b, const float c )
{

	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_a, cx, sx);
	Trig::CosSin(angle_b, cy, sy);
	Trig::CosSin(angle_c, cz, sz);

	this->v.x =   ((sx * cy) * cz) - ((cx * sy) * sz);
	this->v.y =   ((cx * sy) * cz) + ((sx * cy) * sz);
	this->v.z = - ((sx * sy) * cz) + ((cx * cy) * sz);
	this->v.w =   ((cx * cy) * cz) + ((sx * sy) * sz);

}	/* RotXYZIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXZYIdent( const float a, const float b, const float c )
{

	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_a, cx, sx);
	Trig::CosSin(angle_c, cy, sy);
	Trig::CosSin(angle_b, cz, sz);

	this->v.x =  ((sx * cy) * cz) + ((cx * sy) * sz);
	this->v.y =  ((sx * cy) * sz) + ((cx * sy) * cz);
	this->v.z =  ((cx * cy) * sz) - ((sx * sy) * cz);
	this->v.w =  ((cx * cy) * cz) - ((sx * sy) * sz);

}	/* setRotXZYIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYXZIdent( const float a, const float b, const float c )
{
	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_a, cy, sy);
	Trig::CosSin(angle_b, cx, sx);
	Trig::CosSin(angle_c, cz, sz);

	this->v.x = ((sx * cy) * cz) - ((cx * sy) * sz);
	this->v.y = ((cx * sy) * cz) + ((sx * cy) * sz);
	this->v.z = ((sx * sy) * cz) + ((cx * cy) * sz);
	this->v.w = ((cx * cy) * cz) - ((sx * sy) * sz);

}	/* setRotYXZIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYZXIdent( const float a, const float b, const float c )
{

	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_a, cy, sy);
	Trig::CosSin(angle_c, cx, sx);
	Trig::CosSin(angle_b, cz, sz);

	this->v.x = - ((cx * sy) * sz) + ((sx * cy) * cz);
	this->v.y =   ((cx * sy) * cz) - ((sx * cy) * sz);
	this->v.z =   ((cx * cy) * sz) + ((sx * sy) * cz);
	this->v.w =   ((cx * cy) * cz) + ((sx * sy) * sz);

}	/* setRotYZXIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZXYIdent( const float a, const float b, const float c )
{

	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_c, cy, sy);
	Trig::CosSin(angle_b, cx, sx);
	Trig::CosSin(angle_a, cz, sz);

	this->v.x =  ((sx * cy) * cz) + ((cx * sy) * sz);
	this->v.y = -((sx * cy) * sz) + ((cx * sy) * cz);
	this->v.z =  ((cx * cy) * sz) - ((sx * sy) * cz);
	this->v.w =  ((cx * cy) * cz) + ((sx * sy) * sz);

}	/* setRotZXYIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZYXIdent( const float a, const float b, const float c )
{
	float sx,cx;
	float sy,cy;
	float sz,cz;
	const float angle_a = a * 0.5f;
	const float angle_b = b * 0.5f;
	const float angle_c = c * 0.5f;

	Trig::CosSin(angle_b, cy, sy);
	Trig::CosSin(angle_c, cx, sx);
	Trig::CosSin(angle_a, cz, sz);

	this->v.x =  ((cx * sy) * sz) + ((sx * cy) * cz);
	this->v.y =  ((cx * sy) * cz) - ((sx * cy) * sz);
	this->v.z =  ((cx * cy) * sz) + ((sx * sy) * cz);
	this->v.w =  ((cx * cy) * cz) - ((sx * sy) * sz);

}	/* setRotZYXIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setIdentity( void )
{
	this->v.x = 0.0f;
	this->v.y = 0.0f;
	this->v.z = 0.0f;
	this->v.w = 1.0f;
}	/* setIdent */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setZero( void )
{
	this->v.x = 0.0f;
	this->v.y = 0.0f;
	this->v.z = 0.0f;
	this->v.w = 0.0f;
}	/* setZero */

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: Lqvqc(const VectBase &vIn, Vect &vOut) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(vIn);

	const Vect &qV = (const Vect &)(*this);
	const Vect &INqV = (const Vect &)(vIn);
	
	vOut = (2.0f * q.w) * INqV.cross(qV);
	vOut += ( q.w * q.w - qV.dot(qV) ) * INqV;
	vOut += qV *( 2.0f * qV.dot(INqV) );


	//const Vect &v = vIn.getVect();

	//vOut = (2.0f * this->v.w) * v.cross(*this);
	//vOut += ( this->v.w * this->v.w - this->Vect::dot(*this) ) * v;
	//vOut += this->Vect::operator *( 2.0f * this->Vect::dot(v) );
}
																    
/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: Lqvqc(const VectBase &vIn, Vect4D &vOut) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(vIn);
	
//#if (MATH_IS_CPP)


	const Vect &qV = (const Vect &)(*this);
	const Vect &INqV = (const Vect &)(vIn);


	const Vect &v = vIn.getVect();
	Vect vtmp;

	vtmp = (2.0f * q.w) * INqV.cross(qV);
	vtmp += ( q.w * q.w - qV.dot(qV) ) * INqV;
	vtmp += qV *( 2.0f * qV.dot(INqV) );
	vOut.set(vtmp.v.x,vtmp.v.y,vtmp.v.z,v.v.w);



//	const Vect &v = vIn.getVect();
//	Vect vtmp;

//	vtmp = (2.0f * this->v.w) * v.cross(*this);
//	vtmp += ( this->v.w * this->v.w - this->Vect::dot(*this) ) * v;
//	vtmp += this->Vect::operator *( 2.0f * this->Vect::dot(v) );
//	vOut.set(vtmp.v.x,vtmp.v.y,vtmp.v.z,v.v.w);

/* This is slow, it needs work
#elif (MATH_IS_PS2)

	asm __volatile__ ("
	
		// Load
		lqc2			vf1, 0x0(%0)		// vf1 <- qV (this)
		lqc2			vf2, 0x0(%1)		// vf2 <- vIn
		vadd.w			vf3, vf0, vf0		// vf3[w] = 2.0
		
		// Stuff
		vopmula			ACC, vf2, vf1
		vopmsub			vf4, vf1, vf2		// vf4 <- this x qV
		vmul			vf5, vf1, vf1		// vf5 <- qV * qV
		vmulw			vf9, vf3, vf1		// vf9[w] <- qw * 2.0
		vmul			vf6, vf1, vf2		// vf6 <- qV * this
		// nop
		// nop
		vmulw.xyz		vf4, vf4, vf9		// vf4 <- 2.0 * qw * (vIn x this)
		vsubx.w			vf7, vf5, vf5
		vaddy.x			vf8, vf6, vf6
		// nop
		// nop
		vsuby.w			vf7, vf7, vf5
		vaddz.x			vf8, vf8, vf6
		// nop
		// nop
		vsubz.w			vf7, vf7, vf5		// vf7[w] <- qw * qw - qV.dot(qV)
		vmulw.x			vf3, vf8, vf3		// vf3[x] <- 2.0 * qV.dot(vIn)
		// nop
		// nop
		vmulw.xyz		vf7, vf2, vf7
		vmulx.xyz		vf8, vf1, vf3
		vmove.w			vf4, vf0
		// nop
		vadd.xyz		vf4, vf4, vf7
		// nop
		// nop
		// nop
		vadd.xyz		vf4, vf4, vf8
		// nop
		// nop
		// nop
		
		// Store
		sqc2			vf4, 0x0(%2)
	
	":
	 : "r" (this),
	   "r" (&vIn),
	   "r" (&vOut)
	 : );

#else

	#error NO CODE DEFINED
	
#endif */
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: Lqcvq(const VectBase &vIn, Vect4D &vOut) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(vIn);


	const Vect &qV = (const Vect &)(*this);
	const Vect &INqV = (const Vect &)(vIn);

	//const Vect &v = vIn.getVect();
	Vect vtmp;

	vtmp = (2.0f * q.w) * qV.cross(INqV);
	vtmp +=  INqV*( q.w * q.w - qV.dot(qV) );
	vtmp +=  qV*( 2.0f * qV.dot(INqV) );
	vOut.set(vtmp.v.x, vtmp.v.y, vtmp.v.z, INqV.v.w);

	//const Vect &v = vIn.getVect();
	//Vect vtmp;

	//vtmp = (2.0f * this->v.w) * this->cross(v);
	//vtmp +=  v.Vect::operator*( this->v.w * this->v.w - this->Vect::dot(*this) );
	//vtmp +=  this->Vect::operator*( 2.0f * this->Vect::dot(v) );
	//vOut.set(vtmp.v.x,vtmp.v.y,vtmp.v.z,v.v.w);
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: Lqcvq(const VectBase &vIn, Vect &vOut) const
{
	UNINITIALIZED_QUAT_CHECK;
	UNINITIALIZED_VECT_ELEMENT_BASE_CHECK(vIn);

//#if (MATH_IS_CPP)


	const Vect &qV = (const Vect &)(*this);
	const Vect &INqV = (const Vect &)(vIn);


	vOut = (2.0f * q.w) * qV.cross(INqV);
	vOut +=  INqV*( q.w * q.w - qV.dot(qV));
	vOut +=  qV*( 2.0f * qV.dot(INqV) );

	//const Vect &v = vIn.getVect();

	//vOut = (2.0f * this->v.w) * this->cross(v);
	//vOut +=  v.Vect::operator*( this->v.w * this->v.w - this->Vect::dot(*this));
	//vOut +=  this->Vect::operator*( 2.0f * this->Vect::dot(v) );

/* This is slow, it needs work	
#elif (MATH_IS_PS2)

	asm __volatile__ ("
	
		// Load
		lqc2			vf1, 0x0(%0)		// vf1 <- qV (this)
		lqc2			vf2, 0x0(%1)		// vf2 <- vIn
		vadd.w			vf3, vf0, vf0		// vf3[w] = 2.0
		
		// Stuff
		vopmula			ACC, vf1, vf2
		vopmsub			vf4, vf2, vf1		// vf4 <- this x qV
		vmul			vf5, vf1, vf1		// vf5 <- qV * qV
		vmulw			vf9, vf3, vf1		// vf9[w] <- qw * 2.0
		// nop
		vmul			vf6, vf1, vf2		// vf6 <- qV * this
		// nop
		vmulw.xyz		vf4, vf4, vf9		// vf4 <- 2.0 * qw * (vIn x this)
		vsubx.w			vf7, vf5, vf5
		vaddy.x			vf8, vf6, vf6
		// nop
		// nop
		vsuby.w			vf7, vf7, vf5
		vaddz.x			vf8, vf8, vf6
		// nop
		// nop
		vsubz.w			vf7, vf7, vf5		// vf7[w] <- qw * qw - qV.dot(qV)
		vmulw.x			vf3, vf8, vf3		// vf3[x] <- 2.0 * qV.dot(vIn)
		// nop
		// nop
		vmulw.xyz		vf7, vf2, vf7
		vmulx.xyz		vf8, vf1, vf3
		vmove.w			vf4, vf0
		// nop
		vadd.xyz		vf4, vf4, vf7
		// nop
		// nop
		// nop
		vadd.xyz		vf4, vf4, vf8
		// nop
		// nop
		// nop
		
		// Store
		sqc2			vf4, 0x0(%2)
	
	":
	 : "r" (this),
	   "r" (&vIn),
	   "r" (&vOut)
	 : );
	 
#else

	#error NO CODE DEFINED
	
#endif */
}
#endif


Quat Quat :: getT( void ) const
{
	return( Quat(-this->qx, -this->qy, -this->qz, this->qw) );
}


Quat & Quat :: T( void )
{
	this->qx = -this->qx;
	this->qy = -this->qy;
	this->qz = -this->qz;
	this->qw =  this->qw;	
	
	return( *this );
}	/* transpose */


Quat & Quat :: conj( void )
{
	this->qx = -this->qx;
	this->qy = -this->qy;
	this->qz = -this->qz;
	this->qw = this->qw;
	
	return( *this );
}


Quat Quat :: getConj( void ) const
{
	return( Quat(-this->qx,-this->qy,-this->qz,this->qw) );
}


const float Quat::mag( void ) const
{
	float dot_sq;

	dot_sq = this->dot(*this);
	return( sqrtf(dot_sq) );

}


const float Quat::magSquared( void ) const
{
	float dot_sq;
	
	dot_sq = this->dot(*this);

	return( dot_sq );
}


const float Quat::dot( const Quat & qIn ) const
{
	return ( this->qx * qIn.qx + this->qy * qIn.qy + this->qz * qIn.qz + this->qw * qIn.qw );

}

const float Quat::invMag( void ) const
{
	float dot_sq = this->dot(*this);
	float invMag;
	
	if ( dot_sq >  MATH_TOLERANCE )
		{
		invMag = 1.0f / sqrtf(dot_sq);
		}
	else
		{
		assert(0);
		invMag = 1.0f;
		}
		
	return( invMag );
}

Quat Quat :: getNorm( void ) const
{
	float magnitude;
	magnitude = this->dot(*this);
	
	if(magnitude > MATH_TOLERANCE)
		{
		magnitude = 1.0f / sqrtf(magnitude);
		}
	else
		{
		assert( 0 );
		magnitude = 1.0f;
		}
			
	return( Quat(this->qx * magnitude, this->qy * magnitude, this->qz * magnitude, this->qw * magnitude) );
	
}


Quat & Quat :: norm( void ) 
{
	float magnitude;
	magnitude = this->dot(*this);
	
	if(magnitude > MATH_TOLERANCE)
		{
		magnitude = 1.0f / sqrtf(magnitude);
		this->qx *= magnitude;
		this->qy *= magnitude;
		this->qz *= magnitude;
		this->qw *= magnitude;
		}
	else
		{
		assert(0);
		}
	return( *this ); 
	
}  


Quat Quat :: getInv( void ) const
{
	float magnitude;
	magnitude = this->dot(*this);
	
	if(magnitude > MATH_TOLERANCE)
		{
		magnitude = 1.0f / (magnitude);
		}
	else
		{
		// do nothing (magnitude is too small)	
		assert( 0 );
	 	magnitude = 1.0f;
		}
		
	return( Quat(-this->qx * magnitude, -this->qy * magnitude, -this->qz * magnitude, this->qw * magnitude) );
}

Quat & Quat :: inv( void ) 
{
	float magnitude;
	magnitude = this->dot(*this);
	
	if(magnitude > MATH_TOLERANCE)
		{
		magnitude = 1.0f / (magnitude);
		this->qx *= -magnitude;
		this->qy *= -magnitude;
		this->qz *= -magnitude;
		this->qw *=  magnitude;
		}
	else
		{
	 	assert( 0);
		}
		
	return( *this );
}  



#if 0
/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXPI2( void )
{
	this->v.x = MATH_INV_SQRT_2;
	this->v.y = 0.0f;
	this->v.z = 0.0f;
	this->v.w = MATH_INV_SQRT_2;

}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYPI2( void )
{
	this->v.x = 0.0f;
	this->v.y = MATH_INV_SQRT_2;	
	this->v.z = 0.0f;
	this->v.w = MATH_INV_SQRT_2;
}


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZPI2( void )
{
	this->v.x = 0.0f;
	this->v.y = 0.0f;	
	this->v.z = MATH_INV_SQRT_2;	
	this->v.w = MATH_INV_SQRT_2;
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotXPI( void )
{
	this->v.x = 1.0f;
	this->v.y = 0.0f;
	this->v.z = 0.0f;
	this->v.w = 0.0f;
}

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotYPI( void )
{
	this->v.x = 0.0f;
	this->v.y = 1.0f;
	this->v.z = 0.0f;
	this->v.w = 0.0f;
}


/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotZPI( void )
{
	this->v.x = 0.0f;
	this->v.y = 0.0f;
	this->v.z = 1.0f;
	this->v.w = 0.0f;
}

#endif

#if 0

/*****************************************************************************/
/**
* @brief @b NOT @b Documented at this time
******************************************************************************/
void Quat :: setRotAxisAngleNormalized( const Vect &axis, const float angle )
{
	const float angle_a = 0.5f * angle;
	float cos_a;
	float sin_a;

	MATHASSERT( axis.isUnit(MATH_TOLERANCE) );
	
	cos_a = Trig :: Cos(angle_a);
	sin_a = Trig :: Sin(angle_a);

	
	this->set(axis * sin_a, cos_a);

	//this->Vect::operator = (axis * sin_a);
	//this->v.w = cos_a;


}









#endif



/***** END of File Quat.cpp **********************************************/



