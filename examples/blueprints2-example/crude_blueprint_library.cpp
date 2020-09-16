# include "crude_blueprint_library.h"

# ifdef _WIN32
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char* string);
# else
#     include <stdio.h>
# endif

crude_blueprint::PrintFunction crude_blueprint::PrintNode::s_PrintFunction = nullptr;

crude_blueprint::FlowPin crude_blueprint::PrintNode::Execute(Context& context, FlowPin& entryPoint)
{
    auto value = context.GetPinValue<string>(m_String);

    if (s_PrintFunction)
    {
        s_PrintFunction(*this, value);
    }
    else
    {
# ifdef _WIN32
        OutputDebugStringA("PrintNode: ");
        OutputDebugStringA(value.c_str());
        OutputDebugStringA("\n");
# else
        printf("PrintNode: %s\n", value.c_str());
# endif
    }

    return m_Exit;
}
