# Installing Adobe CS3 on case-sensitive drives (Mac OS X)
I wasted approximately 6 hours on this, and probably even more thinking it through.
This was not worth it. It most certainly would have taken lesser time to reinstall Mac OS X entirely.
This tutorial is broken at best - if nothing else, please adopt your own PBHGetVolParmsSync-interposing code.

Ensure you have Xcode installed, and have your copy of a CS3 application mounted.

This has only been tested on Mac OS X 10.5 using Xcode 3.1.4.

1. Obtain a copy of CS3 somewhere.
2. Clone this repository.
3. Run `sudo make run`. This will launch a bootstrap installer, which does nothing more than copy itself elsewhere.
  - If you are on i386/x86_64, you must modify the `-arch` flag within the Makefile to your architecture.
4. A new application will have opened, once more complaining about how case sensitive volumes will cause the destruction of humankind.
At this point, open up a new tab or window within your terminal.
5. Run `ps -ewwo pid,etime,command` and look for the copy of Setup.app running with an `--installerParent` flag. Note the exact flags passed.
6. The original Setup application should have exited by this point. You may have to press return to clear residual on the prompt.
7. Ensure your original terminal is still in the same directory as this repository. Run the following command, correcting `--installerParent` as needed:

```
DYLD_INSERT_LIBRARIES=$(shell pwd)/liboverride_volume_sensitivity_check.dylib /Library/Application\ Support/Adobe/Installers/R1/Setup.app/Contents/MacOS/Setup --ExitWorkflow= --BootstrappedLaunched=1 --record=0 --installerParent=/Library/Application\ Support/Adobe/Installers/1d297c17c06feaa0d5dc42ff9cf5d62 --resourcesPath=/Library/Application\ Support/Adobe/Installers/R1/resources
```
(It is unclear as to what `1d297c17c06feaa0d5dc42ff9cf5d62` means, but it appears on Google with one result as of writing. This may vary by machine, product or installer version.)

8. You should be safe to install and enjoy within the new installer.

The idea for this repository stems from the original [adobe_case_sensitive_volumes](https://github.com/tzvetkoff/adobe_case_sensitive_volumes) repository.
