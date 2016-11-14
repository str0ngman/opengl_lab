/*
 * vertices.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: str
 */

#include"vertices.h"
#include"glm/glm.hpp"

GLfloat basic_triangle[] = {
// Positions          // Colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Top
		};

//primitive preparation
GLfloat vertices[] =
		{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, };

GLfloat axis[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //1
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //2

		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   //3
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   //4

		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //5
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   //6
		};

GLfloat test_line2[20];

GLfloat test_cube[] = { 0.5f, 0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f, 0.5f, 0.0f   // Top Left
		};

GLfloat cube_face[] = {
// Positions          // Colors           // Texture Coords
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
		0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left
		};

GLuint test_cube_indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
				1, 2, 3   // Second Triangle
		};

GLfloat coord_cube[] = {
		//positions //texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -0.5f,
		-0.5f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f };

GLuint coord_cube_indices[] = { 0, 1, 3, 1, 2, 3 };

GLfloat coord_multiple_cubes[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f,	0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,-0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f,  0.5f, 1.0f, 0.0f,

		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,-0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

GLfloat camera_cube_36faces[] =  {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f,	0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,-0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f,  0.5f, 1.0f, 0.0f,

		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,-0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};


glm::vec3 coord_cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f,	5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f,	-12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f) };

glm::vec3 cam_cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f,	5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f,	-12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f) };


void set_array() {

	for (int i = 0; i < 20;) {
		test_line2[i] = -0.9f + (i / 4) * 0.2;
		test_line2[i + 1] = -0.9;
		test_line2[i + 2] = -0.9f + (i / 4) * 0.2;
		test_line2[i + 3] = 0.9;
		i = i + 4;

	}

}
