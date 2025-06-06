#!/usr/bin/env python3

""" example generated by issue 33 """

import yaml

a_dict = {
    '2021-10-08': [{
        'code': '300209',
        'focusstr': '',
    }, {
        'code': '300047',
        'focusstr': '',
    }, {
        'code': '300970',
        'focusstr': '',
    }, {
        'code': '300288',
        'focusstr': '',
    }],
    '2021-10-11': [{
        'code': '300162',
        'focusstr': '',
    }, {
        'code': '300209',
        'focusstr': '',
    }, {
        'code': '300972',
        'focusstr': '',
    }, {
        'code': '300159',
        'focusstr': '',
    }]
}

with open("example.yaml", 'w') as f:
    yaml.dump(a_dict, f,  default_flow_style=False, sort_keys=False)


with open("example.yaml") as stream:
    try:
        print(yaml.safe_load(stream))
    except yaml.YAMLError as exc:
        print(exc)