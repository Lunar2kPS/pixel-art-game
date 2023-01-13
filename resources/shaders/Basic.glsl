#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 uniformMVP;

out vec2 fragUV;

void main() {
    gl_Position = uniformMVP * vec4(position.xyz, 1);
    fragUV = uv;
}

//--- --- --- --- ---
#shader fragment
#version 330 core
in vec2 fragUV; //NOTE: HAS TO MATCH the out variable name from the vertex shader!

uniform vec4 uniformColor;
uniform sampler2D uniformTexture;

out vec4 outColor;

void main() {
    outColor = uniformColor * texture(uniformTexture, fragUV);
}
