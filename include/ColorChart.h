#pragma once

#include <vector>

struct pixel_RGB565;

class ColorChart
{
public:
	ColorChart(int width, int height);
	~ColorChart();

	int getWidth() const;
	int getHeight() const;

	const pixel_RGB565& operator()(int row, int col) const;
	pixel_RGB565& operator()(int row, int col);

private:
	std::vector<pixel_RGB565> m_color_chart_data;
	int m_width;
	int m_height;
};

