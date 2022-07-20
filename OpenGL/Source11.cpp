#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>
//==================================
#include "Header.h"

//VariablesGlobales
bool cuartoCargado;
room r;
source s;
int indiceRayo = 3;
unsigned int variable = GL_LINE;
unsigned int variable2 = GL_LINE;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void laodRoom();


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Exercise 13
//lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    //Version de Open gl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Modelos y Simulacion", NULL, NULL);
    // Check si falla al crear
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Introduce th wwindow into the current context
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Exercise 13 Task 1
    // build and compile our shader zprogram
    // ------------------------------------
    //Shader lightingShader("D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13t3_colors.vs", "D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13t3_colors.fs");
    //Shader lightCubeShader("D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13_lightcube.vs", "D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13_lightcube.fs");
   // Shader lightingShader("shader_1.vs", "shader_1.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    Shader cubo("C:/shaders/shader_exercise13t2_colors.vs", "C:/shaders/shader_exercise13t2_colors.fs");
    Shader icosaedro("C:/shaders/shader_exercise13t2_colors.vs", "C:/shaders/shader_exercise13t2_colors.fs");
    Shader rayo("C:/shaders/shader_exercise13t2_colors.vs", "C:/shaders/shader_exercise13t2_colors.fs");
    //Shader rayo2("C:/shaders/shader_exercise13t2_colors.vs", "C:/shaders/shader_exercise13t2_colors.fs");

    laodRoom();

    float vertices1[108];
    int contradorVertices = 0;
    float vertices2[180];
    int contadorIco = 0;
    int indiceIco = 0;
  




    while (contradorVertices < 108) {
        for (int i = 0; i < r.NP; i++) {
            for (int j = 0; j < r.p[i].NT; j++) {
                vertices1[contradorVertices] = r.p[i].t[j].p0.x;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p0.y;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p0.z;
                contradorVertices++;


                vertices1[contradorVertices] = r.p[i].t[j].p1.x;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p1.y;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p1.z;
                contradorVertices++;


                vertices1[contradorVertices] = r.p[i].t[j].p2.x;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p2.y;
                contradorVertices++;
                vertices1[contradorVertices] = r.p[i].t[j].p2.z;
                contradorVertices++;

            }
        }


    }

    

    while (contadorIco < 180 && indiceIco < 20) {
        vertices2[contadorIco] = s.IcoFace[indiceIco].p0.x;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p0.y;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p0.z;
        contadorIco++;


        vertices2[contadorIco] = s.IcoFace[indiceIco].p1.x;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p1.y;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p1.z;
        contadorIco++;


        vertices2[contadorIco] = s.IcoFace[indiceIco].p2.x;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p2.y;
        contadorIco++;
        vertices2[contadorIco] = s.IcoFace[indiceIco].p2.z;
        contadorIco++;


        indiceIco++;

    }



    s.createRays(20);

    reflection* reflexiones = r.RayTracing(s.p, s.Rays, s.NRAYS);



    point destino;
    point origen;



    origen.x = reflexiones[indiceRayo].r[0].x;
    origen.y = reflexiones[indiceRayo].r[0].y;
    origen.z = reflexiones[indiceRayo].r[0].z;


    destino.x = reflexiones[indiceRayo].r[1].x;
    destino.y = reflexiones[indiceRayo].r[1].y;
    destino.z = reflexiones[indiceRayo].r[1].z;




    /*
    printf("El rayo es el %f \n", destino.x);
    printf("El rayo es el %f \n", destino.y);
    printf("El rayo es el %f \n", destino.z);
    printf("-------------------------------\n");
    */





    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int VBO2, cubeVAO2;
    glGenVertexArrays(1, &cubeVAO2);
    glGenBuffers(1, &VBO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO2);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);








    double tiempoAux = 0;
    int contadorPunto = 1;
    int contador = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float tiempoActual = glfwGetTime();
        deltaTime = tiempoActual - lastFrame;
        lastFrame = tiempoActual;

        // input
        // -----
        processInput(window);

        // render
// ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        cubo.use();
        cubo.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        cubo.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        //Exercise 13 Task 2
        cubo.setVec3("lightPos", lightPos);

        //Exercise 13 Task 3
        cubo.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();


        cubo.setMat4("projection", projection);
        cubo.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        cubo.setMat4("model", model);

        // render the cube
        glPolygonMode(GL_FRONT_AND_BACK, variable);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        icosaedro.use();
        icosaedro.setMat4("projection", projection);
        cubo.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
        icosaedro.setMat4("view", view);
        glm::mat4 model2 = glm::mat4(1.0f);
        icosaedro.setMat4("model", model2);

        glPolygonMode(GL_FRONT_AND_BACK, variable2);
        glBindVertexArray(cubeVAO2);
        glDrawArrays(GL_TRIANGLES, 0, 60);

        double distancia = origen.distancia(destino);
        double tiempoVuelo = glfwGetTime() - tiempoAux;
        double distanciaAux = tiempoVuelo * SPEED;


        if ((distanciaAux) >= distancia) {
            origen = destino;
            contadorPunto++;
            destino.x = reflexiones[indiceRayo].r[contadorPunto].x;
            destino.y = reflexiones[indiceRayo].r[contadorPunto].y;
            destino.z = reflexiones[indiceRayo].r[contadorPunto].z;
            tiempoAux = glfwGetTime();
            contador++;
            //printf("Este es el valor del contador %d\n", contador);
        };
        double moduloVelocidad = SPEED / distancia;
        double distanciaX = (destino.x - origen.x);
        double distanciaY = (destino.y - origen.y);
        double distanciaZ = (destino.z - origen.z);

        double traslacionX = distanciaX * tiempoVuelo * moduloVelocidad;
        double traslacionY = distanciaY * tiempoVuelo * moduloVelocidad;
        double traslacionZ = distanciaZ * tiempoVuelo * moduloVelocidad;

        model = glm::translate(model, glm::vec3(origen.x + traslacionX, origen.y + traslacionY, origen.z + traslacionZ));
        model = glm::scale(model, glm::vec3(0.03f, 0.1f, 0.03f));
        rayo.use();
        rayo.setMat4("model", model);
        rayo.setMat4("projection", projection);
        rayo.setVec3("objectColor", 0.0f, 1.0f, 0.0f);
        rayo.setMat4("view", view);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 60);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &cubeVAO2);
    glDeleteBuffers(1, &VBO2);



    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        variable = GL_POINT;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        variable = GL_FILL;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        variable = GL_LINE;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        variable2 = GL_POINT;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        variable2 = GL_FILL;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        variable2 = GL_LINE;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        indiceRayo = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        indiceRayo = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        indiceRayo = 3;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        indiceRayo = 0;
    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
//================================================================================================================================================

void laodRoom() {
    if (!cuartoCargado) {

        r.NewPlanes(6);

        r.p[0].NewPoints(4);

        r.p[0].p[0].x = -2.0f;
        r.p[0].p[0].y = 2.0f;
        r.p[0].p[0].z = 2.0f;

        r.p[0].p[1].x = -2.0f;
        r.p[0].p[1].y = -2.0f;
        r.p[0].p[1].z = 2.0f;

        r.p[0].p[2].x = -2.0f;
        r.p[0].p[2].y = -2.0f;
        r.p[0].p[2].z = -2.0f;

        r.p[0].p[3].x = -2.0f;
        r.p[0].p[3].y = 2.0f;
        r.p[0].p[3].z = -2.0f;

        r.p[0].PointGenTriangle();



        //Cara del frente
        r.p[1].NewPoints(4);

        r.p[1].p[0].x = 2.0f;
        r.p[1].p[0].y = 2.0f;
        r.p[1].p[0].z = 2.0f;

        r.p[1].p[1].x = 2.0f;
        r.p[1].p[1].y = 2.0f;
        r.p[1].p[1].z = -2.0f;

        r.p[1].p[2].x = 2.0f;
        r.p[1].p[2].y = -2.0f;
        r.p[1].p[2].z = -2.0f;

        r.p[1].p[3].x = 2.0f;
        r.p[1].p[3].y = -2.0f;
        r.p[1].p[3].z = 2.0f;

        r.p[1].PointGenTriangle();

        //cara izquierda
        r.p[2].NewPoints(4);

        r.p[2].p[0].x = -2.0f;
        r.p[2].p[0].y = -2.0f;
        r.p[2].p[0].z = 2.0f;

        r.p[2].p[1].x = 2.0f;
        r.p[2].p[1].y = -2.0f;
        r.p[2].p[1].z = 2.0f;

        r.p[2].p[2].x = 2.0f;
        r.p[2].p[2].y = -2.0f;
        r.p[2].p[2].z = -2.0f;

        r.p[2].p[3].x = -2.0f;
        r.p[2].p[3].y = -2.0f;
        r.p[2].p[3].z = -2.0f;
        r.p[2].PointGenTriangle();

        //cara derecha
        r.p[3].NewPoints(4);

        r.p[3].p[0].x = 2.0f;
        r.p[3].p[0].y = 2.0f;
        r.p[3].p[0].z = 2.0f;

        r.p[3].p[1].x = -2.0f;
        r.p[3].p[1].y = 2.0f;
        r.p[3].p[1].z = 2.0f;

        r.p[3].p[2].x = -2.0f;
        r.p[3].p[2].y = 2.0f;
        r.p[3].p[2].z = -2.0f;

        r.p[3].p[3].x = 2.0f;
        r.p[3].p[3].y = 2.0f;
        r.p[3].p[3].z = -2.0f;
        r.p[3].PointGenTriangle();


        //cara superior
        r.p[4].NewPoints(4);

        r.p[4].p[0].x = -2.0f;
        r.p[4].p[0].y = -2.0f;
        r.p[4].p[0].z = 2.0f;

        r.p[4].p[1].x = -2.0f;
        r.p[4].p[1].y = 2.0f;
        r.p[4].p[1].z = 2.0f;

        r.p[4].p[2].x = 2.0f;
        r.p[4].p[2].y = 2.0f;
        r.p[4].p[2].z = 2.0f;

        r.p[4].p[3].x = 2.0f;
        r.p[4].p[3].y = -2.0f;
        r.p[4].p[3].z = 2.0f;
        r.p[4].PointGenTriangle();

        //cara inferior
        r.p[5].NewPoints(4);

        r.p[5].p[0].x = -2.0f;
        r.p[5].p[0].y = 2.0f;
        r.p[5].p[0].z = -2.0f;

        r.p[5].p[1].x = -2.0f;
        r.p[5].p[1].y = -2.0f;
        r.p[5].p[1].z = -2.0f;

        r.p[5].p[2].x = 2.0f;
        r.p[5].p[2].y = -2.0f;
        r.p[5].p[2].z = -2.0f;

        r.p[5].p[3].x = 2.0f;
        r.p[5].p[3].y = 2.0f;
        r.p[5].p[3].z = -2.0f;
        r.p[5].PointGenTriangle();

        cuartoCargado = true;

        int cont_t = 0;
        for (int i = 0; i < r.NP; i++) {
            r.p[i].n = r.p[i].t[0].TriangleNormal();
            for (int j = 0; j < r.p[i].NT; j++) {
                r.p[i].t[j].CalculateProjection();
                r.p[i].t[j].Centroid();
                r.p[i].t[j].ID = cont_t;
                cont_t++;
            }
        }




    }
}