#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Graph2.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Graph* graph=new Graph();
    graph->init("Graphics",800,400);
    while(graph->isRunning)
    {
        graph->handleEvent();
        graph->update();
        graph->render();
    }
    graph->clean();
    return 0;
}
