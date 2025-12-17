/*
MIT License

Copyright (c) 2019-2025 wsjcpp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Official Source Code: https://github.com/wsjcpp/wsjcpp-yaml
*/

#include <wsjcpp_yaml.h>

int main() {
    WsjcppYaml yaml;
    std::string sFilepath = "../../../../src/tests/data-tests/read-file/example-voiting-app/docker-compose.yml";
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    if (yaml.getRoot()->hasElement("version") != true) {
        std::cerr << "has version" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("version")->isValue() != true) {
        std::cerr << "has version is value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("version")->getValue() != "3") {
        std::cerr << "version-value" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->hasElement("services") != true) {
        std::cerr << "has services" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("services")->isMap() != true) {
        std::cerr << "has services is map" << std::endl;
        return -1;
    }

    WsjcppYamlNode *pServices = yaml.getRoot()->getElement("services");

    // services.vote
    {
        if (pServices->hasElement("vote") != true) {
            std::cerr << "has services.vote" << std::endl;
            return -1;
        }
        if (pServices->getElement("vote")->isMap() != true) {
            std::cerr << "services.vote is map" << std::endl;
            return -1;
        }
        if (pServices->getElement("vote")->getKeys().size() != 5) {
            std::cerr << "services.vote keys size 5" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pVote = pServices->getElement("vote");

        if (pVote->hasElement("build") != true) {
            std::cerr << "has services.vote.build" << std::endl;
            return -1;
        }
        if (pVote->getElement("build")->getValue() != "./vote") {
            std::cerr << "services.vote.build val" << std::endl;
            return -1;
        }

        if (pVote->hasElement("command") != true) {
            std::cerr << "has services.vote.command" << std::endl;
            return -1;
        }
        if (pVote->getElement("command")->getValue() != "python app.py") {
            std::cerr << "services.vote.command val" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pVolumes = pVote->getElement("volumes");

        if (pVolumes->isArray() != true) {
            std::cerr << "services.vote.volumes is array" << std::endl;
            return -1;
        }
        if (pVolumes->getLength() != 1) {
            std::cerr << "services.vote.volumes size 1" << std::endl;
            return -1;
        }
        if (pVolumes->getElement(0)->getValue() != "./vote:/app") {
            std::cerr << "services.vote.volumes val 0" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pVotePorts = pVote->getElement("ports");
        if (pVotePorts->isArray() != true) {
            std::cerr << "services.vote.ports is array" << std::endl;
            return -1;
        }
        if (pVotePorts->getLength() != 1) {
            std::cerr << "services.vote.ports size 1" << std::endl;
            return -1;
        }
        if (pVotePorts->getElement(0)->getValue() != "5000:80") {
            std::cerr << "services.vote.ports val 0" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pVoteNetworks = pVote->getElement("networks");
        if (pVoteNetworks->getLength() != 2) {
            std::cerr << "services.vote.networks size 2" << std::endl;
            return -1;
        }
        if (pVoteNetworks->getElement(0)->getValue() != "front-tier") {
            std::cerr << "services.vote.networks val 0" << std::endl;
            return -1;
        }
        if (pVoteNetworks->getElement(1)->getValue() != "back-tier") {
            std::cerr << "services.vote.networks val 1" << std::endl;
            return -1;
        }
    }

    // services.result
    {
        if (pServices->hasElement("result") != true) {
            std::cerr << "has services.result" << std::endl;
            return -1;
        }
        if (pServices->getElement("result")->isMap() != true) {
            std::cerr << "services.result is map" << std::endl;
            return -1;
        }
        if (pServices->getElement("result")->getKeys().size() != 5) {
            std::cerr << "services.result is map" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pResult = pServices->getElement("result");

        if (pResult->hasElement("build") != true) {
            std::cerr << "has services.result.build" << std::endl;
            return -1;
        }
        if (pResult->getElement("build")->getValue() != "./result") {
            std::cerr << "services.result.build val" << std::endl;
            return -1;
        }

        if (pResult->hasElement("command") != true) {
            std::cerr << "has services.result.command" << std::endl;
            return -1;
        }
        if (pResult->getElement("command")->getValue() != "nodemon server.js") {
            std::cerr << "services.result.command val" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pResultVolumes = pResult->getElement("volumes");
        if (pResultVolumes->isArray() != true) {
            std::cerr << "services.result.volumes is array" << std::endl;
            return -1;
        }
        if (pResultVolumes->getLength() != 1) {
            std::cerr << "services.result.volumes size 1" << std::endl;
            return -1;
        }
        if (pResultVolumes->getElement(0)->getValue() != "./result:/app") {
            std::cerr << "services.result.volumes val 0" << std::endl; return -1;
        }

        WsjcppYamlNode *pResultPorts = pResult->getElement("ports");
        if (pResultPorts->isArray() != true) {
            std::cerr << "services.result.ports is array" << std::endl;
            return -1;
        }
        if (pResultPorts->getLength() != 2) {
            std::cerr << "services.result.ports size 2" << std::endl;
            return -1;
        }
        if (pResultPorts->getElement(0)->getValue() != "5001:80") {
            std::cerr << "services.result.ports val 0" << std::endl;
            return -1;
        }
        if (pResultPorts->getElement(1)->getValue() != "5858:5858") {
            std::cerr << "services.result.ports val 1" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pResultNetworks = pResult->getElement("networks");
        if (pResultNetworks->getLength() != 2) {
            std::cerr << "services.result.networks size 2" << std::endl;
            return -1;
        }
        if (pResultNetworks->getElement(0)->getValue() != "front-tier") {
            std::cerr << "services.result.networks val 0" << std::endl;
            return -1;
        }
        if (pResultNetworks->getElement(1)->getValue() != "back-tier") {
            std::cerr << "services.result.networks val 1" << std::endl;
            return -1;
        }
    }

    // std::cerr << << std::endl; return -1;

    // services.worker
    {
        if (pServices->hasElement("worker") != true) {
            std::cerr << "has services.worker" << std::endl;
            return -1;
        }
        if (pServices->getElement("worker")->isMap() != true) {
            std::cerr << "has services.worker is map" << std::endl;
            return -1;
        }
        if (pServices->getElement("worker")->getKeys().size() != 3) {
            std::cerr << "services.worker keys size 3" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pWorker = pServices->getElement("worker");

        if (pWorker->hasElement("build") != true) {
            std::cerr << "has services.worker.build" << std::endl;
            return -1;
        }
        if (pWorker->hasElement("depends_on") != true) {
            std::cerr << "has services.worker.depends_on" << std::endl;
            return -1;
        }
        if (pWorker->hasElement("networks") != true) {
            std::cerr << "has services.worker.networks" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pWorkerBuild = pWorker->getElement("build");
        if (pWorkerBuild->isMap() != true) {
            std::cerr << "services.worker.build is map" << std::endl;
            return -1;
        }
        if (pWorkerBuild->hasElement("context") != true) {
            std::cerr << "has services.worker.build.context" << std::endl;
            return -1;
        }
        if (pWorkerBuild->getElement("context")->getValue() != "./worker") {
            std::cerr << "services.worker.build.context val" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pWorkerDependsOn = pWorker->getElement("depends_on");
        if (pWorkerDependsOn->isArray() != true) {
            std::cerr << "has services.worker.depends_on" << std::endl;
            return -1;
        }
        if (pWorkerDependsOn->getLength() != 2) {
            std::cerr << "services.worker.depends_on size 2" << std::endl;
            return -1;
        }
        if (pWorkerDependsOn->getElement(0)->getValue() != "redis") {
            std::cerr << "services.worker.depends_on val 0" << std::endl;
            return -1;
        }
        if (pWorkerDependsOn->getElement(1)->getValue() != "db") {
            std::cerr << "services.worker.depends_on val 1" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pWorkerNetworks = pWorker->getElement("networks");
        if (pWorkerNetworks->getLength() != 1) {
            std::cerr << "services.worker.networks size 1" << std::endl;
            return -1;
        }
        if (pWorkerNetworks->getElement(0)->getValue() != "back-tier") {
            std::cerr << "services.worker.networks val 0" << std::endl;
            return -1;
        }
    }

    // services.redis
    {
        if (pServices->hasElement("redis") != true) {
            std::cerr << "has services.redis" << std::endl;
            return -1;
        }
        if (pServices->getElement("redis")->isMap() != true) {
            std::cerr << "services.redis is map" << std::endl;
            return -1;
        }
        if (pServices->getElement("redis")->getKeys().size() != 4) {
            std::cerr << "services.redis keys size 4" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pRedis = pServices->getElement("redis");
        if (pRedis->hasElement("image") != true) {
            std::cerr << "has services.redis.image" << std::endl;
            return -1;
        }
        if (pRedis->hasElement("container_name") != true) {
            std::cerr << "has services.redis.container_name" << std::endl;
            return -1;
        }
        if (pRedis->hasElement("ports") != true) {
            std::cerr << "has services.redis.ports" << std::endl;
            return -1;
        }
        if (pRedis->hasElement("networks") != true) {
            std::cerr << "has services.redis.networks" << std::endl;
            return -1;
        }

        if (pRedis->getElement("image")->getValue() != "redis:alpine") {
            std::cerr << "services.redis.image value" << std::endl;
            return -1;
        }
        if (pRedis->getElement("container_name")->getValue() != "redis") {
            std::cerr << "services.redis.container_name" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pRedisPorts = pRedis->getElement("ports");
        // TODO bug #17
        if (pRedisPorts->isValue() != true) {
            std::cerr << "services.redis.ports is value" << std::endl;
            return -1;
        }
        if (pRedisPorts->getValue() != "[\"6379\"]") {
            std::cerr << "services.redis.ports value" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pRedisNetworks = pRedis->getElement("networks");
        if (pRedisNetworks->getLength() != 1) {
            std::cerr << "services.redis.networks size 1" << std::endl;
            return -1;
        }
        if (pRedisNetworks->getElement(0)->getValue() != "back-tier") {
            std::cerr << "services.redis.networks val 0" << std::endl;
            return -1;
        }
    }

    // services.db
    {
        if (pServices->hasElement("db") != true) {
            std::cerr << "has services.db" << std::endl;
            return -1;
        }
        if (pServices->getElement("db")->isMap() != true) {
            std::cerr << "has services.db is map" << std::endl;
            return -1;
        }
        if (pServices->getElement("db")->getKeys().size() != 5) {
            std::cerr << "services.db keys size 5" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pServicesDb = pServices->getElement("db");

        if (pServicesDb->hasElement("image") != true) {
            std::cerr << "has services.db.image" << std::endl;
            return -1;
        }
        if (pServicesDb->getElement("image")->getValue() != "postgres:9.4") {
            std::cerr << "services.db.image value" << std::endl;
            return -1;
        }
        if (pServicesDb->getElement("container_name")->getValue() != "db") {
            std::cerr << "services.db.container_name" << std::endl;
            return -1;
        }

        if (pServicesDb->hasElement("environment") != true) {
            std::cerr << "has services.db.environment" << std::endl;
            return -1;
        }
        if (pServicesDb->getElement("environment")->isMap() != true) {
            std::cerr << "services.db.environment is map" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pDbEnvironment = pServicesDb->getElement("environment");

        if (pDbEnvironment->hasElement("POSTGRES_USER") != true) {
            std::cerr << "has services.db.environment.POSTGRES_USER" << std::endl;
            return -1;
        }
        if (pDbEnvironment->getElement("POSTGRES_USER")->getValue() != "postgres") {
            std::cerr << "services.db.environment.POSTGRES_USER" << std::endl;
            return -1;
        }

        if (pDbEnvironment->hasElement("POSTGRES_PASSWORD") != true) {
            std::cerr << "has services.db.environment.POSTGRES_PASSWORD" << std::endl;
            return -1;
        }
        if (pDbEnvironment->getElement("POSTGRES_PASSWORD")->getValue() != "postgres") {
            std::cerr << "services.db.environment.POSTGRES_PASSWORD" << std::endl;
            return -1;
        }

        if (pServicesDb->hasElement("volumes") != true) {
            std::cerr << "has services.db.volumes" << std::endl;
            return -1;
        }
        if (pServicesDb->getElement("volumes")->isArray() != true) {
            std::cerr << "services.db.volumes is array" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pDbVolumes = pServicesDb->getElement("volumes");
        if (pDbVolumes->getLength() != 1) {
            std::cerr << "services.db.volumes size 1" << std::endl;
            return -1;
        }
        if (pDbVolumes->getElement(0)->getValue() != "db-data:/var/lib/postgresql/data") {
            std::cerr << "services.db.volumes val 0" << std::endl;
            return -1;
        }

        if (pServicesDb->hasElement("networks") != true) {
            std::cerr << "has services.db.networks" << std::endl;
            return -1;
        }
        if (pServicesDb->getElement("networks")->isArray() != true) {
            std::cerr << "services.db.networks is array" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pDbNetworks = pServicesDb->getElement("networks");
        if (pDbNetworks->getLength() != 1) {
            std::cerr << "services.db.networks size 1" << std::endl;
            return -1;
        }
        if (pDbNetworks->getElement(0)->getValue() != "back-tier") {
            std::cerr << "services.db.networks val 0" << std::endl;
            return -1;
        }
    }

    // volumes
    {
        if (yaml.getRoot()->hasElement("volumes") != true) {
            std::cerr << "has volumes" << std::endl;
            return -1;
        }
        if (yaml.getRoot()->getElement("volumes")->isMap() != true) {
            std::cerr << "has volumes is map" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pVolumes = yaml.getRoot()->getElement("volumes");

        if (pVolumes->hasElement("db-data") != true) {
            std::cerr << "has volumes.db-data" << std::endl;
            return -1;
        }
        if (pVolumes->getElement("db-data")->isUndefined() != true) {
            std::cerr << "has volumes.db-data is undefined" << std::endl;
            return -1;
        }
        if (pVolumes->getKeys().size() != 1) {
            std::cerr << "has volumes keys size 1" << std::endl;
            return -1;
        }
    }

    // networks
    {
        if (yaml.getRoot()->hasElement("networks") != true) {
            std::cerr << "has networks" << std::endl;
            return -1;
        }
        if (yaml.getRoot()->getElement("networks")->isMap() != true) {
            std::cerr << "has networks is map" << std::endl;
            return -1;
        }

        WsjcppYamlNode *pNeworks = yaml.getRoot()->getElement("networks");
        if (pNeworks->getKeys().size() != 2) {
            std::cerr << "has networks keys size 2" << std::endl;
            return -1;
        }

        if (pNeworks->hasElement("front-tier") != true) {
            std::cerr << "has networks.front-tier" << std::endl;
            return -1;
        }
        if (pNeworks->getElement("front-tier")->isUndefined() != true) {
            std::cerr << "has networks.front-tier is undefined" << std::endl;
            return -1;
        }

        if (pNeworks->hasElement("back-tier") != true) {
            std::cerr << "has networks.back-tier" << std::endl;
            return -1;
        }
        if (pNeworks->getElement("back-tier")->isUndefined() != true) {
            std::cerr << "has networks.back-tier is undefined" << std::endl;
            return -1;
        }
    }
    return 0;
}
