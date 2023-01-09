#shader vertex
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 fragUV;

void main() {
    gl_Position = vec4(position.xy, 0, 1);
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
