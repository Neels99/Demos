// ComTestServer.h: объявление CComTestServer

#pragma once
#include "resource.h"       // основные символы



#include "COMserver_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CComTestServer

class ATL_NO_VTABLE CComTestServer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComTestServer, &CLSID_ComTestServer>,
	public IDispatchImpl<IComTestServer, &IID_IComTestServer, &LIBID_COMserverLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComTestServer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMTESTSERVER)


BEGIN_COM_MAP(CComTestServer)
	COM_INTERFACE_ENTRY(IComTestServer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(square)(LONG sizeA, LONG sizeB, LONG* result);
};

OBJECT_ENTRY_AUTO(__uuidof(ComTestServer), CComTestServer)
