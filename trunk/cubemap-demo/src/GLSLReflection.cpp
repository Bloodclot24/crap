#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_TITLE "GLSL SkyBox"
#define SHADER_PATH "./shaders/"
#define SKYBOX_VS SHADER_PATH"SkyBox.vsh"
#define SKYBOX_FS SHADER_PATH"SkyBox.fsh"
#define REFLECTION_VS SHADER_PATH"Reflection.vsh"
#define REFLECTION_FS SHADER_PATH"Reflection.fsh"
#define TEXTURE_PATH "./textures/cubemaps/bright_day/"

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;

void initShaders();
void initGL();
void initTextures();

GLuint cubemap;

string cubemapPaths[6] = {TEXTURE_PATH"positive_x.png", TEXTURE_PATH"negative_x.png", TEXTURE_PATH"positive_y.png",
    TEXTURE_PATH"negative_y.png", TEXTURE_PATH"positive_z.png", TEXTURE_PATH"negative_z.png"};

GLuint skyBoxProg, reflectionProg;

void reshapeFunc(int w, int h)
{
    if (h==0)
        h=1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void displayFunc()
{
    static float rot = 0.0f;
	rot += 0.0005f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-sinf(rot) * 10, cosf(rot) * 30, 20 + sinf(rot) * 20, 0, 0, 0, 0, 1, 0);
	int uni1,uni2;
	uni1=glGetUniformLocation(skyBoxProg, "cubeMap");
	//glUniform1ui(uni1, cubemap);
	uni2=glGetUniformLocation(reflectionProg, "cubeMap");
	//glUniform1ui(uni2, cubemap);
	glPushMatrix();
    glUseProgram(skyBoxProg);
	glutSolidCube(90);
	glUseProgram(0);
	glPopMatrix();
	glUseProgram(reflectionProg);
	glutSolidSphere(3, 32, 32);
	glUseProgram(0);
	glutSwapBuffers();
	glutPostRedisplay();
}

char* loadFileToString(const char *path)
{
    char* data;
    int len;
    ifstream myfile(path);
    if (myfile.is_open())
    {
        myfile.seekg(0, ios::end);
        len = myfile.tellg();
        myfile.seekg(0, ios::beg);
        data = new char[len];
        while ( myfile.good() )
        {
            myfile.read(data, len);
        }
        data[len] = 0;
        cout << "File '" << path << "' has been read" << endl;
        myfile.close();
    }
    else cout << "Unable to open file";

    return data;
}

void printLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength;

	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);

	char infoLog[maxLength];

	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

	if (infologLength > 0)
		cout << infoLog << endl;
}

void initGL()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    initShaders();
    initTextures();
}

void initShaders()
{
    GLuint skyBoxFS, skyBoxVS, reflectionFS, reflectionVS;
    const GLchar* skyBoxFSSource = loadFileToString(SKYBOX_FS);
    const GLchar* skyBoxVSSource = loadFileToString(SKYBOX_VS);
    const GLchar* reflectionFSSource = loadFileToString(REFLECTION_FS);
    const GLchar* reflectionVSSource = loadFileToString(REFLECTION_VS);

    glewInit();

    skyBoxFS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skyBoxFS, 1, &skyBoxFSSource, NULL);
    glCompileShader(skyBoxFS);
    printLog(skyBoxFS);

    skyBoxVS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(skyBoxVS, 1, &skyBoxVSSource, NULL);
	glCompileShader(skyBoxVS);
	printLog(skyBoxVS);

	skyBoxProg = glCreateProgram();
	glAttachShader(skyBoxProg, skyBoxVS);
	glAttachShader(skyBoxProg, skyBoxFS);
	glLinkProgram(skyBoxProg);
	printLog(skyBoxProg);

	reflectionFS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(reflectionFS, 1, &reflectionFSSource, NULL);
    glCompileShader(reflectionFS);
    printLog(reflectionFS);

    reflectionVS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(reflectionVS, 1, &reflectionVSSource, NULL);
	glCompileShader(reflectionVS);
	printLog(reflectionVS);

	reflectionProg = glCreateProgram();
	glAttachShader(reflectionProg, reflectionVS);
	glAttachShader(reflectionProg, reflectionFS);
	glLinkProgram(reflectionProg);
	printLog(reflectionProg);
}

void initTextures()
{
    ILuint ilTex;
    ilInit();
    glGenTextures(1, &cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    for (int i = 0; i < 6; i++)
    {
        ilGenImages(1, &ilTex);
        ilBindImage(ilTex);
        ilLoadImage(cubemapPaths[i].c_str());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
          ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    glutInitWindowPosition(0, 0);

    glutCreateWindow(DEFAULT_TITLE);

    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);

    initGL();

    glutMainLoop();
    return 0;
}
