#include "include/ColorChart.h"

#include "include/pixel_RGB565.h"


ColorChart::ColorChart(int width, int height)
	: m_width(width)
	, m_height(height)
	, m_color_chart_data(width * height)
{
}


ColorChart::~ColorChart()
{
}

int ColorChart::getWidth() const
{
	return m_width;
}

int ColorChart::getHeight() const
{
	return m_height;
}

const pixel_RGB565 & ColorChart::operator()(int row, int col) const
{
	return m_color_chart_data[row * m_width + col];
}

pixel_RGB565& ColorChart::operator()(int row, int col)
{
	return const_cast<pixel_RGB565&> (static_cast<const ColorChart&>(*this)(row, col));
}

