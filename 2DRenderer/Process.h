#pragma once
#include "ColorBuffer.h"
#include "Renderer.h"

namespace Process
{

 void BoxBlur(const ColorBuffer& colorBuffer);
 void GaussianBlur(const ColorBuffer& colorBuffer);
 void Sharpen(const ColorBuffer& colorBuffer);
 void Monochrome(const ColorBuffer& colorBuffer);
 void Edge(const ColorBuffer& colorBuffer, uint8_t threshold);


};