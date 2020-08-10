#include "stdafx.h"
#include "Image.h"

/********************************************************************************
## Image ## 
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로) 

프레임이미지가 아닌 이미지 클래스 생성
*********************************************************************************/
Image::Image(ID2D1Bitmap * const bitmap, const tagLoadedImageInfo & loadinfo)
	:_bitmap(bitmap),_loadInfo(loadinfo),_scale(1.f),_alpha(1.f),_angle(0.f),_maxFrameX(1),_maxFrameY(1)
{
	this->_size.x = (float)this->_bitmap->GetPixelSize().width;
	this->_size.y = (float)this->_bitmap->GetPixelSize().height;

	tagFrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = _size.x;
	rc.height = _size.y;
	this->_frameInfo.push_back(rc);
	this->resetRenderOption();
}
/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로)
@@ int maxFrameX : 가로 프레임 수 
@@ int maxFrameY : 세로 프레임 수 

프레임 이미지 클래스 생성
*********************************************************************************/
Image::Image( ID2D1Bitmap *const bitmap, const tagLoadedImageInfo & loadinfo, const int  maxFrameX, const int  maxFrameY)
	:_bitmap(bitmap), _loadInfo(loadinfo), _maxFrameX(maxFrameX), _maxFrameY(maxFrameY), _scale(1.f), _alpha(1.f), _angle(0.f)
{
	this->_size.x = (float)_bitmap->GetPixelSize().width;
	this->_size.y = (float)_bitmap->GetPixelSize().height;

	float frameX = _size.x / (float)this->_maxFrameX;
	float frameY = _size.y / (float)this->_maxFrameY;

	tagFrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = (float)i * (frameX);
			rc.y = (float)j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->_frameInfo.push_back(rc);
		}
	}

	this->resetRenderOption();
}
/********************************************************************************
## ~Image ##
비트맵 해제 
*********************************************************************************/
Image::~Image()
{
	NEW_SAFE_RELEASE(_bitmap);
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void Image::render(const Vector2& position, bool bisymmetry)
{
	Vector2 size = _size * _scale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(0, 0));
	//회전 행렬을 만들어준다. 
	Vector2 anglePos = _anglePos * _scale;
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(anglePos.x, anglePos.y));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix;
	D2D1::Matrix3x2F lrMatrix;
	if (bisymmetry)
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x + size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(-1, 0, 0, 1, 0, 0);
	}
	else
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(1, 0, 0, 1, 0, 0);
	}
	D2D1::Matrix3x2F skewMatrix = D2D1::Matrix3x2F::Skew(_skewAngle.x, _skewAngle.y, D2D1::Point2F(_skewPos.x, _skewPos.y));
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, _size.x, _size.y);
	D2D_RENDERER->getRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * skewMatrix * lrMatrix * translateMatrix);
	D2D_RENDERER->getRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	resetRenderOption();
}

void Image::render(const Vector2 & position, const Vector2 & size, bool bisymmetry)
{
	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(0, 0));
	//회전 행렬을 만들어준다. 
	Vector2 anglePos = _anglePos * _scale;
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(anglePos.x, anglePos.y));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix;
	D2D1::Matrix3x2F lrMatrix;
	if (bisymmetry)
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x + size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(-1, 0, 0, 1, 0, 0);
	}
	else
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(1, 0, 0, 1, 0, 0);
	}
	D2D1::Matrix3x2F skewMatrix = D2D1::Matrix3x2F::Skew(_skewAngle.x, _skewAngle.y, D2D1::Point2F(_skewPos.x, _skewPos.y));
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.x, size.y);

	D2D_RENDERER->getRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * skewMatrix * lrMatrix * translateMatrix);
	D2D_RENDERER->getRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

	resetRenderOption();
}

void Image::render(const Vector2 & position, const Vector2 & sourPos, const Vector2 & sourSize, bool bisymmetry)
{
	Vector2 size = _size * _scale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(0, 0));
	Vector2 anglePos = _anglePos * _scale;
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(anglePos.x, anglePos.y));
	D2D1::Matrix3x2F translateMatrix;
	D2D1::Matrix3x2F lrMatrix;
	if (bisymmetry)
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x + size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(-1, 0, 0, 1, 0, 0);
	}
	else
	{
		translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);
		lrMatrix = D2D1::Matrix3x2F(1, 0, 0, 1, 0, 0);
	}
	
	D2D1::Matrix3x2F skewMatrix = D2D1::Matrix3x2F::Skew(_skewAngle.x, _skewAngle.y, D2D1::Point2F(_skewPos.x, _skewPos.y));

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, sourSize.x, sourSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF(sourPos.x, sourPos.y, sourPos.x + sourSize.x, sourPos.y + sourSize.y);
	//최종행렬 세팅
	D2D_RENDERER->getRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * skewMatrix * lrMatrix * translateMatrix);
	//렌더링 요청
	D2D_RENDERER->getRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->resetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::frameRender(const Vector2& position, const int frameX, const int frameY, bool bisymmetry)
{
	//현재 프레임인덱스 
	int frame = frameY * _maxFrameX + frameX;
	this->render(position, Vector2(_frameInfo[frame].x, _frameInfo[frame].y), Vector2(_frameInfo[frame].width, _frameInfo[frame].height), bisymmetry);
}

void Image::aniRender(const Vector2 & position, Animation * ani, bool bisymmetry)
{
	POINT sourPos = ani->getFramePos();
	POINT sourSize = { ani->getFrameWidth(), ani->getFrameHeight() };
	this->render(position, Vector2(sourPos), Vector2(sourSize), bisymmetry);
	
}

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void Image::resetRenderOption()
{
	this->_alpha = 1.0f;
	this->_scale = 1.0f;
	this->_angle = 0.f;
	this->_anglePos = Vector2(_size.x / 2.f, _size.y / 2.f);
	this->_skewAngle = Vector2(0, 0);
	this->_skewPos = Vector2(0, 0);

	if (_frameInfo.size() <= 1)
	{
		this->_size.x = (float)_bitmap->GetPixelSize().width;
		this->_size.y = (float)_bitmap->GetPixelSize().height;
	}
	else
	{
		this->_size.x = _frameInfo[0].width;
		this->_size.y = _frameInfo[0].height;
	}
}
