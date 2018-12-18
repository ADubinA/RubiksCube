#pragma once
#include "RubiksCube.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

	glm::vec2 old_pos;
	glm::vec2 curr_pos = glm::vec2(-10.0, -10.0);
	glm::vec2 pixel_difference;
	int wall_mode = 0;  // control which wall to use if rubik_size>3
	RubiksCube cube;

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void updatePosition(double xpos, double ypos);
	void mouseProccessing(int state);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			updatePosition(xpos, ypos);
			mouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
			//std::cout << "RIGHT: " << "x: " << xpos << " y: " << ypos << std::endl;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			updatePosition(xpos, ypos);
			mouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
			//std::cout << "LEFT: " << "x: " << xpos << " y: " << ypos << std::endl;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE ||
			glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			curr_pos = glm::vec2(-10.0, -10.0);

			//std::cout << "RIGHT:  RELEASEEEEEE"  << std::endl;
		}

	}

	void updatePosition(double xpos, double ypos)
	{
		if (curr_pos == glm::vec2(-10.0, -10.0))
		{
			//TODO handle mouse release to set curr_pos back to -10.0
			old_pos = glm::vec2(xpos, ypos);
			curr_pos = glm::vec2(xpos, ypos);
		}
		else
		{
			old_pos = curr_pos;
			curr_pos = glm::vec2(xpos, ypos);
		}
		pixel_difference = curr_pos - old_pos;

	}

	void mouseProccessing(int state)
	{
		if (state == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (old_pos != curr_pos)
				cube.RotateCubeByScreen(old_pos,curr_pos);
			//std::cout << "LEFT: " << std::endl;
		}
		else if (state == GLFW_MOUSE_BUTTON_RIGHT)
		{
			cube.TranslateCube(pixel_difference);
		}
	}
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		cube.setScale(yoffset);
	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				if (action == GLFW_PRESS)
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_RIGHT:
				cube.RotateCube(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case GLFW_KEY_LEFT:
				cube.RotateCube(-45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case GLFW_KEY_UP:
				cube.RotateCube(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			case GLFW_KEY_DOWN:
				cube.RotateCube(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			case GLFW_KEY_R:
				if (action == GLFW_PRESS && cube.checkWall(0 + wall_mode, 0))
				{
					
					if (abs(cube.getRotationAngle()) == 180.0f)
					{
						cube.RotateWall(0 + wall_mode, 0);
					}
					cube.RotateWall(0 + wall_mode, 0);
				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_L:
				if (action == GLFW_PRESS && cube.checkWall(RUBIK_SIZE - 1 - wall_mode, 0))
				{
					if (abs(cube.getRotationAngle()) == 180.0f) 
					{
						cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 0);
					}
					cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 0);
				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_U:
				if (action == GLFW_PRESS && cube.checkWall(RUBIK_SIZE - 1 - wall_mode, 1))
				{
					if (abs(cube.getRotationAngle()) == 180.0f) 
					{
						cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 1);
					}
					cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 1);
				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_D:
				if (action == GLFW_PRESS && cube.checkWall(0 + wall_mode, 1))
				{
					if (abs(cube.getRotationAngle()) == 180.0f) 
					{
						cube.RotateWall(0 + wall_mode, 1);
					}
					cube.RotateWall(0 + wall_mode, 1);

				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_B:
				if (action == GLFW_PRESS && cube.checkWall(RUBIK_SIZE - 1 - wall_mode, 2))
				{
					if (abs(cube.getRotationAngle()) == 180.0f) 
					{
						cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 2);
					}
					cube.RotateWall(RUBIK_SIZE - 1 - wall_mode, 2);
				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_F:
				if (action == GLFW_PRESS && cube.checkWall(0 + wall_mode, 2))
				{
					if (abs(cube.getRotationAngle()) == 180.0f) 
					{
						cube.RotateWall(0 + wall_mode, 2);
					}
					cube.RotateWall(0 + wall_mode, 2);
				}
				else if (action == GLFW_PRESS)
				{
					std::cout << "This wall shell NOT be moved by mortal men!!!" << std::endl;
				}
				break;
			case GLFW_KEY_Z:
				if (action == GLFW_PRESS)
					cube.setRotationAngle(0.5);
				break;
			case GLFW_KEY_A:
				if (action == GLFW_PRESS)
					cube.setRotationAngle(2);
				break;
			case GLFW_KEY_X:
				if (action == GLFW_PRESS)
					if (wall_mode == 0 && RUBIK_SIZE > 3)
						wall_mode++;
					else
						wall_mode = 0;
				break;
			case GLFW_KEY_SPACE:
				if (action == GLFW_PRESS)
					cube.setRotationAngle(-1);
				break;
			case GLFW_KEY_M:
				if (action == GLFW_PRESS)
					cube.Mix(30);
				break;
			default:
				break;
		}

	}
