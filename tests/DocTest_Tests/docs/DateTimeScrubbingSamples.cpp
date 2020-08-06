#include <ApprovalTests/utilities/SystemUtils.h>
#include "doctest/doctest.h"

#include "utilities/DateUtils.h"
#include "utilities/WinMinGWUtils.h"
#include "Approvals.h"

#ifdef APPROVAL_TESTS_MINGW
#include <iostream>
#endif

using namespace ApprovalTests;

namespace
{
    void verifyDateAndTimeString(const std::string& dateRegex,
                                 const std::string& textWithDate)
    {
        INFO("textWithDate " << textWithDate);
        INFO("dateRegex " << dateRegex);

        auto scrubber = Scrubbers::createRegexScrubber(dateRegex, "[date_and_time]");
        CHECK("date: [date_and_time]" == scrubber(textWithDate));

        Approvals::verify(textWithDate, Options().withScrubber(scrubber));
    }

    void
    verifyDateAndTimeDefaultFormat(const std::chrono::system_clock::time_point& dateTime,
                                   const std::string& dateRegex)
    {
        std::string textWithDate = "date: " + DateUtils::toString(dateTime);
        verifyDateAndTimeString(dateRegex, textWithDate);
    }

#ifndef APPROVAL_TESTS_MINGW
    void
    verifyDateAndTimeWithFormat(const std::chrono::system_clock::time_point& dateTime,
                                const char* format,
                                const std::string& dateRegex)
    {
        std::string textWithDate = "date: " + DateUtils::toString(dateTime, format);
        verifyDateAndTimeString(dateRegex, textWithDate);
    }
#endif
}

TEST_CASE("Test DateTime scrubbing - with default format")
{
    // Thu 2020-08-06 11:28:33 UTC
    const auto dateTime = std::chrono::system_clock::now();

    std::string weekDay = R"([A-Za-z]{3})";

    std::string date = R"(\d\d\d\d-\d\d-\d\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string time_zone = "UTC";

    const auto dateRegex = weekDay + " " + date + " " + time + " " + time_zone;

    verifyDateAndTimeDefaultFormat(dateTime, dateRegex);
}

TEST_CASE("Test DateTime scrubbing - with specific format")
{
#ifdef APPROVAL_TESTS_MINGW
    // On Appveyor mingw builds, the date string is 'Thu Aug'
    // and tests fail.
    std::cout << "Skipping test which currently fails on mingw";
#else
    // Mon Jun 22 14:07:34 2020
    // %a  %b  %e %H:%M:%S %G
    const auto dateTime = std::chrono::system_clock::now();
    const char* format = "%a %b %e %T %G";

    std::string weekDay = R"([A-Za-z]{3})";
    std::string month = R"([A-Za-z]{3})";
    std::string date = R"([\d ]\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string year = R"(\d\d\d\d)";
    const auto dateRegex = weekDay + " " + month + " " + date + " " + time + " " + year;

    verifyDateAndTimeWithFormat(dateTime, format, dateRegex);
#endif
}
