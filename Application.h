//GLEW provides the function pointers we need to access the latest features in openGL.
#include <GL/glew.h>    //Must be included before gl.h and glfw.h.

//GLFW provides window creation and input control.
#include <glfw3.h>

//GLM provides openGL mathematics.
#define GLM_FORCE_RADIANS	//Defining this before glm to ignore warnings we don't care about...
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

//Standard Headers…
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <string>
#include <functional>

#pragma once

//Namespaces…
using namespace glm; //For openGL mathematics
using namespace std; //If we want to print stuff

//Defines…
#define APP_NAME "<<Getting Started!>>"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0
#define OPEN_GL_VERSION 3  //Specifies OpenGL 3.3
#define ANTIALIASING 4  //nx antialiasing
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FIELD_OF_VIEW 45.0f
#define Z_NEAR 0.1f
#define Z_FAR 100.0f
#define GLFW_FAIL 0 
#define CAMERA_BOUNDS_TOP 13.5999918f
#define CAMERA_BOUNDS_BOTTOM -13.5999918f
#define CAMERA_BOUNDS_LEFT -10.7999945f
#define CAMERA_BOUNDS_RIGHT 8.79999638f

//External Globals…
extern GLFWwindow* window;

struct Camera{
	GLuint MVPMatrixID;
	mat4 projectionMatrix, viewMatrix, MVPMatrix;
	vec3 position, forward;
};