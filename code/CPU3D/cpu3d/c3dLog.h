#include "c3d.h"
enum c3dErrorType
{
	Nullptr,
	InvalidSize,
	OutOfIndex,
	OutOfRange,
	InvalidInit
};
class c3dLog
{
public:
	enum c3dLogLevel
	{
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};
	
	static void WriteLog(c3dLogLevel level,c3dString text)
	{
		switch (level)
		{
		case c3dLogLevel::Debug:
			std::cout << "[Debug]:" << text << std::endl;
			break;
		case c3dLogLevel::Info:
			std::cout << "[Info]:" << text << std::endl;
			break;
		case c3dLogLevel::Warn:
			std::cout << "[Warn]:" << text << std::endl;
			break;
		case c3dLogLevel::Error:
			std::cout << "[Error]:" << text << std::endl;
			break;
		case c3dLogLevel::Fatal:
			std::cout << "[Fatal]:" << text << std::endl;
			break;
		default:
			break;
		}
	}
	static void WriteErrorLog(c3dErrorType nErrorId)
	{
		switch (nErrorId)
		{
		case c3dErrorType::Nullptr:
			WriteLog(c3dLogLevel::Error, "���õ�ָ��Ϊ�ա�");
			break;
		case c3dErrorType::InvalidSize:
			WriteLog(c3dLogLevel::Error, "�������������buffer��С�Ƿ���");
			break;
		case c3dErrorType::OutOfIndex:
			WriteLog(c3dLogLevel::Error, "�������map���ʳ���������");
			break;
		case c3dErrorType::OutOfRange:
			WriteLog(c3dLogLevel::Error, "�ڴ����Խ�硣");
			break;
		case c3dErrorType::InvalidInit:
			WriteLog(c3dLogLevel::Error, "���豸�ظ���ʼ����");
			break;
		}
	}
};

