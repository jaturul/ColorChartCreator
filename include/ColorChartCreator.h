#pragma once

#include <memory>

class ColorChart;

struct ColorChartDisplayInformation;
struct pixel_RGB565;
struct pixel_RGB565_delta;

class ColorChartCreator
{
public:
	ColorChartCreator();
	~ColorChartCreator();

	std::unique_ptr<ColorChart> createColorChart( ColorChartDisplayInformation colorChartDisplayInformation, int width, int height );

	friend class ColorChartCreatorTest;

protected:
	pixel_RGB565_delta computePixelDelta(pixel_RGB565 startPixel, pixel_RGB565 endPixel, int pixelDistance);

	int m_width;
	int m_height;
};

