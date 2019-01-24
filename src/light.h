#include <iostream>
#include "../headers/glm/glm.hpp"
#include "../headers/glm/gtc/type_ptr.hpp"
#include "Obj.h"

class light{

    public:

        int lightId;
        bool onLinght;
        glm::vec3 ambient;
        glm::vec3 specular;
        glm::vec3 diffuse;
        glm::vec3 position;
		float constantAttenuation,
			linearAttenuation,
			quadraticAttenuation;
		float shininess[1] = {24.0f};
		Obj * mObj;
        
   
		light(int id,Obj *o);

		void displayLight();
        void setPosition(glm::vec3);
        void setAmbientColor(glm::vec3);
        void setSpecularColor(glm::vec3);
        void setDiffuseColor(glm::vec3);
		void setOn(bool a);
		glm::vec3 getAmbientColor();
        glm::vec3 getSpecularColor();
        glm::vec3 getDiffuseColor();
        glm::vec3 getPosition();

		bool getOn();

};