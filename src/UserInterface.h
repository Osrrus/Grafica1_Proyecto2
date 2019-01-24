#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <string>

using std::string;
typedef enum { GL_BEGIN_GL_END, DISPLAY_LIST, VERTEX_POINTER, VBO } DEPLOY_TYPE;
typedef enum { PERSPECTIVE, ORTHO} CAMERA_TYPE;
typedef enum { FLAT, SMOOTH} SHADOW_TYPE;

//Singleton user interface class

class CUserInterface
{
private:

	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;
	glm::vec3 mModelScale;
	glm::vec4 mModelRotation;
	glm::vec3 mBondingColor, mModelColor, mWireColor, mPointsColor, mNormalsColor, mVertexNormalsColor;
	glm::vec3 lAmbientColor[2],lDifuseColor[2],lSpecularColor[2],lPosition[2];
	bool lOn[2];
	bool mBondingVisible, mPointsVisible, mWireVisible, mNormalsVisible, mModelVisible, mVertexNormalsVisible,backFace;
	float mScaleAll;
	int mModelSelect;
	string mDeployMode;
	DEPLOY_TYPE m_currentDeploy;
	CAMERA_TYPE m_cameraType;
	SHADOW_TYPE m_shadowType;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(glm::vec3);
	void setModelScale(glm::vec3 modelScale);
	void setModelRotation(glm::vec4 modelRotation);
	void setBondingColor(glm::vec3 Color);
	void setModelColor(glm::vec3 Color);
	void setWireColor(glm::vec3 Color);
	void setPointsColor(glm::vec3 Color);
	void setNormalsColor(glm::vec3 Color);
	void setVertexNormalsColor(glm::vec3 Color);
	void setScaleAll(float v);
	void setBondingVisible(bool v);
	void setLOn(int a, bool v);
	void setPointsVisible(bool v);
	void setWireVisible(bool v);
	void setNormalsVisible(bool v);
	void setVertexNormalsVisible(bool v);
	void setModelVisible(bool v);
	void setSelectModel(int v);
	glm::vec3 getModelTranslation();
	glm::vec3 getModelScale();
	glm::vec4 getModelRotation();
	glm::vec3 getBondingColor();
	glm::vec3 getModelColor();
	glm::vec3 getWireColor();
	glm::vec3 getPointsColor();
	glm::vec3 getNormalsColor();
	glm::vec3 getVertexNormalsColor();
	bool getBondingVisible();
	bool getPointsVisible();
	bool getWireVisible();
	bool getNormalsVisible();
	bool getVertexNormalsVisible();
	bool getModelVisible();
	int getSelectModel();
	float getScaleAll();
	string getDeployType();
	string getCameraType();

	void setLAmbientColor(glm::vec3 Color,int p);
	void setLSpecularColor(glm::vec3 Color,int p);
	void setLDifuseColor(glm::vec3 Color,int p);
	void setLPosition(glm::vec3 position,int p);
	glm::vec3 getLAmbientColor(int p);
	glm::vec3 getLSpecularColor(int p);
	glm::vec3 getLDifuseColor(int p);
	glm::vec3 getLPosition(int p);

	bool getLOn(int a);

	string getShadowType();

	bool getBackFace();

private:
	///Private constructor
	CUserInterface(); 
};