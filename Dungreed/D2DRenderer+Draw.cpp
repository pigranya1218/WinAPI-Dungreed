#include "stdafx.h"
#include "D2DRenderer.h"



/**********************************************************************************************
## RenderText ##
@@ int x : x ��ǥ
@@ int y : y ��ǥ
@@ wstring text : �׸� �ؽ�Ʈ
@@ int size : ��Ʈ ������
@@ DefaultBrush brush : �׸� �귯�� = DefaultBrush::Black
@@ DWRITE_TEXT_ALIGNMENT align : ���� �ɼ� = DWRITE_TEXT_ALIGNMENT_LEADING
@@ wstring font : ��Ʈ = �������

�⺻ �����ص� �귯���� �ؽ�Ʈ ������
************************************************************************************************/
void D2DRenderer::renderText(const int x, const int y, const wstring& text, const int size,
	const DefaultBrush& defaultBrush, const DWRITE_TEXT_ALIGNMENT& align,const wstring& font, float angle)
{
	locale::global(locale("kor"));
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	HRESULT hr = this->_DWFactory->CreateTextLayout
	(
		text.c_str(),
		text.length(),
		this->_fontList[font],
		(float) text.length() * size,
		(float) size,
		&layout
	);
	assert(SUCCEEDED(hr));

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();

	layout->SetFontSize((float)size, range);
	layout->SetTextAlignment(align);

	//_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// ȸ�� ��� ����
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y)));

	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout,
		_defaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}
/**********************************************************************************************
## RenderText ##
@@ int x : �׸���ǥ
@@ int y : �׸���ǥ
@@ wstring text : �׸� �ؽ�Ʈ
@@ COLORREF color : RGB�÷�
@@ float alpha : ���� ��
@@ int size : ��Ʈ ������
@@ DWRITE_TEXT_ALIGNMENT align : ���Ŀɼ�
@@ wstring font : ��Ʈ

���ο� �귯�� ������ ������
************************************************************************************************/
void D2DRenderer::renderText(const int x, const int y, const wstring& text, const COLORREF& color,
	const float alpha, const int size, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font, float angle)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	//�ؽ�Ʈ ���̾ƿ� ����
	_DWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_fontList[font],
		(float)text.length() * size,
		(float)size,
		&layout
	);

	//���̾ƿ� �¾�
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);
	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//�귯�� ����
	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	//_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// ȸ�� ��� ����
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y)));

	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, brush);

	NEW_SAFE_RELEASE(brush);
	NEW_SAFE_RELEASE(layout);
}
/**********************************************************************************************
## RenderTextField ##
@@ int x : �׸� ��ǥ
@@ int y : �׸� ��ǥ
@@ wstring text : �׸� �ؽ�Ʈ
@@ int size : ��Ʈ ������
@@ int width : ���� ���α���
@@ int heifht : ���� ���α���
@@ DefaultBrush brush : �⺻ ���� �귯��
@@ DWRITE_TEXT_ALIGNMENT align : ���� �ɼ�
@@ wstring font : ��Ʈ

���������� �⺻ �귯���� ���� ���
************************************************************************************************/
void D2DRenderer::renderTextField(const int x, const int y, const wstring& text, const int size,
	const int width, const int height, const DefaultBrush& defaultBrush, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font, float angle)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	_DWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_fontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//���̾ƿ� �¾�
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// ȸ�� ��� ����
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y)));

	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, _defaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}
/**********************************************************************************************
## RenderText ##
@@ int x : �׸� ��ǥ
@@ int y : �׸� ��ǥ
@@ wstring text : �׸� �ؽ�Ʈ
@@ COLORREF color : �׸� �÷�
@@ int size : ��Ʈ ������
@@ int width : ���� ���� ����
@@ int height : ���� ���� ����
@@ float alpha : ���İ�
@@ DWRITE_TEXT_ALIGNMENT align : ���� �ɼ�
@@ wstring font : ��Ʈ

�����ȿ��� ���ο� �귯���� �����ؼ� ��Ʈ���
************************************************************************************************/
void D2DRenderer::renderTextField(const int x, const int y, const wstring& text, const COLORREF& color,
	const int size, const int width, const int height, const float alpha, const DWRITE_TEXT_ALIGNMENT& align, const wstring& font, float angle)
{
	Vector2 pos(x, y);

	IDWriteTextLayout* layout = nullptr;
	_DWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		_fontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//���̾ƿ� �¾�
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//�귯�� ����
	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	//_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// ȸ�� ��� ����
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y)));

	_D2DRenderTarget->DrawTextLayout(D2D1::Point2F((float)x, (float)y), layout, brush);

	NEW_SAFE_RELEASE(layout);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## DrawLine ##
@@ Vector2 start : ���� ��
@@ Vector2 end : �� ��
@@ D2D1::ColorF::Enum color : ����
@@ float alpha : ���� ��
@@ float strokeWidth : �� ����
************************************************************************************************/
void D2DRenderer::drawLine(const Vector2& start, const Vector2& end, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	_D2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y), D2D1::Point2F(endPos.x, endPos.y), brush, strokeWidth);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## RenderText ##
@@ Vector2 start : ���� ��
@@ Vector2 end : �� ��
@@ DefaultBrush brush : �⺻ ���� �귯��
@@ float stroke : �� ����
***********************************************************************************************/
void D2DRenderer::drawLine(const Vector2& start, const Vector2& end, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;

	_D2DRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y),
		D2D1::Point2F(endPos.x, endPos.y), _defaultBrushList[(UINT)defaultBrush], strokeWidth);

}
/**********************************************************************************************
## DrawRectangle ##
@@ FloatRect rc : ��Ʈ
@@ D2D1::ColorF::Enum color : �÷�
@@ float alpha : ���� ��
@@ float strokeWidth : �� ����
************************************************************************************************/
void D2DRenderer::drawRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	FloatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## DrawRectangle ##
@@ FloatRect rc : �׸� ��Ʈ
@@ DefaultBrush brush : �׸� �귯��
@@ float stroke : �� ����
************************************************************************************************/
void D2DRenderer::drawRectangle(const FloatRect& rc, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	FloatRect rect = rc;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		_defaultBrushList[(UINT)defaultBrush], strokeWidth);

}
/**********************************************************************************************
## DrawEllipse ##
@@ Vector2 origin : ����
@@ flaot radius : ������
@@ DefaultBrush brush : �귯��
@@ float stroke : �� ����
************************************************************************************************/
void D2DRenderer::drawEllipse(const Vector2& origin, const float radius, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	FloatRect rc = rectMakePivot(origin, Vector2(radius, radius), PIVOT::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawEllipse(&ellipse, _defaultBrushList[(UINT)defaultBrush], strokeWidth);
}
/**********************************************************************************************
## DrawEllipse ##
@@ Vector2 origin : ����
@@ flaot radius : ������
@@ D2D1::ColorF::Enum color : D2D�÷� ��
@@ float alpha : ���� ��
@@ float stroke : �� ����
************************************************************************************************/
void D2DRenderer::drawEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	FloatRect rc = rectMakePivot(origin, Vector2(radius, radius), PIVOT::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## DrawEllipse ##
@@ Vector2 origin : ����
@@ Vector2 radius : ������
@@ D2D1::ColorF::Enum color : D2D�÷� ��
@@ float alpha : ���� ��
@@ float stroke : �� ����
************************************************************************************************/
void D2DRenderer::drawEllipse(const Vector2 & origin, const Vector2 & radius, const D2D1::ColorF::Enum & color, const float alpha, const float strokeWidth)
{
	Vector2 pos = origin;

	ID2D1SolidColorBrush* brush(nullptr);
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = radius.x;
	ellipse.radiusY = radius.y;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillRectagle ##
@@ FloatRect rc : �׸� ��Ʈ
@@ D2D1::ColorF::Enum color : D2D�÷�
@@ float alpha  : ���� ��
************************************************************************************************/
void D2DRenderer::fillRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color, const float alpha)
{
	FloatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillRectagle ##
@@ FloatRect rc : �׸� ��Ʈ
@@ float red : RGB red, (0 ~ 1)
@@ float green : RGB green, (0 ~ 1)
@@ float blue : RGB blue, (0 ~ 1)
@@ float alpha  : ���� ��
************************************************************************************************/
void D2DRenderer::fillRectangle(const FloatRect & rc, const float red, const float green, const float blue, const float alpha)
{
	FloatRect rect = rc;

	ID2D1SolidColorBrush* brush;
	D2D1_COLOR_F clr;
	clr.r = red;
	clr.g = green;
	clr.b = blue;
	clr.a = alpha;
	_D2DRenderTarget->CreateSolidColorBrush(clr, &brush);
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillRectagle ##
@@ FloatRect rc : �׸� ��Ʈ
@@ int red : RGB red, (0 ~ 255)
@@ int green : RGB green, (0 ~ 255)
@@ int blue : RGB blue, (0 ~ 255)
@@ float alpha  : ���� ��
************************************************************************************************/
void D2DRenderer::fillRectangle(const FloatRect & rc, const int red, const int green, const int blue, const float alpha)
{
	fillRectangle(rc, static_cast<float>(red) / 255, static_cast<float>(green) / 255, static_cast<float>(blue) / 255, alpha);
}
/**********************************************************************************************
## FillRectangle  ##
@@ FloatRec rc : ũ�� ��Ʈ
@@ DefaultBrush brush : �귯��
************************************************************************************************/
void D2DRenderer::fillRectangle(const FloatRect& rc, const DefaultBrush& defaultBrush)
{
	FloatRect rect = rc;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_D2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		_defaultBrushList[(UINT)defaultBrush]);
}
/**********************************************************************************************
## FillEllipse ##
@@ Vector2 origin : ���� ��ǥ
@@ flaot radius : ������
@@ D2D1::ColorF::Enum color : D2D�÷�
@@ float alpha : ���� ��
************************************************************************************************/
void D2DRenderer::fillEllipse(const Vector2& origin, const float radius, const D2D1::ColorF::Enum& color,const float alpha)
{
	FloatRect rc = rectMakePivot(origin, Vector2(radius, radius), PIVOT::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	ID2D1SolidColorBrush* brush(nullptr);
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillEllipse(&ellipse, brush);
	NEW_SAFE_RELEASE(brush);
}
void D2DRenderer::fillEllipse(const Vector2 & origin, const Vector2 & radius, const D2D1::ColorF::Enum & color, const float alpha)
{
	ID2D1SolidColorBrush* brush(nullptr);
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = origin.x;
	ellipse.point.y = origin.y;
	ellipse.radiusX = radius.x;
	ellipse.radiusY = radius.y;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillEllipse(&ellipse, brush);
	NEW_SAFE_RELEASE(brush);
}
/**********************************************************************************************
## FillEllipse ##
@@ Vector2 origin : ���� ��ǥ
@@ float radius : ������
@@ DefaultBrush brush : �귯��
@@ bool isRlative : ī�޶� ���� ����
************************************************************************************************/
void D2DRenderer::fillEllipse(const Vector2& origin, const float radius, const DefaultBrush& brush)
{
	FloatRect rc = rectMakePivot(origin, Vector2(radius, radius), PIVOT::CENTER);
	Vector2 pos = origin;
	float tempRadius = radius;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;
	ellipse.radiusX = tempRadius;
	ellipse.radiusY = tempRadius;

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_D2DRenderTarget->FillEllipse(&ellipse, _defaultBrushList[(UINT)brush]);
}

void D2DRenderer::drawRotationNullRectangle(const FloatRect& rc, const D2D1::ColorF::Enum& color,
	const float alpha, const float angle,  const float strokeWidth)
{
	FloatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.getWidth() / 2;
	offset.y = rect.top + rect.getHeight() / 2;

	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));

	_D2DRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}

void D2DRenderer::drawRotationFillRectangle(const FloatRect& rc, const D2D1::ColorF& color, const float angle)
{
	FloatRect rect = rc;

	D2D1_POINT_2F offset;
	offset.x = rect.left + rect.getWidth() / 2;
	offset.y = rect.top + rect.getHeight() / 2;
	ID2D1SolidColorBrush* brush;
	_D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	_D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	_D2DRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}
