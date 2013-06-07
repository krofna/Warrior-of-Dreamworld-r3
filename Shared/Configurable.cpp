#include "Configurable.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

Configurable::Configurable() : HaveReadFile(false)
{

}

void Configurable::ReadFile(std::ifstream& Config)
{
    std::string Line;
    while (std::getline(Config, Line))
    {
        // 1. Line is empty ? Drop it.
        if (Line.empty())
            continue;
        // 2. A comment ? Drop it.
        if (Line[0] == '#')
            continue;
        // 3. Contain comment ? Drop this part.
        int idxComment = Line.find('#');
        if (idxComment != std::string::npos)
        {
            Line.erase(Line.begin() + idxComment, Line.end());
        }

        // 4. Split it by spaces.
        std::vector<std::string> SplitVec;
        boost::algorithm::split(SplitVec, Line, boost::algorithm::is_any_of(" "));

        // 5. Add it to file content.
        for (unsigned int i = 0 ; i < SplitVec.size() ; ++i)
        {
            FileContent.push(SplitVec[i]);
        }
    } // 6. Epic win 8'D.

    HaveReadFile = true;
}


