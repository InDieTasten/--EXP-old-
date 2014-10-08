#ifndef _LocalControl_hpp_
#define _LocalControl_hpp_

class LocalControl
{
public:
    LocalControl();
    analyzeAction(std::list<std::string> _action);

    float rotateTarget;
    float translateForward;
    float translateBack;
    float translateLeft;
    float translateRight;
};

#endif // _LocalControl_hpp_
