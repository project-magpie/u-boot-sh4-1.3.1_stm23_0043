/*********************************************************************
**
**  this file for make 8M nor-flash image
**  LJF 2010/06/09 create
**
*********************************************************************/



#include <stdio.h>
#include <string.h>
#include <unistd.h>



#define K               (1024)
#define M               (K*K)
//#define BOOT_SIZE       (6*64*K)
#define BUFFER_SIZE     (4*K)
//#define IMAGE_SIZE      (8*M)


/*********************************************************************
    argv[1]: input file name
    argv[2]: output file name
    argv[3]: output file size
*********************************************************************/

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}
	if (!base) {
		base = 10;
	}
	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}

long simple_strtol(const char *cp,char **endp,unsigned int base)
{
	if(*cp=='-')
		return -simple_strtoul(cp+1,endp,base);
	return simple_strtoul(cp,endp,base);
}

int main(int argc, char *argv[])
{
    unsigned char buf[BUFFER_SIZE];
    FILE *fpR = NULL;
    FILE *fpW = NULL;
    int iRet = 0;
    int iReadSize = 0;
    int iWriteSize = 0;
    int OUTPUTFILE_SIZE = 0;

    if(argc < 4)
    {
        printf("---invalid parameter---\n");
        return -1;
    }
	OUTPUTFILE_SIZE = simple_strtol(argv[3], NULL, 0);
	printf("argv[1] = %s, argv[2]=%s, argv[3]=%d\n",argv[1],argv[2],OUTPUTFILE_SIZE);
    memset(buf, 0xFF, sizeof(buf));
    fpR = fopen(argv[1], "rb");
    if(NULL == fpR)
    {
        printf("---open %s failed---\n", argv[1]);
        return -1;
    }

    iRet = unlink(argv[2]);

    fpW = fopen(argv[2], "wb");
    if(NULL == fpW)
    {
        printf("---open %s failed---\n", argv[2]);
        return -1;
    }

    fseek(fpR, 0, SEEK_SET);
    fseek(fpW, 0, SEEK_SET);

    while((iReadSize = fread(buf, 1, BUFFER_SIZE, fpR)) > 0)
 	{
//        printf(".");
        fwrite(buf, iReadSize, 1, fpW);
        iWriteSize += iReadSize;
        memset(buf, 0xFF, sizeof(buf));
    }

    memset(buf, 0xFF, sizeof(buf));
    while(iWriteSize < OUTPUTFILE_SIZE)
    {
//       printf(".");
        iReadSize = ((OUTPUTFILE_SIZE - iWriteSize) > BUFFER_SIZE) ? BUFFER_SIZE : (OUTPUTFILE_SIZE - iWriteSize);
        fwrite(buf, iReadSize, 1, fpW);
        iWriteSize += iReadSize;
        memset(buf, 0xFF, sizeof(buf));
    }

    fclose(fpR);
    fclose(fpW);

    return 0;
}




