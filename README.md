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
**Microcontroller:** Arduino Uno
**Pins Used:**
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
| 9   | A0          | Analog/GPIO   | Microphone
| 10  | A1          | Analog/GPIO   | 
| 11  | A2          | Analog/GPIO   | 
| 12  | A3          | Analog/GPIO   | 
| 13  | A4/SDA      | Analog in/I2C | LCD Screen
| 14  | A5/SCL      | Analog in/I2C | LCD Screen

- **JDIGITAL**

| Pin | Function    | Type          | Usage                            
| --- | ----------- | ------------- | ------------------------------------------ 
| 1   | D0          | Digital/GPIO  |   |
| 2   | D1          | Digital/GPIO  |   |
| 3   | D2          | Digital/GPIO  |   |
| 4   | D3          | Digital/GPIO  |   Used for Speaker
| 5   | D4          | Digital/GPIO  |   mux - s0
| 6   | D5          | Digital/GPIO  |   mux - s1
| 7   | D6          | Digital/GPIO  |   mux - s2
| 8   | D7          | Digital/GPIO  |   mux - s3
| 9   | D8          | Digital/GPIO  |   mux - E
| 10  | D9          | Digital/GPIO  |   mux -sig
| 11  | SS          | Digital       |   |  
| 12  | MOSI        | Digital       |   |
| 13  | MISO        | Digital       |   |
| 14  | SCK         | Digital       |   |
| 15  | GND Power   | Ground        |   |
| 16  | AREF        | Digital       |   |
| 17  | A4/SD4      | Digital       |   |
| 18  | A5/SD5      | Digital       |   |


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
   - stuff
   - plug in

2. **Usage**
   - turn on


## Miscellaneous
Random stuff goes here


