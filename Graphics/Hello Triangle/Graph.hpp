#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OneTri.hpp"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Graph
{
public:
    Graph();
    void init(string title,int width,int height);
    void render();
    void handleEvent();
    void update();
    void clean();

    GLFWwindow* window;
    bool isRunning=false;
    OneTri* triangle1;

};

Graph::Graph(/* args */)
{
}
void Graph::init(string title,int width,int height)
{
    glfwInit();  // GLFW is Initialized
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    window=glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
    if (window==NULL)
    {
        std::cout<<"Failed to Initiallize GLFW window"<<endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }  
    isRunning=!glfwWindowShouldClose(window);  

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
    triangle1=new OneTri();
    triangle1->init(vertices);
}

void Graph::render()
{
    glClearColor(0.2f,0.4f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    triangle1->render();
}

void Graph::handleEvent()
{
    glfwSwapBuffers(window);
    glfwPollEvents();

    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS) glfwSetWindowShouldClose(window,true);
}

void Graph::update()
{
    isRunning= !glfwWindowShouldClose(window);
}

void Graph::clean()
{
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}