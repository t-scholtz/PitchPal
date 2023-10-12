# PitchPal

An Arduino based project aimed at creating a reliable and user-friendly pitch/tuning tool.

## Project Overview
Musicians of all levels, from beginners to pros, desire pitch perfection, but traditional tuning methods are often inaccurate and time-consuming. In response, we're developing a user-friendly device that provides real-time pitch feedback, allowing users to select their desired pitch. This innovation enhances musical precision and empowers musicians, offering a valuable tool for the entire musical community. 

## Table of Contents
- [Project Overview](#project-overview)
- [To-Do List](#to-do-list)
- [Road Map](#road-map)
- [Technical Details](#technical-details)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Setup Instructions](#setup-instructions)

## To-Do List
- [ ] Learn Arduino basics.
- [ ] Set up meeting and project roadmap.
- [ ] Plan out project structure and create organisation scheme.
- [ ] Learn about input/output processing in gernal.
- [ ] Implement user interface for pitch selection.
- [ ] Create audio playback functionality.
- [ ] Develop pitch feedback system with LED grid.
- [ ] Write user manual.
- [ ] Test and debug the device.

## Road Map
* Organise Meeting
* Create Road Map
* Phase 2 (Due date: 11/11/2023 by 5 pm) 
* Phase 3 (Due date: 12/2/2023 by 5 pm) 

## Technical Details
- **Microcontroller:** Arduino [Specify the model or board you're using]
- **Pins Used:**
- **JANALOG**

| Pin | Function    | Type          | Usage                               
| --- | ----------- | ------------- | ------------------------------------------ 
| 1   | NC          | NC            | 
| 2   | IOREF       | IOREF         | 
| 3   | Reset       | Reset         | 
| 4   | +3V3 Power  | +3V3 Power    | 
| 5   | +5V Power   | +5V Power     | 
| 6   | GND Power   | Ground        | 
| 7   | GND Power   | Ground        |
| 8   | VIN Power   | Voltage Input | 
| 9   | A0          | Analog/GPIO   | 
| 10  | A1          | Analog/GPIO   | 
| 11  | A2          | Analog/GPIO   | 
| 12  | A3          | Analog/GPIO   | 
| 13  | A4/SDA      | Analog in/I2C | 
| 14  | A5/SCL      | Analog in/I2C | 

- **JDIGITAL**

| Pin | Function    | Type          | Usage                            
| --- | ----------- | ------------- | ------------------------------------------ 
| 1   | D0          | Digital/GPIO  | Digital pin 0/GPIO                         |
| 2   | D1          | Digital/GPIO  | Digital pin 1/GPIO                         |
| 3   | D2          | Digital/GPIO  | Digital pin 2/GPIO                         |
| 4   | D3          | Digital/GPIO  | Digital pin 3/GPIO                         |
| 5   | D4          | Digital/GPIO  | Digital pin 4/GPIO                         |
| 6   | D5          | Digital/GPIO  | Digital pin 5/GPIO                         |
| 7   | D6          | Digital/GPIO  | Digital pin 6/GPIO                         |
| 8   | D7          | Digital/GPIO  | Digital pin 7/GPIO                         |
| 9   | D8          | Digital/GPIO  | Digital pin 8/GPIO                         |
| 10  | D9          | Digital/GPIO  | Digital pin 9/GPIO                         |
| 11  | SS          | Digital       | SPI Chip Select                            |
| 12  | MOSI        | Digital       | SPI1 Main Out Secondary In                |
| 13  | MISO        | Digital       | SPI Main In Secondary Out                  |
| 14  | SCK         | Digital       | SPI serial clock output                    |
| 15  | GND Power   | Ground        | Ground                                     |
| 16  | AREF        | Digital       | Analog reference voltage                   |
| 17  | A4/SD4      | Digital       | Analog input 4/I2C Data line (duplicated)  |
| 18  | A5/SD5      | Digital       | Analog input 5/I2C Clock line (duplicated) |


## File Structure
- **Code:**
  - `ControlCenter.ino`: Main Arduino sketch.
  - `MyTunerLibrary.h` and `MyTunerLibrary.cpp`: Custom library for pitch handling.
  - `config.h`: Configuration file for pin definitions and constants.
- **Documentation:**
  - `ProjectProposal.md`: Original project proposal.
  - `UserManual.md`: User manual for the device.
- **3D Models (if applicable):**
  - `enclosure.stl`: 3D model of the device's enclosure.
- **Assets:**
  - `C_major_note.wav`: Audio file for pitch reference.
  - `display_logo.png`: Logo for the device display.

## Usage
1. TnT(Tim & Tom) build the thing
2. The thing doens't explode
3. Full marks


## Setup Instructions
Follow these steps to set up the Pitch Tuner Arduino Project:

1. **Hardware Assembly:**
   - Connect the components as specified in the [Technical Details](#technical-details) section.
   - Ensure that all connections are secure and correctly wired.

2. **Arduino IDE:**
   - Install the Arduino IDE if not already installed.

3. **Upload Code:**
   - Open `PitchTuner.ino` in the Arduino IDE.
   - Select the appropriate Arduino board and port in the IDE.
   - Upload the code to the Arduino board.

4. **Power On:**
   - Power on the device and follow the [Usage](#usage) instructions to start using the Pitch Tuner.

## Miscellaneous
Random stuff goes here


