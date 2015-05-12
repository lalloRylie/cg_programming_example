#version 330 core

layout(location = 0)
in vec3 model_space_pos;

uniform mat4 MVP;

void main(){
	gl_Position = MVP * vec4(model_space_pos, 1);
}