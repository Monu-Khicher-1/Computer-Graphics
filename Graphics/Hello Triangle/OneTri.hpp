#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;

class OneTri
{
public:
    OneTri();
    void init(float a[]);
    void render();
    
    unsigned int jointShader;
    unsigned int VAO;
    unsigned int VBO;
};

OneTri::OneTri()
{
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
}

void OneTri::init(float a[])
{
    // Generating
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    // Binding
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //filling data to buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(a),a,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void OneTri::render()
{
    glUseProgram(jointShader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);
    cout<<"reder triangle"<<endl;
}
