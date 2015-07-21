#ifndef CLOCKTALK_H
#define CLOCKTALK_H
#include "clickwise.h"

enum CtTokens
{
	CT_STARTSTOP = 0,
	CT_SPACE,
	CT_A,
	CT_B,
	CT_C,
	CT_D,
	CT_E,
	CT_F,
	CT_G,
	CT_H,
	CT_I,
	CT_J,
	CT_K,
	CT_L,
	CT_M,
	CT_N,
	CT_O,
	CT_P,
	CT_Q,
	CT_R,
	CT_S,
	CT_T,
	CT_U,
	CT_V,
	CT_W,
	CT_X,
	CT_Y,
	CT_Z,
	CT_0,
	CT_1,
	CT_2,
	CT_3,
	CT_4,
	CT_5,
	CT_6,
	CT_7,
	CT_8,
	CT_9,
	CT_TOKEN_COUNT
};

class CtSymbols
{
protected:
	CwSymbol *m_symbol_map;
public:
	CtSymbols();
	~CtSymbols();

	CwSymbol Encode(const char &value);
	char Decode(const CwSymbol &value);
};

class CtSymbolStream : public CwSymbolStream
{
protected:
	CtSymbols *m_dictionary;
	virtual CwSymbol TranslateCharacter(const char &value);
	virtual char     TranslateSymbol(const CwSymbol &value);
public:
	CtSymbolStream(CtSymbols *dictionary);
	~CtSymbolStream();

};

#endif