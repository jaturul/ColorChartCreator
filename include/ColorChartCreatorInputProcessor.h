#pragma once

#include <bitset>
#include <string>
#include <vector>

struct ColorChartDisplayInformation;
struct pixel_RGB565;

class ColorChartCreatorInputProcessor
{
public:
	ColorChartCreatorInputProcessor(int minimumArgumentCount, int maximumArgumentCount, int numberOfRedChannelBits, int numberOfGreenChannelBits, int numberOfBllueChannelBits);
	~ColorChartCreatorInputProcessor();
	
	ColorChartDisplayInformation createColorChartDisplayInformation(int argc, char** argv);

private:
	std::vector<std::string> createArgumentVector(int argc, char** argv);

	void throwIfWrongArgumentCount(int argc);
	void throwIfWrongArgumentType(std::vector<std::string> argumentVector);
	void throwIfWrongPixelColorSize(std::vector<std::string> argumentVector);

	bool isCorrectColorValueSize(const std::string& decimalNumber) const;
	bool isDecimal(const std::string& number) const;
	bool isHexadecimal(const std::string& number) const;

	ColorChartDisplayInformation createInputDataStructure() const;

	std::string getDisplayName() const;
	pixel_RGB565 getTopLeftColor() const;
	pixel_RGB565 getTopRightColor() const;
	pixel_RGB565 getBottomLeftColor() const;
	pixel_RGB565 getBottomRightColor() const;

	pixel_RGB565 computeColorPixel(const std::string& decimalString) const;	

	//Debug
	void displayArgumentVector(std::vector<std::string> argumentVector);

	int m_minimum_argument_count;
	int m_maximum_argument_count;
	int m_number_of_red_channel_bits;
	int m_number_of_green_channel_bits;
	int m_number_of_blue_channel_bits;

	std::vector<std::string> m_argument_vector;
};

