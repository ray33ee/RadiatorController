# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]
### To Do
  - Add `Attributes` class to handle the schedule (Loads the schedule from EEPROM on startup, save the schedule to EEPROM when schedule changes, must fit 7 days of 15-minute chunks in 2048  bytes of EEPROM) and other data stored in the EEPROM suchg as
    - Schedule
    - Descale time
    - Open window duration
    - Offset temperature
    - Boost time
  - Add states:
    - Regulating: Valve is regulated to control the temperature 
    - Descale: Valve is fully opened the fully closed to descale. Must save previous state to return to
    - Boost: Valve is opened for a specified duration. Must save previous state to return to
    - Open Window: A rapid drop in temperature will cause the device to close the valves to save money for a specified duration. Must save previous state to return to
    - NoValve: This state is entered if no valve is detected (must put motor in safe position) (i.e. if max position is about 60)

### Unfinished Ideas
  - The state (not the fsm) should be responsible for storing and restoring previous states
    - Must recursively check the depth of stored previous states

## [0.1.7] - 2021-10-20
### Added
- 10k pullup resistors for I2C added to side board
- Back solder mask rectangle to ground heat sink on front board, to allow better heat dissipation (an even to attach a heat sink)
- Complete redesign of top pcb using measurements from Digimizer

### Changed
- Through holes from micro usb breakout no longer overlap Photon footprint
- Solder jumper changed from open-open to bridged, the bridge connects the Enabled pin to the `Enable_Controlled` track

## [0.1.6] - 2021-10-20
### Added
- On, Off, Startup and Shutdown states
- States can now be loaded via Cloud API functions
- Each state now has an `led_update` function called by `FSM::update` which can be used to create more interesting custom LED effects
- Dedicated LED base class for FSM
- `__DEBUG__` define to enable and disable extra code for debugging and diagnostics
- Main loop() calculates the duration between loop calls and passes it to `FSM::update`

### Changed
- `Shutdown` state renamed to `Safe` reflecting its true purpose, to move the motor to a safe position to allow removal/installation of the unit

### Removed
- Idle state removed as it doesn't do anything

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