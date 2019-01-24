#include "SOff.h"

CSOff::CSOff()
{
}

CSOff::~CSOff()
{
}

bool CSOff::load(string path)
{
	fstream file;
	string token, v1, v2, v3;
	unsigned int yuliana,con = 0;
	float fv1, fv2, fv3;
	
	maxX = maxY = maxZ = -10000;
	
	minX = minY = minZ = 100000;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF" && token !=  "OFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;
		mNumOfVertices = atoi(token.c_str());

		file >> token;
		mNumOfFaces = atoi(token.c_str());

		file >> token;
		mNumOfEdges = atoi(token.c_str());

		for (int i = 0; i < mNumOfVertices; i++)
		{

			file >> v1;
			file >> v2;
			file >> v3;

			fv1 = atof(v1.c_str());
			fv2 = atof(v2.c_str());
			fv3 = atof(v3.c_str());

			if (maxX < fv1) {
				maxX = fv1;
			}
			if (minX > fv1) {
				minX = fv1;
			}
			if (maxY < fv2) {
				maxY = fv2;
			}
			if (minY > fv2) {
				minY = fv2;
			}
			if (maxZ < fv3) {
				maxZ = fv3;
			}
			if (minZ > fv3) {
				minZ = fv3;
			}

			mVertices.push_back(glm::vec3(fv1, fv2, fv3));
		}

		for (int i = 0; i < mNumOfFaces; i++)
		{	
			file >> v1;
			yuliana = atof(v1.c_str())-2;
			file >> v1;
			file >> v3;
			for (int j = 0; j < yuliana; j++) {

				v2 = v3;
				file >> v3;
				mFaces.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
				con++;
			}

			getline(file,token);
			
			
		}
		mNumOfFaces = con;

		float cX, cY, cZ, Tmax;
		cX = (maxX + minX) / 2;
		cY = (maxY + minY) / 2;
		cZ = (maxZ + minZ) / 2;

		Tmax = maxX;
		if (Tmax < maxY) {
			Tmax = maxY;
			
		}
		if (Tmax < maxZ) {
			Tmax = maxZ;
		}

		for (int i = 0; i < mNumOfVertices; i++) {
			mVertices[i].x = (mVertices[i].x - cX) / Tmax;
			mVertices[i].y = (mVertices[i].y - cY) / Tmax;
			mVertices[i].z = (mVertices[i].z - cZ) / Tmax;
		}

		file.close();
		createNormalFace();
		createDL();

		mMax.x = (maxX - cX) / Tmax;
		mMax.y = (maxY - cY) / Tmax;
		mMax.z = (maxZ - cZ) / Tmax;

		mMin.x = (minX - cX) / Tmax;
		mMin.y = (minY - cY) / Tmax;
		mMin.z = (minZ - cZ) / Tmax;

		return true;
	}
}

void CSOff::displayBE() {

	glColor3f(mColor[0], mColor[1], mColor[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	for (int i = 0; i < mNumOfFaces; i++) {

		glNormal3f(mNormalsFaces[i].x, mNormalsFaces[i].y, mNormalsFaces[i].z);

		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
		glEnd();
	}
}

void CSOff::createDL() {

	list[0] = glGenLists(1);//smot
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glNewList(list[0], GL_COMPILE);
		for (int i = 0; i < mNumOfFaces; i++) {
			glNormal3f(mNormalsFaces[i].x, mNormalsFaces[i].y, mNormalsFaces[i].z);
			glBegin(GL_TRIANGLES);
				glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
				glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
				glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
			glEnd();
		}
	glEndList();

	list[1] = glGenLists(1);//flat

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glNewList(list[1], GL_COMPILE);
	for (int i = 0; i < mNumOfFaces; i++) {

		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glNormal3f(normalVertex[mFaces[i].x].x, normalVertex[mFaces[i].x].y, normalVertex[mFaces[i].x].z);

			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glNormal3f(normalVertex[mFaces[i].y].x, normalVertex[mFaces[i].y].y, normalVertex[mFaces[i].y].z);

			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
			glNormal3f(normalVertex[mFaces[i].z].x, normalVertex[mFaces[i].z].y, normalVertex[mFaces[i].z].z);
		glEnd();
	}
	glEndList();

}

void CSOff::displayDL() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glCallList(list[1]);
}