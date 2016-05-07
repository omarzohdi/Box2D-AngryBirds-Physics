

#include "AzulCore.h"


int Camera::getScreenWidth()
{
	return (int)WINDOWWIDTH;
}

int Camera::getScreenHeight()
{
	return (int)WINDOWHEIGHT;
}

Camera *Camera::Instance()
{
	// This is where its actually stored (BSS section)
	static Camera instance;
	return &instance;
}

// default constructor
 Camera :: Camera()
{
};

 void Camera::TargetWorldScreen( Vect &outCamPos, Vect &outCamLookAt, float worldScreenX, float worldScreenY )
{
	// target a world screen coordinates, do not change zoom
	outCamPos    = Vect( (worldScreenX - viewport_width/2.0f), (worldScreenY - viewport_height/2.0f), this->vPos[z] );
	outCamLookAt = Vect( (worldScreenX - viewport_width/2.0f), (worldScreenY - viewport_height/2.0f), this->vLookAt[z] );
}

void Camera::CorrectForOrigin(float &,float &ypos )
{

	float screen_height = (float )(this->viewport_height - 1);
	float t = ypos / screen_height;
	ypos = screen_height + t * (-screen_height);
}

// critical informational knobs for the perspective matrix
// Field of View Y is in degrees (copying lame OpenGL)
void Camera::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
{
	Camera *pCamera = Camera::Instance();
	pCamera->aspectRatio = Aspect;
	pCamera->fovy = Fovy;
	pCamera->nearDist = NearDist;
	pCamera->farDist = FarDist;

	pCamera->camType = CameraType::PERSPECTIVE_TYPE;
};

void Camera::setOrthographic(const float _xMin, const float _xMax, const float _yMin, const float _yMax, const float _zMin, const float _zMax)
{
	Camera *pCamera = Camera::Instance();
	pCamera->camType = CameraType::ORTHOGRAPHIC_TYPE;


	pCamera->xMin = _xMin;
	pCamera->yMin = _yMin;
	pCamera->zMin = _zMin;

	pCamera->xMax = _xMax;
	pCamera->yMax = _yMax;
	pCamera->zMax = _zMax;

	pCamera->far_height = pCamera->yMax - pCamera->yMin;
	pCamera->far_width = pCamera->xMax - pCamera->xMin;
	pCamera->near_width = pCamera->yMax - pCamera->yMin;
	pCamera->nearDist = pCamera->zMin;
	pCamera->farDist = pCamera->zMax;


};

// Just a pass through to setup the view port screen sub window
void Camera::setViewport(const int inX, const int inY, const int width, const int height)
{
	Camera *pCamera = Camera::Instance();

	pCamera->viewport_x = inX;
	pCamera->viewport_y = inY;
	pCamera->viewport_width = width;
	pCamera->viewport_height = height;

   pCamera->privSetViewState();
};

// Simple wrapper
void Camera::privSetViewState( void )
{
	glViewport(this->viewport_x, this->viewport_y, this->viewport_width, this->viewport_height);
};


// Goal, calculate the near height / width, same for far plane 
void Camera::privCalcPlaneHeightWidth( void )
{

   this->near_height = 2.0f * tan(( this->fovy * MATH_PI/180.0f ) * .5f) * this->nearDist;
   this->near_width = this->near_height * this->aspectRatio;

   this->far_height = 2.0f * tan(( this->fovy * MATH_PI/180.0f) * .5f) * this->farDist;
   this->far_width = this->far_height * this->aspectRatio;

};

void Camera::setOrientAndPosition(const Vect &inUp, const Vect &inLookAt, const Vect &inPos)
{
		Camera *pCamera = Camera::Instance();

	// Remember the up, lookAt and right are unit, and are perpendicular.
	// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
	// Make sure that all vectors are unit vectors.

	pCamera->vLookAt = inLookAt;

   // Point out of the screen into your EYE
   pCamera->vDir = inPos - inLookAt;
	pCamera->vDir.norm();

   // Clean up the vectors (Right hand rule)
	pCamera->vRight = inUp.cross( pCamera->vDir );
	pCamera->vRight.norm();

	pCamera->vUp = pCamera->vDir.cross( pCamera->vRight );
	pCamera->vUp.norm();

	pCamera->vPos = inPos;

};


void Camera::privCalcFrustumVerts( void )
{
	// Top Left corner and so forth.  In this form to see the pattern
   // Might be confusing (remember the picture) vDir goes from screen into your EYE
   // so distance from the eye is "negative" vDir
	this->nearTopLeft		   = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
	this->nearTopRight		= this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
	this->nearBottomLeft	   = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
	this->nearBottomRight	= this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
	this->farTopLeft		   = this->vPos - this->vDir * this->farDist  + this->vUp * this->far_height * 0.5f  - this->vRight * this->far_width * 0.5f;
	this->farTopRight		   = this->vPos - this->vDir * this->farDist  + this->vUp * this->far_height * 0.5f  + this->vRight * this->far_width * 0.5f;
	this->farBottomLeft		= this->vPos - this->vDir * this->farDist  - this->vUp * this->far_height * 0.5f  - this->vRight * this->far_width * 0.5f;
	this->farBottomRight   	= this->vPos - this->vDir * this->farDist  - this->vUp * this->far_height * 0.5f  + this->vRight * this->far_width * 0.5f;
};
	
void Camera::privCalcFrustumCollisionNormals( void )
{
	// Normals of the frustum around nearTopLeft
	Vect A = this->nearBottomLeft - this->nearTopLeft;
	Vect B = this->nearTopRight - this->nearTopLeft;
	Vect C = this->farTopLeft - this->nearTopLeft;
	
	this->frontNorm = A.cross(B);
	this->frontNorm.norm();

	this->leftNorm = C.cross(A);
	this->leftNorm.norm();
	
	this->topNorm = B.cross(C);
	this->topNorm.norm();

	// Normals of the frustum around farBottomRight
	A = this->farBottomLeft - this->farBottomRight;
	B = this->farTopRight - this->farBottomRight;
	C = this->nearBottomRight - this->farBottomRight;
	
	this->backNorm = A.cross(B);
	this->backNorm.norm();
	
	this->rightNorm = B.cross(C);
	this->rightNorm.norm();

	this->bottomNorm = C.cross(A);
	this->bottomNorm.norm();
};


// The projection matrix (note it's invertable)
void Camera::privUpdateProjectionMatrix( void )
{

	if( this->camType == CameraType::PERSPECTIVE_TYPE)
	{
	this->projMatrix[m0] = 2.0f * this->nearDist / this->near_width;
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;
	
   this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f * this->nearDist / this->near_height;
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = (this->farDist + this->nearDist)/(this->nearDist - this->farDist);
	this->projMatrix[m11] = -1.0f;

	this->projMatrix[m12] = 0.0f;
	this->projMatrix[m13] = 0.0f;
	this->projMatrix[m14] = (2.0f * this->farDist * this->nearDist)/(this->nearDist - this->farDist);
	this->projMatrix[m15] = 0.0f;
	}
	else
	{
		this->projMatrix[m0] = 2.0f / (xMax - xMin);
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = -((xMax + xMin)/(xMax - xMin));
	
		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = 2.0f / (yMax - yMin);
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = -((yMax + yMin)/(yMax - yMin));

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = -2.0f / (zMax - zMin);
		this->projMatrix[m11] = -((zMax + zMin)/(zMax - zMin));

		this->projMatrix[m12] = 0.0f;
		this->projMatrix[m13] = 0.0f;
		this->projMatrix[m14] = 0.0f;
		this->projMatrix[m15] = 1.0f;

	}

};


void Camera::privUpdateViewMatrix( void )
{
	// This functions assumes the your vUp, vRight, vDir are still unit
	// And perpendicular to each other
   //  view = Rot(orient) * trans(-(eye.basis) )

	this->viewMatrix[m0] = this->vRight[x];
   this->viewMatrix[m1] = this->vUp[x];
   this->viewMatrix[m2] = this->vDir[x];
   this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->vRight[y];
   this->viewMatrix[m5] = this->vUp[y];
   this->viewMatrix[m6] = this->vDir[y];
   this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8]  = this->vRight[z];
	this->viewMatrix[m9]  = this->vUp[z];
	this->viewMatrix[m10] = this->vDir[z];
	this->viewMatrix[m11] = 0.0f;

   // Change of basis (dot with the basis vectors)
   this->viewMatrix[m12]  = -vPos.dot(vRight);
   this->viewMatrix[m13]  = -vPos.dot(vUp);
   this->viewMatrix[m14] = -vPos.dot(vDir);
   this->viewMatrix[m15] = 1.0f;
};


// Update everything (make sure it's consistent)
void Camera::updateCamera(void)
{

		Camera *pCamera = Camera::Instance();

 //  // First find the near height/width, far height/width
	//this->privCalcPlaneHeightWidth( );

 //  // Find the frustum physical verts
	//this->privCalcFrustumVerts( );

 //  // find the frustum collision normals
	//this->privCalcFrustumCollisionNormals( );

   // update the projection matrix
	pCamera->privUpdateProjectionMatrix( );

   // update the view matrix
	pCamera->privUpdateViewMatrix( );
}


// Accessor mess:
Matrix & Camera::getViewMatrix( void )
{
	Camera *pCamera = Camera::Instance();

	return pCamera->viewMatrix;
}

Matrix & Camera::getProjMatrix( void)
{
	Camera *pCamera = Camera::Instance();

	return pCamera->projMatrix;
}

void Camera::getPos( Vect &outPos) const
{
	outPos = this->vPos;
}

void  Camera::getDir( Vect &outDir) const
	{
	outDir = this->vDir;
	}

void  Camera::getUp( Vect &outUp) const
	{
	outUp = this->vUp;
	}

void Camera::getLookAt( Vect &outLookAt ) const
{
	outLookAt = this->vLookAt;
}

void Camera::getRight( Vect &outRight ) const
{
	outRight = this->vRight;
}

void Camera::getFieldOfView( float &Value) const
{
	Value = this->aspectRatio;
};

void Camera::setFieldOfView( const float Value)
{
	this->aspectRatio = Value;
};

void Camera::getNearDist( float &Value) const
{
	Value = this->nearDist;
}

void Camera::setNearDist( const float Value)
{
	this->nearDist = Value;
}