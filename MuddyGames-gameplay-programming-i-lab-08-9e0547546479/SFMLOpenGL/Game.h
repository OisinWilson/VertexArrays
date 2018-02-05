#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3.h>
#include <Matrix3.h>

//@author Oisin Wilson
//@login C00213826
//@description: 
// vertex array cube
//@Known Bugs:
// no known bugs

using namespace std;
using namespace sf;
//using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;

	float vertices[24];

	float colors[24]{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
						1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };

	unsigned int vertex_index[36] { 0, 1, 2, 0, 2, 3,
									4, 5, 6, 4, 6, 7,
									4, 5, 1, 4, 1, 0,
									7, 6, 2, 7, 2, 3,
									4, 0, 3, 4, 3, 7,
									1, 5, 6, 1, 6, 2 };

	Vector3D vertexPoints[8];

	Matrix3 matrix;
	Vector3D center;
};