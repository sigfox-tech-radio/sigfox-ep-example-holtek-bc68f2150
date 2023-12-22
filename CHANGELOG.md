# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v1.3](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/releases/tag/v1.3) - 22 Dec 2023

### Add

* Continous Wave implementation.

### Changed

* Change submodule address (ssh to https).
* Update **sigfox-ep-lib** submodule version from V3.3 to V3.4.
* Remove some comments.

## [v1.2](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/releases/tag/v1.2) - 20 Oct 2023

### Changed

* Change **tx_power_dbm_eirp** to 14 dBm (maximum power).
* Change **number_of_frames** to 3 frame per message.
* Remove docs folder.

### Fixed

## [v1.1](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/releases/tag/v1.1) - 16 Oct 2023

### Changed

* Improve **spectrum template** with new amplitude profile tables.
* Add **ERROR_CODES** return.

### Fixed

* Fix exection issues with new IDE version **HT-IDE3000 V8.1.5** .
* Fix All uplink library feature can be embedded on the Soc but it is strongly recommended to use the **optimization flags** according to targetted the application in order to limit the memory footprint.

### Known limitations

* **600 bps** not compliant with 1.7 EP-SPECS.

## [v1.0](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/releases/tag/v1.0) - 02 Jun 2023

### General

* First version of the Holtek BC68F2150 Sigfox example code.

### Known limitations

* Depending on the Holtek IDE version, some execution issues can appear on some specific conditions (full memory usage and/or call depth). Please consider using **HT-IDE3000 V8.1.4** or above.
* Due to the limited memory size (especially RAM) the full featured library cannot be embedded on the SoC. Use the **optimization flags** according to targetted the application.
