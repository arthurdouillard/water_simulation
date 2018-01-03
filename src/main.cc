#include "main.hh"

#include "waves.hh"
#include <vector>


// settings
const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

float mouse_x = SRC_WIDTH / 2;
float mouse_y = SRC_HEIGHT / 2;
float fov = 45.0f;
unsigned char mouse_action = 0;

Camera* camera = new Camera();
GLFWwindow* window = NULL;

int main(void)
{
    init_opengl();


    int size = 100;
    float width = 0.5f;

    /* Initialize the water */
    Shader shader_water("shaders/vertex_water.glsl", "shaders/frag.glsl");
    unsigned int texture_water = load_texture("resources/reflection.jpg");
    auto vertices_water = init_plane(size, width, 4.0f);
    auto indices_water = init_indices(size);
    unsigned int VAO_water = load_object(vertices_water, indices_water);

    /* Initialize the sand */
    Shader shader_sand("shaders/vertex_sand.glsl", "shaders/frag.glsl");
    unsigned int texture_sand = load_texture("resources/sand.jpg");
    auto vertices_sand = init_plane(size, width, -4.0f);
    auto indices_sand = init_indices(size);
    unsigned int VAO_sand = load_object(vertices_sand, indices_sand);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    shader_water.use();
    shader_water.setInt("myText", 0);

    shader_sand.use();
    shader_sand.setInt("myText", 1);



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_water);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_sand);

        shader_water.use();
        shader_water.updateView(fov, SRC_WIDTH, SRC_HEIGHT, camera->GetViewMatrix());

        float now = glfwGetTime();
        shader_water.setFloat("time", now);

        glBindVertexArray(VAO_water);
        glDrawElements(GL_TRIANGLES, indices_water->size(), GL_UNSIGNED_INT, 0);

    shader_sand.use();
        shader_sand.updateView(fov, SRC_WIDTH, SRC_HEIGHT, camera->GetViewMatrix());

        glBindVertexArray(VAO_sand);
        glDrawElements(GL_TRIANGLES, indices_sand->size(), GL_UNSIGNED_INT, 0);

      //  glBindVertexArray(VAO_sand);
      //  glDrawElements(GL_TRIANGLES, indices_sand->size(), GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        //glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO_water);
  //  glDeleteBuffers(1, &VBO);
  //  glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete camera;
    delete vertices_water;
    delete indices_water;

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    (void)window;

    static float last_time = glfwGetTime();

    float curr_time = glfwGetTime();
    float delta_time = curr_time - last_time;
    last_time = curr_time;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_RIGHT)
            camera->ProcessKeyboard(RIGHT, delta_time);
        else if (key == GLFW_KEY_LEFT)
            camera->ProcessKeyboard(LEFT, delta_time);
        else if (key == GLFW_KEY_UP)
            camera->ProcessKeyboard(FORWARD, delta_time);
        else if (key == GLFW_KEY_DOWN)
            camera->ProcessKeyboard(BACKWARD, delta_time);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window;

    if (!mouse_action)
        return;

    float xoffset = mouse_x - xpos;
    float yoffset = mouse_y - ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
    mouse_x = xpos;
    mouse_y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    (void)mods;
    (void)window;

    if (button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            mouse_action = 1;
    }
    else
        mouse_action = 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void init_opengl(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    // Set callbacks
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
}

unsigned int load_texture(const char* path)
{
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}