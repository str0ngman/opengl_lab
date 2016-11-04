/* filename: main_scene.cpp
   desc: [todo] init glfw, glew, print log on screen(including opengl
	 version, glfw and glew output).
 */

//c++ standard library
#include<iostream>

//glew
#include<GL/glew.h>

//glfw
#include<GLFW/glfw3.h>

//glm
#include<glm/glm.hpp>

//soil
#include<SOIL/SOIL.h>

//assimp
#include<assimp/scene.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>

//utility class inclusion
#include "lab_shader.h"
#include "../util/test.h"
#include "../util/utils.h"
//vertices:triangles, cubes, and other stuff
#include "vertices.h"


//void key_callback(GLFWwindow*, int, int, int, int);
const GLuint WIDTH = 800, HEIGHT = 600;
extern GLfloat test_line2[30];
extern GLfloat axis[60];
extern GLfloat test_cube[12];
extern GLfloat test_cube_indices[6];
extern GLfloat cube_face[32];
int main(int argc, char* argv[]){
 // set_array();
 // int i = 0;
 // while( i<20)
 // {
//	  std::cout<<test_line2[i]<<std::endl;
//	  i++;
//  }


  std::cout<<"starting GLFW context, openGL3.3"<<std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "init oepngl window", NULL, NULL);

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  
  glewExperimental = GL_TRUE;

  glewInit();

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0,0,width,height);


  std::cout<<"preparation finished."<<std::endl;


  /*----------------------------------
   * axis vao vbo
   * --------------------------------*/
  GLuint VAO,VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);//connect vbo to vao slot.
  glBufferData(GL_ARRAY_BUFFER, sizeof(axis),axis, GL_STATIC_DRAW);//fill vao data

  glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);//let vao konw how to interpret
  glEnableVertexAttribArray(0);//use vao slot 0.

  glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);
  /*----------------------------------
   * basic shape vao vbo
   * --------------------------------*/
  GLuint cube_vao, cube_vbo, cube_ebo;
  glGenVertexArrays(1, &cube_vao);
  glGenBuffers(1, &cube_vbo);
  glGenBuffers(1, &cube_ebo);

  glBindVertexArray(cube_vao);
  glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(test_cube),test_cube, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(test_cube_indices), test_cube_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);

 /*----------------------------------
  * transformed cube with color and texture
  * --------------------------------*/
  GLuint cubeface_vao, cubeface_vbo, cubeface_ebo;
  glGenVertexArrays(1,&cubeface_vao);
  glGenBuffers(1, &cubeface_vbo);
  glGenBuffers(1, &cubeface_ebo);

  glBindVertexArray(cubeface_vao);
  glBindBuffer(GL_ARRAY_BUFFER,cubeface_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_face),cube_face, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeface_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(test_cube_indices),test_cube_indices,GL_STATIC_DRAW);

  //position attribute
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
  glEnableVertexAttribArray(0);

  //color attribute
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)3);
  glEnableVertexAttribArray(1);

  //TexCoord attribute
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)6);
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  //texture creation
  GLuint cubeface_texture1;
  glGenTextures(1,&cubeface_texture1);
  glBindTexture(GL_TEXTURE_2D,cubeface_texture1);

  //set texture paramter
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //load create texture and generate mipmaps
  int cftex_width, cftex_height;
  unsigned char* image = SOIL_load_image("../res/jpg/wall.jpg",&cftex_width, &cftex_height,0,SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,cftex_width,cftex_height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);



/*---------------------------------
  test code should be set after
  the render context  initialization stage
  ---------------------------------*/

  //labShaders
  /*---------------------------------*/
   lab_shader triangleShader("../shader/init_vert.glsl","../shader/init_frag.glsl");

   lab_shader cube_shader("../shader/basic_cube_vert.glsl","../shader/basic_cube_frag.glsl");

   lab_shader transformWtex_shader("../shader/transformWtexture_vert.glsl","../shader/transformWtexture_frag.glsl");

  /*----------------------------------
   * render loop starts here
   * --------------------------------*/
  std::cout<<"Entering while loop"<<std::endl;
  //glLineWidth(4.0);
  while(!glfwWindowShouldClose(window)){

    glfwPollEvents();

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//draw axis
    triangleShader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES,0,6);
    glBindVertexArray(0);

    glDisableClientState(GL_VERTEX_ARRAY);

//draw basic cube
    //cube_shader.Use();
    //glBindVertexArray(cube_vao);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);

//draw transformed textured cube
    transformWtex_shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,cubeface_texture1);
    glUniform1i(glGetUniformLocation(transformWtex_shader.Program,"ourTexture1"),0);

    glBindVertexArray(cubeface_vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glDeleteVertexArrays(1, &cube_vao);
  glDeleteBuffers(1, &cube_vbo);

  glfwTerminate();


  return 0;
}

//void key_callback(GLFWwindow* window, int key, int scancode, int action,
//		  int mode){
//  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
//    glfwSetWindowShouldClose(window, GL_TRUE);
//  }
//}
//















