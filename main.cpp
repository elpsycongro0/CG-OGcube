#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"

#include <iostream>
#include "Cube.hpp"
#include "Cross.hpp"
#include "Corners.hpp"
#include "Edges.hpp"
#include "OLL.hpp"
#include "PLL.hpp"
#include "OGcube.hpp"

//format used by cube, temporal
std::string format(std::string s) {
	std::string formatted;

	for (int i = 0; i<s.length(); ++i) {
		if (s[i] == '\'') {
			formatted += s[i - 1];
			formatted += s[i - 1];
		}
		else if (s[i] == '2') {
			formatted += s[i - 1];
		}
		else if (s[i] == ' ') {

		}
		else {
			formatted += s[i];
		}
	}

	return formatted;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 8.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 globalProjection;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 tra = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 sz = glm::vec3(1.0f, 1.0f, 1.0f);
float t1 = 0.0f;
float t2 = 0.0f;
float t3 = 0.0f;
float t4 = 0.0f;
float t5 = 0.0f;
float t6 = 0.0f;

bool isBusy = false;
float rotationStep = 0.0f;
glm::vec3 rotatioStepAxis;
OGcube myRealCube;
OGcube myRealCube2;
OGcube myRealCube3[27];

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
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

	// build and compile our shader zprogram
	// ------------------------------------
	//Shader ourShader("7.3.camera.vs", "7.3.camera.fs");
	Shader ourShader("C://Users//Rod//Documents//2020-2//Compu Grafica//GLFW_GLAD_GLUT_GLEW_cmake_project//src//rubick//6.2.coordinate_systems.vs", "C://Users//Rod//Documents//2020-2//Compu Grafica//GLFW_GLAD_GLUT_GLEW_cmake_project//src//rubick//6.2.coordinate_systems.fs");

	
	unsigned int VBOList[27];
	unsigned int VAOList[27];
	for (int i = 0; i < 27; i++) {
		glGenVertexArrays(1, &VAOList[i]);
		glGenBuffers(1, &VBOList[i]);

		glBindVertexArray(VAOList[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOList[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6 * 6, myRealCube.allVertices[i] , GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	unsigned int VBOList2[27];
	unsigned int VAOList2[27];
	for (int i = 0; i < 27; i++) {
		glGenVertexArrays(1, &VAOList2[i]);
		glGenBuffers(1, &VBOList2[i]);

		glBindVertexArray(VAOList2[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOList2[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6 * 6, myRealCube2.allVertices[i], GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	unsigned int VBOList3[27][27];
	unsigned int VAOList3[27][27];
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			glGenVertexArrays(1, &VAOList3[i][j]);
			glGenBuffers(1, &VBOList3[i][j]);

			glBindVertexArray(VAOList3[i][j]);

			glBindBuffer(GL_ARRAY_BUFFER, VBOList3[i][j]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6 * 6, myRealCube3[i].allVertices[i], GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// texture coord attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
	}
	
	// load and create a texture 
	// -------------------------
	unsigned int texture1;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("C://Users//Rod//Documents//2020-2//Compu Grafica//GLFW_GLAD_GLUT_GLEW_cmake_project//src//rubick//rubikTexture2.jpg", &width, &height, &nrChannels, 0);
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
	

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use();
	ourShader.setInt("texture1", 0);

	std::cout << "MOVES: " << std::endl;
	std::cout << "  [1] RIGHT FACE " << std::endl;
	std::cout << "  [2] LEFT FACE" << std::endl;
	std::cout << "  [3] UP FACE" << std::endl;
	std::cout << "  [4] DOWN FACE " << std::endl;
	std::cout << "  [5] FRONT FACE" << std::endl;
	std::cout << "  [6] BACK FACE" << std::endl;
	std::cout << "  [E] to separate cubies" << std::endl;
	std::cout << "  [Q] to join cubies" << std::endl;
	std::cout << "  [0] to solve cube" << std::endl;
	std::cout << "NABIGATION" << std::endl;
	std::cout << "  QWASD Shift Space and Mouse" << std::endl;
	// render loop
	// -----------
	globalProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(45.0f / 255.0f, 45.0f / 255.0f, 48.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		

		// activate shader
		ourShader.use();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = globalProjection;
		
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);

		// render boxes
		myRealCube.step();
		myRealCube2.step();
		for (int i = 0; i < 27; i++) {
			myRealCube3[i].step();
		}
		for (unsigned int i = 0; i < 27; i++)
		{
			glBindVertexArray(VAOList[i]);
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			/*
			if (i <9) {
				model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				myRealCube.cubeTransforms[i] = model * myRealCube.cubeTransforms[i];
			}
			*/
			
			model = glm::translate(model, tra);
			//float angle = 20.0f * i;
			float angle = 0.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model , sz);

			//ourShader.setMat4("model", model);
			ourShader.setMat4("model", myRealCube.cubeTransforms[i]);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
		}
		for (unsigned int i = 0; i < 27; i++)
		{
			glBindVertexArray(VAOList2[i]);
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
											   /*
											   if (i <9) {
											   model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
											   myRealCube.cubeTransforms[i] = model * myRealCube.cubeTransforms[i];
											   }
											   */

			model = glm::translate(model, tra);
			//float angle = 20.0f * i;
			float angle = 0.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
			//try to change size of 2nd cube
			sz = glm::vec3(0.34f, 0.34f, 0.34f);
			model = glm::scale(model, sz);
			model = model * myRealCube2.cubeTransforms[i];
			//ourShader.setMat4("model", model);
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		 
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	for (int i = 0; i < 27; i++) {
		glDeleteVertexArrays(1, &VAOList[i]);
		glDeleteBuffers(1, &VBOList[i]);
		glDeleteVertexArrays(1, &VAOList2[i]);
		glDeleteBuffers(1, &VBOList2[i]);
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= cameraUp * cameraSpeed;

	//123456
	//235162
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		myRealCube.R();
		myRealCube2.L();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		myRealCube.L();
		myRealCube2.U();
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		myRealCube.U();
		myRealCube2.F();
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		myRealCube.D();
		myRealCube2.R();
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		myRealCube.F();
		myRealCube2.B();
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		myRealCube.B();
		myRealCube2.L();
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		if (!myRealCube.isBusy) {
			myRealCube.solve();	
		}
		if (!myRealCube2.isBusy) {
			myRealCube2.solve();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		if(globalProjection != glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f))std::cout << "GLM ORTHO\n";
		globalProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
		
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		if(globalProjection != glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f))std::cout << "GLM PERSPECTIVE\n";
		globalProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	}
	
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		myRealCube.join();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		myRealCube.separate();

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		rot += glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		rot += glm::vec3(0.0f, 1.0f, 0.0f) ;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		rot += glm::vec3(0.0f, 0.0f, 1.0f) ;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		t1 += 0.005f;
		tra.x = sin(t1) / 2;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		t2 += 0.005f;
		tra.y = sin(t2) / 2;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		t3 += 0.005f;
		tra.z = sin(t3) / 2;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		t4 += 0.005f;
		sz.x = 1.0f + sin(t4) / 2;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		t5 += 0.005f;
		sz.y = 1.0f + sin(t5) / 2;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		t6 += 0.005f;
		sz.z = 1.0f + sin(t6) / 2;
	}
		
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

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

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}