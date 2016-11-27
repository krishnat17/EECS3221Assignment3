/*
  Krishna Thevathasan
  krishnat@my.yorku.ca
  212946893
*/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef void(*test)(void);

int main (int argc, char **argv) {

  const char *error;
  void *module;
  test demo;

  if(argc != 3) {
    fprintf(stderr,"%s - Exactly 2 arguments only\n", argv[0]);
    exit(1);
  }

  if (strncmp("reading", argv[1], strnlen(argv[1])) == 0){
    printf("In reading\n");

    //Load library
    module = dlopen("./reading.so", RTLD_LAZY);
    if (!module) {
      fprintf(stderr, "%s - Couldn't open reading.so\n", dlerror());
      exit(1);
    }

    //Get symbol
    dlerror();
    demo = dlsym(module, "my_cnt");
    if (error = (dlerror())) {
      fprintf(stderr, "%s - Couldn't find my_cnt\n", error);
      exit(1);
    }

    //Call function in library
    (*demo)();

    //Close module
    dlclose(module);

  }
  else if (strncmp("mapping", argv[1], strnlen(argv[1])) == 0){
    printf("In mapping\n");

    //Load library
    module = dlopen("./mapping.so", RTLD_LAZY);
    if (!module) {
      fprintf(stderr, "%s - Couldn't open mapping.so\n", dlerror());
      exit(1);
    }

    //Get symbol
    dlerror();
    demo = dlsym(module, "my_cnt");
    if (error = (dlerror())) {
      fprintf(stderr, "%s - Couldn't find my_cnt\n", error);
      exit(1);
    }

    //Call function in library
    (*demo)();

    //Close module
    dlclose(module);

  }
  else {
    fprintf(stderr,"%s - Only 'reading', 'mapping' or any leading substring are acceptable first arguments.\n'", argv[0]);
    exit(1);
  }

return 0;
}
