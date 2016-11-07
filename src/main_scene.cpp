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
extern GLfloat coord_cube[20];
extern GLfloat coord_cube_indices[6];
extern glm::vec3 coord_cubePositions[10];
extern GLfloat coord_multiple_cubes[180];
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
  std::cout<<glGetError()<<std::endl;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0,0,width,height);

  std::cout<<glGetError()<<std::endl;
  std::cout<<"preparation finished."<<std::endl;




  /*texture experiment*/

  GLfloat v[] = {
          // Positions          // Colors           // Texture Coords
           1.0f,  1.0f, -0.1f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
           1.0f,  0.0f, -0.1f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
           0.0f,  1.0f, -0.1f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
           0.5f,  0.0f, -0.1f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
      };

  GLuint i[] = {3,0,1,2,0,3};

  lab_shader texture_shader("../shader/texture_vert.glsl","../shader/texture_frag.glsl");

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
  GLuint v_vbo, v_vao, v_ebo;
  glGenVertexArrays(1,&v_vao);
  glGenBuffers(1,&v_vbo);
  glGenBuffers(1,&v_ebo);
  glBindVertexArray(v_vao);
  glBindBuffer(GL_ARRAY_BUFFER,v_vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(v),v,GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,v_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(i),i,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  GLuint texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  int w, h;
  unsigned char* image = SOIL_load_image("../res/jpg/wall.jpg",&w, &h,0,SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D,0);


  /*----------------------------------
   * 2.8 Coordinate system textured cube
   * --------------------------------*/
  GLuint vbo_coord, vao_coord, ebo_coord;
  glGenVertexArrays(1, &vao_coord);
  glGenBuffers(1, &vbo_coord);
  glGenBuffers(1, &ebo_coord);

  glBindVertexArray(vao_coord);
  glBindBuffer(GL_ARRAY_BUFFER,vbo_coord);
  glBufferData(GL_ARRAY_BUFFER, sizeof(coord_cube), coord_cube, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_coord);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coord_cube_indices), coord_cube_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5*sizeof(GLfloat),(GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  //Texture
  GLuint texture_coord;
  glGenTextures(1,&texture_coord);
  glBindTexture(GL_TEXTURE_2D, texture_coord);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  int coord_width, coord_height;
  unsigned char* coord_cube_image = SOIL_load_image("../res/jpg/wall.jpg",
		  &coord_width,&coord_height,0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
		  coord_width, coord_height,0,GL_RGB,GL_UNSIGNED_BYTE,coord_cube_image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(coord_cube_image);
  glBindTexture(GL_TEXTURE_2D, 0);



  /*---------------------------------
  test code should be set after
  the render context  initialization stage
  ---------------------------------*/

  //labShaders
  /*---------------------------------*/
   lab_shader triangleShader("../shader/init_vert.glsl","../shader/init_frag.glsl");

   lab_shader cube_shader("../shader/basic_cube_vert.glsl","../shader/basic_cube_frag.glsl");

   lab_shader CoordSystem_shader("../shader/coordinateSystem_vert.glsl","../shader/coordinateSystem_frag.glsl");

  /*----------------------------------
   *while loop
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
   cube_shader.Use();
   glBindVertexArray(cube_vao);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

//draw transformed textured cube
    glBindTexture(GL_TEXTURE_2D,texture);
    texture_shader.Use();
    glm::mat4 trans;
    trans=glm::translate(trans,glm::vec3(0.1f,-0.1f,0.0f));
    trans=glm::rotate(trans,(GLfloat)glfwGetTime()*50.0f,glm::vec3(0.5f,0.5f,0.0f));

    GLuint transformLoc = glGetUniformLocation(texture_shader.Program,"transform");
    glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));
    glBindVertexArray(v_vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

//draw 2.8 coordinate system coord_cube
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_coord);
    glUniform1i(glGetUniformLocation(CoordSystem_shader.Program,"ourTexture1"),0);

    CoordSystem_shader.Use();

    glm::mat4 cordSys_model;
    glm::mat4 cordSys_view;
    glm::mat4 cordSys_projection;

    cordSys_model = glm::rotate(cordSys_model,-55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    cordSys_view = glm::translate(cordSys_view,glm::vec3(0.0f, 0.0f, -3.0f));
    cordSys_projection = glm::perspective(45.0f, (GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f, 100.0f);

    GLint modelLoc = glGetUniformLocation(CoordSystem_shader.Program,"model");
    GLint viewLoc = glGetUniformLocation(CoordSystem_shader.Program,"view");
    GLint projLoc = glGetUniformLocation(CoordSystem_shader.Program,"projection");


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cordSys_model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cordSys_view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cordSys_projection));


    glBindVertexArray(vao_coord);

  //2.8 final: render 10 3d cubes in the scene using for loop
  /*  for (GLuint i = 0; i < 10; i++)
          {
              // Calculate the model matrix for each object and pass it to shader before drawing
              glm::mat4 model;
              model = glm::translate(model, coord_cubePositions[i]);
              GLfloat angle = 20.0f * i;
              model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
              glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

              glDrawArrays(GL_TRIANGLES, 0, 36);
          }*/
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
//draw 2.8 end
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glDeleteVertexArrays(1, &cube_vao);
  glDeleteBuffers(1, &cube_vbo);

  glDeleteVertexArrays(1,&v_vao);
  glDeleteBuffers(1,&v_vbo);
  glDeleteBuffers(1,&v_ebo);

  glfwTerminate();


  return 0;
}

















