#pragma once
#include "Header.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TEXPATH = "ressources/textures/container.jpg";
const char* TEXPATH1 = "ressources/textures/face.png";

std::string TEXPATHS[2] = { TEXPATH, TEXPATH1 };
int main()
{
	//Translation using glm librairy
	glm::mat4 trans = glm::mat4(1.0f);


struct Triangle triforce = {
	{ 
	   -1.0f,-1.f,0,  0.f,0.f,1.f, 
		0.f,-1.f,0,	  1.f,0.f,0.f, 
		-0.5,0,0,	  0.f,1.f,0.f,
		1.f,-1.f,0,	  0.f,0.f,1.f,
		0.5f,0,0,	  1.f,0.f,0.f,
		0.f,1.f,0,    0.f,1.f,0.f,
	},
	{
		0,1,2,
		1,3,4,
		2,4,5,
	},
	9,
};


struct Triangle a = {
	{  //position info           RGB info          Texture info
		-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,     0.0f, 0.0f,
		0.5f,-0.5f,0.0f,	   0.0f,1.0f,0.0f,     1.0f, 0.0f,
		-0.5f,0.5f,0.0f,	   0.0f,0.0f,1.0f,     0.0f, 1.0f,  
		 0.5f,0.5f,0.0f,       1.0f,1.0f,1.0f,      1.0f,1.0f,
	},
	
	{
		0,1,2,
		2,1,3,
	},
	6,
};

	GLFWwindow* window = initContext(WIDTH, HEIGHT, "Testing");

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to instantiate GLEW." << std::endl;
		return -1;
	};


	//VERTICES DATA

	TriangleSet triforceV;
	triforceV.setEverything(1, 0, &triforce, NULL, 0);
	//glEnable(GL_DEPTH_TEST);

	



	Cube cube(1.f, 1.f, 1.f);
	//---------------------------------------------------------
	//glGetVertexArrayiv(VAO, GL_ELEMENT_ARRAY_BUFFER_BINDING, &a); can't use it on OpenGL 3.3
	float temp1 = 0;
		while (!glfwWindowShouldClose(window))
		{

			processInputs(window);
			glfwPollEvents();                               //Trigger events like inputs
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.0f,0.f,0.1f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

			//Shader setting
			float uTime = (float) glfwGetTime();
			cube.draw(uTime);

			glfwSwapBuffers(window);                        
			//glfwSwapInterval(1);                                              // update speed

		};
	glfwTerminate();


}
