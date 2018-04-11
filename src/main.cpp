#include "include/ColorChartProgramController.h"

namespace
{
	const int MINIMUM_ARGUMENT_COUNT = 4; //file name included 
	const int MAXIMUM_ARGUMENT_COUNT = 6; //file name included 
	const int NUMBER_OF_RED_CHANNEL_BITS = 5;
	const int NUMBER_OF_GREEN_CHANNEL_BITS = 6;
	const int NUMBER_OF_BLUE_CHANNEL_BITS = 5;
}

int main(int argc, char** argv)
{
	ColorChartProgramController color_chart_program_controller
	(MINIMUM_ARGUMENT_COUNT, MAXIMUM_ARGUMENT_COUNT, NUMBER_OF_RED_CHANNEL_BITS, NUMBER_OF_GREEN_CHANNEL_BITS, NUMBER_OF_BLUE_CHANNEL_BITS);

	return color_chart_program_controller.runProgram(argc, argv);
}