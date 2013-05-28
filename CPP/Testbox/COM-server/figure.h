// figure.h: ���������� Cfigure

#pragma once
#include "resource.h"       // �������� �������



#include "COMserver_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "������������� COM-������� �� �������������� ������� ������� ���������� Windows CE, �������� ����������� Windows Mobile, � ������� �� ������������� ������ ��������� DCOM. ���������� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, ����� ��������� ATL ������������ �������� ������������� COM-�������� � ��������� ������������� ��� ���������� ������������� COM-��������. ��� ��������� ������ � ����� rgs-����� ������ �������� 'Free', ��������� ��� ������������ ��������� ������, �������������� ��-DCOM ����������� Windows CE."
#endif

using namespace ATL;


// Cfigure

class ATL_NO_VTABLE Cfigure :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cfigure, &CLSID_figure>,
	public IDispatchImpl<Ifigure, &IID_Ifigure, &LIBID_COMserverLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	Cfigure()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FIGURE)


BEGIN_COM_MAP(Cfigure)
	COM_INTERFACE_ENTRY(Ifigure)
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



	STDMETHOD(draw)(SHORT X, SHORT Y);
};

OBJECT_ENTRY_AUTO(__uuidof(figure), Cfigure)
