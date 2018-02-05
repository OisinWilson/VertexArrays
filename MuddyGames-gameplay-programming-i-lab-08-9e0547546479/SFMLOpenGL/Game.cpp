#include <Game.h>

//@author Oisin Wilson
//@login C00213826
//@description: 
// vertex array cube
//@Known Bugs:
// no known bugs

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Vertex Array Cube")
{
	vertexPoints[0] = { 1.0f, 1.0f, -1.0f };
	vertexPoints[1] = { -1.0f, 1.0f, -1.0f };
	vertexPoints[2] = { -1.0f, -1.0f, -1.0f };
	vertexPoints[3] = { 1.0f, -1.0f, -1.0f };
	vertexPoints[4] = { 1.0f, 1.0f, -3.0f };
	vertexPoints[5] = { -1.0f, 1.0f, -3.0f };
	vertexPoints[6] = { -1.0f, -1.0f, -3.0f };
	vertexPoints[7] = { 1.0f, -1.0f, -3.0f };

	for (auto i = 0; i < 8; i++)
	{
		vertices[i * 3] = vertexPoints[i].ReturnX();
		vertices[i * 3 + 1 ] = vertexPoints[i].ReturnY();
		vertices[i * 3 + 2] = vertexPoints[i].ReturnZ();
	}
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -8.0f);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	cout << "Update up" << endl;

	//find center
	center = { vertexPoints[0] + vertexPoints[1] + vertexPoints[2] + vertexPoints[3] + vertexPoints[4] + vertexPoints[5] + vertexPoints[6] + vertexPoints[7] };
	center = { center.ReturnX() / 8, center.ReturnY() / 8, center.ReturnZ() / 8 };

	//translate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = Matrix3::Translate(0.001f, 0) * vertexPoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = Matrix3::Translate(-0.001f, 0) * vertexPoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = Matrix3::Translate(0, 0.001f) * vertexPoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = Matrix3::Translate(0, -0.001f) * vertexPoints[i];
		}
	}

	//rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = (matrix.RotationX(0.1) * (vertexPoints[i] - center)) + center;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = (matrix.RotationY(0.1) * (vertexPoints[i] - center)) + center;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = (matrix.RotationZ(0.1) * (vertexPoints[i] - center)) + center;
		}
	}

	//scaling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = (matrix.Scale3D(101) * (vertexPoints[i] - center)) + center;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (auto i = 0; i < 8; i++)
		{
			vertexPoints[i] = (matrix.Scale3D(99) * (vertexPoints[i] - center)) + center;
		}
	}


	for (auto i = 0; i < 8; i++)
	{
		vertices[i * 3] = vertexPoints[i].ReturnX();
		vertices[i * 3 + 1] = vertexPoints[i].ReturnY();
		vertices[i * 3 + 2] = vertexPoints[i].ReturnZ();
	}
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}