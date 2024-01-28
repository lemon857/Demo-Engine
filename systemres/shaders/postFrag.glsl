#version 330 core

in vec2 TextureCoords;

out vec4 fragColor;

const float offset = 1.0 / 1000.0;

uniform sampler2D renderTexture;
uniform sampler2D depthTexture;

 //fragColor = vec4(texture(texture1, TextureCoords).rgb, 1.0);

 vec4 kernel_effect()
 {
	float kernel[9] = float[](
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1
	);

	vec4 col = vec4(0.0);
	col += kernel[0] * texture(renderTexture, TextureCoords.st + vec2(-offset, offset));
	col += kernel[1] * texture(renderTexture, TextureCoords.st + vec2(0.0, offset));
	col += kernel[2] * texture(renderTexture, TextureCoords.st + vec2(offset, offset));
	col += kernel[3] * texture(renderTexture, TextureCoords.st + vec2(-offset, 0.0));
	col += kernel[4] * texture(renderTexture, TextureCoords.st + vec2(0.0, 0.0));
	col += kernel[5] * texture(renderTexture, TextureCoords.st + vec2(offset, 0.0));
	col += kernel[6] * texture(renderTexture, TextureCoords.st + vec2(-offset, -offset));
	col += kernel[7] * texture(renderTexture, TextureCoords.st + vec2(0.0, offset));
	col += kernel[8] * texture(renderTexture, TextureCoords.st + vec2(offset, offset));

	return col;
 }

 vec4 grascale_effect()
 { 
	vec4 col = vec4(texture(renderTexture, TextureCoords).rgb, 1.0);
	float d = (col.x + col.y + col.z) / 3.0;
	return vec4(d, d, d, 1.0);
 }

void main() {	

	fragColor = kernel_effect();
}