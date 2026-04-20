cl386 -D_POSIX_ -c void.c /Fovoid.o
link32 -debug:full -debugtype:cv -align:0x1000 -subsystem:posix void.o /entry:__PosixProcessStartup libcpsx.lib psxdll.lib psxrtl.lib -out:void.exe 


