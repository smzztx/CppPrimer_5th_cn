#ifndef _SHMDATA_H_HEADER  
#define _SHMDATA_H_HEADER  
  
#define TEXT_SZ 2048  
  
struct shared_use_st  
{  
    //��Ϊһ����־����0����ʾ�ɶ���0��ʾ��д
	int written;
	//��¼д��Ͷ�ȡ���ı�	
    char text[TEXT_SZ];  
};  
  
#endif
