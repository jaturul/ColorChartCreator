#include "include/ColorChartCreator.h"

#include "include/ColorChart.h"
#include "include/ColorChartDisplayInformation.h"
#include "include/pixel_RGB565.h"
#include "include/pixel_RGB565_delta.h"

#include <math.h>

ColorChartCreator::ColorChartCreator()
{
}


ColorChartCreator::~ColorChartCreator()
{
}

std::unique_ptr<ColorChart> ColorChartCreator::createColorChart( ColorChartDisplayInformation colorChartCreatorInputData, int width, int height )
{
	std::unique_ptr<ColorChart> color_chart(new ColorChart(width, height));

	pixel_RGB565_delta vertical_color_delta_left_edge = computePixelDelta
														(colorChartCreatorInputData.top_left_color, colorChartCreatorInputData.bottom_left_color, height - 1);
	pixel_RGB565_delta vertical_color_delta_right_edge = computePixelDelta
														 (colorChartCreatorInputData.top_right_color, colorChartCreatorInputData.bottom_right_color, height - 1);

	for (int row = 0; row < height; ++row)
	{
		pixel_RGB565 row_left_edge_pixel = colorChartCreatorInputData.top_left_color+ vertical_color_delta_left_edge * row;
		pixel_RGB565 row_right_edge_pixel = colorChartCreatorInputData.top_right_color + vertical_color_delta_right_edge * row;

		pixel_RGB565_delta horizontal_color_delta_current_row = computePixelDelta(row_left_edge_pixel, row_right_edge_pixel, width - 1);
		for (int column = 0; column < width; ++column)
		{
			pixel_RGB565 current_pixel_color = row_left_edge_pixel + horizontal_color_delta_current_row * column;
			
			(*color_chart)(row, column) = current_pixel_color;
		}	
	}

	return color_chart;
}

pixel_RGB565_delta ColorChartCreator::computePixelDelta(pixel_RGB565 startPixel, pixel_RGB565 endPixel, int pixelDistance)
{
	return (endPixel - startPixel) / pixelDistance;
}
