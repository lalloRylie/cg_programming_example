#include "Object.h"

Object::Object(){
	objectState = NULL;
	renderMode = GL_TRIANGLES;
	vertexBufferID = 0;
	SetPosition(vec3(0));
	SetScale(vec3(1));
	numIndices = 6;
	textureID = NULL;
}

Object::~Object(){
	
}

void Object::SetPosition(vec3 position){
	this->position = position;
}

void Object::SetScale(vec3 scale){
	this->scale = scale;
}

vec3 Object::GetPosition(){
	return position;
}

float Object::GetLeftX(){
	return leftX;
}

float Object::GetRightX(){
	return rightX;
}

float Object::GetTopY(){
	return topY;
}

float Object::GetBottomY(){
	return bottomY;
}

void Object::Update(const float& deltaTime){
	leftX = position.x - scale.x;
	rightX = position.x + scale.x;
	topY = position.y + scale.y;
	bottomY = position.y - scale.y;
}

void Object::Render(const Camera& camera){
	mat4 modelMatrix = Render();
	mat4 MVPMatrix = camera.projectionMatrix * camera.viewMatrix * modelMatrix;

	glUniformMatrix4fv(camera.MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

//bool loadTextureFromFile( std::string path )
//{
//    //Texture loading success
//    bool textureLoaded = false;
//
//    //Generate and set current image ID
//    ILuint imgID = 0;
//    ilGenImages( 1, &imgID );
//    ilBindImage( imgID );
//
//    //Load image
//    ILboolean success = ilLoadImage( path.c_str() );
//
//    //Image loaded successfully
//    if( success == IL_TRUE )
//    {
//        //Convert image to RGBA
//        success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
//        if( success == IL_TRUE )
//        {
//            //Create texture from file pixels
//            textureLoaded = loadTextureFromPixels32( (GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) );
//        }
//
//        //Delete file from memory
//        ilDeleteImages( 1, &imgID );
//    }
//
//    //Report error
//    if( !textureLoaded )
//    {
//        printf( "Unable to load %s\n", path.c_str() );
//    }
//
//    return textureLoaded;
//}

void Object::LoadTriangles(const GLuint& perRow, const GLuint& perColumn, const GLenum& renderMode){

	/*
		0,1   1,1
		0,0   1,0

		0,0   1,0
		0,-1  1,-1
	*/
	static const GLfloat vertexBuffer[] = {
		0.0f, 1.0f,  0.0f,	//maps to index 0
		0.0f, 0.0f, 0.0f,	//maps to index 1
		1.0f, 1.0f,  0.0f,	//maps to index 2
		1.0f, 0.0f, 0.0f,	//maps to index 3

		1.0f, 0.0f, 0.0f,	//maps to index 4
		0.0f, 0.0f, 0.0f,	//maps to index 5

		0.0f, 0.0f, 0.0f,	//maps to index 6
		0.0f, -1.0f, 0.0f,	//maps to index 7
		1.0f, 0.0f, 0.0f,	//maps to index 8
		1.0f, -1.0f, 0.0f	//maps to index 9
	};

	numIndices = 10;		//For a total of 10 indices
	
	this->renderMode = renderMode;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
}

void Object::SaveObjectState(char *message){
	if(objectState == NULL)
		objectState = (Object*)malloc(sizeof(*this));

	*objectState = *this;
	puts(message);
}

void Object::LoadObjectState(char *message){
	*this = *objectState;
	puts(message);
}

GLuint Object::LoadBMP(const char * imagepath){
	// Data read from the header of the BMP file
	unsigned char header[54];	// Each BMP file begins by a 54-bytes header
	unsigned int dataPos;		// Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;		// = width*height*3
	unsigned char * data;		// Actual RGB data

	// Open the file
	const char* mode = "rb";
	FILE * file = fopen(imagepath, mode);
	if (!file){
		printf("Image could not be opened\n");
		return 0;
	}

	// If not 54 bytes read : problem
	if(fread(header, 1, 54, file)!=54 ){	
		printf("Not a correct BMP file\n");
		return false;
	}

	//Checking to see if first two bytes are 'B' and 'M'
	if ( header[0] != 'B' || header[1] != 'M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if(imageSize==0)    
		imageSize=width*height*3;	// 3 : one byte for each Red, Green and Blue component
	if(dataPos==0)
		dataPos=54;					// The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];
 
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
 
	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	glGenTextures(1, &textureID);
 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
 
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

mat4 Object::Render(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	glDrawArrays(renderMode, 0, numIndices);	//GL_TRIANGLE_STRIP or GL_TRIANGLES
	glDisableVertexAttribArray(0);

	//Every object starts off with an identity matrix...
	/*mat4 objectMatrix = mat4(1.0f);
	mat4 identityMatrix = glm::scale(objectMatrix, scale);	
	mat4 modelMatrix = translate(identityMatrix, position);*/

	mat4 identityMatrix = mat4(1.0f);
	mat4 translateMatrix = translate(identityMatrix, position);
	mat4 modelMatrix = glm::scale(translateMatrix, scale);

	return modelMatrix;
}

//static mat4 Render(GLuint vertexBuffer, const vec3& position, const vec3& scale);