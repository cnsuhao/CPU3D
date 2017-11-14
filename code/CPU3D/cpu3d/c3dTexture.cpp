#include "c3dTexture.h"

bool c3dTexture::Allocate(int width, int height, const c3dColor& color)
{
	if (width <= 0 || height <= 0)
	{
		c3dLog::WriteErrorLog(InvalidSize);
		return false;
	}
	if (bInit)
	{
		texw = width;
		texh = height;
		data = new unsigned char[width * height * 4];
		for (int nIndex = 0; nIndex < width * height; nIndex++)
		{
			data[nIndex] = color.r;
			data[nIndex + 1] = color.g;
			data[nIndex + 2] = color.b;
			data[nIndex + 3] = color.a;
		}
		bInit = true;
	}
	else {
		c3dLog::WriteErrorLog(InvalidInit);
		return false;
	}
	return true;
}

bool c3dTexture::LoadFromImage(c3dString fileName)
{
	c3dLog::WriteLog(c3dLog::Warn, "δʵ�ִ˷���");
	return false;
}

void c3dTexture::Release()
{
	if (bInit)
	{
		delete data;
		data = nullptr;
	}
}

//��ʱ��ɫΪ��ɫ������Ჹ��
void c3dTexture::DrawLine(vec2& p1, vec2& p2)
{
	//��bug�ж������� ���ߵķ�ʽ���� x������������yֵ�仯�Ƚϴ��ʱ��
	//���»��߲���������������Ӹ���X�������߸���y������Ҫ�жϵ�
	vec2 k = p2 - p1;
	vec2 kAbs = glm::abs(k);
	bool bLoopedByY = false;
	kAbs.y > kAbs.x ? bLoopedByY = true : bLoopedByY = false;
	//�ж����������Ƿ�ͷ�����ʵ���� ��ʱû�뵽���õĽ���취��
	//��Ϊ�ü� Ӧ������׶�ü�
	/*if (p1.x >= texw || p2.x >= texw || p1.y >= texh || p2.y >= texh)
	{
	return;
	}*/
	//���洦�����һ����������Ҫ������ ���ܸı仭�ߵ�б��
	/*if ( p1.x > texw ) p1.x = texw;
	if ( p1.y > texh ) p1.y = texh;
	if ( p2.x > texw ) p2.x = texw;
	if ( p2.y > texh ) p2.y = texh;

	if ( p1.x < 0 ) p1.x = 0;
	if ( p1.y < 0 ) p1.y = 0;
	if ( p2.x < 0 ) p2.x = 0;
	if ( p2.y < 0 ) p2.y = 0;*/



	//����Ӧ�ø��� �Ƿ�����Y���껭�������� ����Ҫ��������
	vec2 srcPoint, dstPoint;
	float stepX = 0;
	float stepY = 0;
	if (bLoopedByY)
	{
		if (p1.y < p2.y)
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else {
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.x / k.y;	//����Ҫע�⣬Ϊÿ��һ��Y��x���ߵľ��� xҪת��Ϊ����
		stepX = srcPoint.x;
		for (int y = srcPoint.y; y < dstPoint.y; ++y)
		{
			stepX += step;
			stepY = y;
			int spos = GetPos(stepX, stepY) * 4;
			if (spos > 0 && spos < texw * texh * 4 - 3)
			{
				if (spos < texw * texh * 4 - 3)
				{
					data[spos] = 0xFF;
					data[spos + 1] = 0x00;	//g
					data[spos + 2] = 0x00;	//b
					data[spos + 3] = 0xFF;	//a
				}
			}
		}
	}
	else {
		//����������x���껭��
		if (p1.x < p2.x)
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else {
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.y / k.x;	//����Ҫע�⣬Ϊÿ��һ��Y��x���ߵľ��� xҪת��Ϊ����
		stepY = srcPoint.y;
		for (int x = srcPoint.x; x < dstPoint.x; ++x)
		{
			stepY += step;
			stepX = x;
			int spos = GetPos(stepX, stepY) * 4;
			if (spos > 0 && spos < texw * texh * 4 - 3)
			{
				data[spos] = 0xFF;
				data[spos + 1] = 0xFF;	//g
				data[spos + 2] = 0xFF;	//b
				data[spos + 3] = 0xFF;	//a
			}
		}

	}
}

void c3dTexture::DrawTriangle(vec2& p1, vec2&p2, vec2& p3)
{
	//smoothstep(p1,p2,p3);
	//Ŀǰ���յ��ߵķ�ʽ��
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p1, p3);
}

unsigned char* c3dTexture::GetData()
{
	return data;
}

vec2 c3dTexture::GetPos(int p)
{
	int y = p / texw;
	int x = p % texw;
	return vec2(x, y);
}

int c3dTexture::GetPos(vec2 pos)
{
	if (pos.y < 1)
	{
		return pos.x;
	}
	int m = (pos.y - 1) *texw + pos.x;
	return m;
}

int c3dTexture::GetPos(int x, int y)
{
	if (x < 0 || y < 0)
	{
		//��ȡ��λ����Խ��
		//assert(x < 0);
		return 0;
	}
	if (y < 1)
	{
		return x;
	}
	int m = (y - 1) *texw + x;
	return m;
}

void c3dTexture::DrawDebug(vec2& p1, vec2&p2)
{
#ifdef _DEBUG
	for (int i = 0; i < texw * texh * 4; ++i)
	{
		//data[i] = i % 255 ;
	}
#endif // _DEBUG


}

void c3dTexture::DrawTriangleFill(vec2& p1, vec2&p2, vec2& p3)
{
	//����ʹ��aabb�ķ�ʽ,ȷ�����εĴ�С��Ȼ��������
	//�ƶ�һ����ֱ�Ĺ���Ͷ��
	//glm::intersectRayTriangle();
	float left = p1.x < p2.x ? p1.x : p2.x;
	left = left < p3.x ? left : p3.x;

	float top = p1.y < p2.y ? p1.y : p2.y;
	top = top < p3.y ? top : p3.y;

	float right = p1.x > p2.x ? p1.x : p2.x;
	right = right > p3.x ? right : p3.x;

	float bottom = p1.y > p2.y ? p1.y : p2.y;
	bottom = bottom > p3.y ? bottom : p3.y;

	auto IsInTriangle = [&](float x, float y) ->bool
	{
		glm::vec2 q(x, y);
		glm::vec2 p1q = q - p1;
		glm::vec2 p1p2 = p2 - p1;
		glm::vec2 p1p3 = p3 - p1;

		auto cr1 = glm::dot(p1q, p1p2);
		auto cr2 = glm::dot(p1p2, p1p3);
		if (glm::dot(cr1, cr2) > 0)
		{
			return true;
		}

		return false;
	};
	auto spos = 0;
	for (int y = top; y < bottom; ++y)
	{
		for (int x = left; x < right; ++x)
		{
			if (!IsInTriangle(x, y))
			{
				spos = (x + y * texw) * 4;
				data[spos] = 0xFF;
				data[spos + 1] = 0xFF;	//g
				data[spos + 2] = 0xFF;	//b
				data[spos + 3] = 0xFF;	//a
			}
		}
	}
}

void c3dTexture::DrawScanLine(vec2& p1, int w)
{
	if (w < 0) return;
	int beginX = max(0, p1.x);
	int endX = max(0, p1.x + w);
	if (beginX < 0 || endX <= 0) return;

	for (int cx = beginX; cx < endX; cx++)
	{
		int nPos = GetPos(cx, p1.y);
		data[nPos] = 255;
		data[nPos + 1] = 255;
		data[nPos + 2] = 255;
		data[nPos + 3] = 255;
	}
}

void c3dTexture::Clear()
{
	memset(data, 0, 4 * texw * texh * sizeof(unsigned char));
}

void c3dTextureManager::Switch(int nTexIndex)
{
	std::map<int, c3dTexture*>::iterator res = data.find(nTexIndex);
	if (res != data.end())
	{
		nCurrentIndex = nTexIndex;
	}
	else {
		c3dLog::WriteLog(c3dLog::Warn, "δ�ҵ���ǰ����������");
	}
}

bool c3dTextureManager::Add(int nTexIndex, c3dTexture& tex)
{
	data[nTexIndex] = &tex;
	return true;
}

bool c3dTextureManager::Remove(int nTexIndex)
{
	std::map<int, c3dTexture*>::iterator res = data.find(nTexIndex);
	if (res != data.end())
	{
		data.erase(nTexIndex);
		return true;
	}
	else {
		c3dLog::WriteLog(c3dLog::Warn, "δ�ҵ���ǰ����������");
	}
	return false;
}

c3dTexture* c3dTextureManager::GetCurrentTexture()
{
	c3dTexture* pLocalTex = nullptr;
	std::map<int, c3dTexture*>::iterator res = data.find(nCurrentIndex);
	if (res != data.end())
	{
		pLocalTex = data[nCurrentIndex];
	}
	else {
		c3dLog::WriteLog(c3dLog::Warn, "δ�ҵ���ǰ����������");
	}
	return pLocalTex;
}

c3dTextureManager::c3dTextureManager(const c3dDevice* pDev):nCurrentIndex(0) 
{
	if (pDev == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
	}
	pDevice = pDev;
}

