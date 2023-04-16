#include <calico.h>

#ifdef ENABLE_MAXMOD
#include <maxmod7.h>
#endif

int main(int argc, char* argv[])
{
	// Read settings from NVRAM
	envReadNvramSettings();

	// Set up extended keypad server (X/Y/hinge)
	keypadStartExtServer();

	// Configure and enable VBlank interrupt
	lcdSetIrqMask(DISPSTAT_IE_ALL, DISPSTAT_IE_VBLANK);
	irqEnable(IRQ_VBLANK);

	// Set up RTC
	rtcInit();
	rtcSyncTime();

	// Initialize power management
	pmInit();

#ifdef ENABLE_LOG
	// Set up ARM7->ARM9 debug output
	dietPrintSetFunc(debugOutput);
	dietPrint("[ARM7] Component start\n");
#endif

#ifdef ENABLE_BLKDEV
	// Set up block device peripherals
	blkInit();
#endif

	// Set up devices (touch, sound, mic, camera, wireless)
	touchInit();
	touchStartServer(80, MAIN_THREAD_PRIO);

#ifdef ENABLE_SOUND
	soundStartServer(MAIN_THREAD_PRIO-0x10);
#endif

#ifdef ENABLE_WLMGR
	wlmgrStartServer(MAIN_THREAD_PRIO-8);
#endif

#ifdef ENABLE_MAXMOD
	// Maxmod
	mmInstall(MAIN_THREAD_PRIO+1);
#endif

	// Main loop (mostly idle)
	while (pmMainLoop()) {
		threadWaitForVBlank();
	}

	return 0;
}
