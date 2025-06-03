# wsjcpp-yaml Changelog

All notable changes to wsjcpp-yaml project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [v0.1.8] - 2022-01-12 (2022 Jan 12)

- Fixed #35 Add valFloat / valDouble
- Start migrating tests to cmake tests
- Updated copyright
- Fix for c++ builder 12.2
- Make compatible code with compiler bcc32 C++ Builder


## [v0.1.7] - 2022-01-12 (2022 Jan 12)

- Make compatible code with `msvc2015x86`
- Added script `msvc2015x86_build_simple.bat`
- All logging will be use a `IWsjcppYamlLog`. Like a `yaml.setLogger(pLogger);`

## [v0.1.6] - 2022-01-08 (2022 Jan 8)

- Fixed #29 Problem with lost empty line
- Fixed #27 renamed 'intent' to 'indent'
