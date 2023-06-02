# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v1.0](https://github.com/sigfox-tech-radio/sigfox-ep-example-holtek-bc68f2150/releases/tag/v1.0) - 02 Jun 2023

### General

* First version of the Holtek BC68F2150 Sigfox example code.

### Known limitations

* Depending on the Holtek IDE version, some execution issues can appear on some specific conditions (full memory usage and/or call depth). Please consider using **HT-IDE3000 V8.1.4** or above.
* Due to the limited memory size (especially RAM) the full featured library cannot be embedded on the SoC. Use the **optimization flags** according to targetted the application.
