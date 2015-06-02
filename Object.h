#include "Application.h"

#pragma once

class Object{

	public:
		Object();

		virtual ~Object();
		virtual void Update(const float& deltaTime);
		virtual void Render(const Camera& camera);

		void SetPosition(vec3 position);
		void SetScale(vec3 scale);

		vec3 GetPosition();
		float GetLeftX();
		float GetRightX();
		float GetTopY();
		float GetBottomY();

		void SaveObjectState(char *message = "Saved Object State");
		void LoadObjectState(char *message = "Loaded Object State");
		GLuint LoadBMP(const char * imagepath);
		void LoadTriangles(const GLuint& perRow, const GLuint& perColumn, const GLenum& renderMode);

	protected:
		Object* objectState;
		vec3 position, scale;

	private:
		float leftX, rightX, topY, bottomY;
		mat4 Render();
		GLuint textureID;
		GLuint numIndices, vertexBufferID, renderMode;
};