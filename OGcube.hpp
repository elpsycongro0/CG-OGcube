#ifndef OGCUBE_H
#define OGCUBE_H

#include "Cube.hpp"
#include <glm/glm.hpp>
#include <string>

class OGcube {

public:
	Cube *cubeSolver;	//solver
	float *allVertices[27];	//geometria
	glm::mat4 *cubeTransforms; //transformaciones
	int miniCubes[27];	//posicion de cubies en el estado del cubo

	//variables auxiliares para las rotaciones
	float rotationStep;
	bool isBusy;
	std::string moveQueue;
	int currentFace[9];
	int faceSwap[9];
	glm::vec3 rotationAxis;
	glm::mat4 currentFaceTransforms[9];

	OGcube();
	void step();
	//movimientos, similares a las llamadas a función del solver
	void R();
	void L();
	void U();
	void D();
	void F();
	void B();
	//solver
	void solve();
	void separate();
	void join();
};

#endif

