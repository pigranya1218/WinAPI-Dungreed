#include "stdafx.h"
#include "ImageManager.h"

#include "Image.h"
#include <io.h>

ImageManager::ImageManager()
	:_wicFactory(nullptr)
{
	//WIC 팩토리 생성
	//Windows Imaging Component
	//Direct2D는 이미지를 로드하는 기능이 없다. 
	//고로 Direct2D는 WIC라는 라이브러리의 이미지로부터 이미지 데이터를 만들 수 있다.
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
}

/*********************************************************************
## ImageManager ##
**********************************************************************/
ImageManager::~ImageManager()
{
	this->deleteAll();
	NEW_SAFE_RELEASE(_wicFactory);
}
/*********************************************************************
## AddImage ##
**********************************************************************/
Image * ImageManager::addImage(const string& key, const wstring& file)
{
	Image* image = this->findImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = this->createD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::tagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo);
		_imageList.insert(make_pair(key, image));
		return image;
	}
	else
		assert(SUCCEEDED(E_FAIL));

	return nullptr;
}
/*********************************************************************
## AddFrameImage ##
**********************************************************************/
Image * ImageManager::addFrameImage(const string& key,const wstring& file,const int maxFrameX,const int maxFrameY)
{
	Image* image = this->findImage(key);
	if (image)
		return image;

	ID2D1Bitmap* bitmap = createD2DBitmapFromFile(file);
	if (bitmap)
	{
		Image::tagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap,loadInfo,maxFrameX,maxFrameY);
		this->_imageList.insert(make_pair(key, image));
		return image;
	}

	return nullptr;
}
/*********************************************************************
## FindImage ##
**********************************************************************/
Image * ImageManager::findImage(const string& key)
{
	auto iter = _imageList.find(key);
	if (iter != _imageList.end())
		return iter->second;
	return nullptr;
}
/*********************************************************************
## CreateD2DBitmapFromFile ##
@@ wstring file : 파일 경로
**********************************************************************/
ID2D1Bitmap * ImageManager::createD2DBitmapFromFile(const wstring & file)
{
	//디코더 생성
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = _wicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//디코더에서 프레임얻음
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//프레임을 기반으로 포맷 컨버터 생성
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = _wicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//컨버터 초기화
	hr = convertedSrcBmp->Initialize
	(
		ipFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//컨버트된 데이터를 기반으로 실제 Direct2D용 비트맵을 생성
	ID2D1Bitmap* ipResult = nullptr;
	hr = D2D_RENDERER->getRenderTarget()->CreateBitmapFromWicBitmap
	(
		convertedSrcBmp,
		nullptr,
		&ipResult
	);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif

	NEW_SAFE_RELEASE(convertedSrcBmp);
	NEW_SAFE_RELEASE(ipFrame);
	NEW_SAFE_RELEASE(ipDecoder);

	return ipResult;
}
/*********************************************************************
## DeleteAll ##
**********************************************************************/
void ImageManager::deleteAll()
{
	auto iter = _imageList.begin();
	for (; iter != _imageList.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	_imageList.clear();
}

