#include "MathEngine.h"
#include <math.h>


	// Big 4
Matrix::Matrix()
: v0(0.0f, 0.0f, 0.0f, 0.0f),v1(0.0f, 0.0f, 0.0f, 0.0f),v2(0.0f, 0.0f, 0.0f, 0.0f),	v3(0.0f, 0.0f, 0.0f, 0.0f)
{};

	Matrix::Matrix( const Matrix &tM )	
		:v0(tM.v0),v1(tM.v1),v2(tM.v2),v3(tM.v3)
	{};

	Matrix::~Matrix()
	{};

void Matrix::privSetRotXYZ( const float a,  const float b, const float c)
{
	
   Matrix mx(ROT_X, a);
   Matrix my(ROT_Y, b);
   Matrix mz(ROT_Z, c);

   *this = mx * my * mz;


}	/* RotXIdent */



Matrix :: Matrix( Rot3AxisType mode, const float angle_0, const float angle_1, const float angle_2 )
{
	switch(mode)
		{
		case ROT_XYZ:
			this->privSetRotXYZ( angle_0, angle_1, angle_2 );
			break;

		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}


void Matrix :: set( Rot3AxisType mode, const float angle_0, const float angle_1, const float angle_2 )
{
	switch(mode)
		{
		case ROT_XYZ:
			this->privSetRotXYZ( angle_0, angle_1, angle_2 );
			break;

		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}

	// Constructors
	Matrix::Matrix( const Vect &tV0, const Vect &tV1, const Vect &tV2, const Vect &tV3)	: v0(tV0),v1(tV1),v2(tV2),v3(tV3) {};

	float &Matrix::operator[] (const enum m0_enum ){	return this->v0[x];	};
	float &Matrix::operator[] (const enum m1_enum ) {	return this->v0[y];	};	
	float &Matrix::operator[] (const enum m2_enum ) {	return this->v0[z];	};	
	float &Matrix::operator[] (const enum m3_enum ) {	return this->v0[w];	};	
	float &Matrix::operator[] (const enum m4_enum ) { 	return this->v1[x]; 	};	
	float &Matrix::operator[] (const enum m5_enum ) {	return this->v1[y];	};	
	float &Matrix::operator[] (const enum m6_enum ) {	return this->v1[z];	};	
	float &Matrix::operator[] (const enum m7_enum ) {	return this->v1[w];	};	
	float &Matrix::operator[] (const enum m8_enum ) {	return this->v2[x];	};	
	float &Matrix::operator[] (const enum m9_enum ) {	return this->v2[y];	};	
	float &Matrix::operator[] (const enum m10_enum ) {	return this->v2[z];	};	
	float &Matrix::operator[] (const enum m11_enum ) {	return this->v2[w];	};	
    float &Matrix::operator[] (const enum m12_enum ){	return this->v3[x];	};	
	float &Matrix::operator[] (const enum m13_enum ) {	return this->v3[y];	};	
	float &Matrix::operator[] (const enum m14_enum ) {	return this->v3[z];	};	
	float &Matrix::operator[] (const enum m15_enum ) {	return this->v3[w];	};
	const float Matrix::operator[] (const enum m0_enum ) const {	return this->v0[x];	};
	const float Matrix::operator[] (const enum m1_enum ) const {	return this->v0[y];	};	
	const float Matrix::operator[] (const enum m2_enum ) const {	return this->v0[z];	};	
	const float Matrix::operator[] (const enum m3_enum ) const {	return this->v0[w];	};	
	const float Matrix::operator[] (const enum m4_enum ) const { 	return this->v1[x]; 	};	
	const float Matrix::operator[] (const enum m5_enum ) const {	return this->v1[y];	};	
	const float Matrix::operator[] (const enum m6_enum ) const {	return this->v1[z];	};	
	const float Matrix::operator[] (const enum m7_enum ) const {	return this->v1[w];	};	
	const float Matrix::operator[] (const enum m8_enum ) const {	return this->v2[x];	};	
	const float Matrix::operator[] (const enum m9_enum ) const {	return this->v2[y];	};	
	const float Matrix::operator[] (const enum m10_enum ) const {	return this->v2[z];	};	
	const float Matrix::operator[] (const enum m11_enum ) const {	return this->v2[w];	};	
    const float Matrix::operator[] (const enum m12_enum ) const {	return this->v3[x];	};	
	const float Matrix::operator[] (const enum m13_enum ) const {	return this->v3[y];	};	
	const float Matrix::operator[] (const enum m14_enum ) const {	return this->v3[z];	};	
	const float Matrix::operator[] (const enum m15_enum ) const {	return this->v3[w];	};

Matrix Matrix::operator + (const Matrix &A) const
{
	return Matrix(
					Vect( this->_m0  + A._m0,  this->_m1  + A._m1,  this->_m2  + A._m2,  this->_m3  + A._m3 ),
					Vect( this->_m4  + A._m4,  this->_m5  + A._m5,  this->_m6  + A._m6,  this->_m7  + A._m7 ),
					Vect( this->_m8  + A._m8,  this->_m9  + A._m9,  this->_m10 + A._m10, this->_m11 + A._m11 ),
					Vect( this->_m12 + A._m12, this->_m13 + A._m13, this->_m14 + A._m14, this->_m15 + A._m15 )
				);

};

void Matrix::operator += (const Matrix &A)
{
	v0.set( this->_m0  + A._m0,  this->_m1  + A._m1,  this->_m2  + A._m2,  this->_m3  + A._m3 );
	v1.set( this->_m4  + A._m4,  this->_m5  + A._m5,  this->_m6  + A._m6,  this->_m7  + A._m7 );
	v2.set( this->_m8  + A._m8,  this->_m9  + A._m9,  this->_m10 + A._m10, this->_m11 + A._m11 );
	v3.set( this->_m12 + A._m12, this->_m13 + A._m13, this->_m14 + A._m14, this->_m15 + A._m15 );
};


Matrix Matrix::operator - (const Matrix &A) const
{
	return Matrix(
					Vect( this->_m0 - A._m0,   this->_m1 - A._m1,   this->_m2 - A._m2,   this->_m3 - A._m3 ),
					Vect( this->_m4 - A._m4,   this->_m5 - A._m5,   this->_m6 - A._m6,   this->_m7 - A._m7 ),
					Vect( this->_m8 - A._m8,   this->_m9 - A._m9,   this->_m10 - A._m10, this->_m11 - A._m11 ),
					Vect( this->_m12 - A._m12, this->_m13 - A._m13, this->_m14 - A._m14, this->_m15 - A._m15 )
				);

};

void Matrix::operator -= (const Matrix &A)
{
	v0.set( this->_m0 - A._m0,   this->_m1 - A._m1,    this->_m2  - A._m2,  this->_m3  - A._m3 );
	v1.set( this->_m4 - A._m4,   this->_m5 - A._m5,    this->_m6  - A._m6,  this->_m7  - A._m7 );
	v2.set( this->_m8 - A._m8,   this->_m9 - A._m9,    this->_m10 - A._m10, this->_m11 - A._m11 );
	v3.set( this->_m12 - A._m12, this->_m13 - A._m13,  this->_m14 - A._m14, this->_m15 - A._m15 );
};


Matrix Matrix::operator - (void) const
{
	return Matrix(
					Vect( -this->_m0, -this->_m1, -this->_m2, -this->_m3 ),
					Vect( -this->_m4, -this->_m5, -this->_m6, -this->_m7 ),
					Vect( -this->_m8, -this->_m9, -this->_m10, -this->_m11 ),
					Vect( -this->_m12, -this->_m13, -this->_m14, -this->_m15 )
				);

};


Matrix Matrix::operator * (const float s) const 
{
		return Matrix(
					Vect( s * this->_m0, s * this->_m1, s * this->_m2, s * this->_m3 ),
					Vect( s * this->_m4, s * this->_m5, s * this->_m6, s * this->_m7 ),
					Vect( s * this->_m8, s * this->_m9, s * this->_m10, s * this->_m11 ),
					Vect( s * this->_m12, s * this->_m13, s * this->_m14, s * this->_m15 )
				);
}


Matrix operator *(const float s, const Matrix &A )
{
			return Matrix(
					Vect( s * A[m0], s * A[m1], s * A[m2], s * A[m3] ),
					Vect( s * A[m4], s * A[m5], s * A[m6], s * A[m7] ),
					Vect( s * A[m8], s * A[m9], s * A[m10], s * A[m11] ),
					Vect( s * A[m12], s * A[m13], s * A[m14], s * A[m15] )
				);

}

void Matrix::operator *= (const float s)
{

	v0.set( s * this->_m0, s * this->_m1, s * this->_m2, s * this->_m3 );
	v1.set( s * this->_m4, s * this->_m5, s * this->_m6, s * this->_m7 );
	v2.set( s * this->_m8, s * this->_m9, s * this->_m10, s * this->_m11 );
	v3.set( s * this->_m12, s * this->_m13, s * this->_m14, s * this->_m15 );

}

Matrix Matrix::operator * ( const Matrix &A ) const
{
	return Matrix (

		Vect(	(this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12),
				(this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13),
				(this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14),
				(this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15) ),
		
		Vect(	(this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12),
				(this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13),
				(this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14),
				(this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15) ),
	
		Vect(	(this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12),
				(this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13),
				(this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14),
				(this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15) ),

		Vect(	(this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12),
				(this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13),
				(this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14),
				(this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15) )
		);
}


void  Matrix::operator *= ( const Matrix &A ) 
{


		v0.set(	( this->_m0 * A._m0) + ( this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12),
				   ( this->_m0 * A._m1) + ( this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13),
				   ( this->_m0 * A._m2) + ( this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14),
				   ( this->_m0 * A._m3) + ( this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15) );
		
		v1.set(	( this->_m4 * A._m0) + ( this->_m5 * A._m4) + (this->_m6 * A._m8) +  (this->_m7 * A._m12),
				   ( this->_m4 * A._m1) + ( this->_m5 * A._m5) + (this->_m6 * A._m9)  + (this->_m7 * A._m13),
				   ( this->_m4 * A._m2) + ( this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14),
				   ( this->_m4 * A._m3) + ( this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15) );
	
		v2.set(	( this->_m8 * A._m0) + ( this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12),
				   ( this->_m8 * A._m1) + ( this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13),
				   ( this->_m8 * A._m2) + ( this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14),
				   ( this->_m8 * A._m3) + ( this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15) );

		v3.set(	(this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12),
			   	(this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13),
				   (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14),
				   (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15) );
	
}


Matrix::Matrix( RotType type, const float angle )
{
	float c = cosf(angle);
	float s = sinf(angle);

	switch( type )
	{
	case ROT_X:

		v0.set(1.0f, 0.0f, 0.0f, 0.0f);
		
		this->_m4 = 0.0f;
		this->_m5 = c;
		this->_m6 = s;
		this->_m7 = 0.0f;
	
		this->_m8 = 0.0f;
		this->_m9 = -s;
		this->_m10 = c;
		this->_m11 = 0.0f;

		v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		break;

	case ROT_Y:
	
		this->_m0 = c;
		this->_m1 = 0.0f;
		this->_m2 = -s;
		this->_m3 = 0.0f;
	
		v1.set(0.0f, 1.0f, 0.0f, 0.0f);

		this->_m8 = s;
		this->_m9 = 0.0f;
		this->_m10 = c;
		this->_m11 = 0.0f;
	
		v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		break;

	case ROT_Z:
		this->_m0 = c;
		this->_m1 = s;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		
		this->_m4 = -s;
		this->_m5 = c;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		v2.set( 0.0f, 0.0f, 1.0f, 0.0f);
		v3.set( 0.0f, 0.0f, 0.0f, 1.0f);

		break;
	}
}


Matrix::Matrix( MatrixTransType , const float tx, const float ty, const float tz )
	: v0(1.0f, 0.0f, 0.0f, 0.0f),
	v1( 0.0f, 1.0f, 0.0f, 0.0f),
	v2( 0.0f, 0.0f, 1.0f, 0.0f),
	v3( tx, ty, tz, 1.0f)
{
}

Matrix::Matrix( MatrixTransType , const Vect &vIn )
	: v0(1.0f, 0.0f, 0.0f, 0.0f),
	v1( 0.0f, 1.0f, 0.0f, 0.0f),
	v2( 0.0f, 0.0f, 1.0f, 0.0f),
	v3( vIn[x],vIn[y],vIn[z], 1.0f)
{
}
Matrix::Matrix( MatrixScaleType , const float sx, const float sy, const float sz )
	: v0(sx, 0.0f, 0.0f, 0.0f),
	v1( 0.0f, sy, 0.0f, 0.0f),
	v2( 0.0f, 0.0f, sz, 0.0f),
	v3( 0.0f, 0.0f, 0.0f, 1.0f)
{
}

Matrix::Matrix( MatrixScaleType , const Vect &vIn )
	: v0(vIn[x], 0.0f, 0.0f, 0.0f),
	v1( 0.0f, vIn[y], 0.0f, 0.0f),
	v2( 0.0f, 0.0f, vIn[z], 0.0f),
	v3( 0.0f, 0.0f, 0.0f, 1.0f)
{
}

Matrix::Matrix( MatrixSpecialType type )
{
	switch (type)
	{
		case IDENTITY:
			v0.set(1.0f, 0.0f, 0.0f, 0.0f);
			v1.set(0.0f, 1.0f, 0.0f, 0.0f);
			v2.set(0.0f, 0.0f, 1.0f, 0.0f);
			v3.set(0.0f, 0.0f, 0.0f, 1.0f);
			break;
		case ZERO:
			v0.set(0.0f, 0.0f, 0.0f, 0.0f);
			v1.set(0.0f, 0.0f, 0.0f, 0.0f);
			v2.set(0.0f, 0.0f, 0.0f, 0.0f);
			v3.set(0.0f, 0.0f, 0.0f, 0.0f);
			break;
	}
}

	


void Matrix::set( RotType type, const float angle )
{
	float c = cosf(angle);
	float s = sinf(angle);

	switch( type )
	{
	case ROT_X:

		v0.set(1.0f, 0.0f, 0.0f, 0.0f);
		
		this->_m4 = 0.0f;
		this->_m5 = c;
		this->_m6 = s;
		this->_m7 = 0.0f;
	
		this->_m8 = 0.0f;
		this->_m9 = -s;
		this->_m10 = c;
		this->_m11 = 0.0f;

		v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		break;

	case ROT_Y:
	
		this->_m0 = c;
		this->_m1 = 0.0f;
		this->_m2 = -s;
		this->_m3 = 0.0f;
	
		v1.set(0.0f, 1.0f, 0.0f, 0.0f);

		this->_m8 = s;
		this->_m9 = 0.0f;
		this->_m10 = c;
		this->_m11 = 0.0f;
	
		v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		break;

	case ROT_Z:
		this->_m0 = c;
		this->_m1 = s;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		
		this->_m4 = -s;
		this->_m5 = c;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		v2.set( 0.0f, 0.0f, 1.0f, 0.0f);
		v3.set( 0.0f, 0.0f, 0.0f, 1.0f);

		break;
	}
}


void Matrix::set( MatrixTransType , const float tx, const float ty, const float tz )
{
	v0.set(1.0f, 0.0f, 0.0f, 0.0f);
	v1.set( 0.0f, 1.0f, 0.0f, 0.0f);
	v2.set( 0.0f, 0.0f, 1.0f, 0.0f);
	v3.set( tx, ty, tz, 1.0f);
}

void Matrix::set( MatrixTransType , const Vect &vIn )
{
	v0.set(1.0f, 0.0f, 0.0f, 0.0f);
	v1.set( 0.0f, 1.0f, 0.0f, 0.0f);
	v2.set( 0.0f, 0.0f, 1.0f, 0.0f);
	v3.set(vIn[x], vIn[y], vIn[z], 1.0f);
}

void Matrix::set( MatrixScaleType , const float sx, const float sy, const float sz )
{
	v0.set(sx, 0.0f, 0.0f, 0.0f);
	v1.set( 0.0f, sy, 0.0f, 0.0f);
	v2.set( 0.0f, 0.0f, sz, 0.0f);
	v3.set( 0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix::set( MatrixScaleType , const Vect &vIn)
{
	v0.set( vIn[x], 0.0f, 0.0f, 0.0f);
	v1.set( 0.0f, vIn[y], 0.0f, 0.0f);
	v2.set( 0.0f, 0.0f, vIn[z], 0.0f);
	v3.set( 0.0f, 0.0f, 0.0f, 1.0f);
}


void Matrix::set( MatrixSpecialType type )
{
	switch (type)
	{
		case IDENTITY:
			v0.set(1.0f, 0.0f, 0.0f, 0.0f);
			v1.set(0.0f, 1.0f, 0.0f, 0.0f);
			v2.set(0.0f, 0.0f, 1.0f, 0.0f);
			v3.set(0.0f, 0.0f, 0.0f, 1.0f);
			break;
		case ZERO:
			v0.set(0.0f, 0.0f, 0.0f, 0.0f);
			v1.set(0.0f, 0.0f, 0.0f, 0.0f);
			v2.set(0.0f, 0.0f, 0.0f, 0.0f);
			v3.set(0.0f, 0.0f, 0.0f, 0.0f);
			break;
	}
}

const float Matrix::det() const
{
	float A, B, C, D, E, F;
	
	/*     | m0  m1  m2  m3  | */
	/* m = | m4  m5  m6  m7  | */
	/*     | m8  m9  m10 m11 | */
	/*     | m12 m13 m14 m15 | */
	
	/* det(m) =  m0*[m5(m10*m15-m14*m11) -m6*(m9*m15-m13*m11) +m7*(m9*m14-m13*m10)] */
	/*          -m1*[m4(m10*m15-m14*m11) -m6*(m8*m15-m12*m11) +m7*(m8*m14-m12*m10)] */
	/*           m2*[m4(m9*m15-m13*m11)  -m5*(m8*m15-m12*m11) +m7*(m8*m13-m12*m9) ] */
	/*          -m3*[m4(m9*m14-m13*m10)  -m5*(m8*m14-m12*m10) +m6*(m8*m13-m12*m9) ] */
	
	/* let: A = m10*m15 - m14*m11 */
	/*      B = m8*m15  - m12*m11 */
	/*      C = m8*m13  - m12*m9  */
	/*      D = m8*m14  - m12*m10 */
	/*      E = m9*m15  - m13*m11 */
	/*      F = m9*m14  - m13*m10 */
	
	/* det(m) =  m0*[ m5*A - m6*E + m7*F ] */
	/*          -m1*[ m4*A - m6*B + m7*D ] */
	/*           m2*[ m4*E - m5*B + m7*C ] */
	/*          -m3*[ m4*F - m5*D + m6*C ] */
	
	A = (this->_m10 * this->_m15) - (this->_m14 * this->_m11);
	B = (this->_m8  * this->_m15) - (this->_m12 * this->_m11);
	C = (this->_m8  * this->_m13) - (this->_m12 * this->_m9 ); 
	D = (this->_m8  * this->_m14) - (this->_m12 * this->_m10);
	E = (this->_m9  * this->_m15) - (this->_m13 * this->_m11);
	F = (this->_m9  * this->_m14) - (this->_m13 * this->_m10);
	
	return (  this->_m0 * ((this->_m5 * A) - (this->_m6 * E) + (this->_m7 * F))
		  	- this->_m1 * ((this->_m4 * A) - (this->_m6 * B) + (this->_m7 * D))
		  	+ this->_m2 * ((this->_m4 * E) - (this->_m5 * B) + (this->_m7 * C))
		  	- this->_m3 * ((this->_m4 * F) - (this->_m5 * D) + (this->_m6 * C)) );
}

Matrix &Matrix::T( void )
{
		float tmp;
		
		tmp = this->_m4;
		this->_m4 = this->_m1;
		this->_m1 = tmp;

		tmp = this->_m8;
		this->_m8 = this->_m2;
		this->_m2 = tmp;

		tmp = this->_m12;
		this->_m12 = this->_m3;
		this->_m3= tmp;

		tmp = this->_m9;
		this->_m9 = this->_m6;
		this->_m6 = tmp;

		tmp = this->_m13;
		this->_m13 = this->_m7;
		this->_m7 = tmp;

		tmp = this->_m14;
		this->_m14 = this->_m11;
		this->_m11 = tmp;

	return *this;
}

Matrix Matrix::getT( void ) const
{
	return Matrix (
		Vect( this->_m0,this->_m4, this->_m8,  this->_m12 ),
		Vect( this->_m1, this->_m5, this->_m9,  this->_m13 ),
		Vect( this->_m2, this->_m6, this->_m10, this->_m14 ),
		Vect( this->_m3, this->_m7, this->_m11, this->_m15 )
		);

}




Matrix &Matrix::inv( void )
{
	Matrix tmp;

	float det = this->det();
	float invDet = 1.0f/det;

	tmp = this->getAdj();
	tmp *= invDet;

	*this = tmp;

	return *this;
}



const Matrix Matrix::getInv( void ) const
{
	Matrix tmp;

	float det = this->det();
	float invDet = 1.0f/det;

	tmp = this->getAdj();
	tmp *= invDet;

	return tmp;
}


const Matrix Matrix::getAdj(void) const
{
	float A, B, C, D, E, F, G, H, I;
	Matrix tmp;
	
	A = (this->_m10 * this->_m15) - (this->_m11 * this->_m14);
	B = (this->_m7  * this->_m14) - (this->_m6 * this->_m15);
	C = (this->_m6  * this->_m11) - (this->_m7 * this->_m10);
	D = (this->_m3  * this->_m14) - (this->_m2 * this->_m15);
	E = (this->_m2  * this->_m11) - (this->_m3 * this->_m10);
	F = (this->_m2  * this->_m7)  - (this->_m3 * this->_m6);
	G =  this->_m5;
	H =  this->_m13;
	
		/* 0		a = {5,  9, 13,  6, 10, 14,  7, 11, 15} */
		tmp._m0 =  (G * A) + (this->_m9 * B) + (H * C);
		
		/* 2		a = {1,  5, 13,  2,  6, 14,  3,  7, 15} */
		tmp._m2= - (this->_m1 * B) + (G * D) + (H * F);
		
		G = this->_m0;
		H = this->_m8;
		/* 5		a = {0,  8, 12,  2, 10, 14,  3, 11, 15} */
		tmp._m5 =  (G * A) + (H * D) + (this->_m12 * E);
		
		/* 7		a = {0,  4,  8,  2,  6, 10,  3,  7, 11} */
		tmp._m7 =  (G * C)  + (H * F) - (this->_m4 * E);
		
		A = (this->_m9 * this->_m15) - (this->_m11 * this->_m13);
		B = (this->_m3 * this->_m13) - (this->_m1 * this->_m15);
		C = (this->_m1 * this->_m11) - (this->_m3 * this->_m9);
		D = (this->_m7 * this->_m13) - (this->_m5 * this->_m15);
		E = (this->_m5 * this->_m11) - (this->_m7 * this->_m9);
		F = (this->_m1 * this->_m7) - (this->_m3 * this->_m5);
		G = this->_m2;
		H = this->_m10;
		/* 1		a = {2, 10, 14,  1,  9, 13,  3, 11, 15} */
		tmp._m1 =  (G * A) + (H * B) + (this->_m14 * C);
		
		/* 3		a = {2,  6, 10,  1,  5,  9,  3,  7, 11} */
		tmp._m3 =  (G * E)  + (H * F) - (this->_m6 * C);
		
		G = this->_m4;
		H = this->_m12;
		/* 8		a = {4,  8, 12,  5,  9, 13,  7, 11, 15} */
		tmp._m8 =  (G * A) + (this->_m8 * D) + (H * E);
		
		/* A		a = {0,  4, 12,  1,  5, 13,  3,  7, 15} */
		tmp._m10 = -(this->_m0 * D) + (G * B) + (H * F);
		
		A = (this->_m8 * this->_m15) - (this->_m11 * this->_m12);
		B = (this->_m4 * this->_m11) - (this->_m7 * this->_m8);
		C = (this->_m3 * this->_m12) - (this->_m0 * this->_m15);
		D = (this->_m0 * this->_m7)  - (this->_m3 * this->_m4);
		E = (this->_m7 * this->_m12) - (this->_m4 * this->_m15);
		F = (this->_m0 * this->_m11) - (this->_m3 * this->_m8);
		G = this->_m6;
		H = this->_m14;
		/* 4		a = {6, 10, 14,  4,  8, 12,  7, 11, 15} */
		tmp._m4 =  (G * A) + (this->_m10 * E) + (H * B);
		
		/* 6		a = {2,  6, 14,  0,  4, 12,  3,  7, 15} */
		tmp._m6 = -(this->_m2 * E) + (G * C) + (H * D);
		
		G = this->_m1;
		H = this->_m9;
		/* 9		a = {1,  9, 13,  0,  8, 12,  3, 11, 15} */
		tmp._m9 =  (G * A) + (H * C) + (this->_m13 * F);
		
		/* B		a = {1,  5,  9,  0,  4,  8,  3,  7, 11} */
		tmp._m11 =  (G * B)  + (H * D) - (this->_m5 * F);
		
		A = this->_m4;
		B = this->_m6;
		C = this->_m12;
		D = this->_m14;
		E = (B * C) - (A * D);
		F = this->_m8;
		G = this->_m10;
		H = this->_m5;
		I = this->_m13;
		/* C		a = {5,  9, 13,  4,  8, 12,  6, 10, 14} */
		tmp._m12 =  (H * ((F * D) - (G * C))) + (this->_m9 * E) + (I * ((A * G) - (B * F)));
		
		F = this->_m2;
		G = this->_m0;
		/* E		a = {1,  5, 13,  0,  4, 12,  2,  6, 14} */
		tmp._m14 = -(this->_m1 * E) + (H * ((F * C) - (G * D))) + (I * ((G * B) - (F * A)));
		
		A = this->_m1;
		B = this->_m2;
		C = this->_m9;
		D = this->_m10;
		E = (A * D) - (B * C);
		F = this->_m13;
		G = this->_m14;
		H = this->_m0;
		I = this->_m8;
		/* D		a = {0,  8, 12,  1,  9, 13,  2, 10, 14} */
		tmp._m13 =  (H * ((C * G) - (D * F))) + (I * ((B * F) - (A * G))) + (this->_m12 * E);
		
		F = this->_m5;
		G = this->_m6;
		/* F		a = {0,  4,  8,  1,  5,  9,  2,  6, 10}} */
		tmp._m15 =  - (this->_m4 * E) + (H * ((F * D) - (G * C)))  + (I * ((A * G) - (B * F)));

		return( tmp );

}


const Matrix &Matrix::operator = (const Matrix &A)
{
	v0 = A.v0;
	v1 = A.v1;
	v2 = A.v2;
	v3 = A.v3;


	return *this;
}


Matrix ::Matrix ( const Quat &q )
{

	this->set(q);
}

const bool Matrix :: isRotation( const float epsilon ) const
{
	Matrix mtmp;

	mtmp._m0 = this->_m0;
	mtmp._m1 = this->_m1;
	mtmp._m2 = this->_m2;
	mtmp._m3 = 0.0f;
	mtmp._m4 = this->_m4;
	mtmp._m5 = this->_m5;
	mtmp._m6 = this->_m6;
	mtmp._m7 = 0.0f;
	mtmp._m8 = this->_m8;
	mtmp._m9 = this->_m9;
	mtmp._m10 = this->_m10;
	mtmp._m11 = 0.0f;
	mtmp._m12 = 0.0f;
	mtmp._m13 = 0.0f;
	mtmp._m14 = 0.0f;
	mtmp._m15 = 1.0f;

	// Is 3x3 submatrix determinant ~= 1
	// Is the bottom row is 4x1 a unit W vector
	// Are m03, m13, m23 equal to zero
	
	/*lint -save -e960 */
    return ( Util::isEqual( mtmp.det(),1.0f,epsilon) &&
			 this->v3.isEqual(Vect(0.0f,0.0f,0.0f,1.0f), epsilon ) &&
			 Util::isZero( this->_m3,epsilon) &&
			 Util::isZero( this->_m7,epsilon) &&	
			 Util::isZero( this->_m11,epsilon) );
	/*lint -restore */
}

bool Matrix::isEqual( const Matrix &A, const float epsilon) const
{
		return (
			Util::isEqual( this->_m0, A._m0, epsilon ) &&
			Util::isEqual( this->_m1, A._m1, epsilon ) &&			
			Util::isEqual( this->_m2, A._m2, epsilon ) &&
			Util::isEqual( this->_m3, A._m3, epsilon ) &&
			Util::isEqual( this->_m4, A._m4, epsilon ) &&
			Util::isEqual( this->_m5, A._m5, epsilon ) &&
			Util::isEqual( this->_m6, A._m6, epsilon ) &&
			Util::isEqual( this->_m7, A._m7, epsilon ) &&
			Util::isEqual( this->_m8, A._m8, epsilon ) &&
			Util::isEqual( this->_m9, A._m9, epsilon ) &&
			Util::isEqual( this->_m10, A._m10, epsilon ) &&
			Util::isEqual( this->_m11, A._m11, epsilon ) &&
			Util::isEqual( this->_m12, A._m12, epsilon ) &&
			Util::isEqual( this->_m13, A._m13, epsilon ) &&
			Util::isEqual( this->_m14, A._m14, epsilon ) &&
			Util::isEqual( this->_m15, A._m15, epsilon ) 
			);

}

bool Matrix::isIdentity( const float epsilon) const
{
			return (
			Util::isEqual( this->_m0, 1.0f, epsilon ) &&
			Util::isEqual( this->_m1, 0.0f, epsilon ) &&			
			Util::isEqual( this->_m2, 0.0f, epsilon ) &&
			Util::isEqual( this->_m3, 0.0f, epsilon ) &&
			Util::isEqual( this->_m4, 0.0f, epsilon ) &&
			Util::isEqual( this->_m5, 1.0f, epsilon ) &&
			Util::isEqual( this->_m6, 0.0f, epsilon ) &&
			Util::isEqual( this->_m7, 0.0f, epsilon ) &&
			Util::isEqual( this->_m8, 0.0f, epsilon ) &&
			Util::isEqual( this->_m9, 0.0f, epsilon ) &&
			Util::isEqual( this->_m10, 1.0f, epsilon ) &&
			Util::isEqual( this->_m11, 0.0f, epsilon ) &&
			Util::isEqual( this->_m12, 0.0f, epsilon ) &&
			Util::isEqual( this->_m13, 0.0f, epsilon ) &&
			Util::isEqual( this->_m14, 0.0f, epsilon ) &&
			Util::isEqual( this->_m15, 1.0f, epsilon ) 
			);
}

void Matrix::set(MatrixRowType type, const Vect &V)
{
	switch( type )
	{
	case ROW_0:
		v0.set( V );
		break;
	case ROW_1:
		v1.set( V );
		break;
	case ROW_2:
		v2.set( V );
		break;
	case ROW_3:
		v3.set( V);
		break;

	}
}


Vect Matrix::get(MatrixRowType type) const
{
	Vect V;

	switch( type )
	{
	case ROW_0:
		V.set(v0);
		break;
	case ROW_1:
		V.set(v1);
		break;
	case ROW_2:
		V.set(v2);
		break;
	case ROW_3:
		V.set(v3);
		break;

	}

	return V;

}

void Matrix::set(const Vect &V0, const Vect &V1, const Vect &V2, const Vect &V3)
{
	v0 = V0;
	v1 = V1;
	v2 = V2;
	v3 = V3;
}


void Matrix :: set( const Quat &q )
{



// this function has been transposed
	float x2, y2, z2;
	float xx, xy, xz;
	float yy, yz, zz;
	float wx, wy, wz;
	
	// ADD test to make sure that quat is normalized

	x2 = q[x] + q[x];
	y2 = q[y] + q[y];
	z2 = q[z] + q[z];
	
	xx = q[x] * x2;
	xy = q[x] * y2;
	xz = q[x] * z2;
	
	yy = q[y] * y2;
	yz = q[y] * z2;
	zz = q[z] * z2;
	
	wx = q[w] * x2;
	wy = q[w] * y2;
	wz = q[w] * z2;

	this->_m0 = 1.0f - (yy + zz);  	
   this->_m1 = xy + wz;	
   this->_m2 = xz - wy; 
   this->_m3 = 0.0f;

   this->_m4 = xy - wz;	
   this->_m5 = 1.0f - (xx + zz); 
   this->_m6 = yz + wx;	 
   this->_m7 = 0.0f;

   this->_m8 = xz + wy;  	
   this->_m9 = yz - wx;   
   this->_m10 = 1.0f - (xx + yy); 
   this->_m11 = 0.0f;

   this->v3.set(0.0f, 0.0f, 0.0f, 1.0f); 

}


void Matrix::set( const RotAxisAngleType, const Vect &vAxis, const float angle)
{
	Quat qtmp(ROT_AXIS_ANGLE, vAxis, angle);
	this->set(qtmp);
}






void Matrix :: setRotOrient( const Vect &vect_dof, const Vect &vect_vup)
{
	/* make sure the DOF and VUP are not parallel */
	//MATHASSERT( gsVectDot(vect_dof, vect_vup) != 1.0f ); "gsMatDofOrient: vect_dof and vect_vup are parallel"));
	
	/* rz = vect_dof */
	const Vect rz = vect_dof.getNorm();

	/* find rx */
	Vect rx = vect_vup.cross(rz);
	rx.norm();
	
	/* find ry */
	Vect ry = rz.cross(rx);
	ry.norm();
	

	this->set( rx, ry, rz, Vect(0.0f, 0.0f, 0.0f,1.0f) );
	this->_m3 = 0.0f;
	this->_m7 = 0.0f;
	this->_m11 = 0.0f;
	this->_m15 = 1.0f;
	

}	/* setRotOrient */



void Matrix::set( const RotOrientType mode, const Vect &dof, const Vect &vup)
{

	
	switch(mode)
		{
		case ROT_ORIENT:
			this->setRotOrient(dof,vup);
			break;
		case ROT_INVERSE_ORIENT:
			this->setRotInvOrient(dof,vup);
			break;

		default:
			//MATHASSERT( MATH_ALWAYS_FAIL );
			break;
		}
}


void Matrix :: setRotInvOrient( const Vect &vect_dof, const Vect &vect_vup)
{
	/* make sure the DOF and VUP are not parallel */
	//GS_ASSERTF((gsVectDot(vect_dof, vect_vup) != 1.0f, "gsMatInvDofOrient: vect_dof and vect_vup are parallel"));
	
	/* rz = vect_dof */
	//gsVectNormCopy(&rz, vect_dof);
	const Vect rz = vect_dof.getNorm();
	
	/* find rx */
	//gsVectCrossNorm(&rx, vect_vup, &rz);
	Vect rx = vect_vup.cross(rz);
	rx.norm();
		
	/* find ry */
	//gsVectCrossNorm(&ry, &rz, &rx);
	Vect ry = rz.cross(rx);
	ry.norm();
		
	//gsMatCombineRow44(out, &rx, &ry, &rz);
	this->set(rx, ry, rz, Vect(0.0f, 0.0f, 0.0f, 1.0f) );
	this->T();
	this->set(ROW_3, Vect(0.0f, 0.0f, 0.0f, 1.0f));


}	/* setInvDofOrient */