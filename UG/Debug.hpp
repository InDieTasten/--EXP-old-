#ifndef _Debug_hpp_
#define _Debug_hpp_

struct Debug
{
    std::list<float> tMainSleep;
    std::list<float> tGraphSleep;
    std::list<float> tPhysSleep;
    std::list<float> tModSleep;

    std::list<int> eventCounts;
    std::list<int> taskCounts;

    int eventCount;
    int taskCount;
};

#endif // _Debug_hpp_
