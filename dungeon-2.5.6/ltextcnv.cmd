link32 -debug:full -debugtype:cv -align:0x1000 -subsystem:posix textcnv.o /entry:__PosixProcessStartup libcpsx.lib psxdll.lib psxrtl.lib libf2c.a -out:textcnv.exe 


