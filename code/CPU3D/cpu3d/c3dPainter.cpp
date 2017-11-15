#include "c3dPainter.h"
#include "c3dFrameBuffer.h"

c3dPainter::c3dPainter(void) :bInited(false)
{
}


c3dPainter::~c3dPainter(void)
{
}

void c3dPainter::DrawPoint(c3dVertex v)
{
	if (data == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
	}
	//����ֻ��λ�ú���ɫ �����Ϣ
	int nIndex = v.pos.x * v.pos.y;
	if (nIndex < 0 || nIndex > data->GetSize()) c3dLog::WriteErrorLog(InvalidSize);
	unsigned char *pFrameBuffer = data->GetFrameBuffer();
	unsigned char *pZBuffer = data->GetZBuffer();
	if (v.pos.z >= pZBuffer[nIndex])
	{
		unsigned char * vp = pFrameBuffer + nIndex * 3;
		vp[0] = v.color.r;
		vp[1] = v.color.g;
		vp[2] = v.color.b;
	}
}

void c3dPainter::DrawRect(int x, int y, int w, int h)
{

}

void c3dPainter::DrawLine(int px1, int py1, int px2, int py2)
{

}
void c3dPainter::DrawScanLine(c3dVertex v1, c3dVertex v2)
{

}
//v1 v2����һ��ˮƽ���� ������ʡ�ܶ����
void c3dPainter::DrawTriangle(c3dVertex& v0, c3dVertex& v1, c3dVertex& v2)
{
	//�����triangle��һ��Ҫ�� v1 v2 v3 ����һ������ˮƽ��


}

void c3dPainter::SplitTriangle(const c3dVertex* pIn, c3dVertex** pOut, int& count)
{
	if (pIn == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
		return;
	}
	const c3dVertex& vi0 = pIn[0];
	const c3dVertex& vi1 = pIn[1];
	const c3dVertex& vi2 = pIn[2];

	c3dVertex vt0, vt1, vt2;
	//������� 0 1 2 ����2�������������
	if (vi0.pos.y == vi1.pos.y || vi1.pos.y == vi2.pos.y || vi2.pos.y == vt0.pos.y)
	{
		count = 1;
		*pOut[0] = vi0;
		*pOut[1] = vi1;
		*pOut[2] = vi2;
	}

	//�����ǰ�ˮƽɨ��

	c3dVertex splitVer = vi0;

	int top, bottom;
	int nTopIndex, nMiddleIndex, nBottomIndex;
	c3dVertex vMiddleInter;
	top = max(max(vi0.pos.y, vi1.pos.y), vi2.pos.y);
	bottom = min(min(vi0.pos.y, vi1.pos.y), vi2.pos.y);
	for (int i = 0; i < 2; i++)
	{
		if (pIn[i].pos.y == top)
		{
			nTopIndex = i;
		}
		if (pIn[i].pos.y == bottom)
		{
			nBottomIndex = i;
		}
	}
	nMiddleIndex = 0 + 1 + 2 - nTopIndex - nBottomIndex;	//������ǵ�id�ܺ���һ���ģ�������� �������Ǽ����϶���0 1 2������

	//glm::intersectLineTriangle()
	//middle top bottom�Ľ���
	float v = (pIn[nMiddleIndex].pos.y - bottom) / (float)(bottom - top);
	vMiddleInter = c3dVertex::lerp(pIn[nTopIndex], pIn[nBottomIndex],v);
	pOut[0][0] = pIn[nTopIndex];
	pOut[1][0] = pIn[nBottomIndex];
	pOut[0][1] = pOut[1][1] = pIn[nMiddleIndex];
	pOut[0][2] = pOut[1][2] = vMiddleInter;
	count = 2;
}
