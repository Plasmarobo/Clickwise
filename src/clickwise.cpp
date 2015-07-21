#include <queue>
#include <iostream>
#include <assert.h>
#include "clickwise.h"
#include "..\dependencies\lodepng\lodepng.h"
#include "..\dependencies\lodepng\lodepng_util.h"

void CwSymbol::SetSym(unsigned char height, unsigned char width, unsigned char dot, unsigned char dash, unsigned char unknown)
{
	m_symbol.fields.height = height & 0x1;
	m_symbol.fields.width = width & 0x7;
	m_symbol.fields.dot = dot & 0x3F;
	m_symbol.fields.dash = dash & 0x1F;
	m_symbol.fields.unknown = unknown & 0x1;
}

CwSymbol::CwSymbol()
{
	m_symbol.u16 = 0;
}

CwSymbol::CwSymbol(const CwSymbol & rhs)
{
	m_symbol.u16 = rhs.m_symbol.u16;
}

CwSymbol &CwSymbol::operator=(const CwSymbol & rhs)
{
	m_symbol.u16 = rhs.m_symbol.u16;
	return (*this);
}

CwValue CwSymbol::Value()
{
	return m_symbol;
}

CwSymbol::CwSymbol(
          unsigned char height, 
          unsigned char width, 
          unsigned char dot,
          unsigned char dash,
		  unsigned char unknown)
{
  // Or is safe since we start with zero
  /*m_symbol |= ((height << 15) & CT_height_mask);
  m_symbol |= ((width  << 12) & CT_width_mask);
  m_symbol |= ((dot    <<  6) & CT_dot_mask);
  m_symbol |= (dash           & CT_dash_mask); // The lowest bit is unused
  */
	SetSym(height, width, dot, dash, unknown);
}

CwSymbol::CwSymbol(
          unsigned char height, 
          unsigned char width, 
          unsigned char dot[],
          unsigned char dash[],
		  unsigned char unknown
	)
{
  m_symbol.u16 = 0;
  // Or is safe since we start with zero
  
  unsigned char dot_value  = 0;
  unsigned char dash_value = 0;
  // Convert the array to a single value
  for(unsigned int i = 0; i < 6; ++i)
  {
    dot_value |= (dot[5-i] << i);
  }
  
  for(unsigned int i = 0; i < 5; ++i)
  {
    dash_value |= (dash[4-i] << (i+1));
  }
  
  SetSym(height, width, dot_value, dash_value, unknown);
}

CwSymbol::CwSymbol(
	unsigned char height,
	unsigned char width,
	unsigned int dot[],
	unsigned int dash[],
	unsigned char unknown)
{
	unsigned char dot_value = 0;
	unsigned char dash_value = 0;
	for (unsigned int i = 0; i < 6; ++i)
	{
		dot_value |= (dot[5 - i] << i);
	}

	for (unsigned int i = 0; i < 5; ++i)
	{
		dash_value |= (dash[4 - i] << (i + 1));
	}
	SetSym(height, width, dot_value, dash_value, unknown);
}

CwSymbol::CwSymbol(
	unsigned int height, 
	unsigned int width, 
	unsigned int dot[], 
	unsigned int dash[],
	unsigned int unknown
	)
{
	unsigned char dot_value = 0;
	unsigned char dash_value = 0;
	for (unsigned int i = 0; i < 6; ++i)
	{
		dot_value |= (dot[5 - i] << i);
	}

	for (unsigned int i = 0; i < 5; ++i)
	{
		dash_value |= (dash[4 - i] << (i + 1));
	}
	SetSym(height, width, dot_value, dash_value, unknown);
}

CwSymbol::CwSymbol(unsigned int height, unsigned int width, unsigned int dot, unsigned int dash, unsigned int unknown)
{
	SetSym(height, width, dot, dash, unknown);
}

bool CwSymbol::operator==(const CwSymbol & rhs)
{
	return (m_symbol.u16 == rhs.m_symbol.u16);
}

CwSymbol CwSymbolStream::TranslateCharacter(const char &value)
{
	return CwSymbol();
}

char CwSymbolStream::TranslateSymbol(const CwSymbol &value)
{
	return 0;
}

CwSymbolStream::CwSymbolStream()
{
	//m_buffer.reserve(128);
	m_read_pointer = 0;
}

CwSymbolStream & CwSymbolStream::Write(const char * string)
{
	// TODO: insert return statement here
	unsigned int length = strlen(string);
	for (unsigned int i = 0; i < length; ++i)
	{
		this->Write(string[i]);
	}
	return (*this);
}

CwSymbolStream & CwSymbolStream::Write(const char value)
{
	this->m_buffer.push(this->TranslateCharacter(value));
	return (*this);
}

CwSymbolStream & CwSymbolStream::Write(unsigned int value)
{
	char buffer[11];
	_itoa_s(value, buffer, 11, 10);
	buffer[11] = '\0';
	this->Write(buffer);
	return (*this);
}

CwSymbolStream & CwSymbolStream::Write(int value)
{
	char buffer[11];
	_itoa_s(value, buffer, 11, 10);
	buffer[11] = '\0';
	if (value < 0)
	{
		char str[12];
		strcpy_s(&(str[1]), 11, buffer);
		str[0] = '-';
		this->Write(str);
	}
	else
	{
		this->Write(buffer);
	}
	return (*this);
	
}

bool CwSymbolStream::Read(CwSymbol *buf)
{
	if (buf != NULL && m_buffer.size() > 0)
	{
		*buf = m_buffer.front();
		m_buffer.pop();
		return true;
		
	}
	return false;
}

bool CwSymbolStream::ReadCharacter(char *buf_c)
{
	if (buf_c != NULL)
	{
		CwSymbol buf;
		if (this->Read(&buf))
		{
			*buf_c = this->TranslateSymbol(buf);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

unsigned int CwSymbolStream::Size()
{
	return m_buffer.size();
}

CwSymbolBrush::CwSymbolBrush()
{
}

CwSymbolBrush::CwSymbolBrush(unsigned int width, 
	unsigned int height, 
	unsigned int dot_radius, 
	unsigned int dash_length, 
	unsigned int dash_width,
	unsigned int dot_color, 
	unsigned int dot_fade_radius, 
	float dot_fade_strength, 
	unsigned int dash_color, 
	unsigned int dash_fade_distance, 
	float dash_fade_strength, 
	unsigned int box_color,
	unsigned int startstop_height, 
	unsigned int pad)
{
	m_width = width;
	m_height = height;
	m_dot_radius = dot_radius;
	m_dash_length = dash_length;
	m_dash_width = dash_width;
	m_dot_color = dot_color;
	m_dot_fade_radius = dot_fade_radius;
	m_dot_fade_strength = dot_fade_strength;
	m_dash_color = dash_color;
	m_dash_fade_distance = dash_fade_distance;
	m_dash_fade_strength = dash_fade_strength;
	m_box_color = box_color;
	m_startstop_height = startstop_height;
	m_pad = pad;

}


void CwImage::DrawDot(float x, float y)
{
	unsigned int min_x = (unsigned int)floor(x - (float)this->m_brush->m_dot_radius);
	unsigned int max_x = (unsigned int)ceil(x + (float)this->m_brush->m_dot_radius);
	unsigned int min_y = (unsigned int)floor(y - (float)this->m_brush->m_dot_radius);
	unsigned int max_y = (unsigned int)ceil(y + (float)this->m_brush->m_dot_radius);
	assert(min_x > 0);
	assert(max_x < this->m_width);
	assert(min_y > 0);
	assert(max_y < this->m_height);
	//Weird rasterization
	//Should be improved to a symetrical algorithm
	for (unsigned int j = min_y; j <= max_y; ++j)
	{
		for (unsigned int i = min_x; i <= max_x; ++i)
		{
			float rad = (float)this->m_brush->m_dot_radius + 0.51f;
			if ((i*i + j*j) < (rad*rad))
			{
				this->SetPixel(i, j, this->m_brush->m_dot_color);
			}
		}
	}
}

void CwImage::DrawDash(float x, float y, unsigned int height)
{
	unsigned int min_x = (unsigned int)floor(x - ((float)this->m_brush->m_dash_width / 2.0f));
	unsigned int max_x = (unsigned int)ceil(x + ((float)this->m_brush->m_dash_width / 2.0f));
	unsigned int min_y = (unsigned int)floor(y);
	unsigned int max_y = (unsigned int)ceil(y) + height;
	assert(min_x > 0);
	assert(max_x < this->m_width);
	assert(min_y > 0);
	assert(max_y < this->m_height);
	unsigned int width = max_x - min_x;
	//unsigned int height = max_y - min_y;
	unsigned int *line = new unsigned int[width];
	for (unsigned int i = 0; i < width; ++i)
	{
		line[i] = this->m_brush->m_dash_color;
	}
	this->BltLine(width, height, min_x, min_y, line);
	delete[] line;
}

void CwImage::DrawBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	assert(x > 0);
	assert(x+width < this->m_width);
	assert(y > 0);
	assert(y+height < this->m_height);
	unsigned int *line = new unsigned int[width];
	for (unsigned int i = 0; i < width; ++i)
	{
		line[i] = this->m_brush->m_box_color;
	}
	this->BltLine(width, height, x, y, line);
	delete[] line;
}

void CwImage::DrawUnknown(float x, float y, float width, float height)
{
	unsigned int min_x = (unsigned int)floor(x);
	unsigned int min_y = (unsigned int)floor(y);
	unsigned int max_x = (unsigned int)ceil(x + width);
	unsigned int max_y = (unsigned int)ceil(y + height);
	unsigned int aligned_width = (unsigned int)ceil(width);
	unsigned int *line = new unsigned int[aligned_width];
	for (int i = 0; i < width; ++i)
	{
		line[i] = 0xFF0000FF;
	}
	this->BltLine(aligned_width, (unsigned int)ceil(height), min_x, min_y, line);
	delete[] line;
}

unsigned int CwImage::DrawSymbol(unsigned int x, unsigned int y, CwSymbol * sym)
{
	// Parse the symbol
	CwValue val = sym->Value();
	if (val.fields.unknown)
	{
		this->DrawUnknown((float)x, (float)y, (float)m_brush->m_width, (float)m_brush->m_height);
		return m_brush->m_width;
	}
	else
	{
		unsigned int height = (val.fields.height == CW_SHORT) ? (unsigned int)floor((float)m_brush->m_height * CW_SHORT_COEFF) : m_brush->m_height;
		unsigned int width = m_brush->m_width;
		switch (val.fields.width)
		{
		case CW_SPACE:
			return width = (unsigned int)floor((float)width * CW_TINY_COEFF);
		case CW_FINE:
			width = (unsigned int)floor((float)width * CW_FINE_COEFF);
			break;
		case CW_TINY:
			width = (unsigned int)floor((float)width * CW_TINY_COEFF);
			break;
		case CW_SMALL:
			width = (unsigned int)floor((float)width * CW_SMALL_COEFF);
			break;
		case CW_MED:
			width = (unsigned int)floor((float)width * CW_MED_COEFF);
			break;
		case CW_MAX:
			width = (unsigned int)floor((float)width * CW_MAX_COEFF);
			break;
		default:
			assert(false);
			break;
		}
		this->DrawBox(x, y, width, height);
		//Divide height into cells
		unsigned int cell_height = height / 6;

		//unsigned int cell_width = width;
		float f_y = (float)y + ((float)cell_height / 2.0f);
		float f_x = (float)x + ((float)width / 2.0f);
		for (int i = 0; i < 5; ++i)
		{
			if (val.fields.dash & (1 << i))
			{
				this->DrawDash(f_x, f_y, cell_height);
			}
			if (val.fields.dot & (1 << i))
			{
				this->DrawDot(f_x, f_y);
			}
			f_y += cell_height;
		}
		if (val.fields.dot & (1 << 5))
		{
			this->DrawDot(f_x, f_y);
		}
		return width;
	}
	
}

void CwImage::SetPixel(unsigned int x, unsigned int y, unsigned int value)
{
	assert(x > 0);
	assert(x < this->m_width);
	assert(y > 0);
	assert(y < this->m_height);
	this->m_image_data[x + (y*this->m_width)] = value;
}

void CwImage::BltLine(unsigned int width, unsigned int height, unsigned int min_x, unsigned int min_y, unsigned int * line)
{
	unsigned int pitch = this->m_width; // Should auto-align to 32 bit values
	unsigned int offset = min_x + (pitch * min_y);
	unsigned int *img_ptr = m_image_data + offset;
	for (unsigned int j = 0; j < height; ++j)
	{
		memcpy(img_ptr, line, width * sizeof(unsigned int));
		img_ptr += pitch;
	}
}

unsigned int CwImage::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (0xFF000000 & r << 24) | (0xFF0000 & g << 16) | (0xFF00 & b << 8) | (0xFF & a);
}

CwImage::CwImage(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	m_image_data = new unsigned int[m_width*m_height];
}

void CwImage::DrawStream(CwSymbolStream * stream)
{
	delete[] m_image_data;
	unsigned int length = stream->Size();
	this->m_width = ((this->m_brush->m_pad + this->m_brush->m_width) * length) + this->m_brush->m_pad;
	this->m_height = (this->m_brush->m_pad * 2) + this->m_brush->m_height;
	m_image_data = new unsigned int[m_width*m_height];
	unsigned int *line = new unsigned int[m_width];
	for (unsigned int i = 0; i < m_width; ++i)
	{
		line[i] = 0xAAAAAAFF;
	}
	this->BltLine(m_width, m_height, 0, 0, line);
	delete[] line;
	unsigned int y = this->m_brush->m_pad;
	unsigned int x = this->m_brush->m_pad;
	unsigned int width = 0;
	while (stream->Size() > 0)
	{
		CwSymbol current;
		stream->Read(&current);
		width = this->DrawSymbol(x, y, &current);
		x += this->m_brush->m_pad + width;
	}
}

void CwImage::SetBrush(CwSymbolBrush * brush)
{
	m_brush = brush;
}

bool CwImage::SaveToFile(char * filename)
{
	return false;
}

CwPng::CwPng(unsigned int width, unsigned int height) : CwImage(width, height)
{
}

bool CwPng::SaveToFile(char * filename)
{
	unsigned char* image_data = reinterpret_cast<unsigned char*>(m_image_data);
	unsigned int error = lodepng::encode(filename, image_data, m_width, m_height);
	if (error)
	{
		std::cout << "Encoder Error" << error << ":" << lodepng_error_text(error) << std::endl;
		system("pause");
		return false;
	}
	else
	{
		return true;
	}
}