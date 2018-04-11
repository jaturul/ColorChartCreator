#include "include/ColorChartDisplayInformation.h"
#include "include/ColorChartCreatorInputProcessor.h"
#include "include/pixel_RGB565.h"

#include <cassert>
#include <stdexcept>
#include <sstream>

//Debug
#include <iostream>

namespace
{
	bool DEBUG_MODE = true;

	//-------------------------------------------------------------------------
	std::string createDecimalString(const std::string& hexadecimalString)
	{
		return std::to_string(stol(hexadecimalString, nullptr, 16));
	}
}

//-------------------------------------------------------------------------
ColorChartCreatorInputProcessor::ColorChartCreatorInputProcessor(int minimumArgumentCount, int maximumArgumentCount, int numberOfRedChannelBits, int numberOfGreenChannelBits, int numberOfBlueChannelBits)
	: m_minimum_argument_count(minimumArgumentCount)
	, m_maximum_argument_count(maximumArgumentCount)
	, m_number_of_red_channel_bits(numberOfRedChannelBits)
	, m_number_of_green_channel_bits(numberOfGreenChannelBits)
	, m_number_of_blue_channel_bits(numberOfBlueChannelBits)
{
}

//-------------------------------------------------------------------------
ColorChartCreatorInputProcessor::~ColorChartCreatorInputProcessor()
{
}

//-------------------------------------------------------------------------
ColorChartDisplayInformation ColorChartCreatorInputProcessor::createColorChartDisplayInformation(int argc, char ** argv)
{
	throwIfWrongArgumentCount(argc);
	m_argument_vector = createArgumentVector(argc, argv);

	throwIfWrongArgumentType(m_argument_vector);
	throwIfWrongPixelColorSize(m_argument_vector);

	if (DEBUG_MODE)
	{
		displayArgumentVector(m_argument_vector);
	}

	return createInputDataStructure();
}

//-------------------------------------------------------------------------
std::vector<std::string> ColorChartCreatorInputProcessor::createArgumentVector( int argc, char** argv )
{
	std::vector<std::string> string_argument_vector; // not including the file name argument

	// we start with index = 1, because argv[0] is the file name
	for (int index = 1; index < argc; ++index)
	{
		std::string current_argument = std::string(argv[index]);

		string_argument_vector.push_back(current_argument);
	}

	assert(string_argument_vector.size() == argc - 1); // We don't include the file name in the input vector

	return string_argument_vector;
}

//-------------------------------------------------------------------------
void ColorChartCreatorInputProcessor::throwIfWrongArgumentCount(int argc)
{
	if ((argc < m_minimum_argument_count) || (argc > m_maximum_argument_count))
	{
		throw std::invalid_argument("Wrong number of arguments provided!!!\n");
	}
}

//-------------------------------------------------------------------------
void ColorChartCreatorInputProcessor::throwIfWrongArgumentType(std::vector<std::string> argumentVector)
{
	if (argumentVector[0].empty())
	{
		throw std::invalid_argument("Argument number 1 is empty!!!\n");
	}

	for (int index = 1; index < (int)argumentVector.size(); ++index)
	{
		if (((!isDecimal(argumentVector[index])) && (!isHexadecimal(argumentVector[index]))) ||
			(argumentVector[index].empty()))
		{
			throw std::invalid_argument("Argument number " + std::to_string(index + 1) + " is not decimal/hexadecimal or is empty!!!\n");
		}
	}
}

//-------------------------------------------------------------------------
void ColorChartCreatorInputProcessor::throwIfWrongPixelColorSize(std::vector<std::string> argumentVector)
{
	for (int index = 1; index < (int)argumentVector.size() - 1; ++index)
	{
		if (!isCorrectColorValueSize(argumentVector[index]))
		{
			throw std::invalid_argument("Argument number " + std::to_string(index) + " is of incorrect size!!!\n");
		}
	}
}

//-------------------------------------------------------------------------
bool ColorChartCreatorInputProcessor::isCorrectColorValueSize(const std::string & decimalNumber) const
{
	unsigned int decimal_number_int = std::stoi(decimalNumber);
	int number_of_color_bits = m_number_of_red_channel_bits + m_number_of_green_channel_bits + m_number_of_blue_channel_bits;

	return (decimal_number_int <= (std::pow(2, number_of_color_bits) - 1));
}

//-------------------------------------------------------------------------
bool ColorChartCreatorInputProcessor::isDecimal(const std::string & number) const
{
	if (number.empty() || ((number.size() > 1) && (number[0] == '0')))
	{
		return false;
	}

	for (auto digit : number)
	{
		if (!isdigit(digit))
		{
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------
bool ColorChartCreatorInputProcessor::isHexadecimal(const std::string & number) const
{
	std::string local_number(number);
	// A hexadecimal number needs to have the "0x"/"0X" prefix
	if ((number.size() < 3) ||
		((local_number[0] != '0') || (tolower(local_number[1]) != 'x')))
	{
		return false;
	}
	else
	{
		local_number = local_number.substr(2, local_number.size() - 2);
	}

	for (auto digit : local_number)
	{
		if (!isxdigit(digit))
		{
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------
ColorChartDisplayInformation ColorChartCreatorInputProcessor::createInputDataStructure() const
{
	ColorChartDisplayInformation input_data_structure;

	input_data_structure.display_name = getDisplayName();
	input_data_structure.top_left_color = getTopLeftColor();
	input_data_structure.top_right_color = getTopRightColor();
	input_data_structure.bottom_left_color = getBottomLeftColor();
	input_data_structure.bottom_right_color = getBottomRightColor();

	return input_data_structure;
}

//-------------------------------------------------------------------------
std::string ColorChartCreatorInputProcessor::getDisplayName() const
{
	return m_argument_vector[0];
}

//-------------------------------------------------------------------------
pixel_RGB565 ColorChartCreatorInputProcessor::getTopLeftColor() const
{
	return computeColorPixel(m_argument_vector[1]);
}

//-------------------------------------------------------------------------
pixel_RGB565 ColorChartCreatorInputProcessor::getTopRightColor() const
{
	return computeColorPixel(m_argument_vector[2]);
}

//-------------------------------------------------------------------------
pixel_RGB565 ColorChartCreatorInputProcessor::getBottomLeftColor() const
{
	if (m_argument_vector.size() > 3)
	{
		return computeColorPixel(m_argument_vector[3]);
	}

	return computeColorPixel(m_argument_vector[1]);
	
}

//-------------------------------------------------------------------------
pixel_RGB565 ColorChartCreatorInputProcessor::getBottomRightColor() const
{
	if (m_argument_vector.size() > 4)
	{
		return computeColorPixel(m_argument_vector[4]);
	}

	return computeColorPixel(m_argument_vector[2]);
}

//-------------------------------------------------------------------------
pixel_RGB565 ColorChartCreatorInputProcessor::computeColorPixel(const std::string & numberString) const
{
	unsigned int decimal_number = std::stoi(createDecimalString(numberString));
	pixel_RGB565 color_pixel;

	int blue_channel_mask = static_cast<int>(std::pow(2, m_number_of_blue_channel_bits) - 1);
	color_pixel.blue_channel =  (decimal_number) & blue_channel_mask;

	int green_channel_mask = static_cast<int>(std::pow(2, m_number_of_green_channel_bits) - 1);
	color_pixel.green_channel = (decimal_number >> m_number_of_blue_channel_bits) & green_channel_mask;
	
	int red_channel_mask = static_cast<int>(std::pow(2, m_number_of_red_channel_bits) - 1);
	color_pixel.red_channel = (decimal_number >> (m_number_of_blue_channel_bits + m_number_of_green_channel_bits)) & red_channel_mask;

	return color_pixel;
}

//-------------------------------------------------------------------------
void ColorChartCreatorInputProcessor::displayArgumentVector(std::vector<std::string> argumentVector)
{
	std::cout << "ColorChartCreatorInputProcessor data:\n";
	for (auto input_element : argumentVector)
	{
		std::cout << input_element << " || ";
	}
	std::cout << std::endl;
}
