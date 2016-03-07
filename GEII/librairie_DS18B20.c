
#define SIZE 1
#define NUMELEM 74


double temperature_DS18B20(void)
{
	char tempChar[6];
	double temperature;
	char * pEnd;

	FILE* fd = NULL;
    char buff[1024];
    memset(buff,0,sizeof(buff));

    fd = fopen("/sys/bus/w1/devices/28-041591dd2cff/w1_slave","r");

    if(NULL == fd)
    {
        printf("\n fopen() Error!!!\n");
        return 1;
    }

    if(SIZE*NUMELEM != fread(buff,SIZE,NUMELEM,fd))
    {
        printf("\n fread() failed\n");
        return 1;
    }

    fclose(fd);

    memcpy( tempChar, &buff[69], 5 );
    tempChar[5] = '\0';

    temperature=strtol (tempChar,&pEnd,10);

    return temperature/1000;
}