#version 330 core

in vec2 TextureCoords;

out vec4 fragColor;

const float offset = 1.0 / 6000.0;
const float offsetblur = 1.0 / 650.0;
const float minVal = 0.1;

vec2 reverseMaxSize = vec2(1);
uniform sampler2D renderTexture;
uniform sampler2D depthTexture;

uniform int cur_effect;

 //fragColor = vec4(texture(texture1, TextureCoords).rgb, 1.0);

 vec4 kernel_effect()
 {
	float kernel[9] = float[](
		0, -1, 0,
		-1, 5.05, -1,
		0, -1, 0
	);

	vec4 col = vec4(0.0);

	//if (texture(realTexture, TextureCoords).x < minVal
	//&& texture(realTexture, TextureCoords).y < minVal
	//&& texture(realTexture, TextureCoords).z < minVal)
	//{
	//	return texture(realTexture, TextureCoords);		
	//}

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

 vec4 blur_effect()
 {
	float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
);

	vec4 col = vec4(0.0);

	//if (texture(realTexture, TextureCoords).x < minVal
	//&& texture(realTexture, TextureCoords).y < minVal
	//&& texture(realTexture, TextureCoords).z < minVal)
	//{
	//	return texture(realTexture, TextureCoords);		
	//}

	col += kernel[0] * texture(renderTexture, TextureCoords.st + vec2(-offsetblur, offsetblur));
	col += kernel[1] * texture(renderTexture, TextureCoords.st + vec2(0.0, offsetblur));
	col += kernel[2] * texture(renderTexture, TextureCoords.st + vec2(offsetblur, offsetblur));
	col += kernel[3] * texture(renderTexture, TextureCoords.st + vec2(-offsetblur, 0.0));
	col += kernel[4] * texture(renderTexture, TextureCoords.st + vec2(0.0, 0.0));
	col += kernel[5] * texture(renderTexture, TextureCoords.st + vec2(offsetblur, 0.0));
	col += kernel[6] * texture(renderTexture, TextureCoords.st + vec2(-offsetblur, -offsetblur));
	col += kernel[7] * texture(renderTexture, TextureCoords.st + vec2(0.0, offsetblur));
	col += kernel[8] * texture(renderTexture, TextureCoords.st + vec2(offsetblur, offsetblur));

	return col;
 }

 vec4 grascale_effect()
 { 
	vec4 col = vec4(texture(renderTexture, TextureCoords).rgb, 1.0);
	float d = (col.x + col.y + col.z) / 3.0;
	return vec4(d, d, d, 1.0);
 }

void main()
{
	vec4 col = vec4(0.0);
	switch(cur_effect)
	{
		case 0:
			col = texture(renderTexture, TextureCoords);
			break;
		case 1:
			col = blur_effect();
			break;
		case 2:
			col = grascale_effect();
			break;
		case 3:
			col = kernel_effect();
			break;
		default:
			col = texture(renderTexture, TextureCoords);
			break;
	}
	
	fragColor = col;
}