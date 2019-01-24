#include "light.h"

light::light(int id , Obj *o)
{
	if (id) {

		lightId = GL_LIGHT0;

	}
	else {

		lightId = GL_LIGHT1;
	}
    ambient[0] = ambient[1] = ambient[2] = 1.0f;
	specular[0] = specular[1] = 0.0f;
	specular[2] = 1.0f;
    diffuse[1] = diffuse[0] = diffuse[2]= 0.5f;
    position[0] = position[1] = position[2] = 0.0f;
    onLinght = true;

	mObj = o;
	mObj->setVModel(false);
	mObj->setVWire(true);
}

void light::displayLight(){

    if(onLinght){
        
		glEnable(lightId);
		glLightfv(lightId,GL_POSITION, glm::value_ptr(position));
		glLightfv(lightId,GL_AMBIENT,glm::value_ptr(ambient));
		glLightfv(lightId,GL_SPECULAR, glm::value_ptr(specular));
		glLightfv(lightId,GL_DIFFUSE, glm::value_ptr(diffuse));
		glLightfv(lightId,GL_SHININESS, shininess);

	}
	else {
		glDisable(lightId);
	}
}


void  light::setPosition(glm::vec3 p) {

	position = p;
	mObj->setTranslation(p);
}

void  light::setAmbientColor(glm::vec3 color) {

	ambient = color;
}

void  light::setSpecularColor(glm::vec3 color) {

	specular = color;
}

void  light::setDiffuseColor(glm::vec3 color) {

	diffuse = color;
}


void light::setOn(bool a) {

	onLinght = a;

}

glm::vec3 light::getAmbientColor() {

	return ambient;

}

glm::vec3 light::getSpecularColor() {

	return specular;

}

glm::vec3 light::getDiffuseColor() {

	return diffuse;

}

glm::vec3 light::getPosition() {

	return position;

}

bool light::getOn() {

	return onLinght;

}