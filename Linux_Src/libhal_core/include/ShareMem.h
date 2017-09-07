
//****************************************************************************
//*
//* 文件名: ShareMem.h
//*
//* 用途:
//*     共享内存模块的头文件，与共享内存有关的定义
//*
//* IO-LAN + SHMM ＋ V000 ＋ B000 ＋ D001
//*
//****************************************************************************

#ifndef SHARE_MEM_H
#define SHARE_MEM_H  0x01

#ifdef WIN32
#pragma pack (1)
#define PACKED
#else
#define PACKED __attribute__((packed, aligned(1)))
#endif

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define SHMM_BUFSZ (1024 * 4)

// 定义错误码
#define SHMM_ERR_OK             0x00  // 没有错误
#define SHMM_ERR_FTOK          -0x01  // 执行ftok()函数失败
#define SHMM_ERR_SHMGET        -0x02  // 执行shmget()函数失败
#define SHMM_ERR_SHMCTL        -0x03  // 执行shmctl()函数失败
#define SHMM_ERR_LEN_MAX       -0x04  // 数据长度超过允许的最大值
#define SHMM_ERR_POINT         -0x05  // 向共享内存操作的指针将越界，（即将超出共享内存储存区或）
#define SHMM_ERR_SHMAT         -0x06  // 执行shmat()函数失败
#define SHMM_ERR_SHMDT         -0x07  // 执行shmdt()函数失败
#define SHMM_ERR_SEMGET        -0x08  // 执行semget()函数失败
#define SHMM_ERR_SEMOP         -0x09  // 执行semop()函数失败
#define SHMM_ERR_SEMCTL        -0x0A  // 执行semctl()函数失败
#define SHMM_ERR_NO_RW         -0x0B  // 共享内存不能进行读写操作
#define SHMM_ERR_CHANNEL       -0x0C  // 通道号错误


////////////////////////////////////////////////////////////////////

//***************************************************
//              共享内存记录信息结构体
//***************************************************
typedef struct _SHMM_RECORD_INFO
{  
	char         cValueDi;            // 所有DI通道的当前值
	char         cDiWarnStatus;       // 所有DI通道的告警状态值；1:有告警，0:无告警

	char         cValueEmpty1;        // 预留字符值1
	char         cValueEmpty2;        // 预留字符值2

	float        fValueAi1;           // AI通道1的当前值
	float        fValueAi2;           // AI通道2的当前值
	float        fValueAi3;           // AI通道3的当前值
	float        fValueAi4;           // AI通道4的当前值
	float        fValueAi5;           // AI通道5的当前值
	float        fValueAi6;           // AI通道6的当前值
	float        fValueAi7;           // AI通道7的当前值
	float        fValueAi8;           // AI通道8的当前值
	float        fValueAi9;           // AI通道9的当前值
	float        fValueAi10;          // AI通道10的当前值
	float        fValueAi11;          // AI通道11的当前值
	float        fValueAi12;          // AI通道12的当前值
	float        fValueAi13;          // AI通道13的当前值
	float        fValueAi14;          // AI通道14的当前值

	float        fValueEmpty1;        // 预留浮点值1
	float        fValueEmpty2;        // 预留浮点值2
	
}SHMM_RECORD_INFO, *PSHMM_RECORD_INFO;

//-- start 对外接口函数封装 --

//************************************************************
// 函数: SHMM_Open
//
// 说明:
//  打开或创建共享内存
//    
// 参数：  
//   bCreate  1：创建共享内存；0：打开共享内存
//
// 返回值: 
//	 -1:    失败
//   其它： ipcs key 值
//	
//************************************************************
key_t SHMM_Open(int bCreate);

//************************************************************
// 函数: SHMM_Close
//
// 说明:
//   关闭共享内存
//    
// 参数：   
//   g_keyShmm  ipc key 值
//
// 返回值: 
//	 0:    成功
//   其它: 错误码
//	
//************************************************************
int SHMM_Close();

//************************************************************
// 函数: SHMM_Write
//
// 说明:
//   向共享内存写入数据
//    
// 参数：   
//   nChannelNo  通道号，0：DI，1~14：AI
//   pBuf        储存写的数据的内存指针。
//   nLen        要写入的数据长度。对于DI，为2 char；对于AI，为1 float
//
// 返回值: 
//	 >= 0:    实际写入的数据长度
//   <  0:    错误码
//	
//************************************************************
int SHMM_Write(int nChannelNo, char* pBuf, int nLen);

//************************************************************
// 函数: SHMM_Read
//
// 说明:
//   读取共享内存的数据
//    
// 参数：   
//   nChannelNo  通道号，0：DI，1~14：AI
//   pBuf        储存读取数据的内存指针。
//   nLen        要读取的数据长度。对于DI，为2 char；对于AI，为1 float
//
// 返回值: 
//	 >= 0:    实际读取的数据长度
//   <  0:     错误码
//	
//************************************************************
int SHMM_Read(int nChannelNo, char* pBuf, int nLen);

//************************************************************
// 函数: SHMM_SetReadedStatus
//
// 说明:
//   设置所有DI通道数据已读的标识
//    
// 参数：   
//
// 返回值: 
//	 = 0:      设置正确
//   <  0:     错误码
//	
//************************************************************
int SHMM_SetReadedStatus();

//************************************************************
// 函数: SHMM_GetWarnStatus
//
// 说明:
//   获取所有DI通道的告警标识值
//    
// 参数： 
//   pDiWarnStatus    所有DI通道的告警标识值
//
// 返回值: 
//	 = 0:      正确
//   <  0:     错误码
//	
//************************************************************
int SHMM_GetWarnStatus(char* pDiWarnStatus);

//-- end 对外接口函数封装 --

#ifdef WIN32
#pragma pack (4)
#else
#endif

#endif // SHARE_MEM_H
