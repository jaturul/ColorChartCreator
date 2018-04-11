#include "include/ColorChartProgramController.h"
#include "include/ColorChart.h"
#include "include/ColorChartCreator.h"
#include "include/ColorChartDisplayInformation.h"
#include "include/ColorChartCreatorInputProcessor.h"
#include "include/Display.h"
#include "include/pixel_RGB565.h"

#include <iostream>

namespace
{
	const bool DEBUG_MODE = true;
}

//-------------------------------------------------------------------------
ColorChartProgramController::ColorChartProgramController
							 (int minimumArgumentCount, int maximumArgumentCount, int redChannelBitWidth, int greenChannelBitWidth, int blueChannelBitWidth)
	: m_red_channel_bit_width(redChannelBitWidth)
	, m_green_channel_bit_width(greenChannelBitWidth)
	, m_blue_channel_bit_width(blueChannelBitWidth)
	, m_color_chart_creator(new ColorChartCreator())
	, m_color_chart_creator_input_processor(new ColorChartCreatorInputProcessor(minimumArgumentCount, maximumArgumentCount, redChannelBitWidth, greenChannelBitWidth, blueChannelBitWidth))
	, m_display(new Display())
{
	m_display->get_size(m_display_width, m_display_height);
}

//-------------------------------------------------------------------------
ColorChartProgramController::~ColorChartProgramController()
{
}

//-------------------------------------------------------------------------
int ColorChartProgramController::runProgram(int argc, char ** argv)
{
	ColorChartDisplayInformation color_chart_display_information;
	try
	{
		color_chart_display_information = m_color_chart_creator_input_processor->createColorChartDisplayInformation(argc, argv);
	}
	catch (std::invalid_argument error)
	{
		std::cerr << "Invalid argument: " << error.what();

		return -1;
	}

	std::unique_ptr<ColorChart> color_chart = m_color_chart_creator->createColorChart(color_chart_display_information,m_display_width, m_display_height );

	if (DEBUG_MODE)
	{
		displayColorChartWithColorChannels(*color_chart);
	}
	
	passColorChartDataToDisplay(*color_chart, *m_display, color_chart_display_information.display_name, m_display_width, m_display_height);

	return 0;
}

//-------------------------------------------------------------------------
void ColorChartProgramController::passColorChartDataToDisplay(const ColorChart& colorChart, Display& display, const std::string& displayName, int displayWidth, int displayHeight)
{
	if (display.connect(displayName.c_str()))
	{
		for (int row = 0; row < displayHeight; ++row)
		{
			for (int column = 0; column < displayWidth; ++column)
			{
				unsigned short current_pixel_color = computeCombinedColorValue(colorChart(row, column));
				display.draw_raster(column, row, &current_pixel_color, 1);
			}
		}
	}
}

//-------------------------------------------------------------------------
unsigned short ColorChartProgramController::computeCombinedColorValue(const pixel_RGB565& pixelColors)
{
	unsigned short combined_colors = 0;
	unsigned short red_bits = pixelColors.red_channel << (m_blue_channel_bit_width + m_green_channel_bit_width);
	unsigned short green_bits = pixelColors.green_channel << m_blue_channel_bit_width;
	unsigned short blue_bits = pixelColors.blue_channel;

	return red_bits | green_bits | blue_bits;
}


//-------------------------------------------------------------------------
void ColorChartProgramController::displayColorChartWithColorChannels(const ColorChart& colorChart)
{
	for (int row = 0; row < colorChart.getHeight(); ++row)
	{
		for (int column = 0; column < colorChart.getWidth(); ++column)
		{
			std::cout << "(" << static_cast<int>(colorChart(row, column).red_channel) << ", " << static_cast<int>(colorChart(row, column).green_channel) << ", " << static_cast<int>(colorChart(row, column).blue_channel) << ") ";
		}

		std::cout << std::endl;
	}
}
