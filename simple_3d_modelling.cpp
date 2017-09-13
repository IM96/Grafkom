#include <Windows.h>
#include <GL\glut.h>
#include <iostream>

using namespace std;

// global variabel for cube position
int cx = 0, cy = 0, cz = 0;
int en;
// struct quad for creatring plane
struct Quads {
	int x1, y1, z1;
	int x2, y2, z2;
	int x3, y3, z3;
	int x4, y4, z4;
	float r, g, b;
	int state;
	int total;
}; Quads q[100];

void addQuads() {
	q[0].state++;
	if (q[0].state > 4) q[0].state = 1;
	int st = q[0].state;

	if (st == 1) {
		q[0].total++;
		en = q[0].total;
		q[en].x1 = cx;
		q[en].y1 = cy;
		q[en].z1 = cz;
	}
	if (st == 1 || st == 2) {
		q[en].x2 = cx;
		q[en].y2 = cy;
		q[en].z2 = cz;
	}
	if (st == 1 || st == 2 || st == 3) {
		q[en].x3 = cx;
		q[en].y3 = cy;
		q[en].z3 = cz;
	}
	if (st == 1 || st == 2 || st == 3 || st == 4) {
		q[en].x4 = cx;
		q[en].y4 = cy;
		q[en].z4 = cz;
	}
}

void drawQuads() {
	for (int i = 0; i < q[0].total + 1; i++) {
		glBegin(GL_QUADS);
		glColor3f(q[i].r, q[i].g, q[i].b);
		glVertex3f(q[i].x1, q[i].y1, q[i].z1);
		glVertex3f(q[i].x2, q[i].y2, q[i].z2);
		glVertex3f(q[i].x3, q[i].y3, q[i].z3);
		glVertex3f(q[i].x4, q[i].y4, q[i].z4);
		glEnd();
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w') cz -= 1; // move cube forward
	if (key == 's') cz += 1; // move cube backward
	if (key == 'a') cx -= 1; // move cube left
	if (key == 'd') cx += 1; // move cube right
	if (key == 'q') cy += 1; // move cube up
	if (key == 'z') cy -= 1; // move cube down
	if (key == 32) addQuads();
	if (key == 'r') {
		q[en].r = 1;
		q[en].g = 0;
		q[en].b = 0;
	}
	if (key == 'b') {
		q[en].r = 0;
		q[en].b = 1;
		q[en].g = 0;
	}
	if (key == 'g') {
		q[en].r = 0;
		q[en].b = 0;
		q[en].g = 1;
	}
	glutPostRedisplay();
}

void drawGrid() {
	/*
		create grid
	*/
	for (int i = 0; i < 40; i++) {
		glPushMatrix();
		if (i < 20) glTranslatef(0, 0,i);
		if (i >= 20) {
			glTranslatef(i - 20, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glLineWidth(1);
		glVertex3f(0, - 0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}

void cube() {
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13, 0, -45);
	// rotate cube so that looks like 3d
	glRotatef(40, 1, 1, 0);
	drawGrid();
	drawQuads();
	cube();
	glutSwapBuffers();
}

void init() {
	// init view for 3d prjection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 0.1);
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(1080, 720);
	glutCreateWindow("Tugas 1 Grafkom");
	init();
	// Bind the two functions (above) to respond when necessary
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	// window main loop
	glutMainLoop();
	return 0;
}
