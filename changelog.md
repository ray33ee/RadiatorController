# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]
### To Do
  - Add states:
    - Open Window: A rapid drop in temperature will cause the device to close the valves to save money for a specified duration. Must save previous state to return to
  - Use `onChange` handler to mimic RGB led on external LED

### Unfinished Ideas
- 

## [0.1.16] - 2021-11-02
### Added
- In `Panic` state, we noq flash the LED red `Panic::_code` number of times to indicate error code
- A boost will revert if its previous stats is also a boost (this prevents nested boosts)
- Can now change the default temperature on its own without having to change the other values
- DFU and safe mode now available via api state change function
- Cancel command added to end boost states early
- We now automatically get the DST status for our location from worldtimeapi.org
- We also automatically sync the time with the cloud every day

### Changed
- Motor connector board now moved to seperate project
- 1ohm resistor and zener diodes changed to surface mount
- Elongated orientation holes on danfoss footprint
- Checked to make sure our own LED colours and the system colours do not coincide. System led takes priority over application when the priority is the same
- We stop disable interrupts during timing-critical motor control functions
- Dark mode is only entered if the priority of the led is less than or equal to normal
- Custom rgb colours are stored in constants within the state classes

### Removed
- Removed `Descale` from api state change
- DST flag removed from flags struct (we now get DST status from worldtimeapi.org)

## [0.1.15] - 2021-10-31
### Added
- We now have start temperature different to stop temperature, to prevent rapid on/off cycles for the motor if the temperature is at the schedule temperature
- JLC mark to specify part number
- Added PCB info on back silks
- Mount holes enlarged to allow for extra wiggle room
- 2mm pitch mini PCB for mounting on stepper motor added to front board
- Front mask added to front board

### Changed
- Elongated D+ and D- (pins 31 and 30) on photon footprint
- Pads on the enlarged holes have also been enlarged
- Moved 4-pin temperature sensor header to a more open space
- Moved 10 pin header on top board to give more room for right angle headers
- R1 on front board changed to 7mm length
- Zener diode footprints changed to through hole

## [0.1.14] - 2021-10-30
### Added
- Temporary way to enable DST by creating a DST flag in the attributes class. This will eventually be replaced by automatically getting the time from worldtimeapi
- Error handling to `api_modify_attributes` function
- Variable showing the remaining boost time

### Changed
- Moved RGB LED resistors further from LED 
- Through holes for front and side boards on top board have been widened from 1mm to 1.3mm
- We no longer use pins D3, D5, D6 or D7 as these are briefly used as JTAG at startup and do not start at high impedence. According to the Photon specs:
`Also beware when using pins D3, D5, D6, and D7 as OUTPUT controlling external devices on Gen 2 devices. After reset, these pins will be briefly taken over for JTAG/SWD, before being restored to the default high-impedance INPUT state during boot.`
- Time variable now returns time as a string not as UNIX time

### Fixed
- Boost duration converted from minutes to milliseconds

## [0.1.13] - 2021-10-29
### Added
- Dark mode added, but can be overwritten by states that enter dark mode after it has been set AND do not check schedule_flags
- Soft reset via `set_state` function with custom reason data

### Changed
- API functions that took no arguments changed to variables
- Temperature sensor in FSM moved to private, and exposed via public functions. This means that the offset temperature can be added by the FSM

## [0.1.12] - 2021-10-27
### Added
- `AM2302` class (deriving `TemperatureSensor` class) which contains an algorithm to read the AM2302 temperature sensor

### Changed
- Now only `Safe`, `Boost`,  and `Descale` can be initiated by api
- We now use the `LEDStatus` class to control the led

### Fixed
- `DHT22` temperature taking issues fixed

### Removed
- `On` state is no longer needed now we have the `Regulate` state
- Our own custom led class

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