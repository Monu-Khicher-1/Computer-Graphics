#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



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
    unsigned int VAO;
    unsigned int jointShader;

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

    // Making Triangle
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

    // Building and Compiling our Shaders
    // ----------------------------------

    // =========Vertex Shader==========
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<endl;
        return;
    }

    //===========Fragment Shader ==========

    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(! success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<endl;
        return;
    }

    // =============== Linking All Shaders ==============

    jointShader=glCreateProgram();
    glAttachShader(jointShader,vertexShader);
    glAttachShader(jointShader,fragmentShader);
    glLinkProgram(jointShader);
    glGetProgramiv(jointShader,GL_LINK_STATUS,&success);
    if (! success)
    {
        glGetProgramInfoLog(jointShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<endl;
        return;
    }

    // ================== Deleting Shaders ==============

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO;
    // Generating
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    // Binding
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //filling data to buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Graph::render()
{
    glClearColor(0.2f,0.4f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(jointShader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);
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