# Command-line client
CMDLINE = thulog_console.exe

all: $(CMDLINE)

# One-liner to compile the command-line client from usbtest.c
$(CMDLINE): thulog_console.c
	gcc -I ./libusb/include -L ./libusb/lib/gcc -O -Wall thulog_console.c -o thulog_console.exe -lusb
	
clean:
	$(RM) *.o *.exe
