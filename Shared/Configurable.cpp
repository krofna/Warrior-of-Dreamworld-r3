#include "Configurable.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>

ConfigSystem::ConfigSystem()
{

}

void ConfigSystem::Load(std::string const& FileName)
{
    ReadFile(FileName);
}

std::vector<std::string> ConfigSystem::GetSections() const
{
    return Sections;
}

std::vector<std::string> ConfigSystem::GetKeysFromSection(std::string const& Section) const
{
    std::vector<std::string> Keys;
    auto it = Values.find(Section);
    if (it == Values.end())
            return Keys;

    for (auto Iterator : it->second)
    {
        Keys.push_back(Iterator.first);
    }

    return Keys;
}

void ConfigSystem::ReadFile(std::string const& FileName)
{
    std::ifstream In(FileName.c_str());

    std::string CurSection;

    if (In)
    {
        std::string Line;
        while (std::getline(In, Line))
        {
            // 1. Empty or not, that's the question.
            if (Line.empty())
                continue;
            // 2. Comment or not, that's the question.
            if (Line[0] == '#')
                continue;
            // 3. Contain comment or not, that's the question.
            int idxComment = Line.find('#');
            if (idxComment != std::string::npos)
                Line.erase(Line.begin() + idxComment, Line.end());
            // 4. Is this a new section ?
            if (Line[0] == '@')
            {
                // 5a. Add a new section.
                CurSection = Line.erase(0, 1);
                AddSection(CurSection);
                continue;
            }
            else
            {
                // 6. Split it.
                std::vector<std::string> Pair;
                boost::algorithm::split(Pair, Line, boost::algorithm::is_any_of("="));

                // 7. Add it and trim it.
                try
                {
                    AddConfigPair(CurSection, boost::algorithm::trim_copy(Pair.at(0)), boost::algorithm::trim_copy(Pair.at(1)));
                }
                catch (std::out_of_range const& ex)
                {
                    std::cout << "[Config System] : Failed to parse an pair key-value. (Malformed config file)" << std::endl;
                }
            }
        }
    }
}

void ConfigSystem::AddSection(std::string const& Section)
{
    Sections.push_back(Section);
    std::cout << "[Config System] : Loading section \"" << Section << "\"" << std::endl;
}

void ConfigSystem::AddConfigPair(std::string const& Section, std::string const& Key, std::string const& Value)
{
    Values[Section][Key] = Value;
}

bool ConfigSystem::SectionExist(std::string const& Section) const
{
    return Values.find(Section) != Values.end();
}

bool ConfigSystem::KeyExist(std::string const& Section, std::string const& Key) const
{
    auto FirstIterator = Values.find(Section);
    if (FirstIterator == Values.end())
        return false;
    auto SubMap = FirstIterator->second;
    auto SecondIterator = SubMap.find(Key);
    if (SecondIterator == SubMap.end())
        return false;

    return true;
}
