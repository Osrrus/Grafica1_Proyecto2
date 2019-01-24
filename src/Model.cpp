#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 1.0;
	mRotation[0] = mRotation[1] = mRotation[2] = 0.0f;
	mRotation[3] = 1.0f;

	mColor[0] = mColor[1] = mColor[2] = 196.0f;
	nColor[0] = nColor[1] = nColor[2] = 196.0f;
	wColor[0] = wColor[1] = wColor[2] = 196.0f;
	pColor[0] = pColor[1] = pColor[2] = 196.0f;
	bColor[0] = bColor[2] = 0.0f;
	bColor[1] = 255.0f;

	vWire = vPoints = vNormals = vBonding = false;
	vModel = true;
}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::displayBondingBox() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(bColor[0],bColor[1],bColor[2]);

	glBegin(GL_QUADS);
	//front
		glVertex3f(mMin.x, mMax.y, mMax.z);
		glVertex3f(mMax.x, mMax.y, mMax.z);
		glVertex3f(mMax.x, mMin.y, mMax.z);
		glVertex3f(mMin.x, mMin.y, mMax.z);

	//back
		glVertex3f(mMin.x, mMax.y, mMin.z);
		glVertex3f(mMax.x, mMax.y, mMin.z);
		glVertex3f(mMax.x, mMin.y, mMin.z);
		glVertex3f(mMin.x, mMin.y, mMin.z);

	//top
		glVertex3f(mMin.x, mMax.y, mMax.z);
		glVertex3f(mMax.x, mMax.y, mMax.z);
		glVertex3f(mMax.x, mMax.y, mMin.z);
		glVertex3f(mMin.x, mMax.y, mMin.z);

	//bot
		glVertex3f(mMin.x, mMin.y, mMax.z);
		glVertex3f(mMax.x, mMin.y, mMax.z);
		glVertex3f(mMax.x, mMin.y, mMin.z);
		glVertex3f(mMin.x, mMin.y, mMin.z);

	//left
		glVertex3f(mMin.x, mMax.y, mMin.z);
		glVertex3f(mMin.x, mMax.y, mMax.z);
		glVertex3f(mMin.x, mMin.y, mMin.z);
		glVertex3f(mMin.x, mMin.y, mMax.z);

	//rigth
		glVertex3f(mMax.x, mMax.y, mMin.z);
		glVertex3f(mMax.x, mMax.y, mMax.z);
		glVertex3f(mMax.x, mMin.y, mMin.z);
		glVertex3f(mMax.x, mMin.y, mMax.z);

	glEnd();

}

void CModel::createVBO() {

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vindex);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
}


void CModel::displayVBO() {

}

void CModel::displaVA() {
	float x, y, z;
	x = y = z = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(mVertices), &mVertices);
	glColorPointer(3, GL_FLOAT, sizeof(mColor), &mColor);
	glDrawElements(GL_TRIANGLES,3,GL_FLOAT,&mFaces);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void CModel::displayWire()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(wColor[0],wColor[1],wColor[2]);

	glBegin(GL_TRIANGLES);

		for (int i = 0; i < mNumOfFaces; i++) {

			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);

		}

	glEnd();
}

void CModel::displayNormalsVertex()
{

	glColor3f(nvColor[0], nvColor[1], nvColor[2]);
	glCallList(normalsList[1]);

}

void CModel::displayNormalsFace()
{

	glColor3f(nColor[0], nColor[1], nColor[2]);
	glCallList(normalsList[0]);

}

void CModel::displayPoints()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glColor3f(pColor[0], pColor[1], pColor[2]);
	glPointSize(5.0);

	glBegin(GL_TRIANGLES);

		for (int i = 0; i < mNumOfFaces; i++) {

			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);

		}

	glEnd();

	glPointSize(1.0);
}

void CModel::displayBE()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0.0f, 0.0f, 0.0f);
}	

void CModel::displayDL()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0.0f, 0.0f, 0.0f);
}

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

void CModel::setScale(glm::vec3 scale)
{
	mScale = scale;
}

void CModel::setRotation(glm::vec4 rotation)
{
	mRotation = rotation;
}

void  CModel::setMColor(glm::vec3 color) {

	mColor = color;
}

void  CModel::setNColor(glm::vec3 color) {

	nColor = color;

}

void  CModel::setNVColor(glm::vec3 color) {

	nvColor = color;

}

void  CModel::setWColor(glm::vec3 color) {

	wColor = color;

}

void  CModel::setPColor(glm::vec3 color) {

	pColor = color;

}

void  CModel::setBColor(glm::vec3 color) {

	bColor = color;

}

void CModel::setVBonding(bool a) {

	vBonding = a;
}

void CModel::setVPoints(bool a) {

	vPoints = a;
}

void CModel::setVWire(bool a) {

	vWire = a;
}

void CModel::setVNormals(bool a) {

	vNormals = a;
}

void CModel::setVModel(bool a) {

	vModel = a;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

glm::vec3 CModel::getScale()
{
	return mScale;
}

glm::vec4 CModel::getRotation()
{
	return mRotation;
}

glm::vec3 CModel::getMColor() {

	return mColor;

}

glm::vec3 CModel::getNColor() {

	return nColor;

}

glm::vec3 CModel::getNVColor() {

	return nvColor;

}

glm::vec3 CModel::getWColor() {

	return wColor;

}

glm::vec3 CModel::getPColor() {

	return pColor;

}

glm::vec3 CModel::getBColor() {

	return bColor;

}

bool CModel::getVBonding() {

	return vBonding;

}

bool CModel::getVPoints() {

	return vPoints;

}

bool CModel::getVWire() {

	return vWire;

}

bool CModel::getVNormals() {

	return vNormals;

}

bool CModel::getVModel() {

	return vModel;

}

bool CModel::getVNormalsVercetor() {

	return vNormalsVercetor;
}

void CModel::setVNormalsVercetor(bool a) {
	
	vNormalsVercetor = a;

}

glm::vec3 normNormal(glm::vec3 v)
{
	float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	for (int i = 0; i < 3; i++)
	{
		v[i] = v[i] / length;
	}

	return v;
}

void CModel::createNormalFace() {
	
	map<int,float>averague;
	glm::vec3 a, b,n;

	for (int i = 0; i < mNumOfFaces; i++) {

		a = mVertices[mFaces[i].x] - mVertices[mFaces[i].y];
		b = mVertices[mFaces[i].x] - mVertices[mFaces[i].z];
		

		n = glm::cross(a, b);
		n = glm::normalize(n);
		mNormalsFaces.push_back(n);

		if (!normalVertex.count(mFaces[i].x)) {
			averague[mFaces[i].x] = 1.0f;
			normalVertex[mFaces[i].x] = n;
		}
		else {
			averague[mFaces[i].x]++;
			normalVertex[mFaces[i].x] += n;
		}

		if (!normalVertex.count(mFaces[i].y)) {
			averague[mFaces[i].y] = 1.0f;
			normalVertex[mFaces[i].y] = n;
		}
		else {
			averague[mFaces[i].y]++;
			normalVertex[mFaces[i].y] += n;
		}

		if (!normalVertex.count(mFaces[i].z)) {
			averague[mFaces[i].z] = 1.0f;
			normalVertex[mFaces[i].z] = n;
		}
		else {
			averague[mFaces[i].z]++;
			normalVertex[mFaces[i].z] += n;
		}
	}

	for (int i = 0; i < mNumOfFaces; i++) {

		normalVertex[i].x = normalVertex[i].x / averague[i];
		normalVertex[i].y = normalVertex[i].y / averague[i];
		normalVertex[i].z = normalVertex[i].z / averague[i];

		normalVertex[i] = normNormal(normalVertex[i]);
	
	}
	averague.clear();

	normalsList[0] = glGenLists(1);

	glNewList(normalsList[0], GL_COMPILE);
		glBegin(GL_LINES);
			for (int i = 0; i < mNumOfFaces; i++) {

				a.x = (mVertices[mFaces[i].x].x + mVertices[mFaces[i].y].x + mVertices[mFaces[i].z].x) / 3.0f;
				a.y = (mVertices[mFaces[i].x].y + mVertices[mFaces[i].y].y + mVertices[mFaces[i].z].y) / 3.0f;
				a.z = (mVertices[mFaces[i].x].z + mVertices[mFaces[i].y].z + mVertices[mFaces[i].z].z) / 3.0f;

				glVertex3f(a.x, a.y, a.z);
				glVertex3f((mNormalsFaces[i].x + a.x)*0.85f, (mNormalsFaces[i].y + a.y)*0.85f, (mNormalsFaces[i].z + a.z)*0.85f);

			}
		glEnd();
	glEndList();

	createNormalVertex();
}

void CModel::createNormalVertex() {

	normalsList[1] = glGenLists(1);
	glNewList(normalsList[1], GL_COMPILE);
		glBegin(GL_LINES);
			for (int i = 0; i < mNumOfVertices; i++) {

				glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
				glVertex3f((normalVertex[i].x + mVertices[i].x), (normalVertex[i].y + mVertices[i].y), (normalVertex[i].z + mVertices[i].z));

			}
		glEnd();
	glEndList();
}

void  CModel::displayBES() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glColor3f(mColor[0], mColor[1], mColor[2]);

	for (int i = 0; i < mNumOfFaces; i++) {
		glNormal3f(mNormalsFaces[i].x, mNormalsFaces[i].y, mNormalsFaces[i].z);
		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
		glEnd();
	}
}

void  CModel::displayDLS() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glCallList(list[0]);
}