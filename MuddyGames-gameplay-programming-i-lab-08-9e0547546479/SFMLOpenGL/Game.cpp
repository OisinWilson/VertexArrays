#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	vertexPoints[0] = { 1.0f, 1.0f, 1.0f };
	vertexPoints[1] = { -1.0f, 1.0f, 1.0f };
	vertexPoints[2] = { -1.0f, -1.0f, 1.0f };
	vertexPoints[3] = { 1.0f, -1.0f, 1.0f };
	vertexPoints[4] = { 1.0f, 1.0f, -1.0f };
	vertexPoints[5] = { -1.0f, 1.0f, -1.0f };
	vertexPoints[6] = { -1.0f, -1.0f, -1.0f };
	vertexPoints[7] = { 1.0f, -1.0f, -1.0f };

	for (int i = 0; i < 8; i++)
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 8; i++)
		{
			vertexPoints[i] = matrix.RotationX(0.1) * vertexPoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 8; i++)
		{
			vertexPoints[i] = matrix.RotationY(0.1) * vertexPoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 8; i++)
		{
			vertexPoints[i] = matrix.RotationZ(0.1) * vertexPoints[i];
		}
		
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			vertexPoints[i] = matrix.Scale3D(101) * vertexPoints[i];
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			vertexPoints[i] = matrix.Scale3D(99) * vertexPoints[i];
		}

	}




	for (int i = 0; i < 8; i++)
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

