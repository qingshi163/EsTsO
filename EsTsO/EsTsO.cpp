// EsTsO.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "EsTsO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CEsTsOApp

BEGIN_MESSAGE_MAP(CEsTsOApp, CWinApp)
END_MESSAGE_MAP()


// CEsTsOApp ����

CEsTsOApp::CEsTsOApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CEsTsOApp ����

CEsTsOApp theApp;


// CEsTsOApp ��ʼ��

BOOL CEsTsOApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


#include "TSOPlugin.h"

TSOPlugin *g_plugin = NULL;


void    __declspec ( dllexport )    EuroScopePlugInInit ( EuroScopePlugIn :: CPlugIn ** ppPlugInInstance )
{
    AFX_MANAGE_STATE ( AfxGetStaticModuleState ())

    // create the instance
    * ppPlugInInstance = g_plugin = new TSOPlugin () ;
}


//---EuroScopePlugInExit-----------------------------------------------

void    __declspec ( dllexport )    EuroScopePlugInExit ( void )
{
    AFX_MANAGE_STATE ( AfxGetStaticModuleState ())

    // delete the instance
    delete g_plugin ;
}


