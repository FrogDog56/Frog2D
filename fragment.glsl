#version 400

//in vec2 textureCoords;

out vec4 outColour;

//uniform sampler2D hudTexture;
//uniform int hasTexture;

void main() {
    //outColour = texture(hudTexture, textureCoords) * vec4(0.0, 1.0, 0.8, 1.0);
    outColour = vec4(1.0, 1.0, 0.0, 1.0);
}