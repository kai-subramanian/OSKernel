section	.text
   global _start     ;must be declared for linker (ld)
_start:             ;tell linker entry point

   ;writing the name 'Kailash'
   mov	edx,8       ;message length
   mov	ecx, name   ;message to write
   mov	ebx,1       ;file descriptor (stdout)
   mov	eax,4       ;system call number (sys_write)
   int	0x80        ;call kernel

   mov	[name],  dword 'Kai'    ; Changed the name to Kai'ash'

   ;writing the name 'Kaiash'
   mov	edx,8       ;message length
   mov	ecx,name    ;message to write
   mov	ebx,1       ;file descriptor (stdout)
   mov	eax,4       ;system call number (sys_write)
   int	0x80        ;call kernel

   mov	eax,1       ;system call number (sys_exit)
   int	0x80        ;call kernel

section	.data
name db 'Kailash '
