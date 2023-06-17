#pragma once

#include "OpenGL.h"
#include "Shader.h"
#include "stb_imgae.h"

class Texture
{
public:
	Texture(const char* TextureLocation, unsigned int TexType, unsigned int Slot,unsigned int Format , unsigned int PixelType);
	void TextureUnit(Shader* shader, const char* Uniform, unsigned int Unit);
	~Texture();
	void Bind();
	void UnBind();
	void Delete();
private:
	unsigned int TextureID;
	unsigned int TextureType;

};