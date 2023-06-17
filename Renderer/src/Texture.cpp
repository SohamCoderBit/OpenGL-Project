#include "Texture.h"


Texture::Texture(const char* TextureLocation, unsigned int TexType, unsigned int Slot,unsigned int Format , unsigned int PixelType)
{
	TextureType = TexType;
	int WidthImage, HeightImage, NumColImage;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* Bytes = stbi_load(TextureLocation, &WidthImage, &HeightImage, &NumColImage, STBI_rgb_alpha);
	

	glGenTextures(1, &TextureID);
	glActiveTexture(Slot);
	glBindTexture(TexType, TextureID);

	glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(TexType, 0, GL_RGBA, WidthImage, HeightImage, 0, Format, PixelType,Bytes);
	glGenerateMipmap(TexType);


	stbi_image_free(Bytes);

	glBindTexture(TexType, 0);


}

void Texture::TextureUnit(Shader* shader, const char* Uniform, unsigned int Unit)
{
	int TextureUniform = shader->GetUniformLocation(Uniform);
	shader->Bind();
	glUniform1i(TextureUniform, Unit);
}
Texture::~Texture()
{
	UnBind();
	Delete();
}
void Texture::Bind()
{
	glBindTexture(TextureType, TextureID);
}

void Texture::UnBind()
{
	glBindTexture(TextureType, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &TextureID);
}