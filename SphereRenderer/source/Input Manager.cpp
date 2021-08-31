#include<glfw3.h>
#include<map>
#include<string>

std::map<std::string, int> inputData =
{

	{"quit", GLFW_KEY_ESCAPE},
	{ "moveRight",GLFW_KEY_RIGHT },
	{ "moveLeft", GLFW_KEY_LEFT },
	{ "moveUp", GLFW_KEY_UP },
	{ "moveDown", GLFW_KEY_DOWN },
	{"a", GLFW_KEY_A},
	{"p", GLFW_KEY_P},
	{"n",GLFW_KEY_N}
};