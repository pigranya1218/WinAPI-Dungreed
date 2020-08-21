#include "stdafx.h"
#include "D2DRenderer.h"

/*****************************************************
## D2DRenderer ##
*******************************************************/
D2DRenderer::D2DRenderer()
	:_D2DFactory(nullptr), _D2DRenderTarget(nullptr), _DWFactory(nullptr)
{
	this->createFactory();
	this->createRenderTarget();
	this->createDefaultBrush();
	this->addTextFormat(L"둥근모꼴");
	this->addTextFormat(L"Alagard");
	this->addTextFormat(L"Aa카시오페아");
	_D2DRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
}

/*****************************************************
## ~D2DRenderer ##
*******************************************************/
D2DRenderer::~D2DRenderer()
{
	for (auto iter = _fontList.begin() ; iter != _fontList.end() ; ++iter)
		NEW_SAFE_RELEASE(iter->second);

	for (UINT i = 0; i < (UINT)DefaultBrush::End; ++i)
		NEW_SAFE_RELEASE(_defaultBrushList[i]);
	
	NEW_SAFE_RELEASE(_DWFactory);

	NEW_SAFE_RELEASE(_D2DSurface);
	NEW_SAFE_RELEASE(_D2DRenderTarget);
	NEW_SAFE_RELEASE(_D2DFactory);
}
/*****************************************************
## BeginRender ##
*******************************************************/
void D2DRenderer::beginRender(const D2D1::ColorF& backgroundColor)
{
	_D2DRenderTarget->BeginDraw();
	_D2DRenderTarget->Clear(backgroundColor);
}
/*****************************************************
## EndRender ##
*******************************************************/
void D2DRenderer::endRender()
{

	_D2DRenderTarget->EndDraw();

}


/*****************************************************
## CreateFactory ##
*******************************************************/
void D2DRenderer::createFactory()
{
	//1) D2D 팩토리 생성
	//싱글쓰레드타입으로 
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2DFactory);
	assert(SUCCEEDED(hr));
	//2) DWriteFactory 생성
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*&_DWFactory),
		(IUnknown**)&_DWFactory
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}
/*****************************************************
## CreateRenderTarget ##
*******************************************************/
void D2DRenderer::createRenderTarget()
{
	//렌더타겟이란 백버퍼의 역할을 하는 클래스이자 여러 렌더링을 위한 유틸적인 것들이 들어있는 클래스다
	//해서 화면에 뭔가 렌더링을 요청하려면 렌더타겟을 통해서만 가능하다

	HRESULT hr;
	//1) 윈도우 핸들을 통해서 화면 Rect를 받아온다 (GetClientRect)
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);
	
	//이전에는 Factory를 통해서 현재 디바이스의 DPI를 받아 왔으나 어떤 이유에서인지 MS에서 해당 함수를 사용하지 못하게 변경함, 자체 API함수로 불러오자
	//mD2DFactory->GetDesktopDpi(&dpiX, &dpiY)

	//2) 디바이스의 DPI정보를 받아온다. (WinAPI 함수)
	FLOAT dpiX = GetDeviceCaps(_hdc, LOGPIXELSX);
	FLOAT dpiY = GetDeviceCaps(_hdc, LOGPIXELSY);

	//3) 렌더타겟을 생성하기 위한 속성값들 초기화
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//4) 렌더타겟의 사이즈 초기화(화면 크기로)
	D2D1_SIZE_U renderTargetSize = D2D1::SizeU(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	
	//5) 렌더타겟 생성
	hr = _D2DFactory->CreateHwndRenderTarget(
		renderTargetProperties,
		D2D1::HwndRenderTargetProperties(_hWnd, renderTargetSize),
		&_D2DRenderTarget
	);

	assert(SUCCEEDED(hr));
}
/*****************************************************
## CreateDefaultBrush ##
*******************************************************/
void D2DRenderer::createDefaultBrush()
{
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Black]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::White]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Yellow]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Red]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Blue]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Green]);
	this->_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &_defaultBrushList[(UINT)DefaultBrush::Gray]);
}
/*****************************************************
## AddTextFormat ##
@@ wstring font : 폰트명
@@ float defaultSize : 폰트 사이즈 = 1.f
*******************************************************/
void D2DRenderer::addTextFormat(const wstring& font, const float& defaultSize)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = this->_DWFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		defaultSize,
		L"ko",
		&format
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	this->_fontList.insert(make_pair(font, format));
}


