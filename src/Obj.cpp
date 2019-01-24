#include "Obj.h"

Obj::Obj()
{
}


Obj::~Obj()
{
}

bool Obj::load(string path) {

	fstream file;
	string token, v1, v2, v3;

	file.open(path, std::ios::in);

	file >> token;
	float fv1, fv2, fv3;
	maxX = maxY = maxZ = -1000000;
	minX = minY = minZ = 1000000;
	size_t found;

	while (!file.eof()) {

		if (token == "v") {

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
			mNumOfVertices++;

		}
		else if (token == "f") {

			file >> v1;
			found = v1.find("/");
			if(found != std::string::npos)
				v1 = v1.substr(0, found);

			file >> v2;
			found = v2.find("/");
			if (found != std::string::npos)
				v2 = v2.substr(0, found);

			file >> v3;
			found = v3.find("/");
			if (found != std::string::npos)
				v3 = v3.substr(0, found);

			fv1 = atof(v1.c_str());
			fv2 = atof(v2.c_str());
			fv3 = atof(v3.c_str());

			mFaces.push_back(glm::vec3(fv1 - 1, fv2 - 1, fv3 - 1));
			mNumOfFaces++;
		}

		file >> token;
	}

	file.close();

	float cX, cY, cZ, Tmax;

	cX = (maxX + minX)/2;
	cY = (maxY + minY)/2;
	cZ = (maxZ + minZ)/2;

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

	mMax[0] = ( maxX - cX) / Tmax;
	mMax[1] = ( maxY - cY) / Tmax;
	mMax[2] = ( maxZ - cZ) / Tmax;

	mMin[0] = ( minX - cX)/ Tmax;
	mMin[1] = ( minY - cY)/ Tmax;
	mMin[2] = ( minZ - cZ)/ Tmax;

	createNormalFace();
	createDL();


	return true;
}

void Obj::displayBE() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glColor3f(mColor[0],mColor[1],mColor[2]);

	for (int i = 0; i < mNumOfFaces; i++) {

		//glNormal3f(mNormalsFaces[i].x, mNormalsFaces[i].y, mNormalsFaces[i].z);
		glBegin(GL_TRIANGLES);

			glVertex3f(mVertices[mFaces[i].x].x, mVertices[mFaces[i].x].y, mVertices[mFaces[i].x].z);
			glNormal3f(normalVertex[mFaces[i].x].x, normalVertex[mFaces[i].x].y, normalVertex[mFaces[i].x].z);

			glVertex3f(mVertices[mFaces[i].y].x, mVertices[mFaces[i].y].y, mVertices[mFaces[i].y].z);
			glNormal3f(normalVertex[mFaces[i].y].x, normalVertex[mFaces[i].y].y, normalVertex[mFaces[i].y].z);

			glVertex3f(mVertices[mFaces[i].z].x, mVertices[mFaces[i].z].y, mVertices[mFaces[i].z].z);
			glNormal3f(normalVertex[mFaces[i].z].x, normalVertex[mFaces[i].z].y, normalVertex[mFaces[i].z].z);
		glEnd();
	}

	
}

void Obj::createDL() {

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

void Obj::displayDL() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glCallList(list[1]);
}