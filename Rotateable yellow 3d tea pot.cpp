#include <GL\glut.h>

double dimension = 3;
char *name = "Tugas 3 Grafkom";
int width = 720;
int height = 480;
int th = 0;
int ph = 0;

void drawTeaPot() {
	glColor3f(20, 200, 0);
	glutSolidTeapot(1);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotated(ph, 5, 1, 0);
	glRotated(th, 0, 1, 5);
	drawTeaPot();
	glFlush();
	glutSwapBuffers();
}

void keyInput(unsigned char k, int x, int y) {
	if (k == 'w') {
		ph += 5;
	}
	else if (k == 's') {
		ph -= 5;
	}
	else if(k == 'd'){
		th += 5;
	}
	else if (k == 'a') {
		th -= 5;
	}
	th %= 360;
	ph %= 360;
	glutPostRedisplay();
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow(name);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyInput);
	glutMainLoop();
}