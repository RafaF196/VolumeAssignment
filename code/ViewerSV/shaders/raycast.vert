#version 330

layout (location = 0) in vec3 vert;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

smooth out vec3 tex_coords;
smooth out vec3 position;
smooth out vec3 camera;

void main(void)  {
	tex_coords = vert + vec3(0.5);
	position = vert;
	camera = inverse(view)[3].xyz;

	gl_Position = projection * view * model * vec4(vert, 1);
}
