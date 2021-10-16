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

## [0.1.0] - 2021-10-16
### Added
- Initial commit