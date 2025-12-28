# wsjcpp-yaml Changelog

All notable changes to wsjcpp-yaml project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [v0.1.10] - 2025-12-30 (2025 Dec 30)

- Downgrade min c++ standart to C++11
- Fixed #38: TODO escaping names
- Fixed #24: Auto detect quotes on setValue setName
- Fixed #30: fixing pushing after empty lines

## [v0.1.9] - 2025-12-18 (2025 Dec 18)

- Migrated unit-tests.wsjcpp to ctest
- Fixed config for .github actions

## [v0.1.8] - 2025-06-03 (2025 Jun 3)

- Fixed #35 Add valFloat / valDouble
- Start migrating tests to cmake tests
- Updated copyright
- Fix for c++ builder 12.2
- Make compatible code with compiler bcc32 C++ Builder
- Redesign unit-test from unit-tests.wsjcpp/src/unit_test_yaml_parser_comments.cpp to src/tests/test_parser_comments.cpp
- Removed .travis.yml
- Prepare tests for #33

## [v0.1.7] - 2022-01-12 (2022 Jan 12)

- Make compatible code with `msvc2015x86`
- Added script `msvc2015x86_build_simple.bat`
- All logging will be use a `IWsjcppYamlLog`. Like a `yaml.setLogger(pLogger);`

## [v0.1.6] - 2022-01-08 (2022 Jan 8)

- Fixed #29 Problem with lost empty line
- Fixed #27 renamed 'intent' to 'indent'
