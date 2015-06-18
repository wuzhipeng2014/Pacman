#include "stdafx.h"
#include "GMap.h"
#define PLAYERSPEED 6//����ٶ�
#define ENERMYSPEED 4//�����ٶ�
#define LEGCOUNTS 5//�����ȵ�����
#define DISTANCE 10//ͼ�ͷ�Χ
#define BLUE_ALERT 8//��ɫ���䷶Χ
#define D_OFFSET   2//��ͼ���
#define RD (DISTANCE + D_OFFSET)//��ͼ��Χ 12 
#include <time.h>
//����ö��
enum TWARDS{UP,DOWN,LEFT,RIGHT,OVER};
//������
class GObject{
protected:
	int mX;
	int mY;
	TWARDS twCommand;//ָ���
	POINT point;//��������
	int dRow;//�߼�������
	int dArray;//�߼�������
	int speed;//�ٶ�
	TWARDS tw;//����
	int frame;//����
	//�ӳ���
	bool Achive(); //�ж������Ƿ񵽴��߼�����λ��
	bool Collision() ;//�߼���ײ���,������ڷŵ������λ��
	int PtTransform(int k);//��ʵ������ת��Ϊ�߼�����
	virtual void AchiveCtrl();//�����߼�����������
public:
	void SetPosition(int Row,int Array);
	void DrawBlank( HDC& hdc);
	void virtual Draw( HDC& hdc)=0;//���ƶ���
	static GMap* pStage; //ָ���ͼ���ָ��,����Ϊ��̬,ʹ������������ܹ�ʹ����ͬ�ĵ�ͼ
	GObject(int Row,int Array){
		frame = 1;
		pStage = NULL;
		this->dRow = Row;
		this->dArray  = Array;
		this->point.y = dRow*pStage->LD+pStage->LD/2;
		this->point.x = dArray*pStage->LD+pStage->LD/2;
		this->mX =point.x;
		this->mY =point.y;
	}
	void virtual action() = 0;//���ݱ���ı���
	int GetRow();
	int GetArray();
	
};
//����,��ҿ��ƵĶ���
class PacMan:public GObject{

protected:
	virtual void AchiveCtrl();//��д�麯��
	
public:
	POINT GetPos();
	TWARDS GetTw();
	bool Win();
	void Draw(HDC& hdc);
	void SetTwCommand(TWARDS command);
	void Over();
	PacMan(int x,int y):GObject(x,y)
	{
		this->speed = PLAYERSPEED;
		twCommand=tw = LEFT;
	}
	void action();
};
//׷������ĵ���
class Enermy:public GObject{
protected:
	void Catch();//�Ƿ�ץס����
	void virtual MakeDecision(bool b) = 0;//AIʵ��
	COLORREF color;
public:
	static PacMan* player;
	void virtual  Draw(HDC& hdc);
	Enermy(int x,int y):GObject(x,y)
	{
		this->speed = ENERMYSPEED;
		tw = LEFT;
		twCommand = UP;
	}
	void virtual action();
};

class RedOne:public Enermy  //�漴�ƶ�S
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC& hdc);
	RedOne(int x,int y):Enermy(x,y)
	{
		color = RGB(255,0,0);
	}
};

class BlueOne:public RedOne//������
{	
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC& hdc);
	BlueOne(int x,int y):RedOne(x,y)
	{
	
		color = RGB(0,0,255);
	}
	
};

class YellowOne:public RedOne //������
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC& hdc);
	YellowOne(int x,int y):RedOne(x,y)
	{
		color = RGB(200,200,100);
	}
};



