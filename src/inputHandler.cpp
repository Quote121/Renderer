
// #include "inputHandler.hpp"

// #include <iostream>

// bool InputHandler::joyStickPresent(int &jid)
// {
//     for (unsigned int i = 0; i < GLFW_JOYSTICK_LAST; i++)
//     {
//         // Returns non-0 if detected joystick
//         if (glfwJoystickPresent(GLFW_JOYSTICK_1 + i))
//         {
//             jid = i+1;
//             return true;
//         }
//     }
// }

// void InputHandler::process(GLFWwindow *window, double deltaTime, Camera camera)
// {
//         // For gamepad just testing
//     if (glfwJoystickIsGamepad(gamepadID))
//     {
//         GLFWgamepadstate state;
//         if (glfwGetGamepadState(gamepadID, &state))
//         {
//             // Quit
//             if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK])
//             {
//                 std::cout << "\nGLFW_GAMEPAD_BUTTON_BACK was pressed. Closing..." << std::endl;
//                 glfwSetWindowShouldClose(window, true);
//             }

//             // Up and down
//             if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER])
//                 camera.processKeyboard(Camera_Movement::DOWN, deltaTime);

//             if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER])
//                 camera.processKeyboard(Camera_Movement::UP, deltaTime);

            
//             if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER])

//             camera.ProcessMouseScroll((state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]+1) * -1);
//             camera.ProcessMouseScroll(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]+1);

//             // Now with axis
//             float x_axis_deadzone = 0.3;
//             float y_axis_deadzone = 0.3;
//             std::cout << "Left X: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] << 
//                         " Left Y: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] << 
//                         " || Right X: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] <<
//                         " Left Y: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] << 
//                         " || LEFT TRIGGER: " << state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] <<
//                         " RIGHT TRIGGER: " << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] <<
//                         std::endl;;

//             // Translation movement left and right
//             if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > x_axis_deadzone)
//                 camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
//             if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -x_axis_deadzone)
//                 camera.processKeyboard(Camera_Movement::LEFT, deltaTime);

//             // Translation movement back and forwards
//             if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > y_axis_deadzone)
//                 camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
//             if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -y_axis_deadzone)
//                 camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);

//             // SPRINT
//             if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB])
//             {
//                 if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -y_axis_deadzone)
//                     camera.processKeyboard(Camera_Movement::FORWARD, deltaTime, 2.0f);

//                 if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > y_axis_deadzone)
//                     camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime, 2.0f);
//             }
            
//             // Look
//             if (glm::abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) > x_axis_deadzone || glm::abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) > y_axis_deadzone)
//                 camera.ProcessMouseMovement(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
//         }
//     }

//     //////////// Keyboard
//     // Quit button
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//         std::cout << "\nGLFW_KEY_ESCAPE was pressed. Closing..." << std::endl;
//         glfwSetWindowShouldClose(window, true);
//     }

//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);

//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);

//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);

//     // Sprint logic
//     if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
//         if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//             camera.processKeyboard(Camera_Movement::FORWARD, deltaTime, 2.0f);

//         if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//             camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime, 2.0f);
//     }

//     // Space and ctrl for up and down
//     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::UP, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//         camera.processKeyboard(Camera_Movement::DOWN, deltaTime);

// }
