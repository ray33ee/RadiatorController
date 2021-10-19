# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]
### To Do

### Unfinished Ideas
  - Outline of the classes used in controller
    - Valve: Responsible for configuring the valve and moving the valve to the desired position
    - Attributes: Handles the schedule (Loads the schedule from EEPROM on startup, save the schedule to EEPROM when schedule changes, must fit 7 days of 15-minute chunks in 2048  bytes of EEPROM) and other data stored in the EEPROM suchg as
      - Schedule
      - Descale time
      - Open window duration
      - Offset temperature
      - Boost time
    - Temperature: Responsible for taking the temperature
    - Cloud: Exposes functionality to the Photon cloud api for controlling the FSM
    - FSM: Finite state machine responsible for managing all aspects of the controller. Also controlls the RGB LED and listens to the switch and encoder
      - FSM states:
        - Regulating: Valve is regulated to control the temperature 
        - Off: Valve is closed
        - On: Valve is open
        - Descale: Valve is fully opened the fully closed to descale
        - Boost: Valve is opened for a specified duration
        - Startup: Initiating the valve startup sequence
        - Shutdown: Shutdown sequence 
      - Some states have various modes under which they operate. Modes are listed below:
        - Open Window: When in Regulating or On state, a rapid drop in temperature will cause the device to close the valves to save money for a specified duration
        - Dark: When in any state, turns off the RGB LED

## [0.1.5] - 2021-10-19
### Added
- Extra pin to connector J1 on side board for push button pin
- Pins for RGB LEDs on J1 side board for push button pin
- Schematic for top PCB
- Basic FSM skeleton
- Startup state for FSM
- TemperatureSensor  base class

### Changed
- Moved high current pins to outside of connector on J1 side board
- Move Side J1 header down

## [0.1.4] - 2021-10-19
### Added
- Side board
- Sent off for front and side boards v1.0

## [0.1.3] - 2021-10-18
### Added
- Extra NPTH for front cover on front board
- Added custom order number location marker (JLCJLCJLCJLC)
- Added board description
- Confirmed NPTH and component locations

### Changed
- Modified clearances to comply with JLCPCB
- Changed COIL_* tracks from 0.6mm to 0.15mm

## [0.1.2] - 2021-10-17
### Added
- First draft of front board completed including
  - Wide tracks 
  - JLCPCB track witdth, vias and clearances
  - Heat sink on ground planes for L293D

## [0.1.1] - 2021-10-16
### Added
- Added schematic and PCB layout for front PCB

## [0.1.0] - 2021-10-16
### Added
- Initial commit