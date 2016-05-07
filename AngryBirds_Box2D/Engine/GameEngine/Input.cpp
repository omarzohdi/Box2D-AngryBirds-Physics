#include <string>
#include "AzulCore.h"
#include "Input.h"
#include "GameObject.h"
#include "Box2D.h"
#include "PixelToMeter.h"
#include "Camera.h"
#include "World.h"
#include "ScreenLine.h"
ScreenLine *pLine;
extern bool startworld;

#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;
extern bool userinput;
static bool stretched = false;


enum PositionState
{
	INSIDE,
	OUTSIDE,
	UNKNOWN
};

enum MouseState
{
	RIGHT = 0x1,
	LEFT  = 0x2,
	NONE = 0
};

void getMousePos( GLFWwindow*window, float &posX, float &posY)
{
	// Interface is in Doubles - yuck!
	double xpos_d;
	double ypos_d;

	// get mouse position
	glfwGetCursorPos( window, &xpos_d, &ypos_d);

	// move everything into floats
	posX = (float)xpos_d;
	posY = (float)ypos_d;

	// correct for origin
	Camera *pCam = Camera::Instance();
	pCam->CorrectForOrigin( posX, posY );
}


void MouseTest( GLFWwindow* window, GameObjectBird *pObject,  World * world)
{world;
// Quick and dirty test, if these work the rest do.
// --> try move the mouse inside the window, click right, click left

	float xpos , ypos;
	double xposold , yposold;


	glfwGetCursorPos( window, &xposold , &yposold);

	static float lastXPos;
	static float lastYPos;

	// get mouse position
	getMousePos( window, xpos, ypos);

	// correct for origin
	//float t = ypos / WINDOWHEIGHT;
	//ypos = WINDOWHEIGHT+ t * (-WINDOWHEIGHT);

	PositionState		pState = UNKNOWN;

	// correct bird for the local screen
	Camera *pCam = Camera::Instance();
	pCam;
		
	// world * View * projection
	Vect vout = Vect(0.0f,0.0f,0.0f) * pObject->pGameSprite->getWorld() * pCam->getViewMatrix() * pCam->getProjMatrix();

	// correction for zoom
	float ratio = vout[w];
		
	// make homogeneous
	vout[x] /= ratio;
	vout[y] /= ratio;
		
	// at this point we have a normalized device coordinates
	// process this through the viewport transformation
	float x2 = (vout[x]+1.0f)*(pCam->getScreenWidth()/2.0f);
	float y2 = (vout[y]+1.0f)*(pCam->getScreenHeight()/2.0f);

	Vect vMouse(xpos, ypos, 0.0f);
	Vect vLocalScreen( x2, y2, 0.0f);

	Vect vDiff = vMouse - vLocalScreen;


	if (pObject->state != MOVING)
	{

		if ( vDiff.mag() < (10.0f / ratio) )
		{
			//printf(" INSIDE <---------\n");
			pState = INSIDE;
		}
		else
		{
		//	printf("                   \n");
			pState = OUTSIDE;
		}

	}

	// Mouse - button press?
	MouseState mState = NONE;

	if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS)
	{
		mState = LEFT;
	}
	else if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS)
	{
		mState = RIGHT;
	}

	if (mState == RIGHT && pObject->launched )
	{
		if ( (pObject->health >= 50) || (pObject->health >= 0, pObject->type == BirdType::BLACK_BIRD))
		pObject->LEROYJENKINS();
	}


	// Enter MOVING state
	if( mState == LEFT && pState == INSIDE)
	{
		Vect pos;
		Vect lookAt;
		pCam->TargetWorldScreen( pos, lookAt, WINDOWWIDTH/2, WINDOWHEIGHT/2);

		pos[z] = 0;

		Vect up;
		pCam->getUp( up );
		pCam->setOrientAndPosition( up, lookAt, pos );

		if (pObject->state == NORMAL)
		{
			pObject->state = MOVING;
			pObject->pBody->SetActive(false);
			pObject->origpos = pObject->pos;
		}
	}

	// small sublty here, once moving, left dictates mode
	if( mState == LEFT )
	{
		if ( pObject->state == MOVING && !pObject->launched)
		{
			startworld = true;
			Vect2D mouse;

			b2Vec2 MousePos( PixelToMeter((float)xpos), PixelToMeter((float)ypos) );


			
			b2Vec2 OrigPos ( PixelToMeter((float)pObject->origpos.x), PixelToMeter((float)pObject->origpos.y) );
			float radius = PixelToMeter(100.0f);

			float scale = radius / sqrt(pow(MousePos.x -  OrigPos.x, 2) + pow(MousePos.y -  OrigPos.y, 2));

			if(scale < 1)
			{
				b2Vec2 newPos( (float)(MousePos.x - OrigPos.x) * scale + OrigPos.x, (float)(MousePos.y -  OrigPos.y) * scale + OrigPos.y);

				//pObject->pBody->SetTransform( newPos, pObject->pBody->GetAngle());
				pObject->pBody->SetTransform( newPos, pObject->pBody->GetAngle());
				pObject->pBody->SetLinearVelocity(b2Vec2(0,0));
				pObject->pBody->SetAngularVelocity(0);

				mouse.x = MeterToPixel(newPos.x);
				mouse.y = MeterToPixel(newPos.y);
			}
			else
			{
				mouse.x = MeterToPixel(MousePos.x);
				mouse.y = MeterToPixel(MousePos.y);

				pObject->pBody->SetTransform( MousePos, pObject->pBody->GetAngle());
				pObject->pBody->SetLinearVelocity(b2Vec2(0,0));
				pObject->pBody->SetAngularVelocity(0);


			}


			Vect2D sling( pObject->origpos.x, pObject->origpos.y);

			if (pLine == 0)
				pLine = new ScreenLine( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Poly, 7.0f, Color(Black), mouse,sling  );
			else
			{
				pLine->posA = mouse;
				pLine->posB = sling;
			}

			if (!stretched)
			{
				pSndEngine->play2D("SlingShotStretch.mp3", false);
				stretched = true;
			}


		}
		else
		{
			pObject->origpos.x = pObject->pos.x;
			pObject->origpos.y = pObject->pos.y;
		}
	}
	else
	{
		if (pObject->state == MOVING)
		{
			pSndEngine->play2D("Fly.mp3", false);
			pSndEngine->play2D("Yahoo.mp3", false);
			stretched = false;
			pObject->state = FLYING; 
			pObject->pBody->SetActive(true);

			World::getInstance().TrailList->DisableNodes();

			pLine->posA = Vect2D(-1,-1);
			pLine->posB = Vect2D(-1,-1);

			b2Vec2 newVector = (pObject->origpos - pObject->pos);
			newVector.x = PixelToMeter((float)newVector.x ) * 25.0f;
			newVector.y = PixelToMeter((float)newVector.y ) * 25.0f;
			pObject->pBody->ApplyLinearImpulse(newVector, pObject->pBody->GetPosition() , true);
			pObject->launched = true;
			World::getInstance().BirdsinWorld ++;
		}

	}

}


void KeyboardTest( GLFWwindow* window, GameObject * pObject )
{
	pObject;

	Camera *pCam = Camera::Instance();
	Vect pos;
	Vect dir;
	Vect lookAt;
	Vect up;
	Vect right;

	pCam->getPos( pos );
	pCam->getDir( dir );
	pCam->getLookAt( lookAt );
	pCam->getUp( up );
	pCam->getRight( right );

	
	bool endpos = (pos[x] + WINDOWWIDTH >= LEVELWIDTH );//- WINDOWWIDTH/2 ); 
	bool startpos = (pos[x] < 0);
	bool ZOOMOUT = pos[z] <= MAXZOOM;
	bool ZOOMIN = pos[z] > MINZOOM;

	////////////////////////////////////////ZOOM/////////////////////////////////
	if ( glfwGetKey (window, GLFW_KEY_PERIOD) == GLFW_PRESS && ZOOMOUT)
		{
			pos += dir * 0.01f;
			pCam->setOrientAndPosition( up, lookAt, pos );
		}

	if ( glfwGetKey (window, GLFW_KEY_COMMA) == GLFW_PRESS && ZOOMIN)
		{

			pos -= dir * 0.01f;

			if( (pos - lookAt).dot( dir ) > 0.02f )
				pCam->setOrientAndPosition( up, lookAt, pos );
			else
				pos += dir * 0.01f;
		}
	/////////////////////////////////////////////////////////////////


	/////////////////////Horizontal Movement////////////////////////
	if ( glfwGetKey (window, GLFW_KEY_RIGHT) == GLFW_PRESS && !endpos)
	{
		pos += right * 1.0f;
		lookAt += right * 1.0f;
		
		pCam->setOrientAndPosition( up, lookAt, pos );

		userinput = true;
	}

	if ( glfwGetKey (window, GLFW_KEY_LEFT) == GLFW_PRESS && !startpos)
	{
		pos -= right * 1.0f;
		lookAt -= right * 1.0f;
		pCam->setOrientAndPosition( up, lookAt, pos );

		userinput = true;
	}

	///////////////////////////////////////////////////////

}


