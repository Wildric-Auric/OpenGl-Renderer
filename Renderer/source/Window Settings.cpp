#include "Header.h"

GLFWwindow* initContext(int width,int height, const char* label, bool updateShapesWithWindow) 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window;
	window = glfwCreateWindow(width, height, label, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glViewport(0, 0, 800, 600);
	glfwMakeContextCurrent(window);
	std::cout << "Context created successfully" << '\n' << "OpenGL version: "
		<< glGetString(GL_VERSION) << std::endl;
	if (updateShapesWithWindow)
	{
		glfwSetFramebufferSizeCallback(window, window_size_callback);
	}
	return window;
};

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); //Call this each time you resize the window
}

void processInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, inputData["quit"]) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
};
