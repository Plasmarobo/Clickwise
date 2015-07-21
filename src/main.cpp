#include <assert.h>
#include <iostream>
#include "clickwise.h"
#include "clocktalk.h"

int main(int argc, void * argv)
{
	// Unit tests
	// * Single Char tests
	{
		char a = 'a';
		char z = 'z';
		char b = 'b';
		CtSymbols symbols;
		//Encoding TEST

		//Must match clocktalk.cpp
		CwSymbol a_sym(0u, 1u, 0u, 0u, 0u);
		CwSymbol z_sym(0u, 0u, 0u, 0u, 1);
		unsigned int dots[6] = { 1, 1, 0, 0, 1, 0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		CwSymbol b_sym(0u, 5u, dots, dashes, 0);

		CwSymbol a_int = symbols.Encode(a);
		CwSymbol z_int = symbols.Encode(z);
		CwSymbol b_int = symbols.Encode(b);

		assert(a_int == a_sym);
		assert(b_int == b_sym);

		char result_a = symbols.Decode(a_int);
		char result_z = symbols.Decode(z_int);
		char result_b = symbols.Decode(b_int);

		assert(result_a == 'A');
		assert(result_z != 'Z'); //Negative test
		assert(result_b == 'B');
	}
	// * Stream tests
	{
		char a = 'A';
		// TODO: Numbers
		//char * junkstring = "11@#$^)2";
		char * knownstring = "AEIOU BCDFG JKLMNP RST W   ";
		CtSymbols symbols;
		CtSymbolStream symStream(&symbols);
		CwSymbol a_sym(0u, 1u, 0u, 0u, 0u);

		symStream.Write(a);
		CwSymbol a_res;
		assert(symStream.Read(&a_res));
		assert(a_sym == a_res);

		symStream.Write(a);
		char a_res_c;
		assert(symStream.ReadCharacter(&a_res_c));
		assert(a_res_c == a);

		symStream.Write(knownstring);
		unsigned int ptr = 0;
		char buf;
		while (symStream.ReadCharacter(&buf))
		{
			assert(knownstring[ptr] == buf);
			++ptr;
		}
		assert(ptr == strlen(knownstring));
		//symStream.Write(junkstring);
		//ptr = 0;
		//while (symStream.ReadCharacter(&buf))
		//{
		//	assert(buf == 4);
		//}
	}


	// * Png tests
	{
		char *name = "Austen";
		CtSymbols symbols;
		CtSymbolStream symStr(&symbols);
		CwSymbolBrush default_brush;
		default_brush.m_box_color = 0x000000FF;
		default_brush.m_width = 32;
		default_brush.m_height = default_brush.m_width * 5;
		default_brush.m_dash_color = 0xFFFFFFFF;
		default_brush.m_dot_color =  0xFFFFFFFF;
		default_brush.m_dot_radius = 10;
		default_brush.m_dash_width = 5;
		default_brush.m_pad = 4;
		CwImage *img = new CwPng(10,10);
		img->SetBrush(&default_brush);
		char a = 'a';
		char * knownstring = "aeiou bcdfg jklmnp rst w   ";
		symStr.Write(a);
		img->DrawStream(&symStr);
		img->SaveToFile("a.png");
		symStr.Write(name);
		img->DrawStream(&symStr);
		img->SaveToFile("name.png");
		symStr.Write(knownstring);
		img->DrawStream(&symStr);
		img->SaveToFile("all.png");
		img->Test();
	}


	// * Audio tests



}