/**
 * filename: mainscene.cpp
 * git:		 Lighting: start
 */

//c++ standard library
#include<iostream>

//glew
#include<GL/glew.h>

//glfw
#include<GLFW/glfw3.h>

//glm
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//soil
#include<SOIL/SOIL.h>

//assimp
#include<assimp/scene.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>

//utility class inclusion
#include "lab_shader.h"
#include "../util/test.h"
#include "lab_Camera.h"
#include "vertices.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

//Render Objects
extern GLfloat floor_square[];
extern GLfloat floor_indices[];
extern GLfloat axis[36];

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
lab_Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool    keys[1024];

// Light attributes


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	 std::cout<<"starting GLFW context, openGL3.3"<<std::endl;
	  glfwInit();
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	  glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "init oepngl window", NULL, NULL);

	  glfwMakeContextCurrent(window);

	  glfwSetKeyCallback(window, key_callback);
	  glfwSetCursorPosCallback(window, mouse_callback);
	  glfwSetScrollCallback(window, scroll_callback);

	  //glfw Options
	  //glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	  glewExperimental = GL_TRUE;

	  glewInit();

	  int width, height;
	  glfwGetFramebufferSize(window, &width, &height);
	  glViewport(0,0,width,height);

	  //OpenGL options
	  //glEnable(GL_DEPTH_TEST);

      //PART I: RENDER AXIS
      GLuint axis_vao,axis_vbo;
      glGenVertexArrays(1,&axis_vao);
      glGenBuffers(1,&axis_vbo);

      glBindVertexArray(axis_vao);

      glBindBuffer(GL_ARRAY_BUFFER,axis_vbo);
      glBufferData(GL_ARRAY_BUFFER,sizeof(axis),axis,GL_STATIC_DRAW);

      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)0);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
      glEnableVertexAttribArray(1);

      glBindBuffer(GL_ARRAY_BUFFER,0);
      glBindVertexArray(0);

      lab_shader axisShader("../shader/03Material/axis_shader.vs","../shader/03Material/axis_shader.frag");
      // Game loop
      while (!glfwWindowShouldClose(window))
      {
    	  glfwPollEvents();
    	  glClearColor( GLfloat(212.0f/256.0f),GLfloat(212.0f/256.0f),GLfloat(212.0f/256.0f),1.0f);
    	  glClear(GL_COLOR_BUFFER_BIT );

    	  axisShader.Use();
    	  glBindVertexArray(axis_vao);
    	  glDrawArrays(GL_LINES,0,6);
    	  glBindVertexArray(0);
    	  // glDisableClientState(GL_VERTEX_ARRAY);
    	  // Swap the screen buffers
    	  glfwSwapBuffers(window);
      }

      // Terminate GLFW, clearing any resources allocated by GLFW.
      glfwTerminate();
      return 0;
	}

/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement(){
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
