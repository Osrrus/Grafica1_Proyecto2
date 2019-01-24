#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "Obj.h"
#include "light.h"
#include "UserInterface.h"
#include <iostream> 
#include <fstream> 
#include <string>

using namespace std;
using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CUserInterface * userInterface;
light *mlight[2];
vector <CModel *> models;
int picked, lastPicked;
glm::vec3 scale;
float scaleAll;
string typeDisplay = "glbeg", cameraType = "perspective",shadowType = "null";
bool backFace;

void initInterfazLight() {

	userInterface->setLAmbientColor(mlight[0]->getAmbientColor(),0);
	userInterface->setLDifuseColor(mlight[0]->getDiffuseColor(),0);
	userInterface->setLSpecularColor(mlight[0]->getSpecularColor(),0);
	userInterface->setLOn(0,mlight[0]->getOn());
	userInterface->setLPosition(mlight[0]->getPosition(),0);

	userInterface->setLAmbientColor(mlight[1]->getAmbientColor(),1);
	userInterface->setLDifuseColor(mlight[1]->getDiffuseColor(),1);
	userInterface->setLSpecularColor(mlight[1]->getSpecularColor(),1);
	userInterface->setLOn(1,mlight[1]->getOn());
	userInterface->setLPosition(mlight[1]->getPosition(),1);

}

void ConvertQuaternionToMatrix(glm::vec4 quat, float *mat)
{
	float yy2 = 2.0f * quat[1] * quat[1];
	float xy2 = 2.0f * quat[0] * quat[1];
	float xz2 = 2.0f * quat[0] * quat[2];
	float yz2 = 2.0f * quat[1] * quat[2];
	float zz2 = 2.0f * quat[2] * quat[2];
	float wz2 = 2.0f * quat[3] * quat[2];
	float wy2 = 2.0f * quat[3] * quat[1];
	float wx2 = 2.0f * quat[3] * quat[0];
	float xx2 = 2.0f * quat[0] * quat[0];
	mat[0 * 4 + 0] = -yy2 - zz2 + 1.0f;
	mat[0 * 4 + 1] = xy2 + wz2;
	mat[0 * 4 + 2] = xz2 - wy2;
	mat[0 * 4 + 3] = 0;
	mat[1 * 4 + 0] = xy2 - wz2;
	mat[1 * 4 + 1] = -xx2 - zz2 + 1.0f;
	mat[1 * 4 + 2] = yz2 + wx2;
	mat[1 * 4 + 3] = 0;
	mat[2 * 4 + 0] = xz2 + wy2;
	mat[2 * 4 + 1] = yz2 - wx2;
	mat[2 * 4 + 2] = -xx2 - yy2 + 1.0f;
	mat[2 * 4 + 3] = 0;
	mat[3 * 4 + 0] = mat[3 * 4 + 1] = mat[3 * 4 + 2] = 0;
	mat[3 * 4 + 3] = 1;
}

void updateUserInterface()
{

	if (userInterface->getSelectModel() >= models.size()) {

		userInterface->setSelectModel(models.size()-1);

	}

	picked = userInterface->getSelectModel();
	scaleAll = userInterface->getScaleAll();

	if (scale[0] != scaleAll) {

		scale[0] = scaleAll;
		scale[1] = scaleAll;
		scale[2] = scaleAll;

		userInterface->setModelScale(scale);
	}

	if (lastPicked != picked) {

		userInterface->setModelTranslation(models[picked]->getTranslation());
		userInterface->setModelScale(models[picked]->getScale());
		userInterface->setModelRotation(models[picked]->getRotation());

		userInterface->setBondingColor(models[picked]->getBColor());
		userInterface->setBondingVisible(models[picked]->getVBonding());

		userInterface->setModelColor(models[picked]->getMColor());
		userInterface->setModelVisible(models[picked]->getVModel());

		userInterface->setWireColor(models[picked]->getWColor());
		userInterface->setWireVisible(models[picked]->getVWire());

		userInterface->setPointsColor(models[picked]->getPColor());
		userInterface->setPointsVisible(models[picked]->getVPoints());

		userInterface->setNormalsColor(models[picked]->getNColor());
		userInterface->setNormalsVisible(models[picked]->getVNormals());

		userInterface->setVertexNormalsColor(models[picked]->getNVColor());
		userInterface->setVertexNormalsVisible(models[picked]->getVNormalsVercetor());

		userInterface->setScaleAll(1.0f);

		lastPicked = picked;
		
	}

	models[picked]->setTranslation(userInterface->getModelTranslation());
	models[picked]->setScale(userInterface->getModelScale());
	models[picked]->setRotation(userInterface->getModelRotation());

	models[picked]->setMColor(userInterface->getModelColor());
	models[picked]->setVModel(userInterface->getModelVisible());

	models[picked]->setBColor(userInterface->getBondingColor());
	models[picked]->setVBonding(userInterface->getBondingVisible());

	models[picked]->setPColor(userInterface->getPointsColor());
	models[picked]->setVPoints(userInterface->getPointsVisible());

	models[picked]->setWColor(userInterface->getWireColor());
	models[picked]->setVWire(userInterface->getWireVisible());

	models[picked]->setNColor(userInterface->getNormalsColor());
	models[picked]->setVNormals(userInterface->getNormalsVisible());

	models[picked]->setNVColor(userInterface->getVertexNormalsColor());
	models[picked]->setVNormalsVercetor(userInterface->getVertexNormalsVisible());

	typeDisplay = userInterface->getDeployType();
	cameraType = userInterface->getCameraType();
	shadowType = userInterface->getShadowType();
	backFace = userInterface->getBackFace();

	mlight[0]->setAmbientColor(userInterface->getLAmbientColor(0));
	mlight[0]->setDiffuseColor(userInterface->getLDifuseColor(0));
	mlight[0]->setSpecularColor(userInterface->getLSpecularColor(0));
	mlight[0]->setOn(userInterface->getLOn(0));
	mlight[0]->setPosition(userInterface->getLPosition(0));

	mlight[1]->setAmbientColor(userInterface->getLAmbientColor(1));
	mlight[1]->setDiffuseColor(userInterface->getLDifuseColor(1));
	mlight[1]->setSpecularColor(userInterface->getLSpecularColor(1));
	mlight[1]->setOn(userInterface->getLOn(1));
	mlight[1]->setPosition(userInterface->getLPosition(1));

}

void display()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	reshape(gWindow, gWidth, gHeight);

	if (shadowType == "smoth") {
		glShadeModel(GL_SMOOTH);

	}
	else if (shadowType == "flat") {

		glShadeModel(GL_FLAT);

	}

	if (backFace) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	for (unsigned int i = 0; i < models.size(); i++)
	{	
		float mat[4 * 4];
		glm::vec3 translation = models[i]->getTranslation();
		glm::vec3 scale = models[i]->getScale();
		glm::vec4 rotation = models[i]->getRotation();
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glPushMatrix();

			glTranslatef(translation.x, translation.y, translation.z);
			ConvertQuaternionToMatrix(rotation, mat);
			glMultMatrixf(mat);
			glScalef(scale.x,scale.y,scale.z);
			if (mlight[0]->getOn() || mlight[1]->getOn()) {

				glEnable(GL_LIGHTING);
				glEnable(GL_NORMALIZE);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_COLOR_MATERIAL);

				mlight[0]->displayLight();
				mlight[1]->displayLight();
			}
			else {

				glDisable(GL_NORMALIZE);
				glDisable(GL_LIGHTING);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_COLOR_MATERIAL);
				mlight[0]->displayLight();
				mlight[1]->displayLight();

			}
			

			if (typeDisplay == "glBE" && models[i]->getVModel()) {
				if (shadowType == "flat") {
					models[i]->displayBE();
				}
				else {
					models[i]->displayBES();
				}
			}
			else if (typeDisplay == "VBO" && models[i]->getVModel()) {
				//models[i]->createVBO();

				//models[i]->displayVBO();

			}
			else if (typeDisplay == "VP" && models[i]->getVModel()) {

				models[i]->displaVA();
			}

			else if(models[i]-> getVModel()){

				if (shadowType == "flat") {
					models[i]->displayDL();
				}
				else {

					models[i]->displayDLS();
				}
			}
		

			if (models[i]->getVBonding()) {

				models[i]->displayBondingBox();

			}

			if (models[i]->getVWire()) {

				models[i]->displayWire();

			}

			if (models[i]->getVPoints()) {

				models[i]->displayPoints();

			}

			if (models[i]->getVNormals()) {

				models[i]->displayNormalsFace();

			}
			if (models[i]->getVNormalsVercetor()) {

				models[i]->displayNormalsVertex();

			}

		glPopMatrix();
	}
		
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (cameraType == "perspective") {

		gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

	}
	else {
		glOrtho(-10, 10, -10, 10, 1, 1000);
	}

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 2", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

bool initScene()
{
	Obj * obj = new Obj();
	Obj * obj2 = new Obj();
	Obj * obj3 = new Obj();

	if (!obj->load("../files/sphere.obj"))
		return false;

	if (!obj2->load("../files/sphere.obj"))
		return false;

	if (!obj3->load("../files/Batman.obj"))
		return false;

	models.push_back(obj);
	models.push_back(obj2);
	models.push_back(obj3);

	mlight[0] = new light(0,obj);
	mlight[1] = new light(1,obj2);

	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	picked = 0;
	lastPicked = -1;


	if (!initGlfw() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;


	glEnable(GL_DEPTH_TEST);

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	initInterfazLight();
	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}

void beginLoad(string path) {
	string aux = path;
	string extension = aux.erase(0, aux.find(".") + 1);
	//Caso archivo OFF:
	if (extension == "off" || extension == "OFF") {
		CSOff* off = new CSOff();
		if (!off->load(path))
			return;
		models.push_back(off);
	}
	//Caso archivo OBJ:
	else if (extension == "obj" || extension == "OBJ") {
		Obj* cobj = new Obj();
		if (!cobj->load(path))
			return;
		models.push_back(cobj);
	}
}