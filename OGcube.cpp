#include "Cross.hpp"   // Cruz inicial
#include "Corners.hpp" // Esquinas
#include "Edges.hpp"   // Aristas
#include "OLL.hpp"     // Orient Last Layer
#include "PLL.hpp"     // Permutation of the Last Layer
#include "OGcube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OGcube::OGcube()
{
	cubeSolver = new Cube(false);
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	for (int i = 0; i < 27; i++) {
		allVertices[i] = new float[180];
		memcpy(allVertices[i], vertices, sizeof(vertices));
	}
	int face5[] = { 0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				//allVertices[face[j * 3 + i]][30 * 5 + 5 * k + 3] = 0.0f + 0.125f * ((float)i) + 0.125f * allVertices[face[j * 3 + i]][30 * 5 + 5 * k + 3];
				//allVertices[face[j * 3 + i]][30 * 5 + 5 * k + 4] = 0.625f + 0.125f * ((float)j) + 0.125f * allVertices[face[j * 3 + i]][30 * 5 + 5 * k + 4];
				allVertices[face5[j * 3 + i]][30 * 5 + 5 * k + 3] = 0.0f + 0.1f * ((float)i) + 0.1f * allVertices[face5[j * 3 + i]][30 * 5 + 5 * k + 3];
				allVertices[face5[j * 3 + i]][30 * 5 + 5 * k + 4] = 0.9f - 0.1f * ((float)j) + 0.1f * allVertices[face5[j * 3 + i]][30 * 5 + 5 * k + 4];
			}
		}
	}
	int face3[] = { 20, 11, 2, 23, 14, 5, 26, 17, 8 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				allVertices[face3[j * 3 + i]][30 * 3 + 5 * k + 3] = 0.3f + 0.1f * ((float)i) + 0.1f * allVertices[face3[j * 3 + i]][30 * 3 + 5 * k + 3];
				allVertices[face3[j * 3 + i]][30 * 3 + 5 * k + 4] = 0.9f - 0.1f * ((float)j) + 0.1f * allVertices[face3[j * 3 + i]][30 * 3 + 5 * k + 4];
			}
		}
	}
	int face2[] = { 18, 9, 0, 21, 12, 3, 24, 15, 6 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				allVertices[face2[j * 3 + i]][30 * 2 + 5 * k + 3] = 0.6f + 0.1f * ((float)i) + 0.1f * allVertices[face2[j * 3 + i]][30 * 2 + 5 * k + 3];
				allVertices[face2[j * 3 + i]][30 * 2 + 5 * k + 4] = 0.9f - 0.1f * ((float)j) + 0.1f * allVertices[face2[j * 3 + i]][30 * 2 + 5 * k + 4];
			}
		}
	}
	int face4[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				allVertices[face4[j * 3 + i]][30 * 4 + 5 * k + 3] = 0.0f + 0.1f * ((float)i) + 0.1f * allVertices[face4[j * 3 + i]][30 * 4 + 5 * k + 3];
				allVertices[face4[j * 3 + i]][30 * 4 + 5 * k + 4] = 0.6f - 0.1f * ((float)j) + 0.1f * allVertices[face4[j * 3 + i]][30 * 4 + 5 * k + 4];
			}
		}
	}
	int face1[] = { 6, 7, 8, 15, 16, 17, 24, 25, 26 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				allVertices[face1[j * 3 + i]][30 * 1 + 5 * k + 3] = 0.3f + 0.1f * ((float)i) + 0.1f * allVertices[face1[j * 3 + i]][30 * 1 + 5 * k + 3];
				allVertices[face1[j * 3 + i]][30 * 1 + 5 * k + 4] = 0.6f - 0.1f * ((float)j) + 0.1f * allVertices[face1[j * 3 + i]][30 * 1 + 5 * k + 4];
			}
		}
	}
	int face0[] = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {
				allVertices[face0[j * 3 + i]][30 * 0 + 5 * k + 3] = 0.6f + 0.1f * ((float)i) + 0.1f * allVertices[face0[j * 3 + i]][30 * 0 + 5 * k + 3];
				allVertices[face0[j * 3 + i]][30 * 0 + 5 * k + 4] = 0.6f - 0.1f * ((float)j) + 0.1f * allVertices[face0[j * 3 + i]][30 * 0 + 5 * k + 4];
			}
		}
	}

	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i][120 + j * 5 + 3] *= 0.1f;
			allVertices[i][120 + j * 5 + 4] *= 0.1f;
		}
	}
	for (int i = 9; i < 27; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i][150 + j * 5 + 3] *= 0.1f;
			allVertices[i][150 + j * 5 + 4] *= 0.1f;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i * 3 + 1][60 + j * 5 + 3] *= 0.1f;
			allVertices[i * 3 + 2][60 + j * 5 + 3] *= 0.1f;
			allVertices[i * 3 + 1][60 + j * 5 + 4] *= 0.1f;
			allVertices[i * 3 + 2][60 + j * 5 + 4] *= 0.1f;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i * 3][90 + j * 5 + 3] *= 0.1f;
			allVertices[i * 3 + 1][90 + j * 5 + 3] *= 0.1f;
			allVertices[i * 3 ][90 + j * 5 + 4] *= 0.1f;
			allVertices[i * 3 + 1][90 + j * 5 + 4] *= 0.1f;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i * 9 + 3][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 4][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 5][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 6][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 7][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 8][j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 3][j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 4][j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 5][j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 6][j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 7][j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 8][j * 5 + 4] *= 0.1f;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			allVertices[i * 9 + 0][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 1][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 2][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 3][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 4][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 5][30 + j * 5 + 3] *= 0.1f;
			allVertices[i * 9 + 0][30 + j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 1][30 + j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 2][30 + j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 3][30 + j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 4][30 + j * 5 + 4] *= 0.1f;
			allVertices[i * 9 + 5][30 + j * 5 + 4] *= 0.1f;
		}
	}
	
	glm::vec3 cubePositionsTmp[] = {
		glm::vec3(-1.0f, 1.0f,-1.0f),
		glm::vec3(0.0f, 1.0f,-1.0f),
		glm::vec3(1.0f, 1.0f,-1.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),

		glm::vec3(-1.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(1.0f, 0.0f,-1.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),

		glm::vec3(-1.0f,-1.0f,-1.0f),
		glm::vec3(0.0f,-1.0f,-1.0f),
		glm::vec3(1.0f,-1.0f,-1.0f),
		glm::vec3(-1.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(1.0f,-1.0f, 0.0f),
		glm::vec3(-1.0f,-1.0f, 1.0f),
		glm::vec3(0.0f,-1.0f, 1.0f),
		glm::vec3(1.0f,-1.0f, 1.0f)
	};
	cubeTransforms = new glm::mat4[27];
	for (int i = 0; i < 27; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		cubeTransforms[i] = glm::translate(model, cubePositionsTmp[i]);
		if (i == 13) {
			cubeTransforms[i] = glm::scale(cubeTransforms[i], glm::vec3(0.01f, 0.01f, 0.01f) );
		}
	}
	for (int i = 0; i < 27; i++) {
		miniCubes[i] = i;
	}
	rotationStep = 0.0f;
	isBusy = false;
	moveQueue = "";
}

void OGcube::step()
{
	if (moveQueue != "" && !isBusy) {
		isBusy = false;
		char move = moveQueue.front();
		moveQueue.erase(0, 1);
		if (move == 'R') { 
			R();
			cubeSolver->moves("RRR");
		}
		else if (move == 'L') {
			L();
			cubeSolver->moves("LLL");
		}
		else if (move == 'U') {
			U();
			cubeSolver->moves("UUU");
		}
		else if (move == 'D') {
			D();
			cubeSolver->moves("DDD");
		}
		else if (move == 'F') {
			F();
			cubeSolver->moves("FFF");
		}
		else if (move == 'B') {
			B();
			cubeSolver->moves("BBB");
		}
		//restart solver moves queue
		if(moveQueue == ""){
			//print cube
			for (int i = 0; i < 27; i++) {
				std::cout << miniCubes[i] << ", ";
				if (i % 3 == 2) {
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			std::cout << std::endl;
			cubeSolver->output();

			cubeSolver->movesBuffer = "";
		}
			
	}
	if (isBusy) {
		if (rotationStep == 87.0f) {
			//save face positions state
			int tmp[9];
			for (int i = 0; i < 9; i++) {
				tmp[i] = miniCubes[currentFace[i]];
			}
			//change positions
			for (int i = 0; i < 9; i++) {
				miniCubes[currentFace[i]] = tmp[faceSwap[i]];
			}
			//pop queue
			isBusy = false;
			
		}
		glm::mat4 model = glm::mat4(1.0f); 
		model = glm::rotate(model, glm::radians(3.0f), rotationAxis);
		for (int i = 0; i < 9; i++) {
			cubeTransforms[miniCubes[currentFace[i]]] = model * cubeTransforms[miniCubes[currentFace[i]]];
		}
		rotationStep += 3.0f;
		
	}
}

void OGcube::R()
{
	if (!isBusy) {
		isBusy = true;
		int myface[] = { 2, 5, 8, 11, 14 ,17, 20, 23, 26 };
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(-1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->R(1);
	}
}

void OGcube::L()
{
	if (!isBusy) {
		isBusy = true;
		int myface[] = { 0, 3, 6, 9, 12, 15, 18, 21, 24 };
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->L(1);
	}
}

void OGcube::U()
{
	if(!isBusy){
		isBusy = true;
		int myface[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(0.0f, -1.0f, 0.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->U(1);
	}
}

void OGcube::D()
{
	if (!isBusy) {
		isBusy = true;
		int myface[] = { 18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 };
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->D(1);
	}
}

void OGcube::F()
{
	if (!isBusy) {
		isBusy = true;
		int myface[] = { 6, 7, 8, 15, 16, 17, 24, 25, 26 };
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(0.0f, 0.0f, -1.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->F(1);
	}
}

void OGcube::B()
{
	if (!isBusy) {
		isBusy = true;
		int myface[] = { 0, 1, 2, 9, 10, 11, 18, 19, 20};
		memcpy(currentFace, myface, sizeof(myface));
		int rotSwapPositions[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
		memcpy(faceSwap, rotSwapPositions, sizeof(rotSwapPositions));
		rotationStep = 0.0f;
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 9; i++) {
			currentFaceTransforms[i] = cubeTransforms[miniCubes[currentFace[i]]];
		}
		cubeSolver->B(1);
	}
}

void OGcube::solve()
{
	moveQueue+=" ";
	Cross::solveCross(*cubeSolver);
	std::cout << "Cross solved" << std::endl;
	Corners::solveCorners(*cubeSolver);
	std::cout << "Corners solved" << std::endl;
	Edges::solveEdges(*cubeSolver);
	std::cout << "Edges solved" << std::endl;;
	OLL::solveOLL(*cubeSolver);
	std::cout << "OLL solved" << std::endl;
	PLL::solvePLL(*cubeSolver);
	std::cout << "PLL solved" << std::endl;
	std::cout << cubeSolver->movesBuffer << std::endl;
	moveQueue = cubeSolver->movesBuffer;

}

void OGcube::separate()
{
	for (int i = 0; i < 27; i++) {
		cubeTransforms[i][3][0] += cubeTransforms[i][3][0] * 0.005f;
		cubeTransforms[i][3][1] += cubeTransforms[i][3][1] * 0.005f;
		cubeTransforms[i][3][2] += cubeTransforms[i][3][2] * 0.005f;
	}
}

void OGcube::join()
{
	for (int i = 0; i < 27; i++) {
		cubeTransforms[i][3][0] -= cubeTransforms[i][3][0] * 0.005f;
		cubeTransforms[i][3][1] -= cubeTransforms[i][3][1] * 0.005f;
		cubeTransforms[i][3][2] -= cubeTransforms[i][3][2] * 0.005f;
	}
}

