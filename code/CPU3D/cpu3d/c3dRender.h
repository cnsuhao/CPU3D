#pragma once
#include "c3d.h"
//�滭������״̬ ��ģʽ����ɫģʽ������ģʽ
enum RenderMode
{
	Color,
	Texture
};
enum FillMode
{
	LINE,
	Fill
};
enum ProjectionMode	//��ʱ����
{
	ModelProjection,	//����ͶӰ
	OrthoProjection		//ģ��ͶӰ
};
class c3dRender
{
public:
	RenderMode renderMode;
	FillMode fillMode;
	//���������������ͣ�������Ϊ����档
	void RenderVertex(c3dVertex& p);
	void RenderLine(c3dVertex& p1, c3dVertex& p2);
	void RenderTriagle(c3dVertex& p1, c3dVertex& p2, c3dVertex& p3);
private:
	c3dRender(const c3dDevice* pDev);
	const c3dDevice* pDevice;
	friend c3dDevice;
};
