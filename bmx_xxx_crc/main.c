#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
	if(argc != 2) return 0;
	FILE *f = fopen(argv[1],"rb");
	fseek(f,0,SEEK_END);
	size_t fsize = ftell(f);
	if(fsize != 0x24040)
	{
		puts("No BMX XXX gci!");
		fclose(f);
		return 0;
	}
	rewind(f);
	unsigned char *buf = malloc(fsize);
	fread(buf,fsize,1,f);
	fclose(f);

	unsigned int sum = 0;
	unsigned int chkArea = 0x2319C;

	size_t i;
	for(i = 0x684; i < 0x684+chkArea; i++)
		sum += buf[i];
	printf("%08x\n",sum);
	sum = __builtin_bswap32(sum);

	memcpy(buf+0x40, &sum, 4);
	f = fopen(argv[1],"wb");
	fwrite(buf,0x24040,1,f);
	fclose(f);
	free(buf);
	return 0;
}