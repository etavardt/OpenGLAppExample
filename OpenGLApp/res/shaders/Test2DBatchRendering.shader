#shader vertex
#version 330 core
//Vertex Shader

// 3D point, 2D TexMap Point, Tex index
layout(location = 0) in vec4  l_position;
layout(location = 1) in vec2  l_texCoord;
layout(location = 2) in float l_texInd;

out vec2 v_texCoord;
out float v_texInd;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * l_position;
    v_texCoord = l_texCoord;
    v_texInd = l_texInd;
};

#shader fragment
#version 330 core
// Fragment Shader

layout(location = 0) out vec4 o_color;

in vec2 v_texCoord;
in float v_texInd;

//uniform vec4 u_Color;
uniform sampler2D u_textures[2];

void main()
{
//    vec4 texColor = texture(u_texture, v_texCoord);
    int texInd = int(v_texInd);
    vec4 texColor = texture(u_textures[texInd], v_texCoord);
    o_color = texColor;
    //color = u_Color;
};