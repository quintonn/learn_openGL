#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;

//out vec2 TexCoord;
out vec3 ourColor; // output a color to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 bColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor; // set color using value from vertices array
    //ourColor = bColor; // set color using value set inside render loop
    
}