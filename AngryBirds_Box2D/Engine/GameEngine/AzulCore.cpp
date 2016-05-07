#include "AZULCore.h"

#include "TextMan.h"
#include "EnumName.h"
#include "Rect.h"
#include "ImageMan.h"
#include "Image.h"
#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "BoxModel.h"
#include "BoxSprite.h"
#include "CircleModel.h"
#include "CircleSprite.h"
#include "PolyModel.h"
#include "PolySprite.h"
#include "AzulStopWatch.h"
//#include "Input.h"
#include "Box2D.h"
#include "PixelToMeter.h"
#include "GameObject.h"
#include "GameObjectBird.h"
#include "GameObjectBlock.h"
#include "AngryContactListener.h"
#include "Color.h"
#include "World.h"

AzulStopWatch stopWatch;
AzulStopWatch totalWatch;
GLShaderManager	shaderManager;

#include "irrKlang.h"
using namespace irrklang;
ISoundEngine	*pSndEngine;
ISound	*pSndTheme;


bool startworld = false;

//-----------------------------------------------------------------------------
//  AzulCore::AzulCore()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
AzulCore::AzulCore()
{
	joystickActive = false;
	printf("createGraphicsWindows()\n");

	// create graphics windows with defaults
	char title[256];
	sprintf_s(title,"%s\n",MONKEY);
	window = createGraphicsWindow(title, (int)WINDOWWIDTH , (int)WINDOWHEIGHT);

	// inputs creation
	initInputInterface(window, joystickActive);
}


//-----------------------------------------------------------------------------
// AzulCore::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void AzulCore::Initialize()
{
	AZUL_UNUSED( window );

	// Rendering Context
	this->SetupRC();

	// Setup & compile shaders
	shaderManager.InitializeStockShaders();

	pSndEngine = irrklang::createIrrKlangDevice();

	// scale
	UnitScale::Create( 50.0f );

	// Setup the managers
    TextMan::Create();
	ImageMan::Create();
	SpriteBatchManager::Create();

    // Initialize timer
	AzulStopWatch::initStopWatch();

	// Start timer
	totalWatch.tic();
	stopWatch.tic();

}



//-----------------------------------------------------------------------------
// AzulCore::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void AzulCore::LoadContent()
{
	// Initially setup the camera  (screen size)
	//Camera::setViewport( 0, 0, (int)WINDOWWIDTH, (int)WINDOWHEIGHT);
	//Camera::setOrthographic(-WINDOWWIDTH/2, WINDOWWIDTH/2, -WINDOWHEIGHT/2, WINDOWHEIGHT/2, 1.0f, 1000.0f);
	//Camera::setOrientAndPosition( Vect(0.0f,1.0f,0.0f), Vect(0.0f,0.0f, -1.0f), Vect(0.0f,0.0f, 0.00f) );
	// 

	Camera::setViewport( 0, 0, (int)WINDOWWIDTH, (int)WINDOWHEIGHT);
	Camera::setOrthographic( -Camera::getScreenWidth()/2.0f,  Camera::getScreenWidth()/2.0f,
						   -Camera::getScreenHeight()/2.0f, Camera::getScreenHeight()/2.0f,
		                   1.0f, 1000.0f);
	Camera::setOrientAndPosition( Vect(0.0f,1.0f,0.0f), Vect(0.0f,0.0f, -1.0f), Vect(0.0f,0.0f, 0.0f) );
	World::getInstance().initializeWorld();

	pSndTheme = pSndEngine->play2D("Ambient.mp3", true, false, true); // play some mp3 file, looped
	pSndTheme->setVolume(0.5f);
};


//-----------------------------------------------------------------------------
// AzulCore::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void AzulCore::Update()
{
	// Time update.
	//      Get the time that has passed.
	//      Feels backwards, but its not, need to see how much time has passed
		stopWatch.toc();
		stopWatch.tic();
		totalWatch.toc();

	// Add your update below this line: ----------------------------

	World::getInstance().Update( stopWatch.timeInSeconds(), window);	

	// Camera System - needs to be updated once per frame
	Camera::updateCamera();

   // checking for window quit, leave at bottom of Update()
   if(glfwWindowShouldClose(window))
   {
	   this->Quit();
   }
}

//-----------------------------------------------------------------------------
// AzulCore::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void AzulCore::Draw()
{
   // Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Add Rendering stuff below this line
	SpriteBatchManager::Process();

	// House keeping
	//    Swap buffers
	//    Poll for Events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

//-----------------------------------------------------------------------------
// AzulCore::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void AzulCore::UnLoadContent()
{
	// Todo - fix 
	//	TextureManager::deleteTextures();

	this->ShutdownRC(window);
}


// End of File: AzulCore.cpp