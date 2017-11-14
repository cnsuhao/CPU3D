#pragma once
#include "c3d.h"


/*
����Ļ��ƹ���ʵ������2d�Ļ�ͼ��
��render�������һ��ʵ�֣�����ֻ��
��ʵ���ȱ������ֹ��ܡ�
*/
class c3dTexture
{
public:
	c3dTexture() {}
	~c3dTexture() {}
	bool Allocate(int width, int height,const c3dColor& color=c3dColor::White);
	bool LoadFromImage(c3dString fileName);
	void Release();
	//2d
	void DrawLine(vec2& p1, vec2& p2);	//ֱ�ӻ������ػ�����
	void DrawTriangle(vec2& p1, vec2&p2, vec2& p3); //��������
	void DrawDebug(vec2& p1, vec2&p2); //��������
	//aabb ��ʽʵ��
	void DrawTriangleFill(vec2& p1, vec2&p2, vec2& p3);
	//����ɨ����
	void DrawScanLine(vec2& p1, int w);

	unsigned char* GetData();
	vec2 GetPos(int p);
	int GetPos(vec2 pos);
	int GetPos(int x, int y);
	int GetSize() { return texw* texh; };
	void Clear();
private:
	unsigned char *data;
	int texw, texh;
	bool bInit;
};
class c3dTextureManager
{
public:
	void Switch(int nTexIndex);
	bool Add(int nTexIndex, c3dTexture& tex);
	bool Remove(int nTexIndex);
	c3dTexture* GetCurrentTexture();
	int GetCurrentIndex() const { return nCurrentIndex; }
private:
	std::map<int, c3dTexture*> data;
	int nCurrentIndex;

	c3dTextureManager(const c3dDevice* pDev);
	const c3dDevice* pDevice;
	friend c3dDevice;
};