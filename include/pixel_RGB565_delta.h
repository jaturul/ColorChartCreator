#pragma once

struct pixel_RGB565_delta
{
	float red_channel_delta;
	float green_channel_delta;
	float blue_channel_delta;

	pixel_RGB565_delta operator*(int multiplier)
	{
		pixel_RGB565_delta result;

		result.red_channel_delta = this->red_channel_delta * multiplier;
		result.green_channel_delta = this->green_channel_delta * multiplier;
		result.blue_channel_delta = this->blue_channel_delta * multiplier;

		return result;
	}

	pixel_RGB565_delta operator/(int divider)
	{
		pixel_RGB565_delta result;

		result.red_channel_delta   = this->red_channel_delta   / divider;
		result.green_channel_delta = this->green_channel_delta / divider;
		result.blue_channel_delta  = this->blue_channel_delta  / divider;

		return result;
	}
};