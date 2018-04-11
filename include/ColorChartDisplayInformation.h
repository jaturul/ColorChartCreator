#pragma once

#include "pixel_RGB565.h"

#include <string>


struct ColorChartDisplayInformation
{
	std::string display_name;
	pixel_RGB565 top_left_color;
	pixel_RGB565 top_right_color;
	pixel_RGB565 bottom_left_color;
	pixel_RGB565 bottom_right_color;
};