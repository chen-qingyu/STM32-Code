#include "gprs.h"

void GPRS_Init(void)
{
    printf("AT+CGCLASS=\"B\"\r\n");
    printf("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");
    printf("AT+CGATT=1\r\n");
    printf("AT+CIPCSGP=1,\"CMNET\"\r\n");
    printf("AT+CIPSTART=\"TCP\",\"120.77.208.31\",\"10001\"\r\n");
}

void GPRS_Send(u8 data, OS_TICK ts)
{
    printf("@ %d ms: AT+CIPSEND\r>%3d\r\n", ts * 5, data);
}
