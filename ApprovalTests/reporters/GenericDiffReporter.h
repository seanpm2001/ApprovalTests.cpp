#pragma once

#include "DiffPrograms.h"
#include "CommandReporter.h"
#include "ApprovalTests/launchers/SystemLauncher.h"
#include <string>
#include <vector>

namespace ApprovalTests
{
    class GenericDiffReporter : public CommandReporter
    {
    public:
        SystemLauncher launcher;

    public:
        explicit GenericDiffReporter(const std::string& program);

        explicit GenericDiffReporter(const DiffInfo& info);
    };
}
