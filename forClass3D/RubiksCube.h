#pragma once

#include "glm/glm.hpp"
#include "mesh.h"
#include "shader.h"

#define RESIZE_FACTOR 0.2 * DISPLAY_WIDTH/800
#define RUBIK_SIZE 3
#define NUM_OF_CUBES RUBIK_SIZE*RUBIK_SIZE*RUBIK_SIZE

#define RED glm::vec3(1,0,0)
//#define ORANGE glm::vec3(0.6,0.21,0)
#define PINK glm::vec3(1.0,0.2,0.6) 
#define BLUE glm::vec3(0,0,1)
#define GREEN glm::vec3(0.4,0.8,0.2)
#define YELLOW glm::vec3(1,0.8,0.1)
//#define WHITE glm::vec3(1,1,1)
#define LIGHT_BLUE glm::vec3(0.6,0.86,0.9)

class RubiksCube {
	private:
		Mesh* mesh;
		Shader* shader;
		glm::mat4*** rotations;
		glm::vec3*** euler_angles;
		glm::mat4*** local_translations;
		glm::mat4*** global_translations;
		glm::vec3*** indeces;
		glm::mat4 global_rotation;
		glm::mat4 perspective;
		glm::mat4 scale;
		int display_width;
		int display_height;
		float rotation_angle; //how much to rotate the cube edge. can be negative

	public:
		RubiksCube();
		RubiksCube(const int DISPLAY_WIDTH, const int DISPLAY_HEIGHT, Mesh* mesh1, Shader* shader1);
		~RubiksCube();

		void InitRubiksCube(const int DISPLAY_WIDTH, const int DISPLAY_HEIGHT, Mesh* mesh1, Shader* shader1);
		void RotateCube(float angle, glm::vec3 rotation_axis);
		void RotateCubeByScreen(glm::vec2 old_point, glm::vec2 new_point);
		void TranslateCube(glm::vec2 translate_pos);
		void RotateWall(int wall_index, int axis);
		void Draw();

		bool checkWall(int wall_index, int axis);


		//Getters:
		glm::mat4 getMVP(int i, int j, int k);
		glm::mat4*** getRotations();
		glm::mat4*** getLocalTranslations();
		glm::mat4*** getGlobalTranslations();
		glm::vec3*** getIndeces();
		glm::mat4 getPerspective();
		glm::mat4 getScale();
		float getRotationAngle();
		int getDisplayWidth();
		int getDisplayHeight();
		

		//Setters:
		void setRotations(glm::mat4*** Rotations);
		void setLocalTranslations(glm::mat4*** Translations);
		void setGlobalTranslations(glm::mat4*** Translations);
		void setIndeces(glm::vec3*** Indeces);
		void setPerspective(glm::mat4 Perspective);
		void setScale(float Scale);
		void setRotationAngle(float precent);
		void setDisplayWidth(int Display_width);
		void setDisplayHeight(int Display_height);

};