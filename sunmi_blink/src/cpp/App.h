#ifndef APP_H
#define APP_H

#include <wx/wx.h>

class App : public wxApp
{
    public:
        App();
        virtual ~App();

        virtual bool OnInit();

    protected:

    private:
};

#endif // APP_H
