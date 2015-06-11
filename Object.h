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
		GLuint textureID;

	protected:
		void Object::BuildTriangles(const GLuint& perRow, const GLuint& perColumn);
		Object* objectState;
		vec3 position, scale;

	private:
		//void LoadTriangles(const GLuint& perRow, const GLuint& perColumn, const GLenum& renderMode);
		void Object::LoadTriangles(GLfloat *vertices, GLfloat *uvs);
		float leftX, rightX, topY, bottomY;
		mat4 Render(GLuint textureID);
		GLuint numIndices, numUVs, vertexBufferID, uvBufferID, renderMode;
};