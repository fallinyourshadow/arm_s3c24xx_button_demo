#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "code.c"
int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    int press_cnt[4];
    int isStart = 0;
    system("mknod /dev/buttons c ");
    fd = open("/dev/buttons", 0);  // 打开设备
    if (fd < 0) {
        printf("Can't open /dev/buttons\n");
        return -1;
    }
    // 这是个无限循环，进程有可能在read函数中休眠，当有按键被按下时，它才返回
    while (1) {
        // 读出按键被按下的次数
        ret = read(fd, press_cnt, sizeof(press_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        }
        for (i = 0; i < sizeof(press_cnt)/sizeof(press_cnt[0]); i++) {
            // 如果被按下的次数不为0，打印出来
            if(press_cnt[i])
            {
                printf("%d %d\n",press_cnt[i],i);
            }
        }
    }
    close(fd);
    return 0;
}

