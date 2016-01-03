

#include <iostream>
#include <string>
#include "./CppUnitLite/TestHarness.h"
#include "./CppUnitLite/Test.h"
#include "../TPParser.h"
//#include "./exampleData.h"

TEST(parser, test1) {
    
    char* data = nullptr;
    for (size_t i = 0; i < 2; i++)
    {
        CTPParser parser;
    
        if (0 == i) {
            parser.addTracker("facebook.com");
            parser.addTracker("facebook.de");
        }
        else if (nullptr != data) {
            CHECK(nullptr != data);
            parser.deserialize(data);
        }
    
        CHECK(parser.matchesTracker("facebook.com"));
        CHECK(parser.matchesTracker("facebook.de"));
        CHECK(!parser.matchesTracker("facebook1.com"));
        if (0 == i) {
            unsigned int totalSize = 0;
            data = parser.serialize(&totalSize);
            CHECK(nullptr != data);
            CHECK(0 != totalSize);
        }
        else {
            delete []data;
            data = nullptr;
        }
    }
    
    for (size_t i = 0; i < 2; i++)
    {
        CTPParser parser;
        
        if (0 == i) {
            parser.addTracker("facebook.com");
            parser.addTracker("facebook.de");
            parser.addTracker("google-analytics.com");
        }
        else if (nullptr != data) {
            CHECK(nullptr != data);
            parser.deserialize(data);
        }
        
        CHECK(parser.matchesTracker("subdomain.google-analytics.com"));
        CHECK(parser.matchesTracker("google-analytics.com"));
        CHECK(parser.matchesTracker("facebook.com"));
        CHECK(parser.matchesTracker("facebook.de"));
        CHECK(!parser.matchesTracker("subdomain.google-analytics1.com"));
        if (0 == i) {
            unsigned int totalSize = 0;
            data = parser.serialize(&totalSize);
            CHECK(nullptr != data);
            CHECK(0 != totalSize);
        }
        else {
            delete []data;
            data = nullptr;
        }
    }
    
    for (size_t i = 0; i < 2; i++)
    {
        CTPParser parser;
        
        if (0 == i) {
            parser.addTracker("subdomain.google-analytics.com");
            parser.addTracker("facebook.com");
            parser.addTracker("facebook.de");
        }
        else if (nullptr != data) {
            CHECK(nullptr != data);
            parser.deserialize(data);
        }
        
        CHECK(parser.matchesTracker("subdomain.google-analytics.com"));
        CHECK(parser.matchesTracker("facebook.com"));
        CHECK(parser.matchesTracker("facebook.de"));
        CHECK(!parser.matchesTracker("google-analytics.com"));
        if (0 == i) {
            unsigned int totalSize = 0;
            data = parser.serialize(&totalSize);
            CHECK(nullptr != data);
            CHECK(0 != totalSize);
        }
        else {
            delete []data;
            data = nullptr;
        }
    }
    
    for (size_t i = 0; i < 2; i++)
    {
        CTPParser parser;
        
        if (0 == i) {
            parser.addFirstPartyHosts("facebook.com", "facebook.fr,facebook.de");
            parser.addFirstPartyHosts("google.com", "2mdn.net,admeld.com");
            parser.addFirstPartyHosts("subdomain.google.com", "facebook.fr,facebook.de");
        }
        else if (nullptr != data) {
            CHECK(nullptr != data);
            parser.deserialize(data);
        }
        
        char* thirdPartyHostsSubDomain = parser.findFirstPartyHosts("subdomain.google.com");
        CHECK(nullptr != thirdPartyHostsSubDomain);
        
        char* thirdPartyHosts = parser.findFirstPartyHosts("google.com");
        CHECK(nullptr != thirdPartyHosts);
        if (nullptr != thirdPartyHostsSubDomain && nullptr != thirdPartyHosts) {
            std::string strThirdPartyHostsSubDomain = thirdPartyHostsSubDomain;
            std::string strThirdPartyHosts = thirdPartyHosts;
            CHECK(std::string::npos != strThirdPartyHostsSubDomain.find(strThirdPartyHosts));
        }
        if (nullptr != thirdPartyHosts) {
            delete []thirdPartyHosts;
            thirdPartyHosts = nullptr;
        }
        if (nullptr != thirdPartyHostsSubDomain) {
            delete []thirdPartyHostsSubDomain;
            thirdPartyHostsSubDomain = nullptr;
        }
        
        thirdPartyHosts = parser.findFirstPartyHosts("facebook.com");
        CHECK(nullptr != thirdPartyHosts);
        if (nullptr != thirdPartyHosts) {
            delete []thirdPartyHosts;
            thirdPartyHosts = nullptr;
        }
        
        if (0 == i) {
            unsigned int totalSize = 0;
            data = parser.serialize(&totalSize);
            CHECK(nullptr != data);
            CHECK(0 != totalSize);
        }
        else {
            delete []data;
            data = nullptr;
        }
    }
}