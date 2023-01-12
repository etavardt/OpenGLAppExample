#shader vertex
#version 460 core
//Vertex Shader

// 3D point, 4channel color, 2D TexMap Point, Tex index
layout(location = 0) in vec4  l_position;
layout(location = 1) in vec4  l_color;
layout(location = 2) in vec2  l_texCoord;
layout(location = 3) in float l_texInd;
layout(location = 4) in float l_mvpInd;

out vec4  v_color;
out vec2  v_texCoord;
out float v_texInd;

uniform mat4 u_MVP[2];

void main()
{
    int mvpInd = int(l_mvpInd);

    gl_Position = u_MVP[mvpInd] * l_position;
    v_color     = l_color;
    v_texCoord  = l_texCoord;
    v_texInd    = l_texInd;
};

#shader fragment
#version 460 core
// Fragment Shader

layout(location = 0) out vec4 o_color;

in vec4  v_color;
in vec2  v_texCoord;
in float v_texInd;

//uniform vec4 u_Color;
uniform sampler2D u_textures[2];

void main()
{
    int texInd = int(v_texInd);
    vec4 texColor = texture(u_textures[texInd], v_texCoord);
    o_color = texColor;
    //o_color = v_Color;
};