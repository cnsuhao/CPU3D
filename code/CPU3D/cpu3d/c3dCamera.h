#pragma once
#include "c3d.h"
class c3dCamera
{
public:
	c3dCamera(void);
	~c3dCamera(void);
	vec3 pos;		//�۾�λ��
	vec3 dir;	//�۾�����	
	vec3 upDir;	//ͷ������

	float ration;	//��߱�
	float fnear;	//���� Զ   ��
	float ffar;
};

