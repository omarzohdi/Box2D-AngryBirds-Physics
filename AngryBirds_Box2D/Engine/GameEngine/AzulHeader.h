#ifndef AZULHEADER_H
#define AZULHEADER_H


#define AZUL_UNUSED(x) x

#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAX_NAME 256

#include <GLTools.h>	// OpenGL toolkit
//#include <GL/glew.h>

//#define GLFW_INCLUDE_GLU
#include "..\OpenGL\GLFW\include\glfw3.h"


// When enabliing warning level 4, we get warning C4505: unreferenced local function has been removed
// This pragma kills this needless warning
#pragma warning(disable: 4505)


#include "MathEngine.h"
#include "VectApp.h"
#include "QuatApp.h"

#include "File.h"

#include "PCSNode.h"
#include "PCSTree.h"
#include "Time.h"
#include "Timer.h"
#include "AzulStopWatch.h"

#include "GraphicsObject.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "NullObject.h"

#include "UserInterface.h"

#include "SpriteModel.h"
#include "GameSprite.h"

#include "SpriteBatchManager.h"

#include "UserInterface.h"

#include "Engine.h"


#endif