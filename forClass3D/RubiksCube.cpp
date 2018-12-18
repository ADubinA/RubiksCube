#include "RubiksCube.h"
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include <math.h>
RubiksCube::RubiksCube()
{
	mesh = nullptr;
	shader = nullptr;
	rotations = nullptr;
	local_translations = nullptr;
	global_translations = nullptr;
	indeces = nullptr;
	perspective = glm::mat4(0.0);
	scale = glm::mat4(0.0);
	int display_width = 0;
	int display_height = 0;
}

RubiksCube::RubiksCube(const int DISPLAY_WIDTH, const int DISPLAY_HEIGHT, Mesh* mesh1, Shader* shader1)
{
	mesh = mesh1;
	shader = shader1;

	scale = glm::scale(glm::vec3(RESIZE_FACTOR, RESIZE_FACTOR, RESIZE_FACTOR));
	perspective = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	glm::vec3 pos = glm::vec3(0, 0, -5);
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	perspective = perspective * glm::lookAt(pos, pos + forward, up) * scale;
}

void RubiksCube::InitRubiksCube(const int DISPLAY_WIDTH, const int DISPLAY_HEIGHT, Mesh* mesh1, Shader* shader1)
{
	mesh = mesh1;
	shader = shader1;

	rotations = new glm::mat4**[RUBIK_SIZE];
	local_translations = new glm::mat4**[RUBIK_SIZE];
	global_translations = new glm::mat4**[RUBIK_SIZE];
	indeces = new glm::vec3**[RUBIK_SIZE];
	euler_angles = new glm::vec3**[RUBIK_SIZE];



	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		rotations[i] = new glm::mat4*[RUBIK_SIZE];
		local_translations[i] = new glm::mat4*[RUBIK_SIZE];
		global_translations[i] = new glm::mat4*[RUBIK_SIZE];
		indeces[i] = new glm::vec3*[RUBIK_SIZE];
		euler_angles[i] = new glm::vec3*[RUBIK_SIZE];
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			rotations[i][j] = new glm::mat4[RUBIK_SIZE];
			local_translations[i][j] = new glm::mat4[RUBIK_SIZE];
			global_translations[i][j] = new glm::mat4[RUBIK_SIZE];
			indeces[i][j] = new glm::vec3[RUBIK_SIZE];
			euler_angles[i][j] = new glm::vec3[RUBIK_SIZE];
		}
	}

	//i,j,k need to be between -1 to 1
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				rotations[i][j][k] = glm::rotate(0.0f, glm::vec3(1));
				local_translations[i][j][k] = glm::translate(glm::vec3(0, 0, 0));
				global_translations[i][j][k] = glm::translate(glm::vec3(2.1 * i - 2.1*(RUBIK_SIZE-1)/2, 2.1 * j - 2.1*(RUBIK_SIZE - 1) / 2, 2.1 * k - 2.1*(RUBIK_SIZE - 1) / 2));
				indeces[i][j][k] = glm::vec3(i, j, k);
				euler_angles[i][j][k] = glm::vec3(0);

			}
		}

	}
	scale = glm::scale(glm::vec3(RESIZE_FACTOR, RESIZE_FACTOR, RESIZE_FACTOR));
	perspective = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	global_rotation = glm::rotate(0.0f, glm::vec3(1));

	glm::vec3 pos = glm::vec3(0, 0, -5);
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	rotation_angle = 90.0f;

	perspective = perspective * glm::lookAt(pos, pos + forward, up);
}

RubiksCube::~RubiksCube()
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			delete global_translations[i][j];
			delete rotations[i][j];
			delete local_translations[i][j];
			delete indeces[i][j];
			delete euler_angles[i][j];
		}
		delete global_translations[i];
		delete rotations[i];
		delete local_translations[i];
		delete indeces[i];
		delete euler_angles[i];
	}
	delete global_translations;
	delete rotations;
	delete local_translations;
	delete indeces;
	delete euler_angles;
}

void RubiksCube::RotateCube(float angle, glm::vec3 rotation_axis)
{
	glm::mat4 rotation_matrix = glm::rotate(angle, rotation_axis);
	global_rotation = rotation_matrix * global_rotation;
}

void RubiksCube::RotateCubeByScreen(glm::vec2 old_point, glm::vec2 new_point)
{
	//glm::mat4 rotation_matrix = glm::rotate(angle, rotation_axis);
	
	glm::vec2 difference =  old_point - new_point;

	if (difference.x != 0)
	{
		glm::vec3 rotation_vector = glm::vec3(rotations[RUBIK_SIZE - 2][RUBIK_SIZE - 2][RUBIK_SIZE - 2] *
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		this->RotateCube(-difference.x * 0.5, rotation_vector);

	}
	if (difference.y != 0)
	{
		glm::vec3 rotation_vector = glm::vec3(rotations[RUBIK_SIZE - 2][RUBIK_SIZE - 2][RUBIK_SIZE - 2] *
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		this->RotateCube(difference.y * 0.5, rotation_vector);
	}
	
}

void RubiksCube::TranslateCube(glm::vec2 translate_pos)
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				this->local_translations[i][j][k] = glm::translate(glm::vec3(-0.04f * translate_pos, 0))*local_translations[i][j][k];
			}
		}
	}
}

// axis: 0=x 1=y 2=z
void RubiksCube::RotateWall(int wall_index, int axis)
{
	std::cout << "rotating wall " << std::endl;
	// create a new 2d array
	glm::vec3 **tmp_indeces = new glm::vec3 *[RUBIK_SIZE];
	glm::vec3 rotation_axis;
	if (axis == 0)
	{
		rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (axis == 1)
	{
		rotation_axis = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (axis == 2)
	{
		rotation_axis = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	// create tmp array
	int x, y, z;
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		tmp_indeces[i] = new glm::vec3[RUBIK_SIZE];
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			if (axis == 0)
			{
				if (rotation_angle > 0 )
				{
					tmp_indeces[i][j] = indeces[wall_index][j][i];
				}
				else 
				{
					tmp_indeces[i][j] = indeces[wall_index][RUBIK_SIZE-1-i][j];
				}
			}
				
			if (axis == 1)
			{
				if (rotation_angle > 0)
				{
					tmp_indeces[i][j] = indeces[j][wall_index][i];
				}
				else
				{
					tmp_indeces[i][j] = indeces[i][wall_index][RUBIK_SIZE-1-j];

				}
			}
			if (axis == 2)
			{
				if (rotation_angle > 0)
				{
					tmp_indeces[i][j] = indeces[j][i][wall_index];
				}
				else
				{
					tmp_indeces[i][j] = indeces[RUBIK_SIZE - 1 - i][j][wall_index]; 
				}
			}

		}
	}


	// copy the tmp array and rotate the cube
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			//rotate the cube in screen
			if (axis == 0)
			{
				x = indeces[wall_index][i][j].x;
				y = indeces[wall_index][i][j].y;
				z = indeces[wall_index][i][j].z;
			}
			if (axis == 1)
			{
				x = indeces[i][wall_index][j].x;
				y = indeces[i][wall_index][j].y;
				z = indeces[i][wall_index][j].z;
			}
			if (axis == 2)
			{
				x = indeces[i][j][wall_index].x;
				y = indeces[i][j][wall_index].y;
				z = indeces[i][j][wall_index].z;
			}

			if (axis == 0)
			{
				if (rotation_angle > 0 && rotation_angle + euler_angles[x][y][z].x >= 90)
				{
					indeces[wall_index][i][j] = tmp_indeces[RUBIK_SIZE - 1 - i][j];
				}
				else if(rotation_angle < 0 && rotation_angle + euler_angles[x][y][z].x <= -90)
				{
					indeces[wall_index][i][j] = tmp_indeces[j][i];

				}
			}
			if (axis == 1)
			{
				if (rotation_angle > 0 && rotation_angle + euler_angles[x][y][z].y >= 90)
				{
					indeces[i][wall_index][j] = tmp_indeces[i][RUBIK_SIZE - 1 - j];
				}
				else if (rotation_angle < 0 && rotation_angle + euler_angles[x][y][z].y <= -90)
				{
					indeces[i][wall_index][j] = tmp_indeces[j][i];
				}
			}
			if (axis == 2)
			{
				if (rotation_angle > 0 && rotation_angle + euler_angles[x][y][z].z >= 90)
				{
					indeces[i][j][wall_index] = tmp_indeces[RUBIK_SIZE - 1 - i][j];
				}
				else if (rotation_angle < 0 && rotation_angle + euler_angles[x][y][z].z <= -90)
				{
					indeces[i][j][wall_index] = tmp_indeces[j][i];
				}
			}
			
			if (axis == 0)
			{
				euler_angles[x][y][z] += glm::vec3(rotation_angle, 0, 0);
				while (euler_angles[x][y][z].x >= 90)
					euler_angles[x][y][z].x -= 90;
				while (euler_angles[x][y][z].x <= -90)
					euler_angles[x][y][z].x += 90;
				
			}
			if (axis == 1)
			{
				euler_angles[x][y][z] += glm::vec3(0, rotation_angle, 0);
				while (euler_angles[x][y][z].y >= 90)
					euler_angles[x][y][z].y -= 90;
				while (euler_angles[x][y][z].y <= -90)
					euler_angles[x][y][z].y += 90;
				
			}
			if (axis == 2)
			{
				euler_angles[x][y][z] += glm::vec3(0, 0, rotation_angle);
				while (euler_angles[x][y][z].z >= 90)
					euler_angles[x][y][z].z -= 90;
				while (euler_angles[x][y][z].z <= -90)
					euler_angles[x][y][z].z += 90;
				
			}
			glm::mat4 temp;
			if (abs(rotation_angle)==180.0f)
				temp = glm::rotate(float(rotation_angle)/2, rotation_axis);
			else
				temp = glm::rotate(float(rotation_angle), rotation_axis);
			rotations[x][y][z] = temp * rotations[x][y][z];

		}
	}

	// delete tmp array
	for (int i = 0; i < RUBIK_SIZE; i++) {
		delete[] tmp_indeces[i]; // delete sub array
	}
	delete[] tmp_indeces; //delete outer array
}

void RubiksCube::Draw()
{
	shader->Bind(); 
	int x, y, z;
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				x = indeces[i][j][k].x;
				y = indeces[i][j][k].y;
				z = indeces[i][j][k].z;

				shader->Update(getMVP(x,y,z), rotations[x][y][z]);
				mesh->Draw();
			}
		}
	}
}

bool RubiksCube::checkWall(int wall_index, int axis)
{
	int x, y, z;
	float angle_1, angle_2;

	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			if (axis == 0)
			{
				x = indeces[wall_index][i][j].x;
				y = indeces[wall_index][i][j].y;
				z = indeces[wall_index][i][j].z;
				angle_1 = euler_angles[x][y][z].y;
				angle_2 = euler_angles[x][y][z].z;
			}
			if (axis == 1)
			{
				x = indeces[i][wall_index][j].x;
				y = indeces[i][wall_index][j].y;
				z = indeces[i][wall_index][j].z;
				angle_1 = euler_angles[x][y][z].x;
				angle_2 = euler_angles[x][y][z].z;
			}
			if (axis == 2)
			{
				x = indeces[i][j][wall_index].x;
				y = indeces[i][j][wall_index].y;
				z = indeces[i][j][wall_index].z;
				angle_1 = euler_angles[x][y][z].x;
				angle_2 = euler_angles[x][y][z].y;
			}
	
			if ((int)angle_1 % 90 != 0 || (int)angle_2 % 90 != 0)
			{
				return false;
			}
		}
	}
	return true;
}

//Getters:
glm::mat4 RubiksCube::getMVP(int i,int j,int k)
{
	if (i >= 0 && i <= RUBIK_SIZE - 1 && j >= 0 && j <= RUBIK_SIZE - 1 && k >= 0 && k <= RUBIK_SIZE - 1)
		return perspective * scale * local_translations[i][j][k] *global_rotation * rotations[i][j][k] *  global_translations[i][j][k] ;
	else
		std::cout << "Runtime error: indecies out of range when tring to get MVP:  " << i << ", " << j << ", " << k << std::endl;
	return glm::rotate(0.0f, glm::vec3(1));
}

glm::mat4*** RubiksCube::getRotations()
{
	return rotations;
}

glm::mat4*** RubiksCube::getLocalTranslations()
{
	return local_translations;
}

glm::mat4*** RubiksCube::getGlobalTranslations()
{
	return global_translations;
}

glm::vec3*** RubiksCube::getIndeces()
{
	return indeces;
}

glm::mat4 RubiksCube::getPerspective()
{
	return perspective;
}

glm::mat4 RubiksCube::getScale()
{
	return scale;
}

float RubiksCube::getRotationAngle()
{
	return rotation_angle;
}

int RubiksCube::getDisplayWidth()
{
	return display_width;
}

int RubiksCube::getDisplayHeight()
{
	return display_height;
}

//Setters:
void RubiksCube::setRotations(glm::mat4*** Rotations)
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				rotations[i][j][k] = Rotations[i][j][k];
			}
		}
	}
}

void RubiksCube::setLocalTranslations(glm::mat4*** Translations)
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				local_translations[i][j][k] = Translations[i][j][k];
			}
		}
	}
}

void RubiksCube::setGlobalTranslations(glm::mat4*** Translations)
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				global_translations[i][j][k] = Translations[i][j][k];
			}
		}
	}
}

void RubiksCube::setIndeces(glm::vec3*** Indeces)
{
	for (int i = 0; i < RUBIK_SIZE; i++)
	{
		for (int j = 0; j < RUBIK_SIZE; j++)
		{
			for (int k = 0; k < RUBIK_SIZE; k++)
			{
				indeces[i][j][k] = Indeces[i][j][k];
			}
		}
	}
}

void RubiksCube::setPerspective(glm::mat4 Perspective)
{
	this->perspective = Perspective;
}

void RubiksCube::setScale(float Scale)
{
	if (Scale == -1)
		this->scale *= glm::scale(glm::vec3(0.9));
	else if (Scale == 1)
		this->scale *= glm::scale(glm::vec3(1.1));
}
void RubiksCube::setRotationAngle(float precent)
{
	if (abs(rotation_angle * precent) < 360)
		this->rotation_angle *= precent;
}
void RubiksCube::setDisplayWidth(int Display_width)
{
	this->display_height = Display_width;
}

void RubiksCube::setDisplayHeight(int Display_height)
{
	this->display_height = Display_height;
}
