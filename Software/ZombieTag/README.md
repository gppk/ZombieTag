# ZombieTag Github Readme 
To do !!

[![Build Status]]
Jenkins thing to go here. 

This library enables you to xyz 

## v0.1 Now Available


## Troubleshooting
Lol good luck. 

## Frequently Asked Questions
Some common answers to common questions and problems can be found on our [F.A.Q. wiki page]


## History

## Installation
1. Click "Download ZIP"
2. Extract the downloaded zip file
3. Rename the extracted folder to 

4. Move this folder to your libraries directory (under windows: 


###### Using Git to install library ( Linux )
```
cd ~/Arduino/libraries
git clone 
```
###### To Update to the latest version of the library
`
`

## Unit Tests
The [Unit Tests](https://en.wikipedia.org/wiki/Unit_testing) under the test/ directory are for a Unix machine, **not** the micro-controller (ESP8266).
This allows execution under Travis and on the developer's machine.
We can do this from v2.0 of the library onwards, as everything now uses c98-style type definitions.
e.g. uint16_t etc.
Any Arduino/ESP8266 specific code needs to be disabled using something similar to the following lines:
```
#ifndef UNIT_TEST
<Arduino specific code ...>
#endif
```

This is not a perfect situation as we can not obviously emulate hardware specific features and differences. e.g. Interrupts, GPIOs, CPU instruction timing etc, etc.

If you want to run all the tests yourself, try the following:
```
$ cd test
$ make run
```

## Contributing
If you want to [contribute](.github/CONTRIBUTING.md#how-can-i-contribute) to this project, consider:
- [Report](.github/CONTRIBUTING.md#reporting-bugs) bugs and errors
- Ask for enhancements
- [Create issues](.github/CONTRIBUTING.md#reporting-bugs) and [pull requests](.github/CONTRIBUTING.md#pull-requests)
- Tell other people about this library

## Contributors
Available [here](.github/Contributors.md)
