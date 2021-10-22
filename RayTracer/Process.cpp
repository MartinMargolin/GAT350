#include "Process.h"

void Process::BoxBlur(const ColorBuffer& colorBuffer)
{
	ColorBuffer source = colorBuffer;
	int16_t k[3][3] =
	{
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};

	for (int i = 0; i < source.width * source.height; i++)
	{
		int x = i % source.width;
		int y = i / source.width;

		if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

		int16_t r = 0;
		int16_t g = 0;
		int16_t b = 0;

		for (int iy = -1; iy <= 1 ; iy++)
		{
			for (int ix = -1; ix <= 1; ix++)
			{
				r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[ix + 1][iy + 1];
				g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[ix + 1][iy + 1];
				b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[ix + 1][iy + 1];
			}
		}

		color_t& color = ((color_t*)colorBuffer.data)[i];
		color.r = r / 9;
		color.g = g / 9;
		color.b = b / 9;
	}
}

void Process::GaussianBlur(const ColorBuffer& colorBuffer)
{
	ColorBuffer source = colorBuffer;
	int16_t k[3][3] =
	{
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1}
	};

	for (int i = 0; i < source.width * source.height; i++)
	{
		int x = i % source.width;
		int y = i / source.width;

		if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

		int16_t r = 0;
		int16_t g = 0;
		int16_t b = 0;

		for (int iy = -1; iy <= 1; iy++)
		{
			for (int ix = -1; ix <= 1; ix++)
			{
				r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[ix + 1][iy + 1];
				g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[ix + 1][iy + 1];
				b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[ix + 1][iy + 1];
			}
		}

		color_t& color = ((color_t*)colorBuffer.data)[i];
		color.r = r / 16;
		color.g = g / 16;
		color.b = b / 16;
	}
}

void Process::Sharpen(const ColorBuffer& colorBuffer)
{
	ColorBuffer source = colorBuffer;
	int16_t k[3][3] =
	{
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	for (int i = 0; i < source.width * source.height; i++)
	{
		int x = i % source.width;
		int y = i / source.width;

		if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

		int16_t r = 0;
		int16_t g = 0;
		int16_t b = 0;

		for (int iy = -1; iy <= 1; iy++)
		{
			for (int ix = -1; ix <= 1; ix++)
			{
				r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[ix + 1][iy + 1];
				g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[ix + 1][iy + 1];
				b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[ix + 1][iy + 1];
			}
		}

		color_t& color = ((color_t*)colorBuffer.data)[i];
		color.r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
		color.g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
		color.b = (b < 0) ? 0 : ((b > 255) ? 255 : b);
	}
}

void Process::Monochrome(const ColorBuffer& colorBuffer)
{
	for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++)
	{
		color_t& color = ((color_t*)colorBuffer.data)[i];
		uint16_t sum = (color.r + color.g + color.b);
		uint8_t average = sum / 3;
			color.r = average;
			color.g = average;
			color.b = average;
	}
}

void Process::Edge(const ColorBuffer& colorBuffer, uint8_t threshold)
{
	ColorBuffer source = colorBuffer;

	int16_t kh[3][3] =
	{
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	};

	int16_t kv[3][3] =
	{
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};


	for (int i = 0; i < source.width * source.height; i++)
	{
		int x = i % source.width;
		int y = i / source.width;

		if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;


		int16_t h = 0;
		int16_t v = 0;


		for (int iy = -1; iy <= 1; iy++)
		{
			for (int ix = -1; ix <= 1; ix++)
			{
				h += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * kh[ix + 1][iy + 1];
				v += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * kv[ix + 1][iy + 1];

			}
		}

		uint16_t result = (uint16_t)sqrt((h * h) + (v * v));

		result = (result > threshold) ? result : 0;

		uint8_t c = (result < 0) ? 0 : ((result > 255) ? 255 : result);


		color_t& color = ((color_t*)colorBuffer.data)[i];
		color.r = c;
		color.g = c;
		color.b = c;

	}

}