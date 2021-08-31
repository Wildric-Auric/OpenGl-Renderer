//
//
////#include<GL/glut.h> has problem
//
//
//#include<fstream>
//#include<string>  //Has getline Method
//#include<sstream>  
//
//#include<math.h>
////
////#include "Header.h"
////struct ShaderProgramSrc
////{
////    std::string VertexSource;
////    std::string FragmentSource;
////};
//////Parse shader file
////static ShaderProgramSrc ParseShader(const std::string& path)
////{
////    enum class ShaderType {
////        NONE = -1, VERTEX =0, FRAGMENT =1
////    };
////    std::ifstream stream(path);
////    std::string line;
////    std::stringstream ss[2];
////    ShaderType shaderType = ShaderType::NONE;
////    while (getline(stream, line))
////    {
////        if (line.find("#shader") != std::string::npos)
////        {
////            if (line.find("vertex") != std::string::npos)
////            {
////                shaderType = ShaderType::VERTEX;
////            }
////            else if (line.find("fragment") != std::string::npos)
////            {
////                shaderType = ShaderType::FRAGMENT;
////            }
////        }
////        else if (shaderType!= ShaderType::NONE) {
////            ss[(int)shaderType] << line << "\n";
////        }
////        else { std::cout << "invalid index for string stream: "<< (int)shaderType << std::endl; }
////    }
////     return { ss[0].str(), ss[1].str() };
////}
////
////
//////Compile shader
////static unsigned int CompileShader(unsigned int type, const std::string& source, const std::string& name)
////{
////    unsigned int id = glCreateShader(type);
////    const char* src = source.c_str(); //Same as &source[0]
////    glShaderSource(id, 1, &src, nullptr);
////    glCompileShader(id);
////    int result;
////    ///HANDLING ERROR
////    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
////    if (result == GL_FALSE)
////    {
////        int length;
////        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
////        char* message = (char*)_malloca(length * sizeof(char));
////   
////        glGetShaderInfoLog(id, length, &length, message);
////        std::cout << "Failed to Compile Shader: "<< (type == GL_VERTEX_SHADER? "vertex": "fragment") << std::endl;
////        std::cout << message << std::endl;
////        glDeleteShader;
////        return 0;
////    }
////    //RETURNING SHADER
////    std::cout << name << " " <<"Shader compiled successfuly" << std::endl;
////    return id;
////}
////
////
////
//////Create shader
////static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
////{
////    unsigned int program = glCreateProgram();
////    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader, "Vertex");//COMPILING VERTEX SHADER
////    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader, "Fragment");//COMPILING FRAGMENT SHADER
////    glAttachShader(program, vs);
////    glAttachShader(program, fs);
////    glLinkProgram(program);
////    glValidateProgram(program);
////    glDeleteShader(vs);
////    glDeleteShader(fs);
////    return program;
////}
////
////int main(void)
////{
////    GLFWwindow* window;
////
////    /* Initialize the library */
////    if (!glfwInit())
////        return -1;
////
////    int size[] = { 720,720 };//Window size
////    /* Create a windowed mode window and its OpenGL context */
////    window = glfwCreateWindow(size[0], size[1], "Hello World", NULL, NULL);
////    if (!window)
////    {
////        glfwTerminate();
////        return -1;
////    }
////}
//
////    /* Make the window's context current */
////    glfwMakeContextCurrent(window);
////
////    if (glewInit() != GLEW_OK)
////    {
////        std::cout << "Can't initialize glew" << std::endl;
////    }
////
////    //Buffer
////    float positions[8] = {
////        -0.5f, -0.5f,
////        0.5F ,  -0.5f,
////        0.5f, 0.5f,
////        -0.5f, 0.5f,
////
////
////    };
////    for (int i = 0; i < sizeof(positions) / sizeof(float); i++)
////    {
////        positions[i] = positions[i]*1.f; //Optimization 100%
////    }
////    unsigned int indices[] = {
////        0,1,2,
////        2,3,0
////    };
////    unsigned int buffer;
////    glGenBuffers(1,&buffer);
////    glBindBuffer(GL_ARRAY_BUFFER, buffer);
////    glBufferData(GL_ARRAY_BUFFER, (sizeof(positions) / sizeof(*positions)) * sizeof(float), positions, GL_STATIC_DRAW);
////    //Stride: size of each composant
////    //To enable the generate verex attribute we have one so it's index is 0
////    glEnableVertexAttribArray(0);
////    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);
////    //indicesBuffer
////    unsigned int ib; //stands for indices buffer
////    glGenBuffers(1, &ib);
////    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
////    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(indices) / sizeof(*indices)) * sizeof(unsigned int), indices, GL_STATIC_DRAW);
////
////
////
////    ShaderProgramSrc source = ParseShader("res/shaders/Basic.shader");
////    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
////    glUseProgram(shader);
////
////
////    float time = 0;
////    float freq = 500;
////
////    //Getting location of uniform
////    int location = glGetUniformLocation(shader, "u_Color");
////    int location1 = glGetUniformLocation(shader, "u_Res");
////    int location2 = glGetUniformLocation(shader, "u_Time");
////    glUniform4f(location, 127. / 255., 23. / 255., 31. / 255., 1.0);
////    glUniform2f(location1, size[0],size[1]);
////    glUniform1f(location2, time);
////
////
////
////
////
////    /* Loop until the user closes the window */
////
////    while (!glfwWindowShouldClose(window))
////    {
////        /* Render here */
////        time += 1;
////
////        //Updating uniforms
////        glUniform4f(location, abs(cos(time/freq)), 23. / 255., 31. / 255., 1.0);
////        glUniform1f(location2, time/freq);
////        glClear(GL_COLOR_BUFFER_BIT);
////        glClearColor(0.,0.,0,0);
////        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
////        /* Swap front and back buffers */
////        glfwSwapBuffers(window);
////        
////        /* Poll for and events */
////        glfwPollEvents();
////    }
////    glDeleteProgram(shader);
////    glfwTerminate();
////    return 0;
////}
//
//
//
//
//
//#include <GL/glew.h>
//#include <glfw3.h>
//#include <iostream>
//#include "Header.h"
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const char* vertexShaderSource = parseShader("res/shaders/Basic.shader").first;
//const char* fragmentShaderSource = parseShader("res/shaders/Basic.shader").second;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (glewInit()!=GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//
//    // build and compile our shader program
//    // ------------------------------------
//    // vertex shader
//    unsigned int vertexShader = createShader(&vertexShaderSource, VERTEX);
//        // fragment shader
//        unsigned int fragmentShader = createShader(&fragmentShaderSource, FRAGMENT);
//    // link shaders
//    unsigned int shaderProgram = createShaderProgram(&vertexShader, &fragmentShader);
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        -0.5f, -0.5f, 0.0f, // left  
//         0.5f, -0.5f, 0.0f, // right 
//         0.0f,  0.5f, 0.0f  // top   
//    };
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    glBindVertexArray(0);
//
//
//    // uncomment this call to draw in wireframe polygons.
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // draw our first triangle
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        // glBindVertexArray(0); // no need to unbind it every time 
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}