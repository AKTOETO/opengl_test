#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define RANDOM (float)rand()/RAND_MAX
#define PI 3.14159265358979323846
#define SHIFT 0.1
#define SIZEARR int(2 * PI / SHIFT) + 2

// для хранения цвета
struct color
{
	float r;
	float g;
	float b;
};

// массив цветов для первого круга
color arr_vert1[SIZEARR];
// массив цветов для второго круга
color arr_vert2[SIZEARR];

GLfloat R = 640.0 / 480; //Форматное соотношение
GLfloat w = 40; //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f = 0.5;
GLfloat delta = 0.5;


void init_arr_vert(color arr[])
{
	for (int i = 0; i < SIZEARR; i++)
	{
		//printf("%f\n", float(i) / (SIZEARR*10));
		//arr[i] = { RANDOM, RANDOM, RANDOM };
		// градиент
		arr[i] = {
			float(i) / (SIZEARR * 10),
			float(i) / (SIZEARR * 10),
			float(i) / (SIZEARR * 10)
		};
	}
}

void init(void)
{
	h = w / R; l = -w / 2; r = w / 2; b = -h / 2; t = h / 2; //Расчет параметров мирового окна
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// инициализация цвета первого круга
	init_arr_vert(arr_vert1);
	// инициализация цвета второго круга
	init_arr_vert(arr_vert2);
}

void reshape(GLsizei W, GLsizei H)
{
	if (R > W / H) glViewport(0, 0, W, W / R);
	else glViewport(0, 0, H * R, H);
}

void showAxis(void)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, b);
	glVertex2f(0, t);

	glVertex2f(l, 0);
	glVertex2f(r, 0);
	glEnd();
}


void circle(float _radius, color _col[])
{
	float x_cen = 0;
	float y_cen = 0;

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(_col[0].r, _col[0].g, _col[0].b);
	glVertex2f(x_cen, y_cen);
	int j = 0;
	for (float i = 0; i < 2 * PI; i += SHIFT, j++)
	{
		glColor3f(RANDOM, RANDOM, RANDOM);
		glColor3f(_col[j + 1].r, _col[j + 1].g, _col[j + 1].b);
		glVertex2f(_radius * cos(i), _radius * sin(i));
	}

	glColor3f(_col[SIZEARR - 1].r, _col[SIZEARR - 1].g, _col[SIZEARR - 1].b);
	glVertex2f(_radius, 0);

	glEnd();
}


void scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		showAxis();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-f, 0.0, 0.0, 1.0);
		glTranslatef(4.5, 8.0, 0.0);
		glRotatef(-f, 0.0, 0.0, 1.0);
		circle(5, arr_vert1);
	glPopMatrix();

	glPushMatrix();
		glRotatef(f * 5, 0.0, 0.0, 1.0);
		glTranslatef(4.5, 8.0, 0.0);
		glRotatef(f * 5, 0.0, 0.0, 1.0);
		circle(2, arr_vert2);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	f += delta;
	if (f == 360) f = 0;
	Sleep(15);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(1500, 20);
	glutCreateWindow("Myprog");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}