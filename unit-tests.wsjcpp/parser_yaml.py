import yaml


a_yaml_file = open("./data-tests/read-write-file/docker-compose.yml")

parsed_yaml_file = yaml.load(a_yaml_file, Loader=yaml.FullLoader)

print(parsed_yaml_file)