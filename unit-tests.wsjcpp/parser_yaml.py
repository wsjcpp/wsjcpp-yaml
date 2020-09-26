#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import yaml


a_yaml_file = open("./data-tests/read-write-file/docker-compose.yml")

parsed_yaml_file = yaml.load(a_yaml_file, Loader=yaml.FullLoader)

print(parsed_yaml_file)

a_yaml_file2 = open("./data-tests/parser-simple-array/file.yml")

parsed_yaml_file2 = yaml.load(a_yaml_file2, Loader=yaml.FullLoader)

print(parsed_yaml_file2)
