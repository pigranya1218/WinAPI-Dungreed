#pragma once
#include "Animation.h"

class Image final
{
public:
	struct tagLoadedImageInfo
	{
		string key;
		wstring directory;

		tagLoadedImageInfo() {}
		tagLoadedImageInfo(const string& key,const wstring& directory)
			:key(key), directory(directory) {}
	};

	struct tagFrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap*		_bitmap;
	float				_alpha;			

	Vector2				_size;			
	float				_scale;			
	float				_angle;
	Vector2				_anglePos;

	Vector2				_skewPos, _skewAngle;	// Âî±×·¯Æ®¸± ÁÂÇ¥, °¢µµ

	tagLoadedImageInfo	_loadInfo;

	vector<Image::tagFrameRect>	_frameInfo;
	int							_maxFrameX;
	int							_maxFrameY;
private:
	friend class ImageManager;
	Image() = delete;
	Image( ID2D1Bitmap*const bitmap,const tagLoadedImageInfo& loadinfo);
	Image( ID2D1Bitmap*const bitmap,const tagLoadedImageInfo& loadinfo,const int maxFrameX,const int maxFrameY);
	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	void render(const Vector2& position, bool bisymmetry = false);
	void render(const Vector2& position, const Vector2& size, bool bisymmetry = false);
	void render(const Vector2& position, const Vector2& sourPos, const Vector2& sourSize, bool bisymmetry = false);	
	void render(const Vector2& position,const Vector2& size, const Vector2& sourPos, const Vector2& sourSize, bool bisymmetry = false);	
	void frameRender(const Vector2& position, const int frameX, const int frameY, bool bisymmetry = false);
	void frameRender(const Vector2& position, const Vector2& size, const int frameX, const int frameY, bool bisymmetry = false);
	void aniRender(const Vector2& position, Animation* ani, bool bisymmetry = false);
	void aniRender(const Vector2& position, const Vector2& size, Animation* ani, bool bisymmetry = false);

	void resetRenderOption();

	void setSize(const Vector2& vec) { this->_size = vec; }
	void setAlpha(const float alpha) { this->_alpha = alpha; }
	void setScale(const float scale) { this->_scale = scale; }
	void setAngle(const float angle) { this->_angle = angle; }
	void setAnglePos(const Vector2& vec) { this->_anglePos = vec; }

	float getScale() { return _scale; }
	float getAngle() { return _angle; }
	float getAlpha() { return _alpha; }
	float getRatio() { return (_size.y / _size.x); }

	void setSkew(const Vector2& pos, const Vector2& angle) { this->_skewPos = pos; this->_skewAngle = angle; }

	const int getMaxFrameX()const{ return _maxFrameX; }
	const int getMaxFrameY()const{ return _maxFrameY; }
	const string getKey() const { return this->_loadInfo.key; }
	const UINT getWidth() const{ return _bitmap->GetPixelSize().width; }
	const UINT getHeight()const{ return _bitmap->GetPixelSize().height; }
	const Vector2 getSize()const { return this->_size; }
	Vector2 getFrameSize(const int& frame = 0) const { return Vector2(_frameInfo[frame].width, _frameInfo[frame].height); }
	const tagLoadedImageInfo& getLoadInfo() const { return _loadInfo; }
};

