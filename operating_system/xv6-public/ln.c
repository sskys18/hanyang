#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 4){ //
    printf(2, "Usage: ln [-s] or [-h] <old> <new>\n");
    exit();
  }
  int symbolic = 0;
  int opt;

  // -s 혹은 -h의 명령어인지 확인
  while ((opt = getopt(argc, argv, "sh")) != -1) {
    switch (opt) {
      case 's':
        symbolic = 1;
        break;
      case 'h':
        symbolic = 0;
        break;
      default:
        printf(2, "Unknown option: %c\n", opt);
        exit();
    }
  }

  if (symbolic) {
    if (symlink(argv[3], argv[4]) < 0)
      printf(2, "symlink %s %s: failed\n", argv[optind], argv[optind + 1]);
  } else {
    if (link(argv[3], argv[4]) < 0)
      printf(2, "hardlink %s %s: failed\n", argv[optind], argv[optind + 1]);
  }
}
