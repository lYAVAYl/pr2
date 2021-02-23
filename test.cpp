#include "/home/dima/pr2/Unity/src/unity.h"
#include "PIF.h"
#include <string.h>

using namespace std;

void CtorTest()
{
    PIF pif("some pif", 1, 20, 15, "some company", 0);

    TEST_ASSERT_EQUAL_INT(0, pif.GetId());
    TEST_ASSERT_EQUAL_STRING("some pif", pif.GetPIFName().c_str());
    TEST_ASSERT_EQUAL_INT(1, pif.GetTypeId());
    TEST_ASSERT_EQUAL_DOUBLE(350.5, pif.GetOpenCost());
    TEST_ASSERT_EQUAL_DOUBLE(15.5, pif.GetYearAvgCost());
    TEST_ASSERT_EQUAL_STRING("some company", pif.GetCompanyName().c_str());
}

void SettersTest()
{
    PIF pif("some pif", 1, 20.4, 15.5, "some company", 0);

    pif.SetPIFName("PIF1");
    TEST_ASSERT_EQUAL_STRING("PIF1", pif.GetPIFName().c_str());

    pif.SetTypeId(2.0);
    TEST_ASSERT_EQUAL_INT(2.0, pif.GetTypeId());
    
    pif.SetOpenCost(1.5);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, pif.GetOpenCost());

    pif.SetYearAvgCost(2.1);
    TEST_ASSERT_EQUAL_DOUBLE(2.1, pif.GetYearAvgCost());
    
    pif.SetCompanyName("Company1");
    TEST_ASSERT_EQUAL_STRING("Company1", pif.GetCompanyName().c_str());
}

void ConvertToFileWriteFormatTest()
{
    PIF pif("some pif", 1, 20, 15, "some company", 0);

    //TEST_ASSERT_EQUAL_STRING("some pif/1/20/15/some company/\n", pif.ConvertToFileWriteFormat().c_str());
}

void setUp(){}

void tearDown(){}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(CtorTest);
    RUN_TEST(SettersTest);
    RUN_TEST(ConvertToFileWriteFormatTest);

    return UNITY_END();
}
