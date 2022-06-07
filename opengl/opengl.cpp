#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define HEIGHT 500
#define WIDTH 1500

#define QUADS_PER_HEIGHT 500
#define QUADS_PER_WIDTH 1500

#define QUAD_SIZE_HEIGHT HEIGHT / QUADS_PER_HEIGHT
#define QUAD_SIZE_WIDTH WIDTH / QUADS_PER_WIDTH

#define RANDOM (float)rand()/RAND_MAX

struct color
{
	float r;
	float g;
	float b;
};

struct quad
{
	// coords top_left_corner
	float x;
	float y;

	// height & width
	float height;
	float width;

	//colors
	color col;
}arrquads[QUADS_PER_WIDTH][QUADS_PER_HEIGHT];

void init();
void draw();
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(1500, 50);
	glutCreateWindow("Grafics");
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}
void init()
{
	srand(time(NULL));

	glClearColor(1.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	//init quads
	for (int i = 0; i < QUADS_PER_WIDTH; i++)
	{
		for (int j = 0; j < QUADS_PER_HEIGHT; j++)
		{
			//set up color
			arrquads[i][j].col = { RANDOM, RANDOM, RANDOM };

			//set up size
			arrquads[i][j].width = QUAD_SIZE_WIDTH;
			arrquads[i][j].height = QUAD_SIZE_HEIGHT;

			//set up coords
			arrquads[i][j].x = i * QUAD_SIZE_WIDTH;
			arrquads[i][j].y = j * QUAD_SIZE_HEIGHT;
		}
	}
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, WIDTH, HEIGHT);

	// drawing quads...
	for (int i = 0; i < QUADS_PER_WIDTH; i++)
	{
		for (int j = 0; j < QUADS_PER_HEIGHT; j++)
		{
			glColor3f(
				RANDOM,//arrquads[i][j].col.r,
				RANDOM,//arrquads[i][j].col.g,
				RANDOM);//arrquads[i][j].col.b);

			glBegin(GL_QUADS);

			glVertex2f(
				arrquads[i][j].x,
				arrquads[i][j].y);

			glVertex2f(
				arrquads[i][j].x + arrquads[i][j].width,
				arrquads[i][j].y);

			glVertex2f(
				arrquads[i][j].x + arrquads[i][j].width,
				arrquads[i][j].y + arrquads[i][j].height);

			glVertex2f(
				arrquads[i][j].x,
				arrquads[i][j].y + arrquads[i][j].height);

			glEnd();
		}
	}

	glFlush();
}