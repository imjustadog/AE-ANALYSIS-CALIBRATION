#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <mqueue.h>
#include <string.h>
#include <sys/time.h>


unsigned char buf[128];

int main(int argc, char *argv[]) {

  mqd_t mqd, mqf;
  char timebuf[30];

  int fd, rc, fdw, i;
  int flag = 0;
  int count = 0;
  int capture_count = 0;
  unsigned char folder_name[30];
  unsigned char folder_path[40];
  unsigned char *pfolder = folder_name;
  unsigned char path[70];

  mqd = mq_open("/mqd",O_WRONLY);
  if (mqd < 0) {
      perror("message queue failed to read");
      exit(1);
  }

  mqf = mq_open("/mqf",O_WRONLY);
  if (mqf < 0) {
      perror("message queue failed to read");
      exit(1);
  }

  sprintf(folder_path, "%s/%s", argv[1], argv[2]);
  mkdir(folder_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP |S_IROTH | S_IWOTH |S_IXOTH);
  mq_send(mqd, "o", 1, 0);

    while (1) {
        printf("%d\r\n", capture_count);
    	sprintf(path, "%s/%d", folder_path, capture_count);
        capture_count ++;
        mq_send(mqf, path, strlen(path), 1);
        sleep(5);
    }
}


