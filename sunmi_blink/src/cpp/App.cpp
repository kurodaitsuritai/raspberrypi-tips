#include "App.h"

#include "MainFrame.h"

App::App() :
    wxApp()
{
    //ctor
}

App::~App()
{
    //dtor
}

bool App::OnInit()
{
    MainFrame* frame = new MainFrame();

    frame->Show();

    return true;
}


wxIMPLEMENT_APP(App);
