#include "pch.h"
#include "StringHelper.h"

//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ� �ڸ���
///@param orgin : ���� ���ڿ�
///@param tok : �ڸ� ������ �Ǵ� ���ڿ�
///@return �Ϸ�� ���ڿ� �迭
//////////////////////////////////////////////////////////////////////////
void StringHelper::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}

void StringHelper::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief ���� ���ڿ��� ������ üũ
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : ���� �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool StringHelper::StartsWith(string str, string comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool StringHelper::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ��� ���ԵǾ� �ִ���
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool StringHelper::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool StringHelper::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ����� comp ���ڸ� rep�� ����
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
///@param rep : �ٲܹ��ڿ�
//////////////////////////////////////////////////////////////////////////
void StringHelper::Replace(string * str, string comp, string rep)
{
	string temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

void StringHelper::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string���� wstring������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
wstring StringHelper::StringToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring���� string������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
string StringHelper::WStringToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
//////////////////////////////////////////////////////////////////////////