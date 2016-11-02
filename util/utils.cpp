/*
 * utils.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: str
 */
#include<GL/glew.h>
#include<GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action,
		  int mode){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}





