# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]
### To Do
  - Elongate the D+ and D- SMD pads on the Photon footpring to allow for easier soldering  
  - Check all the hole sizes in through holes
  - Move the three RGB resistors away from the center to allow for more room for the light reflector
  - Add states:
    - Open Window: A rapid drop in temperature will cause the device to close the valves to save money for a specified duration. Must save previous state to return to
  - When we enter the boost state, check the previous state. If the previous state is also a boost, revert to prevent nested boosts.
  - When `Regulation` state is implemented and a schedule is implemented, remove all states from api except safe, descale, boost,
  - Use `onChange` handler to mimic RGB led on external LED
  - Get the time from a website that takes into account your time zone and any DST instead of particle cloud. Do this every hour via `TCPClient`
    - Do this using http://worldtimeapi.org/api/ip/IPV4.txt replacing IPV4 with the IP address of the photon (get the public ip via photon api) 
  - In `Panic` state, flash the LED red `Panic::_code` number of times to indicate error code

### Unfinished Ideas
  - Maybe create a `DFU` or `SafeMode` state?

## [0.1.11] - 2021-10-26
### Added
- Very simple api function added to modify blocks of the schedule and to copy one day to another
- Panic state (with stored error code and message, and cloud api now gets the panic code if there is one)
- Invalid initial valve max_position (too large or too small) will initiate a panic
- Skeleton state `Regulate` added
- Implemented and tested `Descale` state 
- Variables added to include various diagnostic information
- State changes are published to particle api
- Added short and long boost to api

### Fixed
- Dark mode issue fixed (Schedule was taking priority over API call, so now we logical or both to get the final dark mode decision)

## [0.1.10] - 2021-10-25
### Added
- `schedule_state` and `schedule_flags` to allow states to customise exactly what part of the schedule they look at during their `update` cycle
- Added functionality to `FSM` that states can modify to prevent api calls

### Changed
- States are now responsible for calling the functions that check the schedule, not the FSM itself 

## [0.1.9] - 2021-10-23
### Added
- `Settings` class to encapsulate schedule and attributes
- `Entry` class to represent a single entry in the schedule
- `PackedTemperature` to store temperature in a compact 8-bit form

## [0.1.8] - 2021-10-21
### Added
- `FSM::revert` function added to help restore previous states
- All three mounting holes in top pcb are the same size 

### Changed
- Previous state is now stored in the current state, not the FSM

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