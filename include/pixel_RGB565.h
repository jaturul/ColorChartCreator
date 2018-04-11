#pragma once

#include "pixel_RGB565_delta.h"

#include <math.h>

struct pixel_RGB565
{
	unsigned char red_channel;
	unsigned char green_channel;
	unsigned char blue_channel;

	pixel_RGB565 operator+(pixel_RGB565_delta colorDelta)
	{
		pixel_RGB565 result;

		result.red_channel   = static_cast<int>(round(this->red_channel   + colorDelta.red_channel_delta));
		result.green_channel = static_cast<int>(round(this->green_channel + colorDelta.green_channel_delta));
		result.blue_channel  = static_cast<int>(round(this->blue_channel  + colorDelta.blue_channel_delta));

		return result;
	}

	pixel_RGB565_delta operator-(pixel_RGB565 otherPixel)
	{
		pixel_RGB565_delta result;

		result.red_channel_delta   = static_cast<float>(this->red_channel - otherPixel.red_channel);
		result.green_channel_delta = static_cast<float>(this->green_channel - otherPixel.green_channel);
		result.blue_channel_delta  = static_cast<float>(this->blue_channel - otherPixel.blue_channel);

		return result;
	}
};