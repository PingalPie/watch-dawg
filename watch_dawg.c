#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>

#include <sys/inotify.h>
// #include <libnotify/notify.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE            1
#define EXIT_ERR_INIT_INOTIFY   2
#define EXIT_ERR_FILE_TO_WATCH  3
#define EXIT_ERR_READING_FILE   4

void handle_event(int fd, const char *filename) {
  // TODO: add directory handle_event
  char buffer[4096];
  char *msg;
  const struct inotify_event *file_event;
  uint32_t read_length;

  /* NotifyNotification *notification_handle; */
  /* int notify_init_status; */

  /* notify_init_status = notify_init("watch_dawg"); */
  /* if (!notify_init_status){ */
  /*   fprintf(stderr, "[!] Unable to initialize notify"); */
  /* } */

  for (;;) {
    // open file
    read_length = read(fd, buffer, sizeof(buffer));
    if (read_length == -1 && errno != EAGAIN) {
      perror("read");
      exit(EXIT_ERR_READING_FILE);
    }

    for (char *buff_ptr = buffer;
    buff_ptr < buffer + read_length;
    buff_ptr += sizeof(struct inotify_event) + file_event->len) {

      // read file_event
      file_event = (const struct inotify_event *) buff_ptr;
      // check file_event type
      if (file_event->mask & IN_DELETE)
        msg = "Deleted";
      if (file_event->mask & IN_ACCESS)
        msg = "Accessed";
      if (file_event->mask & IN_CLOSE_WRITE)
        msg = "Write closed";
      if (file_event->mask & IN_MODIFY)
        msg = "Modified";
      if (file_event->mask & IN_MOVE_SELF)
        msg = "Edited";

      if (msg == NULL)
        continue;

      /* if (notify_init_status){ */
        msg = strcat(strcat(strcat("[", filename), "]: "), msg);

      /*   notification_handle = notify_notification_new("Watch Dawg", msg, "dialog-information"); */
      /*   if (notification_handle == NULL) { */
      /*     fprintf(stderr, "Unable to start notification handle"); */
      /*     notify_init_status = 0; */
      /*     printf("[FILE]: %s\n", msg); */
      /*     notify_uninit(); */
      /*   } else { */
      /*     if (!notify_notification_show(notification_handle, NULL)) */
      /*       fprintf(stderr, "\n"); */
      /*   } */
      /* } else { */
        printf("[FILE]: %s\n", msg);
      /* } */
    }
  }
  /* if (notify_init_status) */
    /* notify_uninit(); */
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s PATH [PATH...]\n", argv[0]);
    argv[1] = "watch_dawg.c";
    // exit(EXIT_FAILURE);
  }
  // char *files[argc-1];
  // for (int i = 0; i < argc; ++i){
  //   files[i] = argv[i];jklsd
  // }
  const char *basePath = realpath(argv[1], NULL);
  int fd = inotify_init();
  
  const uint32_t watchMask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF; 

  if (fd == -1){
    perror("inotify_init");
    exit(EXIT_ERR_INIT_INOTIFY);
  }

  int ievent_status = inotify_add_watch(fd, basePath, watchMask);
  if (ievent_status == -1) {
    fprintf(stderr, "Cannot watch '%s': %s\n", basePath, strerror(errno));
    exit(EXIT_ERR_FILE_TO_WATCH);
  }

  handle_event(fd, basePath);

  close(fd);
  exit(EXIT_SUCCESS);
}
