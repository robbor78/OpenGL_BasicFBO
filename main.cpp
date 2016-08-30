#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "shader_utils.h"

void Initialize();
void InitGL();
void InitProgram();
void InitBuffer();
void Loop();
void Shutdown();
void OnWindowResize(GLFWwindow* window, int width, int height);

GLFWwindow* window;
int screenWidth = 640;
int screenHeight = 480;
GLuint vs, fs;
GLuint program;
GLuint attribute_vp;
GLuint vao;
GLuint vbo;

int main() {
  Initialize();

  Loop();

  Shutdown();

  return 0;
}

void Initialize() {
  InitGL();
  InitProgram();
  InitBuffer();
}

void InitGL() {
  glfwInit();
  window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);

  glfwMakeContextCurrent(window);
  glewInit();

  //glEnable(GL_DEPTH_TEST); // enable depth-testing
  //glDepthFunc(GL_LESS);

  //glEnable(GL_CULL_FACE); // cull face
  //glCullFace(GL_BACK); // cull back face
  //glFrontFace(GL_CCW); // GL_CCW for counter clock-wise //GL_CW

  // *** POINT SIZE ***
  //glEnable(GL_PROGRAM_POINT_SIZE); //use gl_PointSize in shader
  glDisable(GL_PROGRAM_POINT_SIZE);glPointSize(40.0f); //use glPointSize from the code 

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glPolygonMode(GL_FRONT, GL_LINE); //for wireframe
  //glPolygonMode(GL_BACK, GL_LINE); //for wireframe

  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void InitProgram() {
  program = create_program("basicshader.vs.glsl", "basicshader.fs.glsl", vs, fs);

  attribute_vp = get_attrib(program, "vp");
}

void InitBuffer() {
  float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
  };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

}

void Loop() {

  glUseProgram(program);

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);
 glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }

  }
}

void Shutdown() {

  glUseProgram(0);

  glDetachShader(program, vs);
  glDetachShader(program, fs);

  glDeleteShader(fs);
  glDeleteShader(vs);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteProgram(program);

  glfwTerminate();
}

  // a call-back function
  void OnWindowResize(GLFWwindow* window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, screenWidth, screenHeight);
  }