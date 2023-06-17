#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTex;


out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   gl_Position = proj * view * model * vec4(aPos , 1.0);
   texCoord = aTex;
}


#Shader Fragment
#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0 , texCoord);
}