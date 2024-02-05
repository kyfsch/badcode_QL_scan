// This function is used to detect the vulnerability by triggering a null pointer dereference. Function __div0 is being called from the application. So by creating a stack frame on which the null function pointer is stored and changing the top of stack can achieve this goal..
void __div0 (void)
{
  char buffer[32];
  int *p;
  p = (int*) buffer; // Here, we store the (NULL)address of the buffer on the stack
  ((int(*)(int)) p) (1); // Now, we invoke the function by calling it passing 1 as the argument
}

void __div0_replacement (void)
{
  if (__builtin_expect (get_tls ()->called_from_lib2 != 1, 0))
    abort ();
}

int main (void)
{
  // A new stack frame is created in here. In which the function pointer of __div0_replacement is stored
  __div0_replacement ();
  return 0;
}


// This piece of code is called from the application (lib2) and when called it will call into the vulnerability which is described in lib1.
void vulnerability ()
{
  // We are going to call the __div0 function when we return from this function (when we resume execution from here)
  void(__cdecl *p) (void);
  p = __div0;
  p ();
}

/******************************************************
 *
 * FP 18.03.2017 : 
 *	- This piece of code initializes all the TLS-Information
 *	It is being called when the library is being loaded into the process address space of the target process.
 *
 ******************************************************/

__attribute__((used)) void __attribute__((constructor)) my_init ()
{
  struct tls *tcb;
  // This alloctes 128 bytes of memory using malloc and store the top of the stack by updating the TLS entry tp.
  tcb = tls_alloc (128);
  // We store the pointer of the vulnerability function by the vulnerability function's address
  tcb->vul_f = &vulnerability;
  // This is the top of stack when we return from the vulnerability function
  tcb->top_stack_addr = (void*) ((char*) &stack - 500);  
}