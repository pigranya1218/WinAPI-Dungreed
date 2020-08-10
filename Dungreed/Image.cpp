#include "stdafx.h"
#include "Image.h"

/********************************************************************************
## Image ## 
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���) 

�������̹����� �ƴ� �̹��� Ŭ���� ����
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
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)
@@ int maxFrameX : ���� ������ �� 
@@ int maxFrameY : ���� ������ �� 

������ �̹��� Ŭ���� ����
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
��Ʈ�� ���� 
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

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(0, 0));
	//ȸ�� ����� ������ش�. 
	Vector2 anglePos = _anglePos * _scale;
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(anglePos.x, anglePos.y));
	//�̵� ����� ������ش�.
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
	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(0, 0));
	//ȸ�� ����� ������ش�. 
	Vector2 anglePos = _anglePos * _scale;
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(anglePos.x, anglePos.y));
	//�̵� ����� ������ش�.
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

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, sourSize.x, sourSize.y);
	D2D1_RECT_F dxSrc = D2D1::RectF(sourPos.x, sourPos.y, sourPos.x + sourSize.x, sourPos.y + sourSize.y);
	//������� ����
	D2D_RENDERER->getRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * skewMatrix * lrMatrix * translateMatrix);
	//������ ��û
	D2D_RENDERER->getRenderTarget()->DrawBitmap(_bitmap, dxArea, _alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->resetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::frameRender(const Vector2& position, const int frameX, const int frameY, bool bisymmetry)
{
	//���� �������ε��� 
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
�̹��� Ŭ���� ���� ���� �ɼǵ� ���� �ʱ�ȭ
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
