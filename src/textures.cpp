///////////////////////////////
//// Definitions
//
// Fragment - in openGL a fragment is all the data required to render a single pixel
//
// Fragment shader - a shader to calculate the final colour of a pixel eg lights shadows colour of the light etc
// 
// Normalized device coords - -1 to 1 values relative to the window
// 
// VBO - vertex buffer objects (They can store a large number of verticies in the GPU's memory
//
// VAO - Vertex Array objects
// 
// EBO - Element buffer object
// 
///////////////////////////////

// Glad has to be before glfw as it contains certain headers that will clash otherwise
// Glad/GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp> // opengl mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// STD
#include <stdlib.h> // Clearing cmd for fps
#include <iostream>
#include <cmath> 

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Other
#include "shader.hpp" // Custom shader header
#include "stb_image/stb_image.h" // Image imports
#include "camera.hpp" // Camera class
#include "texture.hpp"
#include "model.hpp"

// Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void joystick_callback(int jid, int event);

// Window constatns
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char* windowTitle = "OpenGL learning";

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;
float cameraFov = 45.0f;


// Mouse position data (center of the screen by init
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Frame vars
double deltaTime = 0.0; // Time between current frame and last frame
double lastFrame = 0.0; // Time of last frame


int main() {
    // Initalise GLFW for the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Spec what the window should have
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Setting to version 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MACOSX
    #endif

    // PAGE 20

    // Create the window assign it to var window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, NULL, NULL);
    // ViewPort tell openGL the size of the rendering window
    // First 2 params are where the window will be created


    if (window == NULL){
        // Error
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Telling open gl that we wanth the resize callback funtion to be called on window when its resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Hide cursor and capture its input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //////////////////
    //
    // Gamepad
    //
    //////////////////
    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    std::cout << "Present" << present << std::endl;
    glfwSetJoystickCallback(joystick_callback);

    // glfwSwapInterval(0); // This will disable vsync and remove frame rate cap
    

    // Initalise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader ourShader("assets/shaders/texture/shader1.vs", "assets/shaders/texture/shader1.fs");
    Shader backpackShader("assets/shaders/backpack/vertexShader.vs", "assets/shaders/backpack/fragmentShader.fs");

    // 1,2 are width. 3,4 are height. 5,6 are near and far plane distance

    // Z buffer for displaying correct trianges
    glEnable(GL_DEPTH_TEST);

    // Removes the backfaces of faces
    // however the cubes in the current state are not correct, normals wrong way
    glEnable(GL_CULL_FACE);


    // note in model loading if the model does not have things like
    // textures it will use the ones before, this needs to be fixed (default texture saying there is no texture defined)
    
    // Model backpack("D:/git/Renderer/assets/models/Backpack/backpack.obj");
    Model cube("D:/git/Renderer/assets/models/cube.obj");

    int fpsSampCount = 0;
    float fpsSum = 0;


    // IMGUI test
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");






    // Render loop to keep rendering until the program is closed
    // If GLFW has been instructed to close then run this function
    while (!glfwWindowShouldClose(window)){

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call the input processer each loop to check if the esc key is pressed
        processInput(window);
        


        // Clearing colour buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // Print fps and coords
        const int sampleSize = 100;
        fpsSum += (1 / deltaTime);
        fpsSampCount += 1;
        if (fpsSampCount == sampleSize) {
            std::cout << ceil((int)(fpsSum / sampleSize * 10)) / 10 << " fps " <<
                "LastX|LastY: " << camera.Pitch << " | " << camera.Yaw <<
                "[x,y,z] : " << camera.GetPositionCoords() << "                   "
                << '\r';
            fpsSum = 0; fpsSampCount = 0;
        }
        

        // 2 View types of view, perspective and orthographic projections. We use perspective becuase we are human and have 2 eyes and so can measure depth
        //glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // Makes stuff look 2d
        // FOV, aspect ratio (width/height), near distance, far distance
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        backpackShader.use();
        backpackShader.setMat4("view", view);
        backpackShader.setMat4("projection", projection);
        backpackShader.setMat4("model", model);
        
        cube.Draw(backpackShader);

        // backpack.Draw(backpackShader);

        ImGui::Begin("ImGui window");
        ImGui::Text("Test text");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Will swap the colour buffers (2d buffer that contains colour values for each pixel in GLFW window)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Context destruction

    // Delete all GLFW resources that where allocated before
    glfwTerminate();
    return 0;
}


// Callback for when a devide such as a gamepad is used
void joystick_callback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        std::cout << "\nJoystick/Gamepad [" << jid << "] was connected.";
    }
    else if (event == GLFW_DISCONNECTED)
    {
        std::cout << "\nJoystick/Gamepad [" << jid << "] was disconnected.";
    }
}


// This should be abstracted
void processInput(GLFWwindow* window) {

    // For gamepad just testing
    if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1))
    {
        GLFWgamepadstate state;
        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
        {
            // Quit
            if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK])
            {
                std::cout << "\nGLFW_GAMEPAD_BUTTON_BACK was pressed. Closing..." << std::endl;
                glfwSetWindowShouldClose(window, true);
            }

            // Up and down
            if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER])
                camera.processKeyboard(Camera_Movement::DOWN, deltaTime);

            if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER])
                camera.processKeyboard(Camera_Movement::UP, deltaTime);

            
            if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER])

            camera.ProcessMouseScroll((state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]+1) * -1);
            camera.ProcessMouseScroll(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]+1);

            // Now with axis
            float x_axis_deadzone = 0.3;
            float y_axis_deadzone = 0.3;
            std::cout << "Left X: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] << 
                        " Left Y: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] << 
                        " || Right X: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] <<
                        " Left Y: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] << 
                        " || LEFT TRIGGER: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] <<
                        " RIGHT TRIGGER: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] <<
                        std::endl;;

            // Translation movement left and right
            if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > x_axis_deadzone)
                camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
            if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -x_axis_deadzone)
                camera.processKeyboard(Camera_Movement::LEFT, deltaTime);

            // Translation movement back and forwards
            if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > y_axis_deadzone)
                camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
            if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -y_axis_deadzone)
                camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);

            // SPRINT
            if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB])
            {
                if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -y_axis_deadzone)
                    camera.processKeyboard(Camera_Movement::FORWARD, deltaTime, 2.0f);

                if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > y_axis_deadzone)
                    camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime, 2.0f);
            }
            
            // Look
            if (glm::abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) > x_axis_deadzone || glm::abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) > y_axis_deadzone)
                camera.ProcessMouseMovement(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
        }
    }

    //////////// Keyboard
    // Quit button
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "\nGLFW_KEY_ESCAPE was pressed. Closing..." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);

    // Used for interacting with ImGui window
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Sprint logic
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboard(Camera_Movement::FORWARD, deltaTime, 2.0f);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime, 2.0f);
    }

    // Space and ctrl for up and down
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::DOWN, deltaTime);

}

// Process mouse inputs // xpos and ypos origignally doubles 
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    // Cast xpos to float
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    // First time tabbing in
    // This is only relevent when the program first runs and captures the mouse input from anypart of the screen
    // then recentering it will cuase a large difference and large movement
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// Callback funtion when the function is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}