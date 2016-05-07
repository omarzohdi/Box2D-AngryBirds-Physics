#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

typedef struct
{
	int joystickID;
	int numberOfButtons;
	float AxesPositions[12];

}JOYSTICK;

typedef struct
{
	int numberOfButtons;
	float posX;
	float posY;
	bool  inWindow;
}MOUSE;

static JOYSTICK joystick1;

void initInputInterface(GLFWwindow* window, bool &joystickActive);
void ChangeSize(int w, int h);
void SpecialKeys(int key, int inX, int inY);
void KeyAction(GLFWwindow* window, int key, int action);
void MouseAction(GLFWwindow* window,int  button,int  action);
void CursorPosition(GLFWwindow* window, float x_pos, float y_pos);
void CursorInView(GLFWwindow* window, int enter);

#endif