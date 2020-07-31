#pragma once
#include "singletonBase.h"
#include <vector>

class TxtData : public SingletonBase<TxtData>
{
public:
	TxtData();
	~TxtData();

	HRESULT init();
	void release();

	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);
};

