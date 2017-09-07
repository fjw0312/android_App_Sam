
#include <signal.h>
#include "stdsys.h"		/* all standard system head files			*/
#include "basetypes.h"
#include "pubfunc.h"
//#include "halcomm.h"
#include "new.h"
#include "err_code.h"

#define TEST_DATA_LENGTH 512

extern "C"
{
HANDLE CommOpen(IN char	*pszStdPortLib,
	IN char *pPortDescriptor,
	IN char *pOpenParams,
	IN DWORD dwPortAttr,	
	IN int	nTimeout,	
	OUT int	*pErrCode);
HANDLE CommAccept(IN HANDLE hPort);
int CommRead ( IN HANDLE hPort, OUT char *pBuffer, IN int nBytesToRead );
int CommWrite ( IN HANDLE hPort, IN char *pBuffer, IN int nBytesToWrite );
int CommControl ( IN HANDLE hPort,IN int nCmd, IN OUT char *pBuffer,  IN int nBufferLength );
int CommClose ( IN HANDLE hPort );
}


	


/*static char *GetStandardPortDriverName(IN int nStdPortType)
{
	const char *pszStdDriver[] =
	{
		"comm_std_serial.so",
		"comm_hayes_modem.so",
		"comm_net_tcpip.so",
		"comm_acu_485.so"
		"comm_virtual_dev.so"
	};

	return (char *)pszStdDriver[nStdPortType];
}*/
void dump_buf( char *buf, int n)
{
	while (n > 0)
	{
		printf( "%c", *buf ++);
		n --;
	}

	printf( "\n" );
}

main()
{
	printf("11\n");
	HANDLE	hPort;
	char	szBuf[3]="12";
	char	szBufRead[3];
	int     n, i;
	int	nErrCode = ERR_COMM_OK;
	

	printf(" szbuf is:%s\n",szBuf);
	
	hPort = CommOpen( "comm_virtual_dev.so",
		"com5", 
		" ", 
		0x00,
		5000,
		&nErrCode);
	
	if (hPort == NULL)
	{
		printf("open error!\n");
		return 0;
	}
	else printf("open ok\n");
	
	//test write the digit number to virtual dev
	n = CommWrite( hPort, szBuf, TEST_DATA_LENGTH );
	if(!n) printf("write error!\n");
	else printf("write ok!\n");
	
	//test read the write number from virtual dev
	n = CommRead(hPort, szBufRead, 9);
	if(!n) printf("read error!\n");
	else printf("read ok!\n");
	printf("szBufRead is %s,\n",&szBufRead);
	dump_buf( szBufRead, n);
	
	//test close the virtual dev
	n=CommClose(hPort);
	if(n) printf("close wrong\n");
	else printf("close ok\n");

	
}
