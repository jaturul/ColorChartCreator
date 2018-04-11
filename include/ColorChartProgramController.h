#pragma once

#include <memory>
#include <string>

class ColorChart;
class ColorChartCreator;
class ColorChartCreatorInputProcessor;
class Display;

struct pixel_RGB565;

class ColorChartProgramController
{
public:
	ColorChartProgramController(int minimumArgumentCount, int maximumArgumentCount, int redChannelBitWidth, int greenChannelBitWidth, int blueChannelBitWidth);
	~ColorChartProgramController();

	int runProgram(int argc, char** argv);

private:
	void passColorChartDataToDisplay(const ColorChart& colorChart, Display& display, const std::string& displayName, int displayWidth, int displayHeight);
	unsigned short computeCombinedColorValue(const pixel_RGB565& pixelColors);
	
	//Debug
	void displayColorChartWithColorChannels(const ColorChart& colorChart);

	int m_red_channel_bit_width;
	int m_green_channel_bit_width;
	int m_blue_channel_bit_width;
	int m_display_width;
	int m_display_height;

	std::unique_ptr<ColorChartCreator> m_color_chart_creator;
	std::unique_ptr<ColorChartCreatorInputProcessor> m_color_chart_creator_input_processor;
	std::unique_ptr<Display> m_display;
};

