#include "AZULCore.h"

//-----------------------------------------------------------------------------
//  Helper Start Up Functions 
//-----------------------------------------------------------------------------

GLFWwindow* createGraphicsWindow( const char* windowName, const int Width,const int Height )
{
	// Set the display mode
	if( !glfwInit() )
	{
		exit(EXIT_FAILURE);
	}

	// the first callback can be replaced by glfwGetPrimaryMonitor() which with some tweaks allows to choose monitor of display
	// creating locally but will pass it outside so no problem with this pointer creating a leak
	GLFWwindow* window = glfwCreateWindow(Width, Height, windowName , NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	//necessary goo of glfw
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
		// return error
	}
	
	return window;
}

void AzulCore::SetupRC()
{
	// Black background
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// added for sprite land
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

void AzulCore::ShutdownRC(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

AzulCore *AzulCore::privInstance()
{
	static AzulCore azulEngine;
	return &azulEngine;
}

Engine *AzulCore::getEngine()
{
	AzulCore *p  = AzulCore::privInstance();
	p->running = true;
	return p;
}