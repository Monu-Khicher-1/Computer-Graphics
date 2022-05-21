# Computer-Graphics
Learning Graphics
## Set up
For Linux Ubuntu:
* For installing GLFW library 
    ```
    sudo apt-get install libglfw3
    sudo apt-get install libglfw3-dev
    ```
* For installing GLAD:
    ```
    git clone https://github.com/Dav1dde/glad.git
    cd glad
    cmake ./
    make
    sudo cp -a include /usr/local/
    ```
* Now from glad/src copy glad.c file and paste it to src folder of your project.
* Now you can compile your main.cpp with `g++ -o test main.cpp glad.c -ldl -lglfw`
