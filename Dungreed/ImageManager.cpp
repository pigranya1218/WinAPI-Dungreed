#include "stdafx.h"
#include "ImageManager.h"

#include "Image.h"
#include <io.h>

ImageManager::ImageManager()
	:_wicFactory(nullptr)
{
	//WIC ���丮 ����
	//Windows Imaging Component
	//Direct2D�� �̹����� �ε��ϴ� ����� ����. 
	//��� Direct2D�� WIC��� ���̺귯���� �̹����κ��� �̹��� �����͸� ���� �� �ִ�.
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
@@ wstring file : ���� ���
**********************************************************************/
ID2D1Bitmap * ImageManager::createD2DBitmapFromFile(const wstring & file)
{
	//���ڴ� ����
	IWICBitmapDecoder* ipDecoder = nullptr;
	HRESULT hr;
	hr = _wicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &ipDecoder);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//���ڴ����� �����Ӿ���
	IWICBitmapFrameDecode* ipFrame = nullptr;
	hr = ipDecoder->GetFrame(0, &ipFrame);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//�������� ������� ���� ������ ����
	IWICFormatConverter* convertedSrcBmp = nullptr;
	hr = _wicFactory->CreateFormatConverter(&convertedSrcBmp);
#ifdef _DEBUG
	assert(SUCCEEDED(hr));
#endif
	//������ �ʱ�ȭ
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
	//����Ʈ�� �����͸� ������� ���� Direct2D�� ��Ʈ���� ����
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

