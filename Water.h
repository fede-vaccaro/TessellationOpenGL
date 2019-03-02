#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <model.h>
#include "shader.h"
#include "buffers.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "drawableObject.h"

class Water : public drawableObject
{
public:
	Water(glm::vec2 position, float scale, float height);
	virtual ~Water();
	virtual void draw();
	void bindRefractionFBO();
	void bindReflectionFBO();
	void unbindFBO();

	void setPosition(glm::vec2 position, float scale, float height) {
		glm::mat4 identity;
		glm::mat4 scaleMatrix = glm::scale(identity, glm::vec3(scale, scale, scale));
		glm::mat4 transMatrix = glm::translate(identity, glm::vec3(position.x, height, position.y));
		this->modelMatrix = transMatrix * scaleMatrix;
	}

	void setHeight(float height) {
		float scale = modelMatrix[0][0];
		float position_x = modelMatrix[3][1];
		float position_z = modelMatrix[3][2];
		std::cout << position_x << " " << position_z << std::endl;

		glm::mat4 identity;
		glm::mat4 scaleMatrix = glm::scale(identity, glm::vec3(scale, scale, scale));
		glm::mat4 transMatrix = glm::translate(identity, glm::vec3(position_x, height, position_z));
		this->modelMatrix = transMatrix * scaleMatrix;
	}

	glm::mat4 getModelMatrix() {
		return modelMatrix;
	}

	static const int FBOw = 1280;
	static const int FBOh = 720;

	FrameBufferObject const& getReflectionFBO() {
		return *reflectionFBO;
	}

private:
	float scale, height;
	FrameBufferObject * reflectionFBO;
	FrameBufferObject * refractionFBO;

	unsigned int dudvMap, normalMap;
	glm::mat4 modelMatrix;
	Shader * shad;
	Model * waterPlane;
};

