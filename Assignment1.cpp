// include C++ headers
#include <cstdio>
#include <iostream>


// include OpenGL related headers
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>





float truckPosition = 0.0f; // Initial truck position
float dumpAngle = 0.0f; // Initial dump box angle
TwBar* tweakBar;
unsigned int gWindowWidth = 1200;
unsigned int gWindowHeight = 800;
bool gWireframe = false; // Wireframe mode on or off
glm::vec3 gBackgroundColor(0.2f); // Background color
glm::vec3 gMoveVec(0.0f); // Object translation
// frame stats
float gFrameRate = 60.0f;
float gFrameTime = 1 / gFrameRate;
// Wheel Rotation
float wheelRotation = 0.0f;

//Draws Circle and Add line segments
void drawCircle(float centerX, float centerY, float radius, int numSegments, float rotationAngle, int numLines) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        float theta = rotationAngle + 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);  // x-coordinate
        float y = radius * sinf(theta);  // y-coordinate
        glVertex2f(centerX + x, centerY + y);

        if (i % (numSegments / numLines) == 0) {
            float lineX = centerX + (radius - 0.01f) * cosf(theta);  // x-coordinate
            float lineY = centerY + (radius - 0.01f) * sinf(theta);  // y-coordinate
            glVertex2f(lineX, lineY);
        }
    }
    glEnd();
}
// Draws Rectangle define and render
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}


void dumpTruck() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(truckPosition, 0.0f, 0.0f);

    //Front of the truck
    glColor3f(0.0f, 0.0f, 1.0f); // Blue Colour
    drawRectangle(-0.4f, -0.1f, 0.3f, 0.4f);
    glColor3f(0.0f, 0.0f, 1.0f);// Blue Colour
    drawRectangle(-0.6f, -0.3f, 0.2f, 0.3f);

    // Front Tyre
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//Black colour
    glTranslatef(-0.5f, -0.31f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, -1.0f);// Rotate the wheel
    drawCircle(0.0f, 0.0f, 0.090f, 100, 0.0f, 5);
    glPopMatrix();

    //Hub Cap
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);// Dark Grey Colour
    glTranslatef(-0.5f, -0.31f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.045f, 100, 0.0f, 1);
    glPopMatrix();

    // Draw the window
    glColor3f(0.5f, 0.5f, 0.6f); // Grey Colour
    drawRectangle(-0.4f, -0.004f, 0.1f, 0.2f);

    //The Door
    glColor3f(0.9f, 0.9f, 1.0f); // White Colour
    drawRectangle(-0.26f, -0.1f, 0.12f, 0.3f);
    glColor3f(0.75f, 0.75f, 0.75f); // Silver Colour
    drawRectangle(-0.18f, 0.0f, 0.03f, 0.02f);

    //Exhaust
    glColor3f(0.0f, 0.0f, 0.0f);// Black Colour
    drawRectangle(-0.12f, 0.3f, 0.020f, 0.2f);

    //Chassis
    glColor3f(0.5f, 0.5f, 0.5f); // Metallic gray chassis
    drawRectangle(-0.4f, -0.3f, 0.8f, 0.2f);

    //Rear Wheels
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//Black Colour
    glTranslatef(0.1f, -0.31f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, -1.0f); // Rotate the wheel
    drawCircle(0.0f, 0.0f, 0.090f, 100, 0.0f, 5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//Black Colour
    glTranslatef(0.3f, -0.31f, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, -1.0f); // Rotate the wheel
    drawCircle(0.0f, 0.0f, 0.090f, 100, 0.0f, 5);
    glPopMatrix();

    // Hub caps
    glColor3f(0.2f, 0.2f, 0.2f); // Dark Grey Colour
    glPushMatrix();
    glTranslatef(0.1f, -0.31f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.045f, 100, 0.0f, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, -0.31f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.045f, 100, 0.0f, 1);
    glPopMatrix();



    //Back of the truck
    glPushMatrix();
    glTranslatef(0.0f, dumpAngle * 0.0055f, 0.0f); // Dump Angle
    glRotatef(-dumpAngle, 0.0f, 0.0f, 0.5f); // Dump Angle
    glColor3f(1.0f, 1.0f, 1.0f); //White Colour
    drawRectangle(-0.078f, -0.09f, 0.46f, 0.38f);
    drawRectangle(-0.09f, -0.09f, 0.02f, 0.45f);
    drawRectangle(0.38f, -0.09f, 0.02f, 0.43f);
    glPopMatrix();

    glPopMatrix();
    glFlush();


}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_LEFT:
            truckPosition -= 0.01f; // Decrease Truck Position
            wheelRotation -= 5.0f; // Decrease Wheel Rotation
            break;
        case GLFW_KEY_RIGHT:
            truckPosition += 0.01f; // Increase Truck Position
            wheelRotation += 5.0f; // Increase Wheel Rotation
            break;
        case GLFW_KEY_UP:
            dumpAngle = fmin(dumpAngle + 1.0f, 45.0f); // Dump Angle
            break;
        case GLFW_KEY_DOWN:
            dumpAngle = fmax(dumpAngle - 1.0f, 0.0f); // Dump Angle
            break;
        }
    }
}
// create and populate tweak bar elements
TwBar* create_UI(const std::string name)
{
    // create a tweak bar
    TwBar* twBar = TwNewBar(name.c_str());

    TwWindowSize(gWindowWidth, gWindowHeight); // Set tweak bar size

    TwDefine(" TW_HELP visible=false "); // Disable help menu
    TwDefine(" GLOBAL fontsize=3 "); // Set large font size

    TwDefine(" Main label='MyGUI' refresh=0.02 text=light size='220 320' ");
    // Frame Rate
    TwAddVarRO(twBar, "Frame Rate", TW_TYPE_FLOAT, &gFrameRate, " group='Frame Stats' precision=2 ");
    TwAddVarRO(twBar, "Frame Time", TW_TYPE_FLOAT, &gFrameTime, " group='Frame Stats' ");
    //Wire Frame
    TwAddSeparator(twBar, "Separator1", nullptr);
    TwAddVarRW(twBar, "Wireframe", TW_TYPE_BOOLCPP, &gWireframe, " group='Display' ");
    //Background Colour
    TwAddVarRW(twBar, "BgColor", TW_TYPE_COLOR3F, &gBackgroundColor, " label='Background Color' group='Display' opened=true ");
    // Trucks Position
    TwAddVarRW(twBar, "Truck Position", TW_TYPE_FLOAT, &truckPosition, " min=-1 max=1 step=0.01 group = 'Truck Controls' ");
    //Dump Angle
    TwAddVarRW(twBar, "Dump Angle", TW_TYPE_FLOAT, &dumpAngle, " min=0 max=45 step=1 group='Truck Controls' ");
    //Wheel Rotation
    TwAddVarRW(twBar, "Wheel Rotation", TW_TYPE_FLOAT, &wheelRotation, " step=1.0 label='Wheel Rotation' group='Truck Controls' ");




    return twBar;
}


static void update_scene(GLFWwindow* window)
{
    // Clear Colour
    glClearColor(gBackgroundColor.r, gBackgroundColor.g, gBackgroundColor.b, 1.0f);

}

static void render_scene()
{
    // Clear Colour
    glClear(GL_COLOR_BUFFER_BIT);
    if (gWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Draw the dump truck
    dumpTruck();

    // Road
    glColor3f(0.6f, 0.6f, 0.6f); // Concrete Grey Colour
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw the AntTweakBar
    TwDraw();

    glFlush();
}

// cursor movement callback function
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // pass cursor position to tweak bar
    TwEventMousePosGLFW(static_cast<int>(xpos), static_cast<int>(ypos));
}

// mouse button callback function
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // pass mouse button status to tweak bar
    TwEventMouseButtonGLFW(button, action);
}

// error callback function
static void error_callback(int error, const char* description)
{
    std::cerr << description << std::endl;	// output error description
}
// window size callback function
static void window_size_callback(GLFWwindow* window, int width, int height)
{
    gWindowWidth = width;
    gWindowHeight = height;
    glViewport(0, 0, width, height);
    TwWindowSize(width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(gWindowWidth, gWindowHeight, "2D Scene", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the context of the window the current context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    TwInit(TW_OPENGL_CORE, nullptr);
    TwBar* tweakBar = create_UI("Main");
    // timing data
    double lastUpdateTime = glfwGetTime();
    double elapsedTime = lastUpdateTime;
    int frameCount = 0;
    glViewport(0, 0, gWindowWidth, gWindowHeight);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {



        update_scene(window);	// update the scene

        render_scene();			// render the scene



        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        frameCount++;
        elapsedTime = glfwGetTime() - lastUpdateTime;	// time since last update

        // if elapsed time since last update > 1 second
        if (elapsedTime > 1.0)
        {
            gFrameTime = elapsedTime / frameCount;	// average time per frame
            gFrameRate = 1 / gFrameTime;			// frames per second
            lastUpdateTime = glfwGetTime();			// set last update time to current time
            frameCount = 0;							// reset frame counter
        }
    }


    TwDeleteBar(tweakBar);
    TwTerminate();

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
