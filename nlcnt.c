/*
  Krishna Thevathasan
  krishnat@my.yorku.ca
  212946893
*/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef void* (*loadedFunction)();

int main (int argc, char *argv[]) {

  const char *error;
  char fileName[100];
  void *handle;
  loadedFunction func;

  //argv[1] should be either the signifier to for reading or mapping
  //argv[2] should be the file name
  if(argc != 3) {
    fprintf(stderr,"%s - Exactly 2 arguments only\n", argv[0]);
    exit(1);
  }

  //Get file name
  strcpy(fileName, argv[2]);

  //Check if user wants to use reading method
  if (strncmp("reading", argv[1], strnlen(argv[1])) == 0){

    //Load library
    handle = dlopen("./reading.so", RTLD_LAZY);
    if (!handle) {
      fprintf(stderr, "%s - Couldn't open reading.so\n", dlerror());
      exit(1);
    }

    //Get symbol
    dlerror();
    *(void**)(&func) = dlsym(handle, "my_cnt");
    if (error = (dlerror())) {
      fprintf(stderr, "%s - Couldn't find my_cnt\n", error);
      exit(1);
    }

    //Call function in library
    (void)func(argv[2]);

    //Close handle
    dlclose(handle);

  }
  //Check if user wants to use mapping method
  else if (strncmp("mapping", argv[1], strnlen(argv[1])) == 0){

    //Load library
    handle = dlopen("./mapping.so", RTLD_LAZY);
    if (!handle) {
      fprintf(stderr, "%s - Couldn't open mapping.so\n", dlerror());
      exit(1);
    }

    //Get symbol
    dlerror();
    *(void**)(&func) = dlsym(handle, "my_cnt");
    if (error = (dlerror())) {
      fprintf(stderr, "%s - Couldn't find my_cnt\n", error);
      exit(1);
    }

    //Call function in library
    (void)func(argv[2]);

    //Close handle
    dlclose(handle);

  }
  else {
    fprintf(stderr,"%s - Only 'reading', 'mapping' or any leading substring are acceptable first arguments.\n'", argv[0]);
    exit(1);
  }

return 0;
}
