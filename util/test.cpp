/*
 * test.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: str
 */

#include "test.h"

#include "../src/lab_shader.h"

void labShader_test(void){
std::cout<<"[test]:labShader_test:start:"<<std::endl;
lab_shader test_shader("../shader/init_vert.glsl","../shader/init_frag.glsl");
test_shader.Use();

std::cout<<"[test]:labShader_test:end."<<std::endl;
}


