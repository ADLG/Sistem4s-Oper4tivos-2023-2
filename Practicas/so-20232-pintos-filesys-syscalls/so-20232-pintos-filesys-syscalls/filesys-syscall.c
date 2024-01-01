#include "userprog/filesys-syscall.h"
#include <stdio.h> // here putbuf is defined
#include "devices/input.h" // here getinputc is defined
#include "filesys/filesys.h"
#include "filesys/file.h"
// TODO: here add any other needed import

void filesys_syscall_init (void)
{
  // TODO: here perform any initialization for this module
  // TODO: Con this function in syscall_init in src/userprog/syscall.c
}

// TODO: Here add the other remaining functions from file-syscall.h