#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <math.h>

// Global variables for animation
float sunRotation = 0.0f;
float cloudPosition1 = 0.0f;
float cloudPosition2 = -1.0f;
float windmillRotation = 0.0f;

void init() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Sky blue background
}

// Function to draw a house with windows and door
void drawHouse() {

    // House body (rectangle)
    glColor3f(0.8f, 0.6f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, 0.2f);
    glVertex2f(-0.3f, 0.2f);
    glEnd();

    // Roof (triangle)
    glColor3f(0.7f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // Door
    glColor3f(0.5f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.07f, -0.3f);
    glVertex2f(0.07f, -0.3f);
    glVertex2f(0.07f, -0.05f);
    glVertex2f(-0.07f, -0.05f);
    glEnd();

    // Doorknob
    glColor3f(0.8f, 0.8f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.04f, -0.17f);
    glEnd();

    // Left Window
    glColor3f(0.8f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(-0.15f, -0.1f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.25f, 0.05f);
    glEnd();

    // Right Window
    glBegin(GL_QUADS);
    glVertex2f(0.15f, -0.1f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.25f, 0.05f);
    glVertex2f(0.15f, 0.05f);
    glEnd();

    // Window Crosses
    glColor3f(0.4f, 0.2f, 0.1f);
    glLineWidth(2.0f);

    // Left Window Cross
    glBegin(GL_LINES);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.25f, -0.025f);
    glVertex2f(-0.15f, -0.025f);
    glEnd();

    // Right Window Cross
    glBegin(GL_LINES);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, 0.05f);
    glVertex2f(0.15f, -0.025f);
    glVertex2f(0.25f, -0.025f);
    glEnd();
}

// Function to draw the sun with clear rotation edges
void drawSun() {
    glPushMatrix();

    glTranslatef(0.7f, 0.7f, 0.0f);
    glRotatef(sunRotation, 0.0f, 0.0f, 1.0f);

    // Main sun circle
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);

    for(int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cos(angle) * 0.1f, sin(angle) * 0.1f);
    }

    glEnd();

    // Sun rays
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for(int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.14159f / 180.0f;
        glVertex2f(cos(angle) * 0.12f, sin(angle) * 0.12f);
        glVertex2f(cos(angle) * 0.2f, sin(angle) * 0.2f);
    }
    glEnd();

    glPopMatrix();
}

// Function to draw a single cloud
void drawSingleCloud(float xOffset, float yOffset) {
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw multiple circles to form a cloud
    float cloudPoints[][2] = {
        {0.0f, 0.0f},
        {0.1f, 0.05f},
        {0.2f, 0.0f},
        {0.05f, -0.05f},
        {0.15f, -0.05f}
    };

    for(int i = 0; i < 5; i++) {
        glBegin(GL_TRIANGLE_FAN);
        for(int j = 0; j <= 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(cloudPoints[i][0] + cos(angle) * 0.08f,
                      cloudPoints[i][1] + sin(angle) * 0.08f);
        }
        glEnd();
    }
    glPopMatrix();
}

// Function to draw moving clouds
void drawClouds() {
    drawSingleCloud(cloudPosition1, 0.6f);
    drawSingleCloud(cloudPosition2, 0.7f);
}

// Function to draw a windmill with rotating blades
void drawWindmill() {
    // Base
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-2.5f, -0.4f);
    glVertex2f(-2.25f, -0.4f);
    glVertex2f(-2.375f, 0.3f);
    glEnd();

    // Rotating blades
    glPushMatrix();
    glTranslatef(-2.375f, 0.3f, 0.0f);
    glRotatef(windmillRotation, 0.0f, 0.0f, 1.0f);
    glColor3f(0.4f, 0.4f, 0.4f);

    for(int i = 0; i < 4; i++) {
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.0f, 0.05f);
        glEnd();
    }

    glPopMatrix();
}

void drawGarden() {

    // Tree trunk (rectangle)
    glColor3f(0.45f, 0.32f, 0.17f);
    glBegin(GL_QUADS);
    glVertex2f(0.4f, -0.4f);
    glVertex2f(0.45f, -0.4f);
    glVertex2f(0.45f, -0.7f);
    glVertex2f(0.4f, -0.7f);
    glEnd();

    // Tree leaves (using triangles)
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    // Bottom layer
    glVertex2f(0.3f, -0.45f);
    glVertex2f(0.55f, -0.45f);
    glVertex2f(0.425f, -0.3f);
    // Middle layer
    glVertex2f(0.35f, -0.35f);
    glVertex2f(0.5f, -0.35f);
    glVertex2f(0.425f, -0.2f);
    // Top layer
    glVertex2f(0.38f, -0.25f);
    glVertex2f(0.47f, -0.25f);
    glVertex2f(0.425f, -0.1f);
    glEnd();

    // Bench seat (darker brown)
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0.55f, -0.5f);
    glVertex2f(0.75f, -0.5f);
    glVertex2f(0.75f, -0.55f);
    glVertex2f(0.55f, -0.55f);
    glEnd();

    // Seat border
    glColor3f(0.2f, 0.1f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.55f, -0.5f);
    glVertex2f(0.75f, -0.5f);
    glVertex2f(0.75f, -0.55f);
    glVertex2f(0.55f, -0.55f);
    glEnd();

    // Bench back (lighter brown)
    glColor3f(0.6f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.55f, -0.5f);
    glVertex2f(0.75f, -0.5f);
    glVertex2f(0.75f, -0.4f);
    glVertex2f(0.55f, -0.4f);
    glEnd();

    // Back border
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.55f, -0.5f);
    glVertex2f(0.75f, -0.5f);
    glVertex2f(0.75f, -0.4f);
    glVertex2f(0.55f, -0.4f);
    glEnd();

    // Bench legs (darkest brown)
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(0.56f, -0.55f);
    glVertex2f(0.58f, -0.55f);
    glVertex2f(0.58f, -0.65f);
    glVertex2f(0.56f, -0.65f);
    glEnd();

    // Left leg border
    glColor3f(0.2f, 0.1f, 0.05f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.56f, -0.55f);
    glVertex2f(0.58f, -0.55f);
    glVertex2f(0.58f, -0.65f);
    glVertex2f(0.56f, -0.65f);
    glEnd();

    // Right leg
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(0.72f, -0.55f);
    glVertex2f(0.74f, -0.55f);
    glVertex2f(0.74f, -0.65f);
    glVertex2f(0.72f, -0.65f);
    glEnd();

    // Right leg border
    glColor3f(0.2f, 0.1f, 0.05f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.72f, -0.55f);
    glVertex2f(0.74f, -0.55f);
    glVertex2f(0.74f, -0.65f);
    glVertex2f(0.72f, -0.65f);
    glEnd();

    // [Previous flower bed code remains the same]
    // Pink rhombus flower
    glColor3f(1.0f, 0.4f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -0.4f);
    glVertex2f(-0.7f, -0.5f);
    glVertex2f(-0.8f, -0.6f);
    glVertex2f(-0.9f, -0.5f);
    glEnd();

    // Yellow hexagon flower
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 6; i++) {
        float angle = i * 60 * 3.14159f / 180.0f;
        glVertex2f(-0.6f + cos(angle) * 0.05f,
                  -0.5f + sin(angle) * 0.05f);
    }
    glEnd();

    // Flower stems
    glColor3f(0.0f, 0.5f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.8f, -0.6f);
    glVertex2f(-0.8f, -0.7f);
    glVertex2f(-0.6f, -0.55f);
    glVertex2f(-0.6f, -0.7f);
    glEnd();

    // Small scattered flowers
    float flowerPositions[][2] = {
        {0.3f, -0.8f}, {-0.7f, -0.9f}, {0.1f, -0.7f}, {-0.5f, -0.8f},
        {-0.2f, -0.9f}, {0.0f, -0.85f}, {-0.9f, -0.7f}, {0.4f, -0.9f},
        {-0.4f, -0.7f}, {0.2f, -0.95f}, {-0.8f, -0.85f}, {0.5f, -0.75f},
        {-0.3f, -0.75f}, {0.6f, -0.85f}, {-0.6f, -0.95f}, {0.7f, -0.9f}
    };

    float flowerColors[][3] = {
        {1.0f, 0.3f, 0.3f},   // Red
        {1.0f, 0.6f, 0.8f},   // Pink
        {0.8f, 0.4f, 1.0f},   // Purple
        {0.4f, 0.8f, 1.0f},   // Light blue
        {1.0f, 0.8f, 0.4f}    // Light yellow
    };

    for(int f = 0; f < 16; f++) {
        int colorIndex = f % 5;
        glColor3f(flowerColors[colorIndex][0],
                 flowerColors[colorIndex][1],
                 flowerColors[colorIndex][2]);

        glBegin(GL_POLYGON);
        for(int i = 0; i < 5; i++) {
            float angle = i * 72 * 3.14159f / 180.0f;
            glVertex2f(flowerPositions[f][0] + cos(angle) * 0.03f,
                      flowerPositions[f][1] + sin(angle) * 0.03f);
        }
        glEnd();

        glColor3f(1.0f, 1.0f, 0.0f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2f(flowerPositions[f][0], flowerPositions[f][1]);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ground
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();

    drawSun();
    drawClouds();
    drawGarden();
    drawHouse();

    glPushMatrix();
    glTranslatef(0.5f, -0.1f, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    drawWindmill();
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    // Update animations
    sunRotation += 2.0f;
    if(sunRotation > 360.0f) {
        sunRotation -= 360.0f;
    }

    // Update first cloud position
    cloudPosition1 += 0.01f;
    if(cloudPosition1 > 1.5f) {
        cloudPosition1 = -1.5f;
    }

    // Update second cloud position (slightly different speed)
    cloudPosition2 += 0.008f;
    if(cloudPosition2 > 1.5f) {
        cloudPosition2 = -1.5f;
    }

    windmillRotation -= 5.0f;
    if(windmillRotation < 360.0f) {
        windmillRotation += 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Habiba's Farm");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
