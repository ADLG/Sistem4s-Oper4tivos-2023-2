#ifndef USERPROG_FILESYS_SYSCALL_H
#define USERPROG_FILESYS_SYSCALL_H

#include "filesys/filesys.h"
#include "threads/synch.h"
#include <list.h>

struct lock mutex;

struct process_open_file 
{
  struct file * file_pointer;   /* Apuntador de los archivos. */
  struct list_elem elem;        /* La lista de elementos. */
  int fd;                       /* Descriptor de archivo. */
};

void filesys_syscall_init (void);
bool filesys_syscall_create (const char* file_name, unsigned initial_size);
bool filesys_syscall_remove (const char* file_name);
int32_t filesys_syscall_open (const char* file_name);
void filesys_syscall_close (int32_t file_descriptor);
void filesys_syscall_close_all (void);
int32_t filesys_syscall_write (int32_t file_descriptor, const void* buffer, unsigned size);
int32_t filesys_syscall_read (int32_t file_descriptor, void* buffer, unsigned size);
int32_t filesys_syscall_size (int32_t file_descriptor);
void filesys_syscall_seek (int32_t file_descriptor, unsigned position);
unsigned filesys_syscall_tell (int32_t file_descriptor);

#endif /* userprog/filesys-syscall.h */