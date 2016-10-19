#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;

void main()
{
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position.xyz = vertexPosition_modelspace;
  	gl_Position.w = 1.0;
}
