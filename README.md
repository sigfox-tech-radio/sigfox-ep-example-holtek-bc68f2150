# Sigfox End-Point library implementation example on Holtek BC68F2150

## Description

This repository shows an example of Sigfox End-Point Library integraton on a HOLTEK low cost transmiter with flash MCU. It uses the code optimization features of the EP-LIB in order to minimize the memory footprint inside the MCU.
To have more informations about this design please refer to [wiki documentation](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/wiki).

## Architecture

This repository contains several source code and project files needed to compile the Low Cost Device (LCD) project. Only the source code files of the EP_LIB are not be included inside this repository: the EP_LIB project is a submodule and must be updated before to upload sources files in `middleware/sigfox/sigfox-ep-lib` folder.

```
.                                # Root directory
├── middleware                   # Middleware
│   ├── sigfox                   # Sigfox middleware subdirectory
│   │    ├── sigfox-ep-lib       # EP_LIB submodule
│   │    │    └── ...
│   │    ├── manuf               # EP_LIB manufacturer API specific to this SoC
│   │    │    └── mcu_api.c
│   │    │    └── rf_api.c
│   │    │    └── mcu_rf_api_rodata.c
│   │    │    └── mcu_rf_api_rodata.h
│   │    │    └── TI_aes_128_encr_only.c
│   │    │    └── TI_aes_128_encr_only.h
├── driver                       # Drivers
│   │    ├── src                 # Driver header subdirectory
│   │    │    └── iap.h
│   │    ├── src                 # Driver source subdirectory
│   │    │    └── iap.c
├── output                       # Output generation folder, containing all generated files by IDE
│   ├── *.OBJ
│   ├── *.ASM
│   ├── *.LST
│   └── *...
├── main.c                       # Application source file
├── lcd.opt                      # Project option file
├── lcd.pjt                      # Project file
├── lcd.pjtx                     # Project file
└── README.md
```

## Hardware

The following figure shows the hardware architecture of the Holtek BC68F2150 board.

<p align="center">
<img src="https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/wiki/images/holtek_bc68f2150_architecture.drawio.png" width="600"/>
</p>

All gerbers and schematics are available in the wiki of this repository.

## Getting Started

### Cloning the repository and submodule

```bash
$ git clone https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150.git
$ cd sigfox-ep-example-holtek-bc68f2150
$ git submodule init
$ git submodule update
```

### How to build project

- Download the HT-IDE3000 software from Holtek web site.
- Click on pjtx project file to run IDE. Now you are ready to compile and update the source code for your application. *For more information on the IDE, compiler, etc... please refer to pdf files available in DOC IDE folder.*
- To configure the EP_LIB flags: right-click on the project > Project Settings > Project Option > Define Symbol.

### How to program and debug

- To flash or debug the device you need to buy a *e-link* programmer from HOLTEK
- Connect the device to the programmer and click on the Build/Rebuild button, the flash process will be launched automatically.
