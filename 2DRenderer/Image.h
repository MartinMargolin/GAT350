#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <string>


class Image
{
public: 
	ColorBuffer colorBuffer;

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	friend class Framebuffer;
private:
	uint8_t header[54];


};