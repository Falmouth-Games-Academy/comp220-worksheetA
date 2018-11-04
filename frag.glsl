#version 330 core 

//** required a output value for binding with fragment 
uniform vec3 MyVariable;

out vec3 colour;
in vec4 myVariable;
void main()
{
	colour = vec3(1.0, 0.0, 0.0);
}