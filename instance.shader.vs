#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in float aColor;
layout (location = 2) in mat4 aInstanceMatrix;

out vec3 ourColor; // output a color to the fragment shader

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 colors[6];

void main()
{
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f); 
    
    //ourColor = aColor;
    if (gl_VertexID < 4)
    {
        ourColor = colors[0];
    }
    else if (gl_VertexID < 8)
    {
        ourColor = colors[3];
    }
    else if (gl_VertexID < 12)
    {
        ourColor = colors[4];
    }
    else if (gl_VertexID < 16)
    {
        ourColor = colors[1];
    }
    else if (gl_VertexID < 20)
    {
        ourColor = colors[4];
    }
    else if (gl_VertexID < 24)
    {
        ourColor = colors[1];
    }
    else if (gl_VertexID < 28)
    {
        ourColor = colors[5];
    }
    else if (gl_VertexID < 32)
    {
        ourColor = colors[2];
    }
    else if (gl_VertexID < 36)
    {
        ourColor = colors[5];
    }
    else if (gl_VertexID < 40)
    {
        ourColor = colors[2];
    }
    else
    {
        ourColor = vec3(0, 0, 0);
    }
}