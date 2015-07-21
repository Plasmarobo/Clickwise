#ifndef CLICKWISE_H
#define CLICKWISE_H
#include "..\dependencies\lodepng\lodepng.h"
#include <queue>


const unsigned char CW_FINE = 1;
const float CW_FINE_COEFF = 0.2f;

const unsigned char CW_SPACE = 0;
const unsigned char CW_TINY = 2;
const float CW_TINY_COEFF = 0.4f;

const unsigned char CW_SMALL = 3;
const float CW_SMALL_COEFF = 0.6f;

const unsigned char CW_MED = 4;
const float CW_MED_COEFF = 0.8f;

const unsigned char CW_MAX = 5;
const float CW_MAX_COEFF = 1.0f;

const unsigned char CW_SHORT = 1;
const float CW_SHORT_COEFF = 0.8f;


typedef 
	union {
		struct {
			unsigned short unknown : 1; //[15]
			unsigned short dash : 5; //[10-14]
			unsigned short dot : 6; //[4-9]
			unsigned short width : 3; //[1-3]
			unsigned short height : 1; // [0]
		} fields;
		unsigned short u16;
	} CwValue;


class CwSymbol
{
  protected:
	  static const unsigned short cw_height_mask = 0x8000;
	  static const unsigned short cw_width_mask  = 0x7000;
	  static const unsigned short cw_dot_mask    = 0x0FC0;
	  static const unsigned short cw_dash_mask   = 0x003F;
	  // The lowest bit of dash_mask is unused
	  CwValue m_symbol;
	  void SetSym(
		  unsigned char height,
		  unsigned char width,
		  unsigned char dot,
		  unsigned char dash,
		  unsigned char unknown
		  );
	  
  
  public:
	  CwSymbol();
	  CwSymbol(const CwSymbol &rhs);
	  CwSymbol& operator=(const CwSymbol &rhs);

	  CwValue Value();
  
	  //Construction expects unaligned values
	  CwSymbol(
			  unsigned char height,  //Height, valued between 0-1 
			  unsigned char width,   //Width, valued between 0-5
			  unsigned char dot,    //Dot,   bitmask of 6-bits
			  unsigned char dash,   //Dash,  bitmask of 5-bits
			  unsigned char unknown //Unknown, valued between 0-1
			  );
	  CwSymbol(
		   unsigned char height,
		   unsigned char width,
		   unsigned char dot[], // array 6
		   unsigned char dash[], // array 5
		   unsigned char unknown
		   );
	  // To support default-int
	  CwSymbol(
		  unsigned char height,
		  unsigned char width,
		  unsigned int dot[],
		  unsigned int dash[],
		  unsigned char unknown
		  );
	  CwSymbol(
		  unsigned int height,
		  unsigned int width,
		  unsigned int dot[],
		  unsigned int dash[],
		  unsigned int unknown
		  );
	  CwSymbol(
		  unsigned int height,
		  unsigned int width,
		  unsigned int dot,
		  unsigned int dash,
		  unsigned int unknown
		  );

	  bool operator==(const CwSymbol &rhs);
};

class CwSymbolStream
{
protected:
	std::queue<CwSymbol> m_buffer;
	unsigned int m_read_pointer;

	virtual CwSymbol TranslateCharacter(const char &value);
	virtual char     TranslateSymbol(const CwSymbol &value);
	
public:
	CwSymbolStream();

	CwSymbolStream &Write(const char *string);
	CwSymbolStream &Write(const char value);
	CwSymbolStream &Write(unsigned int value);
	CwSymbolStream &Write(int value);
	bool Read(CwSymbol *buf);
	bool ReadCharacter(char *buf);

	unsigned int Size();

};

struct CwSymbolBrush
{
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_dot_radius;
	unsigned int m_dash_length;
	unsigned int m_dash_width;
	unsigned int m_dot_color;
	unsigned int m_dot_fade_radius;
	float        m_dot_fade_strength;
	unsigned int m_dash_color;
	unsigned int m_dash_fade_distance;
	float        m_dash_fade_strength;
	unsigned int m_box_color;
	unsigned int m_startstop_height;
	unsigned int m_pad;

	CwSymbolBrush();
	CwSymbolBrush(
		unsigned int width,
		unsigned int height,
		unsigned int dot_radius,
		unsigned int dash_length,
		unsigned int dash_width,
		unsigned int dot_color,
		unsigned int dot_fade_radius,
		float        dot_fade_strength,
		unsigned int dash_color,
		unsigned int dash_fade_distance,
		float		 dash_fade_strength,
		unsigned int box_color,
		unsigned int startstop_height,
		unsigned int pad);
};

class CwImage
{
protected:
	// RGBA
	unsigned int  *m_image_data;
	unsigned int   m_height;
	unsigned int   m_width;
	unsigned int   m_background_color;
	CwSymbolBrush *m_brush;
	void DrawDot(float x, float y);
	void DrawDash(float x, float y, unsigned int height);
	void DrawBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	void DrawUnknown(float x, float y, float width, float height);
	unsigned int DrawSymbol(unsigned int x, unsigned int y, CwSymbol *sym);
	void SetPixel(unsigned int x, unsigned int y, unsigned int value);
	void BltLine(unsigned int width, unsigned int height, unsigned int min_x, unsigned int min_y, unsigned int *line);

	unsigned int RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
public:
	CwImage(unsigned int width, unsigned int height);
	
	void DrawStream(CwSymbolStream *stream);

	void SetBrush(CwSymbolBrush *brush);
	virtual bool SaveToFile(char* filename);


};

class CwPng : public CwImage
{
public:
	CwPng(unsigned int width, unsigned int height);
	virtual bool SaveToFile(char *filename);
};
#endif