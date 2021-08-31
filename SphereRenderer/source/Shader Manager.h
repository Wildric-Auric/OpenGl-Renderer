#include<GL/glew.h>
#include<glfw3.h> 
#include<iostream>
#include<fstream>
#include<string.h>
#include"Header.h"


std::pair<const char*, const char*> parseShader(const char* path)
{
	std::string frag, vert = "";
	unsigned int current = 0;
	std::ifstream file(path);
	for (std::string line; std::getline(file, line); )
	{
		if (line.find("//fragment shader") != -1) current = 1;
		else if (line.find("//vertex shader") != -1) current = 2;
		if (current == 1) frag += line + '\n';
		else if (current == 2) vert += line + '\n';
	}
	return std::make_pair(_strdup(&vert[0]), _strdup(&frag[0]));
}



unsigned int createShader(const char** data, int shaderType)
{
	unsigned int id;
	if (shaderType == VERTEX) {

		id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (shaderType == FRAGMENT) {
	    id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	glShaderSource(id, 1, data, NULL);
	glCompileShader(id);
	int successInfo;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &successInfo);
	if (!successInfo) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR:: SHADER " << shaderType<< " COMPILATION FAILED" << "\n"
		<<infoLog<<std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int createShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader)
{
	unsigned int shaderProg = glCreateProgram();
	glAttachShader(shaderProg, *vertexShader);
	glAttachShader(shaderProg, *fragmentShader);
	glLinkProgram(shaderProg);
	int successInfo;
	char infoLog[512];
	glGetShaderiv(shaderProg, GL_LINK_STATUS, &successInfo);
	if (!successInfo)
	{
		glGetShaderInfoLog(shaderProg, 512, NULL, infoLog);
		std::cout << "ERROR::LINKING SHADERS FAILED \n" << infoLog << std::endl;
		glDeleteProgram(shaderProg);
		return 0;
	};
	return shaderProg;

}

