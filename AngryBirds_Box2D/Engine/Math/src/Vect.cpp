#include "MathEngine.h"
#include <math.h>

Vect::~Vect()	{};

void Vect::set(const float inX, const float inY, const float inZ, const float inW ) 
	{
		this->vx = inX;
		this->vy = inY;
		this->vz = inZ;
		this->vw = inW;
	};

const float Vect::magSqr( void ) const	{
		return ( this->vx * this->vx + this->vy * this->vy + this->vz * this->vz );
	};


const float Vect::dot( const Vect &vIn ) const
	{
		return( this->vx * vIn.vx + this->vy * vIn.vy + this->vz * vIn.vz);
	};

const Vect Vect::cross( const Vect &vIn ) const
	{
		return  Vect( this->vy * vIn.vz - this->vz * vIn.vy,
					this->vz * vIn.vx - this->vx * vIn.vz,
					this->vx * vIn.vy - this->vy * vIn.vx);
	};

void Vect::operator *= (const float scale)
	{
		this->vx *= scale;
		this->vy *= scale;
		this->vz *= scale;
		this->vw = 1.0f;
	};



Vect Vect::operator * (const float scale) const
	{
		return Vect( this->vx*scale, this->vy*scale, this->vz*scale );
	};


void Vect::operator -= (const Vect &inV)
	{
		this->vx -= inV.vx;
		this->vy -= inV.vy;
		this->vz -= inV.vz;
		this->vw = 1.0f;
	};

Vect Vect::operator - (void) const
	{
		return Vect( -this->vx, -this->vy, -this->vz);
	};

















Vect Vect:: operator + (void) const 
	{	
		return Vect(this->vx,this->vy,this->vz);	
	};

Vect Vect:: operator + (const Vect &inV) const
	{
		return Vect( this->vx+inV.vx, this->vy+inV.vy, this->vz+inV.vz );
	};

	void Vect::operator += (const Vect &inV)
	{
		this->vx += inV.vx;
		this->vy += inV.vy;
		this->vz += inV.vz;
		this->vw = 1.0f;
	};

	Vect Vect:: operator - (const Vect &inV) const 
	{
		return Vect( this->vx-inV.vx, this->vy-inV.vy, this->vz-inV.vz );
	};


Vect::Vect()	
: vx(0.0f), vy(0.0f), vz(0.0f), vw(1.0f)
{
};


Vect:: Vect( const Vect &inV )	
: vx(inV.vx), vy(inV.vy), vz(inV.vz), vw(inV.vw)
{
};

	// Constructors
Vect::Vect(const float in_x, const float in_y, const float in_z,  const float in_w)
: vx(in_x), vy(in_y), vz(in_z), vw(in_w)
{	};


	// Bracket
	float & Vect::operator[] (const enum x_enum)	{	return this->vx;	};
	float & Vect::operator[] (const enum y_enum)	{	return this->vy;	};
	float & Vect::operator[] (const enum z_enum)	{	return this->vz;	};
	float & Vect::operator[] (const enum w_enum)	{	return this->vw; };


	const float Vect::operator[] (const enum x_enum) const { return this->vx; };
	const float Vect::operator[] (const enum y_enum) const { return this->vy; };
	const float Vect::operator[] (const enum z_enum) const { return this->vz; };
	const float Vect::operator[] (const enum w_enum) const { return this->vw; };


Vect operator *(const float scale, const Vect &inV ) 
	{
		return Vect( scale*inV.vx, scale*inV.vy, scale*inV.vz, 1.0f);
	};

const float Vect::mag( void ) const
	{
		return sqrtf( this->vx * this->vx + this->vy * this->vy + this->vz * this->vz );
	}


Vect & Vect::norm( void )
{
	float magnitude;
	magnitude = this->dot(*this);
	
	if(magnitude > (ENGINE_MATH_TOLERANCE * ENGINE_MATH_TOLERANCE) )
		{
		magnitude = 1.0f / sqrt(magnitude);
		this->vx *= magnitude;
		this->vy *= magnitude;
		this->vz *= magnitude;
		this->vw = 1.0f;
		}
	else
		{
		// do nothing (magnitude is too small)
	 	
		}
		
	return ( *this ); 
}

Vect Vect::getNorm( void ) const
{
	float mag;
	mag = this->dot(*this);
	
	if(mag > (ENGINE_MATH_TOLERANCE * ENGINE_MATH_TOLERANCE) )
		{
		mag = 1.0f / sqrt(mag);
		}
	else
		{
		// do nothing (magnitude is too small)
	 	
		}
		
	return  Vect( this->vx * mag, this->vy * mag, this->vz*mag ); 
}

const float Vect::getAngle( const Vect &vIn ) const
{
	return acos( this->dot(vIn)/ (this->mag()*vIn.mag()) );
}



bool Vect::isEqual( const Vect &v, const float epsilon ) const
{
	return (Util::isEqual( this->vx, v.vx, epsilon ) &&
			Util::isEqual( this->vy, v.vy, epsilon ) &&
			Util::isEqual( this->vz, v.vz, epsilon ) &&
			Util::isEqual( this->vw, v.vw, epsilon ));
}


bool Vect::isZero( const float epsilon ) const
{
	return (Util::isEqual( this->vx, 0.0f, epsilon ) &&
			Util::isEqual( this->vy, 0.0f, epsilon ) &&
			Util::isEqual( this->vz, 0.0f, epsilon ) &&
			Util::isEqual( this->vw, 1.0f, epsilon ));

}

void Vect::set( const Vect &A)
{
	this->vx = A.vx;
	this->vy = A.vy;
	this->vz = A.vz;
	this->vw = A.vw;
}

Vect Vect::operator* ( const Matrix &m ) const
{
	return Vect (	vx * m[m0] + vy * m[m4] + vz * m[m8]  + vw * m[m12],
			        vx * m[m1] + vy * m[m5] + vz * m[m9]  + vw * m[m13],
			        vx * m[m2] + vy * m[m6] + vz * m[m10] + vw * m[m14],
			        vx * m[m3] + vy * m[m7] + vz * m[m11] + vw * m[m15] );
	
}


Vect Vect::operator*= (  const Matrix &m ) 
{
	float tx,ty,tz,tw;
		tx =	  vx * m[m0] + vy * m[m4] + vz * m[m8]  + vw * m[m12];
		ty =      vx * m[m1] + vy * m[m5] + vz * m[m9]  + vw * m[m13];
		tz =      vx * m[m2] + vy * m[m6] + vz * m[m10] + vw * m[m14];
		tw =      vx * m[m3] + vy * m[m7] + vz * m[m11] + vw * m[m15];

		this->set(tx,ty,tz,tw);
	return( *this );
}


const Vect & Vect::operator=(const Vect &v)
{
	this->vx = v.vx;
	this->vy = v.vy;
	this->vz = v.vz;
	this->vw = v.vw;

	return *this;
}

