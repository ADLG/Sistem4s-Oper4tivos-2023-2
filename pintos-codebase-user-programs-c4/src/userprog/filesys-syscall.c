#include "userprog/filesys-syscall.h"
#include <stdio.h> // here putbuf is defined
#include <stdlib.h>
#include "devices/input.h" // here getinputc is defined
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "lib/syscall-nr.h"
#include "threads/interrupt.h"
#include "userprog/syscall.h"
#include "threads/thread.h"

struct process_open_file * get_file(int);
static void exit_syscall (int exit_status);

void filesys_syscall_init (void)
{
  lock_init(&mutex);
}

bool filesys_syscall_create (const char* file_name, unsigned initial_size)
{
  if (file_name == NULL) {exit_syscall(-1);}
  bool success = false ;
  lock_acquire (& mutex );
  success = filesys_create ( file_name , initial_size );
  lock_release (& mutex );
  return success ;
}

bool filesys_syscall_remove (const char* file_name)
{
  if (file_name == NULL) {exit_syscall(-1);}
  bool success = false ;
  lock_acquire (& mutex );
  success = filesys_remove(file_name);
  lock_release (& mutex );
  return success;
}

int32_t filesys_syscall_open (const char* file_name)
{
  lock_acquire (& mutex );
  struct file_name * file_pointer = filesys_open(file_name);
  lock_release (& mutex );

  if (file_pointer == NULL) {exit_syscall(-1);}

  struct process_open_file * fd_elem = malloc (sizeof(struct process_open_file));
  fd_elem->fd = ++thread_current()->fd_count;
  fd_elem->file_pointer = file_pointer;
  list_push_front(&thread_current()->file_list,&fd_elem->elem);
  return fd_elem->fd;
}

void filesys_syscall_close (int32_t file_descriptor)
{
  if (file_descriptor == STDIN_FILENO || file_descriptor == STDOUT_FILENO)
  return;
  
  struct process_open_file * fd_elem = get_file(file_descriptor);
  if (fd_elem == NULL) {exit_syscall(-1);}
  
  lock_acquire(&mutex);
  file_close(fd_elem->file_pointer);
  lock_release(&mutex);

  list_remove(&fd_elem->elem);
  free(fd_elem);
}

void filesys_syscall_close_all (void)
{
  shutdown_power_off();
}

int32_t filesys_syscall_write (int32_t file_descriptor, const void* buffer, unsigned size)
{
  if (file_descriptor == STDOUT_FILENO)
  {
    putbuf(buffer,size);
    return size;
  }
  
  struct process_open_file * fd_elem = get_file(file_descriptor);
  if(fd_elem == NULL) {exit_syscall(-1);}
  
  lock_acquire(&mutex);
  int ret = file_write(fd_elem->file_pointer,buffer,size);
  lock_release(&mutex);
  return ret;
}

int32_t filesys_syscall_read (int32_t file_descriptor, void* buffer, unsigned size)
{
  int tam =0;
  if (file_descriptor == STDIN_FILENO)
  { 
    while (tam < size)
    {
      *((char *)buffer+tam) = input_getc();
      tam++;
    }
    return tam;
  }

  struct process_open_file * fd_elem = get_file(file_descriptor);
  if (fd_elem == NULL) {exit_syscall(-1);}
  
  lock_acquire(&mutex);
  tam = file_read(fd_elem->file_pointer,buffer,size);
  lock_release(&mutex);
  return tam;
}

int32_t filesys_syscall_size (int32_t file_descriptor)
{
  struct process_open_file * fd_elem = get_file(file_descriptor);
  if(fd_elem == NULL) {exit_syscall(-1);}
      
  lock_acquire(&mutex);
  int length = file_length(fd_elem->file_pointer); 
  lock_release(&mutex);
  return length;
}

void filesys_syscall_seek (int32_t file_descriptor, unsigned position)
{
  struct process_open_file * fd_elem = get_file(file_descriptor);
  if (fd_elem == NULL) {exit_syscall(-1);}
  
  lock_acquire(&mutex);
  file_seek(fd_elem->file_pointer,position);
  lock_release(&mutex);
}

unsigned filesys_syscall_tell (int32_t file_descriptor)
{
  struct process_open_file * fd_elem = get_file(file_descriptor);
  if (fd_elem == NULL) {exit_syscall(-1);}
  
  lock_acquire(&mutex);
  unsigned pos = file_tell (fd_elem->file_pointer);
  lock_release(&mutex);
  return pos;
}

struct process_open_file * get_file (int fd)
{
  struct thread * curr = thread_current();
  struct list_elem * e;

  for (e = list_begin(&curr->file_list); e != list_end (&curr->file_list); e = list_next(e))
  {
    struct process_open_file * fd_elem = list_entry(e, struct process_open_file,elem);
    if (fd_elem->fd == fd)
      return fd_elem;
  }
  return NULL;
}

static void 
exit_syscall (int exit_status UNUSED)
{
  struct thread * t = thread_current();
  struct thread * padre = t->padre;
  printf ("%s: exit(%d)\n", t->name, exit_status);

  if (padre != NULL)
  {
    struct list * hijos = &padre->hijos;
    struct list_elem * hijos_e;
    if (!list_empty(hijos))
    {
      for (hijos_e = list_front(hijos); hijos_e != list_end(hijos); hijos_e = list_next(hijos_e))
      {
        struct threadch * thhijo = list_entry(hijos_e, struct threadch, elem);
        if (thhijo->tid == t->tid)
        {
          thhijo->exitst = exit_status;
          sema_up(&padre->wait);
        }
      }
    }
  }
  thread_exit ();
}
// TODO: Here add the other remaining functions from file-syscall.h