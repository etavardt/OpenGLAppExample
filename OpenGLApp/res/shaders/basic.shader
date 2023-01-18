#shader vertex
#version 330 core
//Vertex Shader

layout(location = 0) in vec4 l_position;
layout(location = 1) in vec2 l_texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * l_position;
    v_TexCoord = l_texCoord;
};

#shader fragment
#version 330 core
// Fragment Shader

layout(location = 0) out vec4 l_color;

in vec2 v_TexCoord;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    l_color = texColor;
    //color = u_Color;
};