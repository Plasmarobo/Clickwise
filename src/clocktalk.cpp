#include "clickwise.h"
#include "clocktalk.h"
#include <assert.h>

CtSymbols::CtSymbols()
{
	m_symbol_map = new CwSymbol[CT_TOKEN_COUNT];

	//CwSymbol(h,w,do,da)
	m_symbol_map[CT_STARTSTOP] = CwSymbol(1u, 3u, 0u, 0u, 0u);
	m_symbol_map[CT_SPACE] = CwSymbol(0u, 0u, 0u, 0u, 0u);
	m_symbol_map[CT_A] = CwSymbol(0u, 1u, 0u, 0u, 0u);
	{
		unsigned int dots[6] = { 1, 1, 0, 0, 1, 0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_B] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,1,1,0,1,0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_C] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,1,1,1,0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_D] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_E] = CwSymbol(0u, 2u, 0u, 0u, 0);
	{
		unsigned int dots[6] = { 1,1,0,0,0,0 };
		unsigned int dashes[5] = { 1,0,0,0,0 };
		m_symbol_map[CT_F] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,0,1,1,0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_G] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_H] = CwSymbol(0u, 5u, 0u, 0u, 1);
	m_symbol_map[CT_I] = CwSymbol(0u, 3u, 0u, 0u, 0);
	{
		unsigned int dots[6] = { 1,1,0,0,1,1 };
		unsigned int dashes[5] = { 1,1,1,1,1 };
		m_symbol_map[CT_J] = CwSymbol(0u, 5u, dots , dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,1,1,1,1 };
		unsigned int dashes[5] = { 1,1,1,1,1 };
		m_symbol_map[CT_K] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,1,0,0,0 };
		unsigned int dashes[5] = { 1,1,0,0,0 };
		m_symbol_map[CT_L] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,0,1,0,0 };
		unsigned int dashes[5] = { 1,1,1,0,0 };
		m_symbol_map[CT_M] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,0,0,1,0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_N] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_O] = CwSymbol(0u, 4u, 0u, 0u, 0);
	{
		unsigned int dots[6] = { 1,1,0,1,1,0 };
		unsigned int dashes[5] = { 1,1,1,1,0 };
		m_symbol_map[CT_P] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_Q] = CwSymbol(0u, 5u, 0u, 0u, 1);
	{
		unsigned int dots[6] = { 1,0,0,1,0,1 };
		unsigned int dashes[5] = { 1,1,1,0,0 };
		m_symbol_map[CT_R] = CwSymbol(0u, 5u, dots , dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,0,0,0,0,1 };
		unsigned int dashes[5] = { 1,1,1,1,1 };
		m_symbol_map[CT_S] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	{
		unsigned int dots[6] = { 1,1,0,1,1,1 };
		unsigned int dashes[5] = { 1,1,1,1,1 };
		m_symbol_map[CT_T] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_U] = CwSymbol(0u, 5u, 0u, 0u, 0);
	m_symbol_map[CT_V] = CwSymbol(0u, 5u, 0u, 0u, 1);
	{
		unsigned int dots[6] = { 1,0,0,0,1,1 };
		unsigned int dashes[5] = { 1,1,1,1,1 };
		m_symbol_map[CT_W] = CwSymbol(0u, 5u, dots, dashes, 0);
	}
	m_symbol_map[CT_X] = CwSymbol(0u, 5u, 0u, 0u, 1);
	m_symbol_map[CT_Y] = CwSymbol(0u, 5u, 0u, 0u, 1);
	m_symbol_map[CT_Z] = CwSymbol(0u, 5u, 0u, 0u, 1);
	m_symbol_map[CT_0] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_1] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_2] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_3] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_4] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_5] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_6] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_7] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_8] = CwSymbol(0u, 0u, 0u, 0u, 1);
	m_symbol_map[CT_9] = CwSymbol(0u, 0u, 0u, 0u, 1);
}
CtSymbols::~CtSymbols()
{
	delete[] m_symbol_map;
}
CwSymbol CtSymbols::Encode(const char &value)
{
	CwSymbol sym;
	if (value == ' ')
	{
		sym =  m_symbol_map[CT_SPACE];
	}
	else
	{
		if (value <= '9')
		{
			assert(value >= '0');
			sym = m_symbol_map[CT_0 + (value - '0')];
		}
		else
		{
			if (value <= 'Z')
			{
				assert(value >= 'A');
				sym = m_symbol_map[CT_A + (value - 'A')];
			}
			else
			{
				if (value <= 'z')
				{
					assert(value >= 'a');
					sym = m_symbol_map[CT_A + (value - 'a')];
				}
				else
				{
					sym = CwSymbol(0u, 0u, 0u, 0u, 1u); //Error
				}
			}
		}
	}
	return sym;
}
char CtSymbols::Decode(const CwSymbol &value)
{
	for (unsigned int i = 0; i < CT_TOKEN_COUNT; ++i)
	{
		if (m_symbol_map[i] == value)
		{
			if (i != CT_SPACE)
			{
				if (i == CT_STARTSTOP)
				{
					return '\n';
				}
				else
				{
					if (i < CT_0)
					{
						return 'A' + (i - CT_A);
					}
					else
					{
						return '0' + (i - CT_0);
					}
				}
			}
			else
			{
				return ' ';
			}
		}
	}
	return 4; //EOT error
}
;

CwSymbol CtSymbolStream::TranslateCharacter(const char &value)
{
	return m_dictionary->Encode(value);
}

char CtSymbolStream::TranslateSymbol(const CwSymbol &value)
{
	return m_dictionary->Decode(value);
}

CtSymbolStream::CtSymbolStream(CtSymbols * dictionary) : CwSymbolStream()
{
	m_dictionary = new CtSymbols;
}

CtSymbolStream::~CtSymbolStream()
{
	delete m_dictionary;
}
