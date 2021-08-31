#ifndef  HEADER_H
#define HEADER_H

#include<GL/glew.h>
#include<glfw3.h> 
#include<iostream>
#include<map>
#include<cstdio>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<tgmath.h>

GLFWwindow* initContext(int w, int h, const char* label, bool updateShapesWithWindow = 1);
void window_size_callback(GLFWwindow* w, int width, int height);
void processInputs(GLFWwindow* w);
extern std::map<std::string, int> inputData;
std::pair<const char*, const char*> parseShader(const char* path);
unsigned int createShader(const char** data, int shaderType);
unsigned int createShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader);

enum shaderType {
	VERTEX,
	FRAGMENT,
};
struct Triangle {
	float verticesData[1000];
	unsigned int indices[1000];
	int vnum;                  //TODO: Dynamic array length in structure

};

extern const int WIDTH;
extern const int HEIGHT;
extern const char* TEXPATH;
extern const char* TEXPATH1;
extern std::string TEXPATHS[2];


unsigned char* loadImage(const char* a, int* b, int* c, int* d, int e);


//----------------------------------------------------




class TransMatrices
{
public:
	int usingOrtho = 0;
	const int* width;
	const int* height;
	float minDistance, maxDistance, fov, worldRotation, defaultSceneDistance;

	glm::mat4 local = glm::mat4(1.0f), model = glm::mat4(1.0f), view = glm::mat4(1.0f), projection = glm::mat4(1.0f), clip = glm::mat4(1.0f);

	TransMatrices(float worldRotation, float defaultSceneDistance,
		const int* width, const int* height, float minDistance, float maxDistance, float fov,
		bool ortho = 0)
	{
		this->minDistance = minDistance;
		this->maxDistance = maxDistance;
		this->fov = fov;
		this->worldRotation = worldRotation;
		this->defaultSceneDistance = defaultSceneDistance;
		this->width = width;
		this->height = height;
		usingOrtho = ortho;

		update();
	};
	void update(glm::vec3 localTrans = glm::vec3(0.0f, 0.0f, 0.0f), float localRot = 0,
		glm::vec3 rotInfo = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		local = glm::mat4(1.0f), model = glm::mat4(1.0f), view = glm::mat4(1.0f), projection = glm::mat4(1.0f), clip = glm::mat4(1.0f);
		local = glm::scale(local, scale);
		local = glm::translate(local, localTrans);
		local = glm::rotate(local, glm::radians(localRot), rotInfo);

		model = glm::rotate(model, glm::radians(worldRotation), glm::vec3(1.0f, 0.0f, 0.0));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, defaultSceneDistance));
		if (usingOrtho) projection = glm::ortho(0.0f, (float)*width, 0.0f, (float)*height, minDistance, maxDistance);
		else {
			projection = glm::perspective(glm::radians(fov), (float)(*width)/(float)(*height), minDistance, maxDistance);
		};
		
		clip = projection * view * model;
	}
};





//-----------------------------------------------------




class TriangleSet {
private:
	unsigned int VBO, EBO;
	unsigned int stride;
	int width, height, nrChannels;

public:
	unsigned int VAO;
	int vnum;
	unsigned int tex[17];
	void setStride(bool usingColor, bool usingTexture) {
		stride = (3 + 3*usingColor + 2*usingTexture) * sizeof(float);                               //Size of each vertex;
	}
	void setTriangles(struct Triangle* triangleStruct) {
		float* verticesData = (*triangleStruct).verticesData;
		unsigned int* indices = (*triangleStruct).indices;
		int vsize = sizeof((*triangleStruct).verticesData);
		int isize = sizeof((*triangleStruct).indices);
		
		this->vnum = (*triangleStruct).vnum;
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);                                //Call this in update to switch VAO
		glBufferData(GL_ARRAY_BUFFER, vsize, verticesData, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);


	};
	void setVertices() {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);
	}
	void setColor() {
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	};
	void setTexture(const char* path, unsigned int texIndex) {
		glGenTextures(1, &tex[texIndex]);

		glBindTexture(GL_TEXTURE_2D, tex[texIndex]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		const char* texPath = path;
		unsigned char* data = loadImage(texPath, &width, &height, &nrChannels, 0);
		if (!data) { std::cout << "WARNING::FAILED TO LOAD TEXTURE: " << texPath << std::endl; }
		else {
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			if (((std::string)path).find("png") != -1) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	void useTexture() {
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

	}
	void updateTex(std::string* pathArray, int size) {

		for (int i = 0; i < size; i++) {
			this->setTexture(pathArray[i].c_str(), i);
		}
	}

	void setEverything(bool usingColor, bool usingTex, Triangle* data, std::string* pathArray, int size) {
		this->setStride(usingColor,usingColor);
		this->setTriangles(data);
		this->setVertices();
		if (usingColor) this->setColor();

		if (usingTex) {
			this->updateTex(pathArray, size);
			this->useTexture();
		}

	}

};



//---------------------------------------------------------




class Shader
{
private:
	unsigned int shaderProg;
	unsigned int vertexShader;
	unsigned int fragmentShader;
public:
	TransMatrices t = TransMatrices(0.0f, -5.0f, &WIDTH, &HEIGHT, 0.01f, 100.0f, 45.0f, 0);
	void create(const char* PATH)
	{
		std::pair < const char*, const char*> shaderData = parseShader(PATH);
		vertexShader = createShader(&shaderData.first, VERTEX);
		fragmentShader = createShader(&shaderData.second, FRAGMENT);
		shaderProg = createShaderProgram(&vertexShader, &fragmentShader);
		//glDeleteShader(vertexShader);
		//glDeleteShader(fragmentShader);
	}
	void use() {
		try {
			glUseProgram(shaderProg);
		}
		catch (int ex) { std::cout << ex << std::endl; }
	}
	void setUniform1(const char* name, float value) {
		glUniform1f(glGetUniformLocation(shaderProg, name), value);
	}
	void setInt(const char* name, int value) {
		glUniform1i(glGetUniformLocation(shaderProg, name), value);
	}
	void setMat4(const char* name,glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(shaderProg, name), 1, GL_FALSE, glm::value_ptr(value));
	}
};


//-------------------------------------------------------




class Cube {
private:
	struct Triangle vertexInfo = {
{  //position info           RGB info          Texture info
	-0.5f,0.5f,0.0f,	   0.0f,0.0f,1.0f,     0.0f, 1.0f,
	 0.5f,0.5f,0.0f,       1.0f,1.0f,1.0f,      1.0f,1.0f,
	-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,     0.0f, 0.0f,
	0.5f,-0.5f,0.0f,	   0.0f,1.0f,0.0f,     1.0f, 0.0f,
},

{
	0,2,3,
	3,1,0,
},
6,
	};
public:
	std::pair<TriangleSet, Shader> faces[1000] = { };
	Cube(float sizeX, float sizeY, float sizeZ, float offsetX = 0.f, float offsetY = -0.5f, float offsetZ = 0.0f, 
		bool sub  = 0, int ratio = 5, bool sphere = 0) {
		if (sub) {
			this->vertexInfo = generateInfoArray(ratio, sphere);
		}
		std::tuple<glm::vec3, float, glm::vec3, glm::vec3> posInfo[6] = {
			std::make_tuple(glm::vec3(0.f + offsetX, 0.0f+offsetY, 0.5f + offsetZ), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),
			std::make_tuple(glm::vec3(-0.f + offsetX, 0.0f + offsetY, -.5f + offsetZ), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),
			std::make_tuple(glm::vec3(0.5f + offsetX, 0.0f+offsetY, 0.0f + offsetZ), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),
			std::make_tuple(glm::vec3(-.5f + offsetX, 0.f + offsetY, 0.f + offsetZ), 90.0f, glm::vec3(.0f, 1.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),
			std::make_tuple(glm::vec3(0.0f + offsetX, -0.5f + offsetY, 0.0f+offsetZ), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),
			std::make_tuple(glm::vec3(0.0f + offsetX, 0.5f + offsetY, 0.0f + offsetZ), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(sizeX, sizeY, 1.0f)),

		};
		for (int i = 0; i < vertexInfo.vnum; i++)
		{

			TriangleSet face;
			Shader cubeShader;
			face.setEverything(1, 1, &vertexInfo, TEXPATHS, 2);
			cubeShader.create("ressources/shaders/Basic.shader");
			cubeShader.use();
			cubeShader.setInt("sampleTex", 0);
			cubeShader.setInt("sampleTex1", 1);
			//Transformation from local to world------------------------

			int temp = i / ratio;
			cubeShader.t.update(std::get<0>(posInfo[temp]), std::get<1>(posInfo[temp]), std::get<2>(posInfo[temp]), std::get<3>(posInfo[temp]));
			cubeShader.setMat4("model", cubeShader.t.model);
			cubeShader.setMat4("local", cubeShader.t.local);
			cubeShader.setMat4("view", cubeShader.t.view);
			cubeShader.setMat4("proj", cubeShader.t.projection);
			cubeShader.setMat4("clip", cubeShader.t.clip);

			faces[i] = std::make_pair(face, cubeShader);
		}
	}

	struct Triangle generateInfoArray(int ratio, bool sphere=0) {
		struct Triangle newInfo;
		int cur = 0;
		float magnitude = (float)pow(0.5 * 0.5 * 2, 0.5);
		float subd = 1.f/ ratio;
		for (int i = 0; i < ratio + 1; i++) {
			for (int j = 0; j < ratio + 1; j++) {
				(newInfo.verticesData)[cur] = (-0.5 + j*subd);
				(newInfo.verticesData)[cur+1] = (0.5 - i*subd);
				(newInfo.verticesData)[cur+2] = 0;
				(newInfo.verticesData)[cur+3] = 0;
				(newInfo.verticesData)[cur+4] = 0;
				(newInfo.verticesData)[cur+5] = 0;
				(newInfo.verticesData)[cur+6] = j*subd;
				(newInfo.verticesData)[cur+7] = 1-i*subd;
				cur += 8;
			}
		}
		unsigned int count = 0, total = 0;
		for (int i = 0; i < (int)(cur/8) - ratio -1; i++) {
			if (count == ratio) {
				count = 0;
				continue;
			}

			(newInfo.indices)[total] = i;
			(newInfo.indices)[total+1] = i+ratio+1;
			(newInfo.indices)[total+2] = i+ratio +2;
			(newInfo.indices)[total+3] = i+ratio +2;
			(newInfo.indices)[total+4] = i+1;
			(newInfo.indices)[total+5] = i;
			count += 1;
			total += 6;
		}
		newInfo.vnum = total;
		return newInfo;
	};

	void draw(float uTime, float uPredominance, int uNormalized) {

		for (auto face : faces)
		{

			glActiveTexture(GL_TEXTURE0);                                        //Activate texture unit
			glBindTexture(GL_TEXTURE_2D, face.first.tex[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, face.first.tex[1]);

			face.second.use();
			face.second.setUniform1("uTime", uTime);
			face.second.setUniform1("uPredominance", uPredominance);
			face.second.setInt("uNormalized", uNormalized);
			//Updating rotation-------------------------------------
			face.second.t.model = glm::rotate(face.second.t.model, uTime * glm::radians(10.0f), glm::vec3(.5f, 1.0f, 0.0f));
			face.second.setMat4("model", face.second.t.model);
			//------------------------------------------------------
			glBindVertexArray(face.first.VAO);
			glDrawElements(GL_TRIANGLES, face.first.vnum, GL_UNSIGNED_INT, 0);
		}

	}

};
#endif