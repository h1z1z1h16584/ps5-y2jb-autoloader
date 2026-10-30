// SPDX-License-Identifier: GPL-3.0-or-later
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define NOTIFY_MAX 3075
#define COPY_BUF_SIZE (256 * 1024)

typedef struct {
  char unused[45];
  char message[NOTIFY_MAX];
} notify_request_t;

int sceKernelSendNotificationRequest(int, notify_request_t *request, size_t size, int flags);

static void notify(const char *msg) {
  notify_request_t req;
  memset(&req, 0, sizeof(req));
  snprintf(req.message, sizeof(req.message), "USB Y2JB Installer\n%s", msg);
  sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

/* Scans /mnt/ for any attached USB drive that contains download0.dat */
static int find_usb_source(char *out_path, size_t max_len) {
  for (int i = 0; i < 8; i++) {
    char test_path[256];
    snprintf(test_path, sizeof(test_path), "/mnt/usb%d/download0.dat", i);
    struct stat st;
    if (stat(test_path, &st) == 0 && st.st_size > 0) {
      snprintf(out_path, max_len, "%s", test_path);
      return 0;
    }
  }
  return -1;
}

/* Finds the installed YouTube title folder under /user/download/ */
static int find_target_dir(char *out_dir, size_t max_len) {
  const char *base = "/user/download";
  DIR *dir = opendir(base);
  if (!dir) {
    return -1;
  }

  struct dirent *entry;
  int found = -1;
  while ((entry = readdir(dir)) != NULL) {
    if (strncmp(entry->d_name, "PPSA0165", 8) == 0) {
      snprintf(out_dir, max_len, "%s/%s", base, entry->d_name);
      found = 0;
      break;
    }
  }
  closedir(dir);

  if (found != 0) {
    snprintf(out_dir, max_len, "/user/download/PPSA01650");
    mkdir(out_dir, 0777);
    found = 0;
  }
  return found;
}

static int copy_file(const char *src, const char *dst) {
  int in_fd = open(src, O_RDONLY);
  if (in_fd < 0) {
    return -1;
  }

  char partial_dst[512];
  snprintf(partial_dst, sizeof(partial_dst), "%s.partial", dst);

  int out_fd = open(partial_dst, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (out_fd < 0) {
    close(in_fd);
    return -2;
  }

  char *buf = malloc(COPY_BUF_SIZE);
  if (!buf) {
    close(in_fd);
    close(out_fd);
    unlink(partial_dst);
    return -3;
  }

  ssize_t bytes_read;
  int err = 0;
  while ((bytes_read = read(in_fd, buf, COPY_BUF_SIZE)) > 0) {
    ssize_t bytes_written = 0;
    while (bytes_written < bytes_read) {
      ssize_t res = write(out_fd, buf + bytes_written, bytes_read - bytes_written);
      if (res <= 0) {
        err = -4;
        break;
      }
      bytes_written += res;
    }
    if (err) {
      break;
    }
  }

  if (bytes_read < 0) {
    err = -5;
  }

  fsync(out_fd);
  close(in_fd);
  close(out_fd);
  free(buf);

  if (err != 0) {
    unlink(partial_dst);
    return err;
  }

  if (rename(partial_dst, dst) != 0) {
    unlink(partial_dst);
    return -6;
  }

  return 0;
}

int main(void) {
  notify("Searching for USB...");

  char src_path[256];
  if (find_usb_source(src_path, sizeof(src_path)) != 0) {
    notify("Error: download0.dat not found on root of USB!");
    return 1;
  }

  char target_dir[256];
  if (find_target_dir(target_dir, sizeof(target_dir)) != 0) {
    notify("Error: Could not locate /user/download/PPSA0165*");
    return 1;
  }

  char dest_path[512];
  snprintf(dest_path, sizeof(dest_path), "%s/download0.dat", target_dir);

  notify("Copying download0.dat from USB...");

  int res = copy_file(src_path, dest_path);
  if (res == 0) {
    notify("Success! download0.dat copied to YouTube folder.");
  } else {
    char err_msg[128];
    snprintf(err_msg, sizeof(err_msg), "Copy failed! (Error code %d)", res);
    notify(err_msg);
    return 1;
  }

  return 0;
}
