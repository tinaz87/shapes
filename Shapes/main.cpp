// Shapes.cpp : definisce il punto di ingresso dell'applicazione.
//

#include "stdafx.h"
#include <Windowsx.h>
#include <stdio.h>
#include "main.h"
#include "Field\Field.h"
#include "ShapeBuilder\ShapeBuilder.h"
#include "CollisionDetection\CollisionDetection.h"
#define MAX_LOADSTRING 100

Field mField;


// Variabili globali:
HINSTANCE hInst;                                // istanza corrente
WCHAR szTitle[MAX_LOADSTRING];                  // Testo della barra del titolo
WCHAR szWindowClass[MAX_LOADSTRING];            // nome della classe di finestre principale

// Dichiarazioni con prototipo delle funzioni incluse in questo modulo di codice:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	// TODO: inserire qui il codice.

	// Inizializzare le stringhe globali
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SHAPES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Eseguire l'inizializzazione dall'applicazione:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHAPES));

	MSG msg;

	// Ciclo di messaggi principale:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNZIONE: MyRegisterClass()
//
//  SCOPO: registra la classe di finestre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = (CS_HREDRAW | CS_VREDRAW);
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHAPES));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_SHAPES);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNZIONE: InitInstance(HINSTANCE, int)
//
//   SCOPO: salva l'handle di istanza e crea la finestra principale
//
//   COMMENTI:
//
//        In questa funzione l'handle di istanza viene salvato in una variabile globale e
//        la finestra di programma principale viene creata e visualizzata.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Memorizzare l'handle di istanza nella variabile globale

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, 640, 480, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	tagRECT pRect;
	GetClientRect(hWnd, &pRect);

	mField.setHeight(pRect.bottom);
	mField.setWidth(pRect.right);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;          // handle to device context (DC)  
	PAINTSTRUCT ps;   // paint data for Begin/EndPaint  

	switch (uMsg)
	{
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Analizzare le selezioni di menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;

	}
	case WM_PAINT: {
		BeginPaint(hwnd, &ps);

		// Because the default brush is white, select  
		// a different brush into the device context  
		// to demonstrate the painting of filled shapes.  

		SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN: {

		short xPos = GET_X_LPARAM(lParam);
		short yPos = GET_Y_LPARAM(lParam);
		char buffer[100];
		LogDebug( "Click => X:%d,Y:%d", xPos, yPos);

		BasePolygon* pPoly = shape_builder::createPolygon(xPos, yPos);


		if (pPoly) {
			const std::vector<BasePolygon*>& pPolyList = mField.getPolyList();
			float pScale = 1.f;
			for (size_t i = 0; i < pPolyList.size(); ++i)
			{
				LogDebug("Iterazione sul %d-esimo poligono", i);
				
				bool pCollisionDetected = collision_detection::detectCollision(pPoly, pPolyList.at(i));
				if (pCollisionDetected) {					
					LogDebug("Collisione rilevata");
					pScale -= 0.1;
					if (pScale > 0) {
						LogDebug("Riduzione scala oggetto a %f",pScale);						
						i = i - 1;
						pPoly->Scale(pScale);
					}
					else {
						delete pPoly;
						return 0;
					}
					
				}
			}

			mField.addPoly(pPoly);

			hdc = GetDC(hwnd);

			SelectObject(hdc, GetStockObject(DC_BRUSH));
			const Color& pPolyColor = pPoly->getColor();
			SetDCBrushColor(hdc, RGB(pPolyColor.mRed, pPolyColor.mGreen, pPolyColor.mBlue));
			switch (pPoly->getType())
			{
			case BasePolygon::RECTANGLE: {
				const auto& pPointLeft = pPoly->getTopLeft();
				const auto& pPointRight = pPoly->getBottomRight();

				BOOL r = Rectangle(hdc, pPointLeft.mXCoordinate, pPointLeft.mYCoordinate,
					pPointRight.mXCoordinate, pPointRight.mYCoordinate);
				break;
			}
			case BasePolygon::CIRCLE: {
				const auto& pPointLeft = pPoly->getTopLeft();
				const auto& pPointRight = pPoly->getBottomRight();

				BOOL r = Ellipse(hdc, pPointLeft.mXCoordinate, pPointLeft.mYCoordinate,
					pPointRight.mXCoordinate, pPointRight.mYCoordinate);
				break;
			}
			default:
				break;
			}

			ReleaseDC(hwnd, hdc);

		}


		

		return 0;
	}
	case WM_DESTROY:

		// Destroy the background brush, compatible bitmap,  
		// and bitmap.  
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return (LRESULT)NULL;
}

// Gestore di messaggi per la finestra Informazioni su.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
