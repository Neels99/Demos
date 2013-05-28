// figure.cpp: реализация Cfigure

#include "stdafx.h"
#include "figure.h"
#include <windows.h>
#include <sstream>


// Cfigure



STDMETHODIMP Cfigure::draw(SHORT X, SHORT Y)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss<<"Position: "<<X<<"-"<<Y;		
	MessageBox(0,(LPCWSTR)ss.str().c_str(),L"Message",0);

	return S_OK;
}
