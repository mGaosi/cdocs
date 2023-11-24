#include <project.h>

using namespace cdocs;

int main(int argc, const char* argv[])
{
    if (argc > 1)
    {
        backend::Project pj(argv[1]);
        pj.Build(
            [](const std::string_view& strFile) -> bool
            {
                return true;
            });
    }
}