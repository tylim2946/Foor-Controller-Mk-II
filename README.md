# Foor Controller MK II

## Introduction

This device allows you to type keyboard or mouse inputs with your foot. This time, it does not require an external software (i.e. FC Options) and uses HID protocol that can be run on many different platforms.

## Preparation

1. HM-10 Bluetooth Module (Uses TI CC2541)
2. Arduino Pro Mini 3.3V
3. MPU9250 Breakout Board
4. TP4056 Battery Charger with Protection
5. 3.7V Li-Po Battery
6. USB to TTL Serial Adaptor

## Getting Started

### 1. Flashing CC2541 HID Firmware

1. Download [CCLoader.exe](https://github.com/RedBearLab/CCLoader/tree/master/Windows) and [CCLoader.ino](https://github.com/RedBearLab/CCLoader/blob/master/Arduino/CCLoader/CCLoader.ino) and upload the sketch to Arduino
2. Wire by referring to the following schematic:
> ![](https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/schematics/hm10_flash_setup.jpg)
3. Download the [firmware](https://github.com/joric/cc2540-keyboard/blob/master/BLE-CC254x-1.4.0/Projects/ble/HIDEmuKbd/CC2540DB/CC2540DK-MINI%20Keyfob%20Slave/Exe/HidEmuKbd.hex) and convert .hex to .bin
4. Put CC2541 into command mode by sending "@@@" then Carriage Return at 57600 baud
5. Run CCLoader.exe, then enter the following command line: "CCLoader.exe [Port] [FileName] 0"
> i.e. COM1 and HIDEmuKbd.bin: "CCLoader.exe 1 HIDEmuKbd.bin 0"

### 2. Download Arduino program

1. Download and upload the [sketch](https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/Foot-Controller/Foot-Controller.ino) to Arduino

### 3. Soldering

1. Solder by referring to the following schematic:
> ![](https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/schematics/fc2_setup.jpg)

## Images

<table>
	<tr>
		<td><img src="https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/images/burning-firmware%20(1).jpg" width="727" height="409"></td>
		<td><img src="https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/images/burning-firmware%20(2).jpg" width="270" height="409"></td>
	</tr>
</table>
<table>
	<tr>
		<td><img src="https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/images/building-hardware%20(1).jpg" width="611" height="329"></td>
		<td><img src="https://github.com/tylim2946/Foor-Controller-Mk-II/blob/main/images/building-hardware%20(2).jpg" width="306" height="329"></td>
	</tr>
</table>

## Tools Used

- [CCLoader](https://github.com/RedBearLab/CCLoader)

## Firmware Used

- [HidEmuKbd](https://github.com/joric/cc2540-keyboard)

## Library Used

- [MPU9250](https://github.com/hideakitai/MPU9250)

## See Also
- [Turning HM-10, HM-11 into Bluetooth HID modules](https://imgur.com/a/KWmz6)
- [cc25xx-hidKbdM](https://github.com/rampadc/cc254x-hidKbdM)
