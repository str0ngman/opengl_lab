//lab_shader.h

#ifndef LAB_SHADER_H
#define LAB_SHADER_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include <GL/glew.h>

class lab_shader {
public:
	GLuint Program;
	lab_shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

		//1. Retrieve the vertex/fragment src code form filePath
		std::string vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;

		//ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try {
			//Open files
			vShaderFile.open(vertexPath);

			if (!vShaderFile) {
				std::cerr << "Error opening vertex.vs" << std::endl;
				return;
			}
			else{
				std::cout << "vertex vs opened properly\n\n\n\n";
			}

			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;

			//Readf file's buffer contents into streams
			vShaderStream<<vShaderFile.rdbuf();
			fShaderStream<<fShaderFile.rdbuf();

			//clse file handlers
			vShaderFile.close();
			fShaderFile.close();

			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}

		catch (std::ifstream::failure &e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY READ"
					<< std::endl;
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		//output using for debug
		std::cout<<"vertex code---------------------\n";
        std::cout<<vShaderCode<<std::endl;

        std::cout<<"fragment code-------------------\n";
        std::cout<<fShaderCode<<std::endl;

        //2.Compile Shaders
        GLuint vertex;
        GLuint fragment;
        GLint success;
        GLchar infoLog[512];


        //vetex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        //print Compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
        	glGetShaderInfoLog(vertex,512,NULL, infoLog);
        	std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
        			<<infoLog<<std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode,NULL);

        glCompileShader(fragment);

        //print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS,&success);
        if(!success)
        {
        	glGetShaderInfoLog(fragment,512, NULL, infoLog);
        	std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
        			<<infoLog<<std::endl;
        }

        //shader program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);

        //print linking errors if any
        glGetProgramiv(this->Program, GL_LINK_STATUS,&success);
        if(!success){
        	glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        	std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
        			<<infoLog<<std::endl;
        }

        //delete the shaders as they're linked into our program
        //and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);

	}

	/*--------end of lab_shader constructor-----*/
	/*------------------------------------------*/


	void Use(){
		glUseProgram(this->Program);

	}
};

#endif //LAB_SHADER_H ends
