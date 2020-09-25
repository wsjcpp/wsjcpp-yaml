
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestReadYaml

class UnitTestReadYaml : public WsjcppUnitTestBase {
    public:
        UnitTestReadYaml();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestReadYaml)

UnitTestReadYaml::UnitTestReadYaml()
    : WsjcppUnitTestBase("UnitTestReadYaml") {
}

// ---------------------------------------------------------------------

bool UnitTestReadYaml::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestReadYaml::executeTest() {
    WsjcppYaml yaml;
    std::string sFilepath = "./data-tests/read-file/example-voiting-app/docker-compose.yml";
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("has version", yaml.getRoot()->hasElement("version"), true);
    compare("has version is value", yaml.getRoot()->getElement("version")->isValue(), true);
    compare("version-value", yaml.getRoot()->getElement("version")->getValue(), "3");

    compare("has services", yaml.getRoot()->hasElement("services"), true);
    compare("has services is map", yaml.getRoot()->getElement("services")->isMap(), true);


    WsjcppYamlItem *pServices = yaml.getRoot()->getElement("services");

    compare("has services.vote", pServices->hasElement("vote"), true);
    compare("has services.vote is map", pServices->getElement("vote")->isMap(), true);
   

    /*
    
services:
  vote:
    build: ./vote
    command: python app.py
    volumes:
     - ./vote:/app
    ports:
      - "5000:80"
    networks:
      - front-tier
      - back-tier

  result:
    build: ./result
    command: nodemon server.js
    volumes:
      - ./result:/app
    */

    // services.result
    {
        compare("has services.result", pServices->hasElement("result"), true);
        compare("services.result is map", pServices->getElement("result")->isMap(), true);
        compare("services.result keys size 5", pServices->getElement("result")->getKeys().size(), 5);
        
        WsjcppYamlItem *pResult = pServices->getElement("result");

        WsjcppYamlItem *pResultVolumes = pResult->getElement("volumes");
        compare("services.result.volumes is array", pResultVolumes->isArray(), true);
        compare("services.result.volumes size 1", pResultVolumes->getLength(), 1);
        compare("services.result.volumes val 0", pResultVolumes->getElement(0)->getValue(), "./result:/app");

        WsjcppYamlItem *pResultPorts = pResult->getElement("ports");
        compare("services.result.ports is array", pResultPorts->isArray(), true);
        compare("services.result.ports size 2", pResultPorts->getLength(), 2);
        compare("services.result.ports val 0", pResultPorts->getElement(0)->getValue(), "5001:80");
        compare("services.result.ports val 1", pResultPorts->getElement(1)->getValue(), "5858:5858");

        WsjcppYamlItem *pResultNetworks = pResult->getElement("networks");
        compare("services.result.networks size 2", pResultNetworks->getLength(), 2);
        compare("services.result.networks val 0", pResultNetworks->getElement(0)->getValue(), "front-tier");
        compare("services.result.networks val 1", pResultNetworks->getElement(1)->getValue(), "back-tier");
    }

    // services.worker
    {
        compare("has services.worker", pServices->hasElement("worker"), true);
        compare("has services.worker is map", pServices->getElement("worker")->isMap(), true);
        compare("services.worker keys size 3", pServices->getElement("worker")->getKeys().size(), 3);
        WsjcppYamlItem *pWorker = pServices->getElement("worker");
        
        compare("has services.worker.build", pWorker->hasElement("build"), true);
        
        compare("has services.worker.depends_on", pWorker->hasElement("depends_on"), true);
        compare("has services.worker.networks", pWorker->hasElement("networks"), true);

        WsjcppYamlItem *pWorkerBuild = pWorker->getElement("build");
        compare("services.worker.build is map", pWorkerBuild->isMap(), true);
        compare("has services.worker.build.context", pWorkerBuild->hasElement("context"), true);
        compare("services.worker.build.context val", pWorkerBuild->getElement("context")->getValue(), "./worker");

        WsjcppYamlItem *pWorkerDependsOn = pWorker->getElement("depends_on");
        compare("has services.worker.depends_on", pWorkerDependsOn->isArray(), true);
        compare("services.worker.depends_on size 2", pWorkerDependsOn->getLength(), 2);
        compare("services.worker.depends_on val 0", pWorkerDependsOn->getElement(0)->getValue(), "redis");
        compare("services.worker.depends_on val 1", pWorkerDependsOn->getElement(1)->getValue(), "db");

        WsjcppYamlItem *pWorkerNetworks = pWorker->getElement("networks");
        compare("services.worker.networks size 1", pWorkerNetworks->getLength(), 1);
        compare("services.worker.networks val 0", pWorkerNetworks->getElement(0)->getValue(), "back-tier");
    }

    // services.redis
    {
        compare("has services.redis", pServices->hasElement("redis"), true);
        compare("services.redis is map", pServices->getElement("redis")->isMap(), true);
        compare("services.redis keys size 4", pServices->getElement("redis")->getKeys().size(), 4);

        WsjcppYamlItem *pRedis = pServices->getElement("redis");
        compare("has services.redis.image", pRedis->hasElement("image"), true);
        compare("has services.redis.container_name", pRedis->hasElement("container_name"), true);
        compare("has services.redis.ports", pRedis->hasElement("ports"), true);
        compare("has services.redis.networks", pRedis->hasElement("networks"), true);

        compare("services.redis.image value", pRedis->getElement("image")->getValue(), "redis:alpine");
        compare("services.redis.container_name", pRedis->getElement("container_name")->getValue(), "redis");

        WsjcppYamlItem *pRedisPorts = pRedis->getElement("ports");
        // TODO bug #17
        compare("services.redis.ports is value", pRedisPorts->isValue(), true);
        compare("services.redis.ports value", pRedisPorts->getValue(), "[\"6379\"]");

        WsjcppYamlItem *pRedisNetworks = pRedis->getElement("networks");
        compare("services.redis.networks size 1", pRedisNetworks->getLength(), 1);
        compare("services.redis.networks val 0", pRedisNetworks->getElement(0)->getValue(), "back-tier");
    }

    // services.db
    {
        compare("has services.db", pServices->hasElement("db"), true);
        compare("has services.db is map", pServices->getElement("db")->isMap(), true);
        compare("services.db keys size 5", pServices->getElement("db")->getKeys().size(), 5);

        WsjcppYamlItem *pServicesDb = pServices->getElement("db");

        compare("has services.db.image", pServicesDb->hasElement("image"), true);
        compare("services.db.image value", pServicesDb->getElement("image")->getValue(), "postgres:9.4");
        compare("services.db.container_name", pServicesDb->getElement("container_name")->getValue(), "db");

        compare("has services.db.environment", pServicesDb->hasElement("environment"), true);
        compare("services.db.environment is map", pServicesDb->getElement("environment")->isMap(), true);

        WsjcppYamlItem *pDbEnvironment = pServicesDb->getElement("environment");

        compare("has services.db.environment.POSTGRES_USER", pDbEnvironment->hasElement("POSTGRES_USER"), true);
        compare("services.db.environment.POSTGRES_USER", pDbEnvironment->getElement("POSTGRES_USER")->getValue(), "postgres");

        compare("has services.db.environment.POSTGRES_PASSWORD", pDbEnvironment->hasElement("POSTGRES_PASSWORD"), true);
        compare("services.db.environment.POSTGRES_PASSWORD", pDbEnvironment->getElement("POSTGRES_PASSWORD")->getValue(), "postgres");
        
        compare("has services.db.volumes", pServicesDb->hasElement("volumes"), true);
        compare("services.db.volumes is array", pServicesDb->getElement("volumes")->isArray(), true);
        
        WsjcppYamlItem *pDbVolumes = pServicesDb->getElement("volumes");
        compare("services.db.volumes size 1", pDbVolumes->getLength(), 1);
        compare("services.db.volumes val 0", pDbVolumes->getElement(0)->getValue(), "db-data:/var/lib/postgresql/data");

        compare("has services.db.networks", pServicesDb->hasElement("networks"), true);
        compare("services.db.networks is array", pServicesDb->getElement("networks")->isArray(), true);

        WsjcppYamlItem *pDbNetworks = pServicesDb->getElement("networks");
        compare("services.db.networks size 1", pDbNetworks->getLength(), 1);
        compare("services.db.networks val 0", pDbNetworks->getElement(0)->getValue(), "back-tier");
    }

    // volumes
    {
        compare("has volumes", yaml.getRoot()->hasElement("volumes"), true);
        compare("has volumes is map", yaml.getRoot()->getElement("volumes")->isMap(), true);

        WsjcppYamlItem *pVolumes = yaml.getRoot()->getElement("volumes");

        compare("has volumes.db-data", pVolumes->hasElement("db-data"), true);
        compare("has volumes.db-data is undefined", pVolumes->getElement("db-data")->isUndefined(), true);
        compare("has volumes keys size 1", pVolumes->getKeys().size(), 1);  
    }

    // networks
    {
        compare("has networks", yaml.getRoot()->hasElement("networks"), true);    
        compare("has networks is map", yaml.getRoot()->getElement("networks")->isMap(), true);

        WsjcppYamlItem *pNeworks = yaml.getRoot()->getElement("networks");
        compare("has networks keys size 2", pNeworks->getKeys().size(), 2);

        compare("has networks.front-tier", pNeworks->hasElement("front-tier"), true);
        compare("has networks.front-tier is undefined", pNeworks->getElement("front-tier")->isUndefined(), true);

        compare("has networks.back-tier", pNeworks->hasElement("back-tier"), true);
        compare("has networks.back-tier is undefined", pNeworks->getElement("back-tier")->isUndefined(), true);
    }
}

// ---------------------------------------------------------------------

bool UnitTestReadYaml::doAfterTest() {
    // do somethig after test
    return true;
}


