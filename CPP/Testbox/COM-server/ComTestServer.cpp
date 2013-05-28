// ComTestServer.cpp: реализация CComTestServer

#include "stdafx.h"
#include "ComTestServer.h"


// CComTestServer



STDMETHODIMP CComTestServer::square(LONG sizeA, LONG sizeB, LONG* result)
{
	*result = sizeA*sizeB;
	return S_OK;
}
