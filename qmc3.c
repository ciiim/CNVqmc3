#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MASKLENGTH 128 //掩码长度
int MoveLeftArray(int[], int);
int main(int argc, char *argv[])
{
    int mask[MASKLENGTH] = {0xc3, 0x4a, 0xd6, 0xca, 0x90, 0x67, 0xf7, 0x52, 0xd8, 0xa1, 0x66, 0x62, 0x9f, 0x5b, 0x09, 0x00,
                            0xc3, 0x5e, 0x95, 0x23, 0x9f, 0x13, 0x11, 0x7e, 0xd8, 0x92, 0x3f, 0xbc, 0x90, 0xbb, 0x74, 0x0e,
                            0xc3, 0x47, 0x74, 0x3d, 0x90, 0xaa, 0x3f, 0x51, 0xd8, 0xf4, 0x11, 0x84, 0x9f, 0xde, 0x95, 0x1d,
                            0xc3, 0xc6, 0x09, 0xd5, 0x9f, 0xfa, 0x66, 0xf9, 0xd8, 0xf0, 0xf7, 0xa0, 0x90, 0xa1, 0xd6, 0xf3,
                            0xc3, 0xf3, 0xd6, 0xa1, 0x90, 0xa0, 0xf7, 0xf0, 0xd8, 0xf9, 0x66, 0xfa, 0x9f, 0xd5, 0x09, 0xc6,
                            0xc3, 0x1d, 0x95, 0xde, 0x9f, 0x84, 0x11, 0xf4, 0xd8, 0x51, 0x3f, 0xaa, 0x90, 0x3d, 0x74, 0x47,
                            0xc3, 0x0e, 0x74, 0xbb, 0x90, 0xbc, 0x3f, 0x92, 0xd8, 0x7e, 0x11, 0x13, 0x9f, 0x23, 0x95, 0x5e,
                            0xc3, 0x00, 0x09, 0x5b, 0x9f, 0x62, 0x66, 0xa1, 0xd8, 0x52, 0xf7, 0x67, 0x90, 0xca, 0xd6, 0x4a};
    //mask
    FILE *fp1;             //被读取的文件的指针
    FILE *fp2;             //新建文件的指针
    char name[100];        //名字
    char bbuffer, abuffer; //缓冲区,a-after,b-before
    int i = 0;             //循环掩码
    static int c = 0;      //判断一组掩码是否使用完毕
    short code = 0;
    if (argc <= 1)
    {
        puts("缺少参数");
        getchar();
        exit(1);
    }

    strncpy(name, argv[1], 99);
    if (((fp1 = fopen(argv[1], "rb")) == NULL))
    {
        printf("无法打开：%s\n", argv[1]);
        exit(1);
    }
    strncpy(name, argv[1], 99);
    char *pos = strrchr(name, '.');//找到后缀名起始的标志“.”
    if (((strlen(name) + 4) <= 100) && *(pos + 4) == '3') //修改后缀名
    {
        *(++pos) = 'm';
        *(++pos) = 'p';
        *(++pos) = '3';
        *(++pos) = '\0';
    }
    else if (((strlen(name) + 4) <= 100) && *(pos + 4) == 'f')//修改后缀名
    {
        *(++pos) = 'f';
        *(++pos) = 'l';
        *(++pos) = 'a';
        *(++pos) = 'c';
        *(++pos) = '\0';
    }

    else
    {
        puts("不支持的格式");
        exit(1);
    }

    fp2 = fopen(name, "wb");

    size_t size = 0;
    fseek(fp1, 0, SEEK_END);
    size = ftell(fp1);
    fseek(fp1, 0, SEEK_SET);
    char *buf = malloc(size);//为要转换的文件分配空间
    //for(int i=0;i<10;i++)//test

    //char *buff1 = malloc( size );
    //char *buf = (char*)malloc( size );
    while ((fread(buf, sizeof(char), size, fp1)) == size)
    {
        for (int j = 0; j < size; j++, c++)
        {
            if (c == 0x8000)
            {
                MoveLeftArray(mask, MASKLENGTH);
                c = 0x0;
            }
            abuffer = (buf[j] ^ mask[i]);
            putc(abuffer, fp2);
            if (i == 127)
                i = 0;
            else
                i++;
        }
    }
    printf("DONE-[%s]\n", name);
    fclose(fp1);
    fclose(fp2);
}

int MoveLeftArray(int Mmask[], int length)//移动数组
{
    int temp = Mmask[0]; //
    for (int i = 1; i < length; i++)
        Mmask[i - 1] = Mmask[i];
    Mmask[length - 1] = temp;
    /*for(int i=0;i<length;i++)//test
        printf("%3d : %3X\n",i,Mmask[i]);*/
    //puts("-----------------");
    return 1;
}
