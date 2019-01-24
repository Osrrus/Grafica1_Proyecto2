#pragma once
#include "../headers/GL/glew.h"
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::map;

class CModel
{
	protected:
		vector<glm::vec3> mVertices,mFaces,mNormalsFaces,mNormalsVertex;
		glm::vec3 mTranslation;
		glm::vec3 mScale;
		glm::vec4 mRotation;
		glm::vec3 mMax;
		glm::vec3 mMin;
		GLint list[2];
		map <int,glm::vec3> normalVertex;
		GLuint colours_vbo, points_vbo;
		GLuint vbo;
		GLuint vindex;
		GLint normalsList[2];
		float maxX, maxY, maxZ;
		float minX, minY, minZ;
		int mNumOfVertices,mNumOfFaces,mNumOfEdges;
		bool vBonding,vWire,vPoints,vNormals,vModel,vNormalsVercetor;
		GLfloat ambient[4] = { 0.4f, 0.2f, 0.0f, 1.0f };
		GLfloat specular[4] = { 0.1F, 0.1F, 0.0F, 1.0F };
		GLfloat diffuse[4] = { 0.9F, 0.5F, 0.0F, 1.0F };
		GLfloat shininess[1] = { 0.0F };
		glm::vec3 mColor, nColor,nvColor, wColor, pColor, bColor;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void displayBE();
		virtual void displayBES();
		virtual void displayDL();
		virtual void displayDLS();
		virtual void displayVBO();
		void displayBondingBox();
		void createVBO();
		void displaVA();
		void displayWire();
		void displayNormalsFace();
		void displayNormalsVertex();
		void displayPoints();
		void setTranslation(glm::vec3 translation);
		void setScale(glm::vec3 scale);
		void setRotation(glm::vec4 rotation);
		void setMColor(glm::vec3);
		void setNColor(glm::vec3);
		void setNVColor(glm::vec3 color);
		void setWColor(glm::vec3);
		void setPColor(glm::vec3);
		void setBColor(glm::vec3);
		void setVBonding(bool);
		void setVPoints(bool a);
		void setVWire(bool a);
		void setVNormals(bool a);
		void setVNormalsVercetor(bool a);
		void setVModel(bool a);
		void createNormalFace();
		void createNormalVertex();
		glm::vec3 getTranslation();
		glm::vec3 getScale();
		glm::vec4 getRotation();
		glm::vec3 getMColor();
		glm::vec3 getNColor();
		glm::vec3 getNVColor();
		glm::vec3 getWColor();
		glm::vec3 getPColor();
		glm::vec3 getBColor();
		bool getVBonding();
		bool getVPoints();
		bool getVWire();
		bool getVNormals();
		bool getVNormalsVercetor();
		bool getVModel();
};