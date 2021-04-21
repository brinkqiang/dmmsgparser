
#include "gtest.h"

#include "dmsys.h"
#include "dmformat.h"
#include "dmguard.h"
#include "dmfile.h"
#include "dmstrtk.hpp"
#include "dmutil.h"
#include "dmstl.h"
#include "dmcast.h"
#include "dmsingleton.h"

void LOG(const std::string& strData)
{
    std::cout << strData << std::endl;
}


TEST(LOG, LOG_GUARD)
{
    LOG("Guard #");
    {
        CDMWorkPathGuard oGuard;
        LOG("DMGetRootPath(): " + DMGetRootPath());
        LOG("DMGetExePath(): " + DMGetExePath());
        LOG("DMGetExeNameString(): " + DMGetExeNameString());
        LOG("DMGetWorkPath(): " + DMGetWorkPath());
    }
}
TEST(LOG, NoGuard)
{
    LOG("NoGuard #");
    {
        LOG("DMGetRootPath(): " + DMGetRootPath());
        LOG("DMGetExePath(): " + DMGetExePath());
        LOG("DMGetExeNameString(): " + DMGetExeNameString());
        LOG("DMGetWorkPath(): " + DMGetWorkPath());
    }
}


TEST(DMLoadFile, DMLoadFile)
{
    std::string strData = DMLoadFile(__FILE__);
    LOG(strData);
}

std::vector<int> vINT;
std::vector<std::string> vSTR;
TEST(join, join_init)
{
    for (int i = 0; i < 10000; i++)
    {
        vINT.push_back(i);
    }

    for (int i = 0; i < 10000; i++)
    {
        vSTR.push_back(fmt::to_string(i));
    }
}

TEST(join, join_strtk)
{
    std::string strLine = strtk::join(",", vINT);
    std::string strLine2 = strtk::join(",", vSTR);
    LOG(fmt::to_string(strLine.size() + strLine2.size()));
}

template<class T>
std::string join(const std::string& delimiter, std::vector<T>& v)
{
    if (v.empty())
    {
        return "";
    }

    std::string str;
    str += fmt::to_string((*v.begin()));

    std::for_each(v.begin() + 1, v.end(), [&](T& data)
    {
        str += delimiter;
        str += fmt::to_string(data);
    });
    return std::move(str);
}

template<>
std::string join(const std::string& delimiter, std::vector<std::string>& v)
{
    if (v.empty())
    {
        return "";
    }

    std::string str;
    str += (*v.begin());

    std::for_each(v.begin() + 1, v.end(), [&](std::string& data)
    {
        str += delimiter;
        str += data;
    });
    return str;
}

template<class T>
std::string join_stringstream(const std::string& delimiter, std::vector<T>& v)
{
    std::stringstream ss;

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        ss << *it;

        if (it != v.end() - 1)
        {
            ss << ',';
        }
    }

    return ss.str();
}

TEST(join, join_stringstream)
{
    std::string strLine = join_stringstream(",", vINT);
    std::string strLine2 = join_stringstream(",", vSTR);
    LOG(fmt::to_string(strLine.size() + strLine2.size()));
}

TEST(cast, cast)
{
    bool data1 = dmcast::lexical_cast<bool>("1");
    char data2 = dmcast::lexical_cast<char>("1");
    uint8_t data3 = dmcast::lexical_cast<uint8_t>("1");
    int16_t data4 = dmcast::lexical_cast<int16_t>("1");
    uint16_t data5 = dmcast::lexical_cast<uint16_t>("1");
    int32_t data6 = dmcast::lexical_cast<int32_t>("1");
    uint32_t data7 = dmcast::lexical_cast<uint32_t>("1");
    int64_t data8 = dmcast::lexical_cast<int64_t>("1");
    uint64_t data9 = dmcast::lexical_cast<uint64_t>("1");
    float data10 = dmcast::lexical_cast<float>("1");
    double data11 = dmcast::lexical_cast<double>("1");
    long double data12 = dmcast::lexical_cast<long double>("1");
    std::string data13 = dmcast::lexical_cast<std::string>("1");

    std::string str1 = dmcast::lexical_cast<std::string>(data1);
    std::string str2 = dmcast::lexical_cast<std::string>(data2);
    std::string str3 = dmcast::lexical_cast<std::string>(data3);
    std::string str4 = dmcast::lexical_cast<std::string>(data4);
    std::string str5 = dmcast::lexical_cast<std::string>(data5);
    std::string str6 = dmcast::lexical_cast<std::string>(data6);
    std::string str7 = dmcast::lexical_cast<std::string>(data7);
    std::string str8 = dmcast::lexical_cast<std::string>(data8);
    std::string str9 = dmcast::lexical_cast<std::string>(data9);
    std::string str10 = dmcast::lexical_cast<std::string>(data10);
    std::string str11 = dmcast::lexical_cast<std::string>(data11);
    std::string str12 = dmcast::lexical_cast<std::string>(data12);
    std::string str13 = dmcast::lexical_cast<std::string>(data13);

    ASSERT_TRUE(str1 == "1");
    ASSERT_TRUE(str2 == "1");
    ASSERT_TRUE(str3 == "1");
    ASSERT_TRUE(str4 == "1");
    ASSERT_TRUE(str5 == "1");
    ASSERT_TRUE(str6 == "1");
    ASSERT_TRUE(str7 == "1");
    ASSERT_TRUE(str8 == "1");
    ASSERT_TRUE(str9 == "1");
    ASSERT_TRUE(str10 == "1.000000");
    ASSERT_TRUE(str11 == "1.000000");
    ASSERT_TRUE(str12 == "1.000000");
    ASSERT_TRUE(str13 == "1");
}

TEST(cast2, cast2)
{
    std::string str = "-1";
    bool data1 = dmcast::lexical_cast<bool>(str);
    char data2 = dmcast::lexical_cast<char>(str);
    uint8_t data3 = dmcast::lexical_cast<uint8_t>(str);
    int16_t data4 = dmcast::lexical_cast<int16_t>(str);
    uint16_t data5 = dmcast::lexical_cast<uint16_t>(str);
    int32_t data6 = dmcast::lexical_cast<int32_t>(str);
    uint32_t data7 = dmcast::lexical_cast<uint32_t>(str);
    int64_t data8 = dmcast::lexical_cast<int64_t>(str);
    uint64_t data9 = dmcast::lexical_cast<uint64_t>(str);
    float data10 = dmcast::lexical_cast<float>(str);
    double data11 = dmcast::lexical_cast<double>(str);
    long double data12 = dmcast::lexical_cast<long double>(str);
    std::string data13 = dmcast::lexical_cast<std::string>(str);

    std::string str1 = dmcast::lexical_cast<std::string>(data1);
    std::string str2 = dmcast::lexical_cast<std::string>(data2);
    std::string str3 = dmcast::lexical_cast<std::string>(data3);
    std::string str4 = dmcast::lexical_cast<std::string>(data4);
    std::string str5 = dmcast::lexical_cast<std::string>(data5);
    std::string str6 = dmcast::lexical_cast<std::string>(data6);
    std::string str7 = dmcast::lexical_cast<std::string>(data7);
    std::string str8 = dmcast::lexical_cast<std::string>(data8);
    std::string str9 = dmcast::lexical_cast<std::string>(data9);
    std::string str10 = dmcast::lexical_cast<std::string>(data10);
    std::string str11 = dmcast::lexical_cast<std::string>(data11);
    std::string str12 = dmcast::lexical_cast<std::string>(data12);
    std::string str13 = dmcast::lexical_cast<std::string>(data13);

    ASSERT_TRUE(str1 == "1");
    ASSERT_TRUE(str2 == "-1");
    ASSERT_TRUE(str3 == "255");
    ASSERT_TRUE(str4 == "-1");
    ASSERT_TRUE(str5 == "65535");
    ASSERT_TRUE(str6 == "-1");
    ASSERT_TRUE(str7 == "4294967295");
    ASSERT_TRUE(str8 == "-1");
    ASSERT_TRUE(str9 == "18446744073709551615");
    ASSERT_TRUE(str10 == "-1.000000");
    ASSERT_TRUE(str11 == "-1.000000");
    ASSERT_TRUE(str12 == "-1.000000");
    ASSERT_TRUE(str13 == "-1");
}

TEST(Singleton, Singleton)
{
    CDMSingletonFrame::Instance()->Init();
    CDMSingletonFrame::Instance()->UnInit();
    CDMSingletonFrame::Instance()->Release();
}
