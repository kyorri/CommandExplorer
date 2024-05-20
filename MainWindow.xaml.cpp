#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CommandExplorer::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    hstring MainWindow::ExecuteCommand(hstring const& command)
    {
        std::wstring commandStr(command.begin(), command.end());

        FILE* pipe = _wpopen(commandStr.c_str(), L"r");
        if (!pipe)
        {
            return L"Error: Unable to execute command";
        }

        wchar_t buffer[128];
        std::wstring result;
        while (fgetws(buffer, 128, pipe))
        {
            result += buffer;
        }

        _pclose(pipe);

        std::wstring wresult(result.begin(), result.end());
        return hstring(wresult);
    }

    void MainWindow::Button_Click(IInspectable const&, RoutedEventArgs const&)
    {
        hstring command = InputTextBox().Text();

        hstring output = ExecuteCommand(command);

        OutputTextBox().Text(output);
    }
}
