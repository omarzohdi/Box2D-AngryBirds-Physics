#ifndef AZULCORE_H
#define AZULCORE_H

#include "AzulHeader.h"

#define WINDOWWIDTH 1280.0f
#define WINDOWHEIGHT 864.0f

#define LEVELWIDTH 2000//1280.0f
#define LEVELHEIGHT 864.0f

#define MAXZOOM 1.133f
#define MINZOOM -0.33

struct GLFWwindow;

class AzulCore : public Engine
{

public:

	AzulCore();

	void Initialize();
	void LoadContent();
	void Update();
	void Draw();
	void UnLoadContent();

	static Engine *getEngine();
	
private:
	void SetupRC();
	void ShutdownRC(GLFWwindow* window);

	static AzulCore *privInstance();

	GLFWwindow * window;
	bool joystickActive;
};


GLFWwindow* createGraphicsWindow( const char* windowName, const int Width,const int Height );


#endif 